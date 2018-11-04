#ifndef NOISE_CL
#define NOISE_CL

#include "RendererAPI.h"
#include "../CommonCL.h"

// An image filter that applies random noise to an image
namespace Filters {
	class NoiseCL : public ImageFilter{
	public:
		NoiseCL(Examples::CLContext& context) : m_Context(context) {}
		Image* Filter(Image* sourceImageOne);
		Examples::CLContext& m_Context;
	};
};

#endif