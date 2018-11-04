// Created by jonas on 15.05.18.

#ifndef BLUR_GPU_H
#define BLUR_GPU_H


#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies a blur effect to an image
namespace Filters {
    class BlurCL : public ImageFilter{
    public:
        BlurCL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
};


#endif
