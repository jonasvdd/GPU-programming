// Created by jonas on 16.05.18.

#include "Histogram_CPU.h"
#include <cmath>

#define BYTE_RANGE  255

//unsigned char keepInBounds(int value){
//    value = std::max(0, value);
//    return (unsigned char) std::min(255, value);
//}

Image *Filters::HistogramCPU::Filter(Image *sourceImageOne) {
    Image *destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    const unsigned int imgWidth = sourceImageOne->GetWidth();
    const unsigned int imgHeight = sourceImageOne->GetHeight();
    const int numbPixels = imgHeight * imgWidth;
    unsigned char *pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char *pixelDataDestination = destinationImage->GetPixelData();


    // create the default empty Histogram array
    unsigned int hist_data[BYTE_RANGE + 1] = {0};

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
        if (min_cdf_value == -1 && hist_data[i]!= 0)
            min_cdf_value = hist_data[i];
        if (i != 0)
            hist_data[i] += hist_data[i - 1];
    }

    // calculate the equalized histogram
    unsigned char equalHist[BYTE_RANGE] = {0};
    for (int i = 0; i <= BYTE_RANGE; i++){
        equalHist[i] = (unsigned char)(255* (((float)hist_data[i] - min_cdf_value))/(numbPixels - min_cdf_value));
    }

    // CPU implementation to fill the histogram
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            // retrieve R, G, B
            unsigned char r = pixelDataSource[(y * imgWidth + x) * 4 + 0];
            unsigned char g = pixelDataSource[(y * imgWidth + x) * 4 + 1];
            unsigned char b = pixelDataSource[(y * imgWidth + x) * 4 + 2];

            // calculate max, min and delta color intensity
            const unsigned char max = std::max(r, std::max(g, b));
            const unsigned char min = std::min(r, std::min(g, b));
            float delta = max - min;
//            if (delta == 0)
//                delta = 1;
            // TODO why the fudjdklja;lj3el does this not work
            // const float delta = std::max(1, (max - min));

            // retrieve hsv
            float h;
            float s;
            const unsigned int v = equalHist[(int)max];

            if (max > 0) {

                s = delta / max;
                // calculate the hue
                if (r == max)
                    h = (g - b) / delta;        // between yellow & magenta
                else if (g == max)
                    h = 2 + (b - r) / delta;    // between cyan & yellow
                else
                    h = 4 + (r - g) / delta;    // between magenta & cyan

                // note: I removed the conversion to degrees to gain more efficiency
                if (h < 0)
                    h += 6;
                if (h > 6)
                    h -= 6;

                // convert back to RGB
                unsigned char i = h;
                float f = h - i;            // factorial part of h
                float p = v * (1 - s);
                float q = v * (1 - s * f);
                float t = v * (1 - s * (1 - f));

                switch (i) {
                    case 0:
                        r = v;
                        g = t;
                        b = p;
                        break;
                    case 1:
                        r = q;
                        g = v;
                        b = p;
                        break;
                    case 2:
                        r = p;
                        g = v;
                        b = t;
                        break;
                    case 3:
                        r = p;
                        g = q;
                        b = v;
                        break;
                    case 4:
                        r = t;
                        g = p;
                        b = v;
                        break;
                    case 5:
                    default:
                        r = v;
                        g = p;
                        b = q;
                        break;
                }
            }

            // write data to the destination image
            pixelDataDestination[(y * imgWidth + x) * 4 + 0] = r; //keepInBounds(r);
            pixelDataDestination[(y * imgWidth + x) * 4 + 1] = g; //keepInBounds(g);
            pixelDataDestination[(y * imgWidth + x) * 4 + 2] = b; // keepInBounds(b);
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = pixelDataSource[(y * imgWidth + x) * 4 + 3];
        }
    }
    return destinationImage;
}