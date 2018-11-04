// Created by jonas on 22.05.18.

#ifndef HISTOGRAM_CL_H
#define HISTOGRAM_CL_H

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that increases the contrast on the image
namespace Filters{
    class Histogram_CL : public ImageFilter {
    public:
        Histogram_CL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
}


#endif //HISTOGRAM_CL_H
