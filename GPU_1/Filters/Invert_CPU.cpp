// Created by jonas on 5/2/18.

#include "Invert_CPU.h"

Image* Filters::Invert::Filter(Image *sourceImageOne)
{
    // Create a new image that reserves space for the destination image
    Image* destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char* pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char* pixelDataDestination = destinationImage->GetPixelData();

    // CPU implementation of inversion
    for (unsigned int x = 0; x < imgWidth; x++)
    {
        for (unsigned int y = 0; y < imgHeight; y++)
        {
            unsigned char redValue = 255 - pixelDataSource[(y * imgWidth + x) * 4 + 0];
            unsigned char greenValue = 255 - pixelDataSource[(y * imgWidth + x) * 4 + 1];
            unsigned char blueValue = 255 - pixelDataSource[(y * imgWidth + x) * 4 + 2];
            unsigned char alphaValue = pixelDataSource[(y * imgWidth + x) * 4 + 3];

            pixelDataDestination[(y * imgWidth + x) * 4 + 0] = redValue;
            pixelDataDestination[(y * imgWidth + x) * 4 + 1] = greenValue;
            pixelDataDestination[(y * imgWidth + x) * 4 + 2] = blueValue;
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = alphaValue;
        }
    }
    return destinationImage;

}