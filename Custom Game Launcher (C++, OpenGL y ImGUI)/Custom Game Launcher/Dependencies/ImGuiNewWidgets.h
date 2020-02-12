#pragma once

#include <string>

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui/imgui.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui/imgui_internal.h"

#include <ctype.h>      // toupper
#include <stdint.h>     // intptr_t

// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4127) // condition expression is constant
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#endif


//Declaration
namespace ImGui
{
	IMGUI_API bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
	IMGUI_API bool ImageButtonZoomOnHover(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4 & bg_col = ImVec4(0, 0, 0, 0), const ImVec4 & tint_col = ImVec4(1, 1, 1, 1));
	IMGUI_API bool SliderFloatCustomizable(const char* label, void* v, const void* v_min, const void* v_max, const char* format = "%.3f", float sliderBackgroundHeight = 0.0f, float sliderWidth = 0.0f, float power = 1.0f);
	IMGUI_API void NoSpaceNewLine();
	IMGUI_API void VerticalDummy(float y);
	IMGUI_API void WaitingModal(const char* title, const char* body);
	IMGUI_API void LocalWaitingModal(const char* title, const char* body);
}

//Implementation
bool ImGui::Spinner(const char* label, float radius, int thickness, const ImU32& color)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return false;

	window->DrawList->PathClear();

	int num_segments = 30;
	int start = ImFabs(ImSin(g.Time * 1.8f) * (num_segments - 5));

	const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

	const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

	for (int i = 0; i < num_segments; i++) {
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
			centre.y + ImSin(a + g.Time * 8) * radius));
	}

	window->DrawList->PathStroke(color, false, thickness);
}

bool ImGui::ImageButtonZoomOnHover(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	PushID((void*)(intptr_t)user_texture_id);
	const ImGuiID id = window->GetID("#image");
	PopID();

	const ImVec2 padding = (frame_padding >= 0) ? ImVec2((float)frame_padding, (float)frame_padding) : style.FramePadding;
	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + size + padding * 2);
	const ImRect image_bb(window->DC.CursorPos + padding, window->DC.CursorPos + padding + size);
	const ImVec2 backup_item_spacing = g.Style.ItemSpacing;
	g.Style.ItemSpacing = ImVec2(0.0f, 0.0f);
	ItemSize(bb);
	if (!ItemAdd(bb, id))
		return false;

	g.Style.ItemSpacing = backup_item_spacing;

	bool hovered, held;
	bool pressed = ButtonBehavior(bb, id, &hovered, &held);

	const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);

	RenderNavHighlight(bb, id);
	RenderFrame(bb.Min, bb.Max, col, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, style.FrameRounding));
	if (bg_col.w > 0.0f)
		window->DrawList->AddRectFilled(image_bb.Min, image_bb.Max, GetColorU32(bg_col));
	if (hovered)
		window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, ImVec2(uv0.x + 0.025f, uv0.y + 0.025f), ImVec2(uv1.x - 0.025f, uv1.y - 0.025f), GetColorU32(tint_col));
	else
		window->DrawList->AddImage(user_texture_id, image_bb.Min, image_bb.Max, uv0, uv1, GetColorU32(tint_col));

	return pressed;
}

bool ImGui::SliderFloatCustomizable(const char* label, void* v, const void* v_min, const void* v_max, const char* format, float sliderBackgroundHeight, float sliderWidth, float power)
{
	ImGuiDataType data_type = ImGuiDataType_Float;

	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = CalcItemWidth();

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, id, &frame_bb))
		return false;

	// Default format string when passing NULL
	if (format == NULL)
		format = DataTypeGetInfo(data_type)->PrintFmt;

	// Tabbing or CTRL-clicking on Slider turns it into an input box
	const bool hovered = ItemHoverable(frame_bb, id);
	bool temp_input_is_active = TempInputTextIsActive(id);
	bool temp_input_start = false;
	if (!temp_input_is_active)
	{
		const bool focus_requested = FocusableItemRegister(window, id);
		const bool clicked = (hovered && g.IO.MouseClicked[0]);
		if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
		{
			SetActiveID(id, window);
			SetFocusID(id, window);
			FocusWindow(window);
			g.ActiveIdAllowNavDirFlags = (1 << ImGuiDir_Up) | (1 << ImGuiDir_Down);
			if (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavInputId == id)
			{
				temp_input_start = true;
				FocusableItemUnregister(window);
			}
		}
	}
	if (temp_input_is_active || temp_input_start)
		return TempInputTextScalar(frame_bb, id, label, data_type, v, format);

	ImRect background = frame_bb;
	if (sliderBackgroundHeight > 0.0f) {
		background.Min.y = frame_bb.Min.y + ((frame_bb.Max.y - frame_bb.Min.y - sliderBackgroundHeight) / 2);
		background.Max.y = background.Min.y + sliderBackgroundHeight;
	}

	// Draw frame
	const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	RenderNavHighlight(frame_bb, id);
	RenderFrame(background.Min, background.Max, frame_col, true, g.Style.FrameRounding);

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = SliderBehavior(frame_bb, id, data_type, v, v_min, v_max, format, power, ImGuiSliderFlags_None, &grab_bb);
	if (value_changed)
		MarkItemEdited(id);

	// Render grab
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, v, format);
	RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

	if (label_size.x > 0.0f)
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
	return value_changed;
}

void ImGui::NoSpaceNewLine()
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImVec2 backup_item_spacing = g.Style.ItemSpacing;
	g.Style.ItemSpacing = ImVec2(0.0f, 0.0f);
	const ImGuiLayoutType backup_layout_type = window->DC.LayoutType;
	window->DC.LayoutType = ImGuiLayoutType_Vertical;
	ItemSize(ImVec2(0, 0));

	window->DC.LayoutType = backup_layout_type;
	g.Style.ItemSpacing = backup_item_spacing;
}

void ImGui::VerticalDummy(float y)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImVec2 backup_item_spacing = g.Style.ItemSpacing;
	g.Style.ItemSpacing = ImVec2(0.0f, 0.0f);

	const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(0.0f, y));
	ItemSize(ImVec2(0.0f, y));
	ItemAdd(bb, 0);

	g.Style.ItemSpacing = backup_item_spacing;
}

void ImGui::WaitingModal(const char* title, const char* body)
{
	const float verticalPadding = 10.0f;
	const float horizontalPadding = (CalcTextSize(body).x / 5);
	const float spinnerRadius = 15.0f;
	const float spinnerThickness = 5.0f;

	SetNextWindowContentSize(ImVec2(CalcTextSize(body).x + (horizontalPadding * 2),
		CalcTextSize(body).y + (verticalPadding * 3) + ((spinnerRadius + spinnerThickness) * 2)));

	OpenPopup(title);

	if (BeginPopupModal(title, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoScrollbar))
	{
		VerticalDummy(verticalPadding);
		NoSpaceNewLine();
		
		SameLine(0, (CalcTextSize(body).x / 2) + horizontalPadding - 15);
		Spinner("Spinner", 15, 5, GetColorU32(ImGuiCol_ButtonHovered));
		
		NoSpaceNewLine();
		VerticalDummy(verticalPadding);
		NoSpaceNewLine();
		
		SameLine(0, horizontalPadding);
		Text(body);
		SameLine(0, horizontalPadding);

		NoSpaceNewLine();
		VerticalDummy(verticalPadding);
		NoSpaceNewLine();

		EndPopup();
	}
}

void ImGui::LocalWaitingModal(const char* title, const char* body)
{
	GetCurrentWindow()->DrawList->AddRectFilled(GetWindowPos(), GetWindowPos() + GetWindowSize(), GetColorU32(GetStyleColorVec4(ImGuiCol_ModalWindowDimBg)));
	
	const float verticalPadding = 10.0f;
	const float horizontalPadding = (CalcTextSize(body).x / 5);
	const float spinnerRadius = 15.0f;
	const float spinnerThickness = 5.0f;

	SetNextWindowContentSize(ImVec2(CalcTextSize(body).x + (horizontalPadding * 2),
		CalcTextSize(body).y + (verticalPadding * 3) + ((spinnerRadius + spinnerThickness) * 2)));
	SetNextWindowPosCenter();

	PushStyleColor(ImGuiCol_TitleBg, GetStyleColorVec4(ImGuiCol_TitleBgActive));
	PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	Begin(title, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse);

	VerticalDummy(verticalPadding);
	NoSpaceNewLine();

	SameLine(0, (CalcTextSize(body).x / 2) + horizontalPadding - 15);
	Spinner("Spinner", 15, 5, GetColorU32(ImGuiCol_ButtonHovered));

	NoSpaceNewLine();
	VerticalDummy(verticalPadding);
	NoSpaceNewLine();

	SameLine(0, horizontalPadding);
	Text(body);
	SameLine(0, horizontalPadding);

	NoSpaceNewLine();
	VerticalDummy(verticalPadding);
	NoSpaceNewLine();

	End();
	PopStyleColor();
	PopStyleColor();
}