#include "PrimitiveRenderUtilities.h"
#include "Framework/Graphics/GraphicsController.h"

void PrimitiveRenderUtilities::RenderRect(float x, float y, float w, float h, const Sample::Vector4F& color, bool isFilled)
{
	GLenum type;
	float pVerCoord[12];
	if (isFilled)
	{
		pVerCoord[0] = pVerCoord[3] = x;
		pVerCoord[1] = pVerCoord[7] = y;
		pVerCoord[4] = pVerCoord[10] = y + h;
		pVerCoord[6] = pVerCoord[9] = x + w;
		pVerCoord[2] = pVerCoord[5] = pVerCoord[8] = pVerCoord[11] = 0;
		type = GL_TRIANGLE_STRIP;
	}
	else
	{
		pVerCoord[0] = pVerCoord[9] = x;
		pVerCoord[1] = pVerCoord[4] = y;
		pVerCoord[3] = pVerCoord[6] = x + w;
		pVerCoord[7] = pVerCoord[10] = y + h;
		pVerCoord[2] = pVerCoord[5] = pVerCoord[8] = pVerCoord[11] = 0;
		type = GL_LINE_LOOP;
	}

	RenderPolygon2D(pVerCoord, color, type, 4);
}

void PrimitiveRenderUtilities::RenderPolygon2D(float * pVertex, const Sample::Vector4F & color, GLenum type, int count)
{
}
