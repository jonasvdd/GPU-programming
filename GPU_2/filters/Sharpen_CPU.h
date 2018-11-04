// Created by jonas on 09.05.18.


#ifndef SHARPEN_CPU_H
#define SHARPEN_CPU_H


#include "RendererAPI.h"

namespace Filters {
    class Sharpen : public ImageFilter {
        Image * Filter(Image* sourceImageOne);
    };
}

#endif
