//
// Created by jonas on 08.05.18.
//


#include "HueShift_CPU.h"
#include <cmath>


#define HUESHIFT -30

Image* Filters::HueShift_CPU::Filter(Image *sourceImageOne) {
    Image* destinationImage = new Image(sourceImageOne->GetWidth(), sourceImageOne->GetHeight());

    unsigned int imgWidth = sourceImageOne->GetWidth();
    unsigned int imgHeight = sourceImageOne->GetHeight();
    unsigned char* pixelDataSource = sourceImageOne->GetPixelData();
    unsigned char* pixelDataDestination = destinationImage->GetPixelData();

    // CPU implementation of inversion
    for (unsigned int x = 0; x < imgWidth; x++) {
        for (unsigned int y = 0; y < imgHeight; y++) {
            // retrieve R, G, B
            unsigned char r = pixelDataSource[(y * imgWidth + x) * 4 + 0];
            unsigned char g = pixelDataSource[(y * imgWidth + x) * 4 + 1];
            unsigned char b = pixelDataSource[(y * imgWidth + x) * 4 + 2];

            // calculate max, min and delta color intensity
            unsigned char max = std::max(r, std::max(g, b));
            unsigned char min = std::min(r, std::min(g, b));
            float delta = max - min;

            // retrieve hsv
            float h;
            float s;
            unsigned char v = max;

            if (max > 0) {
                s = delta / max;

                // calculate the hue
                if (r == max)
                    h = (g - b) / delta;        // between yellow & magenta
                else if (g == max)
                    h = 2 + (b - r) / delta;    // between cyan & yellow
                else
                    h = 4 + (r - g) / delta;    // between magenta & cyan

                // note: I removed the conversion to degrees to gain more
                // efficiency

                // shift the hue and make sure its between 0 and 360 degrees.
                h += float(HUESHIFT)/60;
                if (h < 0)
                    h += 6;
                else if (h > 6)
                    h -= 6;

                // convert back to RGB
                unsigned char i = floor(h);
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
                    default:
                        r = v;
                        g = p;
                        b = q;
                        break;
                }
            }
            // write data to the destination image
            pixelDataDestination[(y * imgWidth + x) * 4 + 0] = r;
            pixelDataDestination[(y * imgWidth + x) * 4 + 1] = g;
            pixelDataDestination[(y * imgWidth + x) * 4 + 2] = b;
            pixelDataDestination[(y * imgWidth + x) * 4 + 3] = pixelDataSource[(y * imgWidth + x) * 4 + 3];
        }
    }
    return destinationImage;
}