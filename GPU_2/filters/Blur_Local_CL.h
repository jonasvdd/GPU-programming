// Created by jonas on 16.05.18.


#ifndef BLUR_LOCAL_CL_H
#define BLUR_LOCAL_CL_H

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies a median - blur effect to an image
namespace Filters{
    class BlurLocalCL : public ImageFilter {
    public:
        BlurLocalCL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
}


#endif //GPUPROGRAMMING_BLUR_LOCAL_CL_H
