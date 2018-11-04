//
// Created by jonas on 5/3/18.
//

#ifndef GREENSCREEN_CPU_H
#define GREENSCREEN_CPU_H

#include "RendererAPI.h"

// A filter that makes pixels that are similar to a color key transparant
namespace Filters{
    class GreenScreenCPU: public ImageFilter{
        Image* Filter(Image* sourceImageOne);
    };
}

#endif //GPUPROGRAMMING_GREENSCREEN_CPU_H
