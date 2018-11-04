// Created by jonas on 08.05.18.
//

#ifndef HUESHIFT_CL_H
#define HUESHIFT_CL_H

#include "RendererAPI.h"
#include "../CommonCL.h"

namespace Filters{
    class HueShift_CL : public ImageFilter {
    public:
        HueShift_CL(Examples::CLContext& context): m_Context(context) {}
        Image* Filter(Image* sourceImageOne);
        Examples::CLContext& m_Context;
    };
}



#endif
