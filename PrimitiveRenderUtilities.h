#pragma once
#include "Framework/Framework/Framework.h"

class PrimitiveRenderUtilities
{
public:

	static void RenderRect(float x, float y, float w, float h, const Sample::Vector4F& color, bool isFilled);

	static void RenderPolygon2D(float* pVertex, const Sample::Vector4F& color, GLenum type, int count);

private:
	PrimitiveRenderUtilities() = delete;
	~PrimitiveRenderUtilities() = delete;
};

