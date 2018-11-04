// Created by jonas on 5/3/18.

#include "Greenscreen_CL.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image* Filters::GreenscreenCL::Filter(Image* sourceImageOne)
{

    Image* destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char* pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char* pixelDataDestination = destinationImage->GetPixelData();

    const int pixels = imgWidth * imgHeight;
    const size_t pixelsInBytes = pixels * 4 * sizeof(char);

    std::string kernelProgram(
            "       __kernel void greenscreen(__global const int* inputImage, __global int* outputImage){		"
                    ""
                    "		const size_t rowcol = (get_global_id(1) * get_global_size(0) + get_global_id(0));"		// linear address of the pixel
                    ""
                    "       int red_key = 52, green_key = 177, blue_key = 77; "
                    "       int min_delta = 6400, max_delta = 14400;"
                    ""
                    "		int color =  inputImage[rowcol];"									// colors are stored in A R G B order (alpha, red, green, blue)
                    "		int delta_red   = ((color & 0xFF0000) >> 16) - red_key;"								// use bitmask and shift operations to find the value of the red channel [0,255]
                    "		int delta_green = ((color & 0x00FF00) >> 8) - green_key;"								// use bitmask and shift operations to find the value of the green channel [0,255) ]
                    "		int delta_blue  = ((color & 0x0000FF) >> 0) - blue_key;"								// use bitmask and shift operations to find the value of the blue channel [0,255]
                    "       int rgb_non_shift = (color & 0xFFFFFF);"
                    ""
                    "       int delta = delta_red * delta_red + delta_green * delta_green + delta_blue * delta_blue;"
                    ""
                    "       int alpha = 0xFF000000;"
                    "       if (delta < min_delta){"
                    "           alpha = 0x00000000;"
                    "       }"
                    "       else if (delta < max_delta) { "                                     // min_delta < alpha < max_delta
                    "           alpha = (255*(delta - min_delta)/(max_delta - min_delta)) << 24;"
                    "       }"
                    ""
                    "		int newColor = alpha | rgb_non_shift;"							// combine the channels and alpha back into a 4 channel color
                    "		outputImage[rowcol] = newColor;"
                    "	}"
    );

    cl::Program kernels;
    cl::CommandQueue clQueue = (cl::CommandQueue)m_Context;

    if (m_Context.BuildKernels(kernelProgram, kernels))
    {
        cl_int result = CL_SUCCESS;

        // define work-items and workgroup layout
        cl::NDRange rangeOffset(0, 0);
        cl::NDRange rangeGlobal(imgWidth, imgHeight);
        cl::NDRange rangeLocal(16, 2, 0);

        // create buffers and upload all buffers
        cl::Buffer bufferIn((cl::Context)m_Context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataSource);			// no upload!
        cl::Buffer bufferOut((cl::Context)m_Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataDestination);		// no upload required (will store the result later)

        char *mappedPointerIn = (char*)clQueue.enqueueMapBuffer(bufferIn, CL_TRUE, CL_MAP_WRITE, 0, pixelsInBytes, 0, 0, &result);	// expicit upload
        clQueue.finish();

        if (result == CL_SUCCESS)
        {
            memcpy(mappedPointerIn, pixelDataSource, pixelsInBytes);
            cl::Event endEvent;
            result = clQueue.enqueueUnmapMemObject(bufferIn, mappedPointerIn, 0, &endEvent);
            if (result == CL_SUCCESS)
            {
                endEvent.wait();
            }
        }
        else
        {
            std::cout << "Map input buffer:" << ClErrorToString(result) << std::endl;
        }

        // define functor
        auto greenscreen = cl::KernelFunctor< cl::Buffer&, cl::Buffer&>(kernels, "greenscreen");

        // execute functor ( == kernel desaturate) with input arguments and output argument
        cl::Event event = greenscreen(cl::EnqueueArgs(rangeGlobal, rangeLocal), bufferIn, bufferOut, result);

        // if success, download results to host
        if (result == CL_SUCCESS)
        {
            // copy back the result buffer form the device to the host image buffer
            char *mappedPointer = (char*)clQueue.enqueueMapBuffer(bufferOut, CL_TRUE, CL_MAP_READ, 0, pixelsInBytes, 0, 0, &result);
            if (result == CL_SUCCESS)
            {
                memcpy(pixelDataDestination, mappedPointer, pixelsInBytes);
                cl::Event endEvent;
                result = clQueue.enqueueUnmapMemObject(bufferOut, mappedPointer, 0, &endEvent);
                if (result == CL_SUCCESS)
                {
                    endEvent.wait();
                }
            }

        }
        else
        {
            std::cout << "Problem invoking kernel Green Screen;" << std::endl;
            std::cout << " error " << ClErrorToString(result) << std::endl;
            std::cout << " error code: " << (int)result << std::endl;
        }
    }
    else
    {
        std::cout << "Problem building kernel Green Screen;" << std::endl;
        std::cout << " build info:" << m_Context.GetBuildOutput() << std::endl;
    }

    return destinationImage;
}
