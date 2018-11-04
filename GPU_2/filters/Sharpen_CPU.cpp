// Created by jonas on 09.05.18.

#include "Sharpen_CPU.h"

#define FILTER_WIDTH            3       // assuming that he filter block width is odd
#define BLOCK_WIDTH             3       // assuming that the filter block width is odd
#define NUMB_COLORS             3       // amount of different color values in the color that we need to iterate over

unsigned char keepInBounds(int value){
    value = std::max(0, value);
    return (unsigned char) std::min(255, value);
}

Image *Filters::Sharpen::Filter(Image *sourceImageOne) {
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());
    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char *sourcePixData = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();
    // declare the blurring kernel
    const int FILTER[BLOCK_WIDTH][FILTER_WIDTH] = {{0,  -1, 0},
                                                     {-1, 5,  -1},
                                                     {0,  -1, 0}};
    // iterate over the pixels
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            // the alpha value stays unchanged
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = sourcePixData[(y * imgWidth + x) * 4 + 3];

            if ((x >= FILTER_WIDTH / 2) && (x < (imgWidth - FILTER_WIDTH / 2))) {
                // no vertical overlap
                if ((y >= BLOCK_WIDTH / 2) && (y < (imgHeight - BLOCK_WIDTH / 2))) {
                    // no horizontal overlap --> base case, the filter doesn't cross the edge
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int result = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < FILTER_WIDTH; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++)
                                result +=
                                        FILTER[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x - 1 + k) * 4 + i];
                        result = std::max(0, result);
                        result = std::min(255, result);
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInBounds(result);
                    }
                } else if (y == 0) { // horizontal overlap at the top
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int result = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < FILTER_WIDTH; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++)
                                result += FILTER[j][k] * sourcePixData[((y + j / 2) * imgWidth + x - 1 + k) * 4 + i];
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInBounds(result);
                    }
                } else { // horizontal overlap at the bottom
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int result = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < FILTER_WIDTH; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++)
                                result += FILTER[j][k] *
                                          sourcePixData[((y - (2 + j) / 2) * imgWidth + x - 1 + k) * 4 + i];
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInBounds(result);
                    }
                }
            } else if ((y >= BLOCK_WIDTH / 2) && (y < (imgHeight - BLOCK_WIDTH / 2))) {
                if (x == 0) {
                    // vertical overlap at left side
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int result = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < FILTER_WIDTH; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++)
                                result += FILTER[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x + k / 2) * 4 + i];
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInBounds(result);
                    }
                } else { // vertical overlap at the  right side
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int result = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < FILTER_WIDTH; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++)
                                result += FILTER[j][k] *
                                          sourcePixData[((y - 1 + j) * imgWidth + x + (-2 + k) / 2) * 4 + i];
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInBounds(result);
                    }
                }
            } else {
                // the corners, we apply no special case to it, i know im lazy, but i only got 90 lines of code tho
                for (unsigned char i = 0; i < NUMB_COLORS; i++)
                    pixelDataDestination[(y * imgWidth + x) * 4 + i] = sourcePixData[(y * imgWidth + x) * 4 + i];
            }
        }
    }
    return destinationImage;
}