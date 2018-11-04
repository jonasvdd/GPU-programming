// Created by jonas on 16.05.18.


#include "Blur_Local_CL.h"

#define FILTER_WIDTH        3
#define FILTER_HEIGHT       3
#define FILTER_FACTOR       16

Image* Filters::BlurLocalCL::Filter(Image* sourceImageOne)
{

    Image* destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char* pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char* pixelDataDestination = destinationImage->GetPixelData();

    const int pixels = imgWidth * imgHeight;
    const size_t pixelsInBytes = pixels * 4 * sizeof(char);

    char filterKernel[FILTER_HEIGHT * FILTER_WIDTH] =
            {1, 2, 1,
             2, 4, 2,
             1, 2, 1};


    //searche info from http://www.cmsoft.com.br/opencl-tutorial/case-study-high-performance-convolution-using-opencl-__local-memory/
    std::string kernelProgram(
            "       __kernel void blur(__global const int* inputImage, __global int* outputImage, __global const unsigned char* filter, const int filterWidth, const int filterHeight, const int filterFactor){"
            "       "
            "       size_t y = get_global_id(1);"               // if we are at an edge, move y one position further from it
            "       y = (y < filterHeight/2) ?  1 : y;"
            "       y = ((get_global_size(1) - 1 - filterHeight/2) < y) ? (get_global_size(1) - 1 - filterHeight/2) : y;"
            ""
            "       size_t x = get_global_id(0);"               // if x is at an edge, move x one position further from it
            "       x = (x < filterWidth/2) ?  filterWidth/2 : x;"
            "       x = ((get_global_size(0) - 1 - filterWidth/2) < x) ? (get_global_size(0) - 1 - filterWidth/2) : x;"
            ""
            "       int lx = get_local_id(0);"
            "       int ly = get_local_id(1);"
            "		__local unsigned int localBuffer[32+2][32+2];"
            "       "
            "		const size_t rowcol = (get_global_id(1) * get_global_size(0) + get_global_id(0));"		// linear address of the pixel
            "       localBuffer[lx][ly] = inputImage[rowcol];"

            ""// Check if actual work-item is on border of work_group and load extra pixels if needed
            "       if(lx > get_local_size(0) - filterWidth)"
            "       {"
            "           localBuffer[lx + filterWidth - 1][ly] = inputImage[rowcol + filterWidth - 1];"		"       }"
            "       if(ly > get_local_size(1) - filterHeight)"
            "       {"
            "           localBuffer[lx][ly + filterHeight - 1] = inputImage[rowcol + (get_global_size(0)*(filterHeight -1))];"
            "       }"
            ""
            "       barrier (CLK_LOCAL_MEM_FENCE);"
            "       "
            "       int r = 0, g = 0, b = 0;"
            "       for (int row = 0; row < filterHeight; row++){"
            "           for (int col = 0; col < filterWidth; col++){"
            "               int color = localBuffer[lx + col][ly + row];"
            "               r += filter[row*filterWidth + col] * (color & 0xFF0000); "
            "               g += filter[row*filterWidth + col] * (color & 0x00FF00); "
            "               b += filter[row*filterWidth + col] * (color & 0x0000FF); "
            "           }"
            "       }"
            ""      // keeping the r, g and b values in bound
            "       r = (r / filterFactor) & 0xFF0000;"
            "       g = (g / filterFactor) & 0xFF00;"
            "       b = (b / filterFactor) & 0xFF;"

            "       int newColor = (localBuffer[lx+1][ly+1] & 0xFF000000) | r | g | b;"""
            "       outputImage[rowcol + get_global_size(0) + 1] = newColor;"
            "   }"
    );

    cl::Program kernels;
    cl::CommandQueue clQueue = (cl::CommandQueue)m_Context;

    if (m_Context.BuildKernels(kernelProgram, kernels))
    {
        cl_int result = CL_SUCCESS;

        // define work-items and workgroup layout
        cl::NDRange rangeOffset(0, 0);
        cl::NDRange rangeGlobal(imgWidth, imgHeight);
        cl::NDRange rangeLocal(32, 32, 0);

        // create buffers and upload all buffers
        cl::Buffer bufferIn((cl::Context)m_Context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataSource);			// no upload!
        cl::Buffer bufferOut((cl::Context)m_Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataDestination);		// no upload required (will store the result later)
        cl::Buffer bufferFilter((cl::Context)m_Context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, cl::size_type(FILTER_WIDTH*FILTER_HEIGHT), filterKernel);         // no upload

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
        auto blur = cl::KernelFunctor<cl::Buffer&, cl::Buffer&, cl::Buffer&, cl_int, cl_int, cl_int>(kernels, "blur");

        // execute functor ( == kernel blur) with input arguments and output argument
        cl::Event event = blur(cl::EnqueueArgs(rangeOffset, rangeGlobal, rangeLocal), bufferIn, bufferOut, bufferFilter, FILTER_WIDTH, FILTER_HEIGHT, FILTER_FACTOR, result);

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
            std::cout << "Problem invoking kernel blur local cl;" << std::endl;
            std::cout << " error " << ClErrorToString(result) << std::endl;
            std::cout << " error code: " << (int)result << std::endl;
        }
    }
    else
    {
        std::cout << "Problem building kernel blur local cl;" << std::endl;
        std::cout << " build info:" << m_Context.GetBuildOutput() << std::endl;
    }

    return destinationImage;
}