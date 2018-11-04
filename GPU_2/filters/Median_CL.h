// Created by jonas on 16.05.18.


#ifndef MEDIAN_CL_H
#define MEDIAN_CL_H


#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies a median - blur effect to an image
namespace Filters {
    class MedianCL : public ImageFilter {
    public:
        MedianCL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
}


#endif //GPUPROGRAMMING_MEDIAN_CL_H
