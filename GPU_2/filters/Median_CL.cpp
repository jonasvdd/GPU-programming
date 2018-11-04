// Created by jonas on 15.05.18.


#include "Median_CL.h"


#define FILTER_WIDTH        3
#define FILTER_HEIGHT       3

Image *Filters::MedianCL::Filter(Image *sourceImageOne) {
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char *pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();

    const int pixels = imgWidth * imgHeight;
    const size_t pixelsInBytes = pixels * 4 * sizeof(char);


    std::string kernelProgram(
            "   inline void sort(unsigned char data[], int size){"
            "       unsigned char l, m, tmp;"
            "       for (l = 0;  l< size; l++){"
            "           m = l;"
            "           while (m > 0 && data[m - 1] > data[m]) {"
            "               tmp = data[m];"
            "               data[m] = data[m - 1];"
            "               data[m - 1] = tmp;"
            "               m--;"
            "           }"
            "       }"
            "   }"
            "       __kernel void blur(__global const int* inputImage, __global int* outputImage, const int filterWidth, const int filterHeight){		"
            ""
            "       size_t y = get_global_id(1);"               // if we are at an edge, move y one position further from it
            "       y = (y < filterHeight/2) ?  1 : y;"
            "       y = ((get_global_size(1) - 1 - filterHeight/2) < y) ? (get_global_size(1) - 1 - filterHeight/2) : y;"
            ""
            "       size_t x = get_global_id(0);"               // if x is at an edge, move x one position further from it
            "       x = (x < filterWidth/2) ?  filterWidth/2 : x;"
            "       x = ((get_global_size(0) - 1 - filterWidth/2) < x) ? (get_global_size(0) - 1 - filterWidth/2) : x;"
            ""
            "       unsigned char r_data[9] = {0};"
            "       unsigned char g_data[9] = {0};"
            "       unsigned char b_data[9] = {0};"

            "       for(int row = 0; row < filterHeight; row++){"
            "           for(int col = 0; col < filterWidth; col++){"
            "               r_data[row*filterWidth + col] = (inputImage[((y + row - 1) * get_global_size(0) + x + col - 1)] & 0xFF0000) >> 16;"
            "               g_data[row*filterWidth + col] = (inputImage[((y + row - 1) * get_global_size(0) + x + col - 1)] & 0xFF00) >> 8;"
            "               b_data[row*filterWidth + col] = (inputImage[((y + row - 1) * get_global_size(0) + x + col - 1)] & 0xFF);"
            "           }"
            "       }"
            ""
            "       sort(r_data, filterWidth*filterHeight);"
            "       sort(g_data, filterWidth*filterHeight);"
            "       sort(b_data, filterWidth*filterHeight);"
            ""
            "       int mid = (filterWidth * filterHeight)/2;"
            "       const size_t rowcol = (get_global_id(1) * get_global_size(0) + get_global_id(0));"
            "       outputImage[rowcol] = (inputImage[rowcol] & 0xFF000000) | (r_data[mid] << 16) | (g_data[mid] << 8) | b_data[mid] ;"
            "	}"
            );
    cl::Program kernels;
    cl::CommandQueue clQueue = (cl::CommandQueue) m_Context;

    if (m_Context.BuildKernels(kernelProgram, kernels)) {
        cl_int result = CL_SUCCESS;

        // define work-items and workgroup layout
        // todo play around with this
        cl::NDRange rangeGlobal(imgWidth, imgHeight);
        cl::NDRange rangeLocal(16, 2, 0);

        // create buffers and upload all buffers
        // todo add the filter buffer here
        cl::Buffer bufferIn((cl::Context) m_Context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            cl::size_type(pixelsInBytes), pixelDataSource);            // no upload!
        cl::Buffer bufferOut((cl::Context) m_Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
                             cl::size_type(pixelsInBytes),
                             pixelDataDestination);        // no upload required (will store the result later)


        char *mappedPointerIn = (char *) clQueue.enqueueMapBuffer(bufferIn, CL_TRUE, CL_MAP_WRITE, 0, pixelsInBytes, 0,
                                                                  0, &result);    // expicit upload
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
        // todo declar which data the functor receives
        auto median = cl::KernelFunctor<cl::Buffer &, cl::Buffer &, cl_int, cl_int>(kernels, "blur");

        // execute functor ( == kernel median) with input arguments and output argument
        // todo pass the arguments to the fucntor
        cl::Event event = median(cl::EnqueueArgs(rangeGlobal, rangeLocal), bufferIn, bufferOut, FILTER_WIDTH, FILTER_WIDTH, result);

        // if success, download results to host
        if (result == CL_SUCCESS) {
            // copy back the result buffer form the device to the host image buffer
            char *mappedPointer = (char *) clQueue.enqueueMapBuffer(bufferOut, CL_TRUE, CL_MAP_READ, 0, pixelsInBytes,
                                                                    0, 0, &result);
            if (result == CL_SUCCESS) {
                memcpy(pixelDataDestination, mappedPointer, pixelsInBytes);
                cl::Event endEvent;
                result = clQueue.enqueueUnmapMemObject(bufferOut, mappedPointer, 0, &endEvent);
                if (result == CL_SUCCESS) {
                    endEvent.wait();
                }
            }
        } else {
            std::cout << "Problem invoking kernel median;" << std::endl;
            std::cout << " error " << ClErrorToString(result) << std::endl;
            std::cout << " error code: " << (int) result << std::endl;
        }
    } else {
        std::cout << "Problem building kernel median;" << std::endl;
        std::cout << " build info:" << m_Context.GetBuildOutput() << std::endl;
    }

    return destinationImage;
}
