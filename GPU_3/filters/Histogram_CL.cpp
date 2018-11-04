// Created by jonas on 22.05.18

#include "Histogram_CL.h"
#include <cmath>

#define BYTE_RANGE  255

Image* Filters::Histogram_CL::Filter(Image* sourceImageOne) {

    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    const unsigned int imgWidth = sourceImageOne->GetWidth();
    const unsigned int imgHeight = sourceImageOne->GetHeight();
    const int numbPixels = imgHeight * imgWidth;
    unsigned char *pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();

    const int pixels = imgWidth * imgHeight;
    const size_t pixelsInBytes = pixels * 4 * sizeof(char);

    // create the histogram array
    int hist_data[BYTE_RANGE + 1] = {0};

    // CPU implementation to fill the histogram
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            // retrieve R, G, B
            unsigned char r = pixelDataSource[(y * imgWidth + x) * 4 + 0];
            unsigned char g = pixelDataSource[(y * imgWidth + x) * 4 + 1];
            unsigned char b = pixelDataSource[(y * imgWidth + x) * 4 + 2];

            // calculate max, min and delta color intensity
            unsigned char v = std::max(r, std::max(g, b));
            hist_data[v] += 1;
        }
    }

    //  create the cummulative  probability histogram
    int min_cdf_value = -1;
    for (int i = 0; i <= BYTE_RANGE; i++) {
        if (min_cdf_value == -1 && hist_data[i]!= 0){
            min_cdf_value = hist_data[i];
        }
        if (i != 0)
            hist_data[i] += hist_data[i - 1];
    }

    // calculate the equalized histogram
    unsigned char equalHist[BYTE_RANGE] = {0};
    for (int i = 0; i <= BYTE_RANGE; i++){
        equalHist[i] = (unsigned char)round((255* (((float)hist_data[i] - min_cdf_value))/(numbPixels - min_cdf_value)));
        // std::cout << equalHist[i] << std::endl;
    }


    // use the gpu to create the new colors
    std::string kernelProgram(
            "       __kernel void hist(__global const int* inputImage, __global int* outputImage, __global unsigned char* equal_hist){		"
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
            "       if (delta == 0)"
            "           delta = 1;"
            ""
            "       float h, s, v;"
            ""
            "       v = (float)equal_hist[max];"
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
            "       r = (r & 0xFF) << 16;"
            "       g = (g & 0xFF) << 8;"
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
        cl::NDRange rangeGlobal(imgWidth, imgHeight);
        cl::NDRange rangeLocal(16, 2, 0);

        // create buffers and upload all buffers
        cl::Buffer bufferIn((cl::Context)m_Context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataSource);			// no upload!
        cl::Buffer bufferOut((cl::Context)m_Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, cl::size_type(pixelsInBytes), pixelDataDestination);		// no upload required (will store the result later)
        cl::Buffer buffer_hist((cl::Context)m_Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, cl::size_type(BYTE_RANGE + 1), equalHist);		// no upload required (will store the result later)

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
        auto hist = cl::KernelFunctor< cl::Buffer&, cl::Buffer&, cl::Buffer&>(kernels, "hist");

        // execute functor ( == kernel desaturate) with input arguments and output argument
        cl::Event event = hist(cl::EnqueueArgs(rangeGlobal, rangeLocal), bufferIn, bufferOut, buffer_hist, result);

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
            std::cout << "Problem invoking kernel Histogram;" << std::endl;
            std::cout << " error " << ClErrorToString(result) << std::endl;
            std::cout << " error code: " << (int)result << std::endl;
        }
    }
    else
    {
        std::cout << "Problem building kernel Histogram;" << std::endl;
        std::cout << " build info:" << m_Context.GetBuildOutput() << std::endl;
    }

    return destinationImage;
}
