//
// Created by jonas on 5/2/18.
//

#ifndef GPUPROGRAMMING_INVERTCL_H
#define GPUPROGRAMMING_INVERTCL_H

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that inverts an image by subtracting the R, G and B values from 255
namespace Filters{
    class InvertCL : public ImageFilter {
    public:
        InvertCL(Examples::CLContext& context) : m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
};



#endif //GPUPROGRAMMING_INVERTCL_H
