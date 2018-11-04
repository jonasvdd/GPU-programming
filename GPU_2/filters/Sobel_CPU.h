// Created by jonas on 09.05.18.


#ifndef SOBEL_CPU_H
#define SOBEL_CPU_H

#include "RendererAPI.h"

namespace Filters {
    class Sobel: public ImageFilter {
        Image* Filter(Image* sourceImageOne);
    };
}

#endif //SOBEL_CPU_H
