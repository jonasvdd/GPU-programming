// Created by jonas on 5/2/18.

#include "Invert_CL.h"

Image* Filters::InvertCL::Filter(Image *sourceImageOne) {
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char *pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();

    const int pixels = imgWidth * imgHeight;
    const size_t pixelsInBytes = pixels * 4 * sizeof(char);

    std::string kernelProgram(
//            " __kernel void invert(__global const int* inputImage, __global int* outputImage){ "
//                    "		const size_t rowcol = (get_global_id(1) * get_global_size(0) + get_global_id(0));"        // linear address of the pixel
//                    "		int color =  inputImage[rowcol];"                                    // colors are stored in A R G B order (alpha, red, green, blue)
//                    "       int rgb   =  0xFFFFFF - (color & 0xFFFFFF);"
//                    "       int alpha_non_shift = color & 0xFF000000;"
//                    "		int newColor = alpha_non_shift | rgb;"
//                    "		outputImage[rowcol] = newColor;"
//                    "	}"
//    );
    "\t__kernel void invert(__global const int* inputImage, __global int* outputImage){ \n"
    "            const size_t rowcol = (get_global_id(1) * get_global_size(0) + get_global_id(0));\n"
    "            int color =  inputImage[rowcol];                            \n"
    "            \n"
    "            int red   = (color & 0xFF0000) >> 16;                       \n"
    "            int green = (color & 0x00FF00) >> 8;\n"
    "            int blue  = (color & 0x0000FF) >> 0;                             \n"
    "            int alpha_non_shift = (color & 0xFF000000); \n"
    "\n"
    "            red   = (255 - red)   << 16;                                     \n"
    "            green = (255 - green) << 8;"
    "            blue  = (255 - blue)  << 0;"
    "            int newColor = alpha_non_shift | red | green | blue;  "
    "            outputImage[rowcol] = newColor;"
    "       }");
    cl::Program kernels;
    cl::CommandQueue clQueue = (cl::CommandQueue)m_Context;

    if (m_Context.BuildKernels(kernelProgram, kernels)) {
        cl_int result = CL_SUCCESS;

        // define work-items and workgroup layout
        cl::NDRange rangeOffset(0, 0);
        cl::NDRange rangeGlobal(imgWidth, imgHeight);
        cl::NDRange rangeLocal(16, 2, 0);

        // create buffers and upload all buffers
        cl::Buffer bufferIn((cl::Context) m_Context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataSource);            // no upload!
        cl::Buffer bufferOut((cl::Context) m_Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataDestination);        // no upload required (will store the result later)

        char *mappedPointerIn = (char *) clQueue.enqueueMapBuffer(bufferIn, CL_TRUE, CL_MAP_WRITE, 0, pixelsInBytes, 0, 0, &result);    // expicit upload
        clQueue.finish();

        if (result == CL_SUCCESS) {
            memcpy(mappedPointerIn, pixelDataSource, pixelsInBytes);
            cl::Event endEvent;
            result = clQueue.enqueueUnmapMemObject(bufferIn, mappedPointerIn, 0, &endEvent);
            if (result == CL_SUCCESS) {
                endEvent.wait();
            }
        } else {
            std::cout << "Map input buffer:" << ClErrorToString(result) << std::endl;
        }

        // define functor
        auto invert = cl::KernelFunctor<cl::Buffer &, cl::Buffer &>(kernels, "invert");

        // execute functor ( == kernel invert) with input arguments and output argument
        cl::Event event = invert(cl::EnqueueArgs(rangeGlobal, rangeLocal), bufferIn, bufferOut, result);

        // if success, download results to host
        if (result == CL_SUCCESS) {
            // copy back the result buffer form the device to the host image buffer
            char *mappedPointer = (char *) clQueue.enqueueMapBuffer(bufferOut, CL_TRUE, CL_MAP_READ, 0, pixelsInBytes, 0, 0, &result);
            if (result == CL_SUCCESS) {
                memcpy(pixelDataDestination, mappedPointer, pixelsInBytes);
                cl::Event endEvent;
                result = clQueue.enqueueUnmapMemObject(bufferOut, mappedPointer, 0, &endEvent);
                if (result == CL_SUCCESS) {
                    endEvent.wait();
                }
            }

        } else {
            std::cout << "Problem invoking kernel invert;" << std::endl;
            std::cout << " error " << ClErrorToString(result) << std::endl;
            std::cout << " error code: " << (int) result << std::endl;
        }
    } else {
        std::cout << "Problem building kernel invert;" << std::endl;
        std::cout << " build info:" << m_Context.GetBuildOutput() << std::endl;
    }

    return destinationImage;
}