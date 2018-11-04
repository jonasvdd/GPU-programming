// Created by jonas on 5/2/18.

#ifndef INVERTFILTER_H
#define INVERTFILTER_H

#include "RendererAPI.h"

// An image filter that inverts an image by subtracting the R, G and B values from 255
namespace Filters{
    class Invert: public ImageFilter{
        Image* Filter(Image* sourceImageOne);
    };
}


#endif
