// Created by jonas on 15.05.18.

#ifndef SHARPEN_CL_H
#define SHARPEN_CL_H


#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies random noise to an image
namespace Filters {
    class Sharpen_CL : public ImageFilter {
    public:
        Sharpen_CL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
};



#endif //GPUPROGRAMMING_SHARPEN_CL_H
