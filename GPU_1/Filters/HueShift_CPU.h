// Created by jonas on 08.05.18.

#ifndef GPUPROGRAMMING_HUESHIFT_CPU_H
#define GPUPROGRAMMING_HUESHIFT_CPU_H


#include "RendererAPI.h"

namespace Filters{
    class HueShift_CPU: public ImageFilter {
        Image* Filter(Image* sourceImageOne);
    };
}


#endif //GPUPROGRAMMING_HUESHIFT_CPU_H
