// Created by jonas on 09.05.18.


#ifndef GPUPROGRAMMING_BLUR_CPU_H
#define GPUPROGRAMMING_BLUR_CPU_H

// a block base image filter that applies the blur effect to an image
#include "RendererAPI.h"

namespace Filters {
    class Blur : public ImageFilter {
        Image* Filter(Image* sourceImageOne);
    };

}


#endif //GPUPROGRAMMING_BLUR_CPU_H
