// Created by jonas on 10.05.18.


#ifndef MEDIAN_CPU_H
#define MEDIAN_CPU_H

#include "RendererAPI.h"

namespace Filters{
    class Median : public ImageFilter {
        Image* Filter(Image* sourceImageOne);
    };
}



#endif //GPUPROGRAMMING_MEDIAN_CPU_H
