#ifndef DESATURATE_CL
#define DESATURATE_CL

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that converts the image to gray

namespace Filters {
	class DesaturateCL: public ImageFilter{
	public:
		DesaturateCL(Examples::CLContext& context) : m_Context(context) {}
		Image* Filter(Image* sourceImageOne);
		Examples::CLContext& m_Context;
	};
};


#endif // !DESATURATE_CL
