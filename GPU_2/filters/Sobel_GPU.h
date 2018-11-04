// Created by jonas on 16.05.18.

#ifndef SOBEL_GPU_H
#define SOBEL_GPU_H

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies a blur effect to an image
namespace Filters {
    class SobelCL : public ImageFilter{
    public:
        SobelCL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
}



#endif //GPUPROGRAMMING_SOBEL_GPU_H
