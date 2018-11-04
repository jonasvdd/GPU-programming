// Created by jonas on 08.05.18.

#include "HueShift_CL.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image* Filters::HueShift_CL::Filter(Image* sourceImageOne)
{

    Image* destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char* pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char* pixelDataDestination = destinationImage->GetPixelData();

    const int pixels = imgWidth * imgHeight;
    const size_t pixelsInBytes = pixels * 4 * sizeof(char);

    std::string kernelProgram(
            "       __kernel void hueshift(__global const int* inputImage, __global int* outputImage){		"
            ""
            "		const size_t rowcol = (get_global_id(1) * get_global_size(0) + get_global_id(0));"		// linear address of the pixel
            ""
            ""
            "		int color =  inputImage[rowcol];"									// colors are stored in A R G B order (alpha, red, green, blue)
            "		int r   = (color & 0xFF0000) >> 16;"								// use bitmask and shift operations to find the value of the red channel [0,255]
            "		int g   = (color & 0x00FF00) >> 8;"								// use bitmask and shift operations to find the value of the green channel [0,255]
            "		int b   = (color & 0x0000FF);"								// use bitmask and shift operations to find the value of the blue channel [0,255]
            "		int alpha_non_shift = (color & 0xFF000000);"
            ""
            "       int max = r;"
            "       if (g > max && g > b)"
            "           max = g;"
            "       else if (b > max)"
            "           max = b;"
            ""
            "       int min = r;"
            "       if (g < min && g < b)"
            "           min = g;"
            "       else if (b < min)"
            "           min = b;"
            "       float delta = max - min;"
            ""
            "       float h, s, v;"
            "       float HUESHIFT = -0.5;"                                             // hue shift = -30°/60
            ""
            "       v = max;"
            ""
            "       if (max > 0) {"
            "           s = delta / max;"
            "           if (r == max)"                                                 // calculate the Hue
            "               h = (g - b) / delta;"
            "           else if (g == max)"
            "               h = 2 + (b - r) / delta;"
            "           else"
            "               h = 4 + (r - g) / delta;"
            ""
            "           h -= HUESHIFT;"
            "           if (h < 0)"
            "               h += 6;"
            "           else if (h > 6)"
            "               h -= 6;"
            ""
            "           unsigned char i = floor(h);"
            "           float f = h - i;"
            "           float p = v * (1 - s);"
            "           float q = v * (1 - s * f);"
            "           float t = v * (1 - s * (1 - f));"
            ""
            ""
            "           switch(i) {"  // some magic stuff, which i just copied of the internet, yay!
            "               case 0:"  //   https://www.cs.rit.edu/~ncs/color/t_convert.html
            "                   r = v;"
            "                   g = t;"
            "                   b = p;"
            "                   break;"
            "               case 1:"
            "                   r = q;"
            "                   g = v;"
            "                   b = p;"
            "                   break;"
            "               case 2:"
            "                   r = p;"
            "                   g = v;"
            "                   b = t;"
            "                   break;"
            "               case 3:"
            "                   r = p;"
            "                   g = q;"
            "                   b = v;"
            "                   break;"
            "               case 4:"
            "                   r = t;"
            "                   g = p;"
            "                   b = v;"
            "                   break;"
            "               default:"
            "                   r = v;"
            "                   g = p;"
            "                   b = q;"
            "                   break;"
            "           }"
            "       }"
            ""
            "       r = (r << 16);"
            "       g = (g << 8);"
            "       b = b & 0xFF;"
            "		int newColor = alpha_non_shift | r | g | b;"    // combine the channels and alpha back into a 4 channel color
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
        auto hueshift = cl::KernelFunctor< cl::Buffer&, cl::Buffer&>(kernels, "hueshift");

        // execute functor ( == kernel desaturate) with input arguments and output argument
        cl::Event event = hueshift(cl::EnqueueArgs(rangeGlobal, rangeLocal), bufferIn, bufferOut, result);

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
            std::cout << "Problem invoking kernel Hue shift;" << std::endl;
            std::cout << " error " << ClErrorToString(result) << std::endl;
            std::cout << " error code: " << (int)result << std::endl;
        }
    }
    else
    {
        std::cout << "Problem building kernel hue shift;" << std::endl;
        std::cout << " build info:" << m_Context.GetBuildOutput() << std::endl;
    }

    return destinationImage;
}
