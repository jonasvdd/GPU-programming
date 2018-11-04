// Created by jonas on 16.05.18.


#ifndef HISTOGRAM_CPU_H
#define HISTOGRAM_CPU_H

#include "RendererAPI.h"

namespace Filters {
    class HistogramCPU: public ImageFilter {
    public:
        Image* Filter(Image* sourceImageOne);
    };
}


#endif
