#include "Desaturate_CPU.h"

Image* Filters::Desaturate::Filter(Image* sourceImageOne)
{
	// Create a new image that reserves space for the destination image
	Image* destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

	unsigned int imgWidth = sourceImageOne->GetWidth();
	unsigned int imgHeight = sourceImageOne->GetHeight();
	unsigned char* pixelDataSource = sourceImageOne->GetPixelData();
	unsigned char* pixelDataDestination = destinationImage->GetPixelData();

	// CPU implementation of desaturation
	for (unsigned int x = 0; x < imgWidth; x++)
	{
		for (unsigned int y = 0; y < imgHeight; y++)
		{

			unsigned char avgColorValue = (
				pixelDataSource[(y * imgWidth + x) * 4 + 0] + 
				pixelDataSource[(y * imgWidth + x) * 4 + 1] + 
				pixelDataSource[(y * imgWidth + x) * 4 + 2]) / 3;
			unsigned char alphaValue = 
				pixelDataSource[(y * imgWidth + x) * 4 + 3];


			pixelDataDestination[(y * imgWidth + x) * 4 + 0] = avgColorValue;
			pixelDataDestination[(y * imgWidth + x) * 4 + 1] = avgColorValue;
			pixelDataDestination[(y * imgWidth + x) * 4 + 2] = avgColorValue;
			pixelDataDestination[(y * imgWidth + x) * 4 + 3] = alphaValue;

		}
	}

	return destinationImage;
}