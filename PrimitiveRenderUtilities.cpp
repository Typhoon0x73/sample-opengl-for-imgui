#include "PrimitiveRenderUtilities.h"
#include "Framework/Graphics/GraphicsController.h"

void PrimitiveRenderUtilities::RenderRect(float x, float y, float w, float h, const Sample::Vector4F& color, bool isFilled)
{
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImColor imColor(color.r, color.g, color.b, color.a);
	ImVec2 lt(x, y);
	ImVec2 rb(x + w, y + h);
	if (isFilled)
	{
		draw_list->AddRectFilled(lt, rb, imColor);
	}
	else
	{
		draw_list->AddRect(lt, rb, imColor);
	}
}

void PrimitiveRenderUtilities::RenderPolygon2D(float * pVertex, const Sample::Vector4F & color, GLenum type, int count)
{
}
