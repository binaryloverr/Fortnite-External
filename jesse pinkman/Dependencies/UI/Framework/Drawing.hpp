#include "../Drawing/imgui.h"

void draw_static(int X, int Y, int W, int H, const ImColor color, int thickness)
{
	float lineW = (W / 1);
	float lineH = (H / 1);

	//black outlines
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), color, thickness);
}

void cornered(int X, int Y, int W, int H, int thickness, ImColor color) {
	float lineW = (W / 5);
	float lineH = (H / 6);
	float lineT = 1;

	//outline
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y - lineT), ImVec2(X + lineW, Y - lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness); //top left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y - lineT), ImVec2(X - lineT, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y + H - lineH), ImVec2(X - lineT, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness); //bot left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - lineT, Y + H + lineT), ImVec2(X + lineW, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y - lineT), ImVec2(X + W + lineT, Y - lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness); // top right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W + lineT, Y - lineT), ImVec2(X + W + lineT, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W + lineT, Y + H - lineH), ImVec2(X + W + lineT, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);// bot right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H + lineT), ImVec2(X + W + lineT, Y + H + lineT), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), thickness);

	//inline
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), color, thickness);//top left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), color, thickness); //top right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), color, thickness); //bot left
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), color, thickness);//bot right
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), color, thickness);

}

void outlined_text(ImDrawList* drawlist, int x, int y, ImColor Color, const char* text)
{
	ImVec2 offsets[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	for (const auto& offset : offsets)
	{
		drawlist->AddText(ImVec2(x + offset.x, y + offset.y), ImColor(0, 0, 0, 255), text);
	}

	drawlist->AddText(ImVec2(x, y), Color, text);
}

 void draw_string(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, std::string text)
{
	if (text.empty()) {
		return;
	}

	if (bCenter) {
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x -= textSize.x / 2;
		y -= textSize.y / 2;
	}

	// Outline/stroke the text if required
	if (stroke) {
		ImVec4 black = ImVec4(0, 0, 0, 1);
		ImColor black_color = ImColor(black);
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), black_color, text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), black_color, text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), black_color, text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), black_color, text.c_str());
	}

	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), color, text.c_str());
}

 void line(fvector ScreenPositionA, fvector ScreenPositionB, int Thickness, ImColor RenderColor, bool outline) {
	if (outline)
	{
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x + 1, ScreenPositionB.y + 1), ImColor(0, 0, 0, 255), Thickness + 1.5);
	}
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.x, ScreenPositionA.y), ImVec2(ScreenPositionB.x + 1, ScreenPositionB.y + 1), RenderColor, Thickness);
}

void filled(int x, int y, int w, int h, ImColor color1, ImColor color2)
{
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	draw_list->AddRectFilledMultiColor(
		ImVec2(x, y), ImVec2(x + w, y + h),
		color1, color1, color2, color2
	);
}

void drawstatic_(const fvector2d head_box, float box_width, float box_height, const ImColor& viscolor) {
	draw_static((head_box.x - (box_width / 2)), head_box.y, box_width, box_height, viscolor, 0.5);
}

void drawfilled_(const fvector2d head_box, float box_width, float box_height, const ImColor& filldecolor, const ImColor& filldecolor1) {
	filled((head_box.x - (box_width / 2)), head_box.y, box_width, box_height, filldecolor, filldecolor1);
}

void drawcorner_(const fvector2d head_box, float box_width, float box_height, const ImColor& viscolor) {
	cornered((head_box.x - (box_width / 2)), head_box.y, box_width, box_height, 0.5, viscolor);
}

void drawoutlined_(const std::string& text, const ImVec2& position, ImColor color, int offset_y) {
	ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
	outlined_text(ImGui::GetBackgroundDrawList(), position.x - (text_size.x / 2), position.y + offset_y, color, text.c_str());
}
