// Created by jonas on 10.05.18.

#include "Median_CPU.h"

#define BLOCK_HEIGHT            3       // assuming that he filter block width is odd
#define BLOCK_WIDTH             3       // assuming that the filter block width is odd
#define MEDIAN_INDEX            (BLOCK_HEIGHT * BLOCK_WIDTH)/2
#define NUMB_COLORS             3       // amount of different color values in the color that we need to iterate over


unsigned char median9(unsigned char data[]){
    unsigned char l, m, tmp;
    for (l = 0;  l< BLOCK_HEIGHT * BLOCK_WIDTH; l++){
        m = l;
        while (m > 0 && data[m - 1] > data[m]) {
            // swap
            tmp = data[m];
            data[m] = data[m - 1];
            data[m - 1] = tmp;
            m--;
        }
    }
    return data[MEDIAN_INDEX];
}

Image *Filters::Median::Filter(Image *sourceImageOne) {
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char *pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();

    // CPU implementation of inversion
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            // the alpha value stay the same
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = pixelDataSource[(y * imgWidth + x) * 4 + 3];

            if ((x >= BLOCK_HEIGHT / 2) && (x < (imgWidth - BLOCK_HEIGHT / 2))) {
                // no vertical overlap
                if ((y >= BLOCK_WIDTH / 2) && (y < (imgHeight - BLOCK_WIDTH / 2))) {
                    // calculate the convolution value of the kernel
                    for (unsigned char i = 0; i < NUMB_COLORS; i++) {
                        unsigned char data [BLOCK_HEIGHT * BLOCK_WIDTH] = {};
                        unsigned char tmp = 0;
                        // calculate the convolution value of the kernel
                        for (unsigned char j = 0; j < BLOCK_HEIGHT; j++)
                            for (unsigned char k = 0; k < BLOCK_WIDTH; k++){
                                data[tmp] = pixelDataSource[((y - 1 + j) * imgWidth + x - 1 + k) * 4 + i];
                                tmp+=1;
                            }
                        pixelDataDestination[(y * imgWidth + x) * 4 + i] = median9(data);
                    }
                }
            } else {
                for (unsigned char i = 0; i < NUMB_COLORS; i++)
                    pixelDataDestination[(y * imgWidth + x) * 4 + i] = pixelDataSource[(y * imgWidth + x) * 4 + i];
            }
        }
    }
    return destinationImage;
}