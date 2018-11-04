// Created by jonas on 09.05.18.

#include "Sobel_CPU.h"
#include <math.h>

#define BLOCK_HEIGHT            3       // assuming that he filter block width is odd
#define BLOCK_WIDTH           3       // assuming that the filter block width is odd
#define NUMB_COLORS             3       // amount of different color values in the color that we need to iterate over

unsigned char keepInHalfBounds(int value) {
    return (unsigned char) std::min(255, value);
}

Image *Filters::Sobel::Filter(Image *sourceImageOne) {
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());
    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char *sourcePixData = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();
    // declare the blurring kernel
    const int FILTER[BLOCK_WIDTH][BLOCK_HEIGHT] = {{-1, 0, 1},
                                                     {-2, 0, 2},
                                                     {-1, 0, 1}};
    const int FILTER2[BLOCK_WIDTH][BLOCK_HEIGHT] = {{1,  2,  1},
                                                      {0,  0,  0},
                                                      {-1, -2, -1}};
    // iterate over the pixels
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            // the alpha value stays unchanged
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = sourcePixData[(y * imgWidth + x) * 4 + 3];

            if ((x >= BLOCK_HEIGHT / 2) && (x < (imgWidth - BLOCK_HEIGHT / 2))) {
                // no vertical overlap
                if ((y >= BLOCK_WIDTH / 2) && (y < (imgHeight - BLOCK_WIDTH / 2))) {
                    // no horizontal overlap --> base case, the filter doesn't cross the edge
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int resultF1 = 0, resultF2 = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < BLOCK_HEIGHT; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++) {
                                resultF1 +=
                                        FILTER[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x - 1 + k) * 4 + i];
                                resultF2 +=
                                        FILTER2[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x - 1 + k) * 4 + i];
                            }
                        resultF1 = sqrt(resultF1 * resultF1 + resultF2 * resultF2);
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInHalfBounds(resultF1);
                    }
                } else if (y == 0) { // horizontal overlap at the top
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int resultF1 = 0, resultF2 = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < BLOCK_HEIGHT; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++) {
                                resultF1 +=
                                        FILTER[j][k] * sourcePixData[((y + j / 2) * imgWidth + x - 1 + k) * 4 + i];
                                resultF2 +=
                                        FILTER2[j][k] * sourcePixData[((y + j / 2) * imgWidth + x - 1 + k) * 4 + i];
                            }
                        resultF1 = sqrt(resultF1 * resultF1 + resultF2 * resultF2);
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInHalfBounds(resultF1);
                    }
                } else { // horizontal overlap at the bottom
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int resultF1 = 0, resultF2 = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < BLOCK_HEIGHT; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++) {
                                resultF1 += FILTER[j][k] *
                                            sourcePixData[((y - (2 + j) / 2) * imgWidth + x - 1 + k) * 4 + i];
                                resultF2 +=
                                        FILTER2[j][k] *
                                        sourcePixData[((y - (2 + j) / 2) * imgWidth + x - 1 + k) * 4 + i];
                            }
                        resultF1 = sqrt(resultF1 * resultF1 + resultF2 * resultF2);
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInHalfBounds(resultF1);
                    }
                }
            } else if ((y >= BLOCK_WIDTH / 2) && (y < (imgHeight - BLOCK_WIDTH / 2))) {
                if (x == 0) {
                    // vertical overlap at left side
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int resultF1 = 0, resultF2 = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < BLOCK_HEIGHT; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++) {
                                resultF1 += FILTER[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x + k / 2) * 4 + i];
                                resultF2 += FILTER2[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x + k / 2) * 4 + i];

                            }
                        resultF1 = sqrt(resultF1 * resultF1 + resultF2 * resultF2);
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInHalfBounds(resultF1);
                    }
                } else { // vertical overlap at the  right side
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        int resultF1 = 0, resultF2 = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < BLOCK_HEIGHT; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++) {
                                resultF1 += FILTER[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x + (-2 + k) / 2) * 4 + i];
                                resultF2 += FILTER2[j][k] * sourcePixData[((y - 1 + j) * imgWidth + x + (-2 + k) / 2) * 4 + i];
                            }
                        resultF1 = sqrt(resultF1 * resultF1 + resultF2 * resultF2);
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = keepInHalfBounds(resultF1);
                    }
                }
            }
        }
    }
    return destinationImage;
}