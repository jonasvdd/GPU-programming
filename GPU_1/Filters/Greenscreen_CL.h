// Created by jonas on 5/3/18.

#ifndef GREENSCREEN_CL_H
#define GREENSCREEN_CL_H

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies desaturation to an image by averaging the R, G and B components
namespace Filters{
    class GreenscreenCL: public ImageFilter{
    public:
        GreenscreenCL(Examples::CLContext& context): m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
}

#endif //GPUPROGRAMMING_GREENSCREEN_CL_H
