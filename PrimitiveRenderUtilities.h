#pragma once
#include "Framework/Framework/Framework.h"

class PrimitiveRenderUtilities
{
public:

	void RenderRect(float x, float y, float w, float h, const Sample::Vector4F& color, bool isFilled);

	void RenderPolygon2D(float* pVertex, const Sample::Vector4F& color, GLenum type, int count);

private:
	PrimitiveRenderUtilities() = delete;
	~PrimitiveRenderUtilities() = delete;
};

