//
// Created by jonas on 5/3/18.
//

#include "Greenscreen_CPU.h"
#include "cmath"

// declare the constant key values which will be mapped against the pixel values
#define RED_KEY 55
#define GREEN_KEY 177
#define BLUE_KEY 77

// declare the constant delta values
#define MIN_DELTA 80*80             // 80
#define MAX_DELTA 120*120           // 120

Image *Filters::GreenScreenCPU::Filter(Image *sourceImageOne) {
    // Create a new image that reserves space for the destination image
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char *pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();

    // CPU implementation of green screen
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            auto delta =
                    pow(pixelDataSource[(y * imgWidth + x) * 4 + 0] - RED_KEY, 2) +
                    pow(pixelDataSource[(y * imgWidth + x) * 4 + 1] - GREEN_KEY, 2) +
                    pow(pixelDataSource[(y * imgWidth + x) * 4 + 2] - BLUE_KEY, 2);

            unsigned char alphaValue = 255;
            if (delta < MIN_DELTA) {         // small difference
                alphaValue = 0;
            } else if (delta < MAX_DELTA) {  // between min and max delta color
                // lineair interpolation
                alphaValue = (255 * (delta - MIN_DELTA) / (MAX_DELTA - MIN_DELTA));
            }

            pixelDataDestination[(y * imgWidth + x) * 4 + 0] = pixelDataSource[(y * imgWidth + x) * 4 + 0];
            pixelDataDestination[(y * imgWidth + x) * 4 + 1] = pixelDataSource[(y * imgWidth + x) * 4 + 1];
            pixelDataDestination[(y * imgWidth + x) * 4 + 2] = pixelDataSource[(y * imgWidth + x) * 4 + 2];
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = alphaValue;
        }
    }
    return destinationImage;
}