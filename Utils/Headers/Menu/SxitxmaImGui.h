#pragma once

#include "ImGuiNotify.hpp"

namespace ImGui {
	IMGUI_API static void          NewLines(int amount);

	IMGUI_API static void          AddCursorPos(const ImVec2& local_pos);

	IMGUI_API static void          HoverItemText(const char* text, const char* fmt = "(?)");

	static float _ButtonSize = 106.5f;
	static float _ButtonWidth = 28;
	IMGUI_API static bool		   CustomButton(const char* label, const char* name, const ImVec2& size = ImVec2(_ButtonSize, _ButtonWidth));
	
	
	IMGUI_API static bool		   CustomInputText(const char* label, const char* name, char* buf, size_t buf_size, ImVec2 _size = ImVec2(0.0f, 0.0f), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);


	struct CustomComboStruct
	{
		const char* Name;
	};
	template<typename T> // so that you can also use your own structs or classes (variable with Name must exist tho)
	IMGUI_API static void          CustomCombo(const char* label, std::vector<T> _list, int* ItemIndexVariable,
											   const char* preview_value, ImColor bg_color = ImColor(100, 84, 138), float length = 100.0f, // length: 0.0f = default
											   ImGuiComboFlags flags = 0, std::function<void()>CodeInIfStatement = []() {});

	IMGUI_API static void          CustomCombo(const char* label, std::vector<const char*> _list, int* ItemIndexVariable,
											   const char* preview_value, ImColor bg_color = ImColor(100, 84, 138), float length = 100.0f, // length: 0.0f = default
											   ImGuiComboFlags flags = 0, std::function<void()>CodeInIfStatement = []() {});
}

static void ImGui::NewLines(int amount) { for (int i = 0; i < amount; i++) { ImGui::NewLine(); } }

static void ImGui::AddCursorPos(const ImVec2& local_pos) { ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + local_pos.x, ImGui::GetCursorPosY() + local_pos.y)); }

static void ImGui::HoverItemText(const char* text, const char* fmt) {
	ImGui::TextDisabled(fmt);
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(text);
		ImGui::EndTooltip();
	}
}


static bool ImGui::CustomButton(const char* label, const char* name, const ImVec2& size_arg)
{
	return ImGui::CustomButtonEx(label, name, size_arg, ImGuiButtonFlags_None);
}

static bool ImGui::CustomInputText(const char* label, const char* name, char* buf, size_t buf_size, ImVec2 size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	IM_ASSERT(!(flags & ImGuiInputTextFlags_Multiline));
	ImGui::Text(name); ImGui::NewLine(); ImGui::SameLine();
	return InputTextEx(("##" + std::string(label)).c_str(), NULL, buf, (int)buf_size, size, flags, callback, user_data);
}

template<typename T>
static void ImGui::CustomCombo(const char* label, std::vector<T> _list, int* ItemIndexVariable, const char* preview_value, ImColor bg_color, float length, ImGuiComboFlags flags, std::function<void()>CodeInIfStatement)
{
	ImColor dark_color = ImColor(bg_color.Value.x - (10.0 * (1.0f / 255.0f)), bg_color.Value.y, bg_color.Value.z); // bg_color but darker (most likely for hover shit)
	ImColor more_dark_color = ImColor(bg_color.Value.x - (20.0 * (1.0f / 255.0f)), bg_color.Value.y, bg_color.Value.z); // bg_color but more darker (most likely for hover shit)

	//ImGui::PushStyleColor(ImGuiCol_FrameBg, bg_color.Value);
	//ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, dark_color.Value);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(24, 25, 27).Value);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(25, 25, 25, 225).Value);

	ImGui::PushStyleColor(ImGuiCol_Header, bg_color.Value);
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, dark_color.Value);
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, more_dark_color.Value);

	//ImGui::PushStyleColor(ImGuiCol_Button, dark_color.Value);
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, bg_color.Value);

	ImGui::PushStyleColor(ImGuiCol_Button, ImColor(25, 25, 25, 225).Value);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(24, 25, 27).Value);

	if (length != 0.0f) ImGui::PushItemWidth(length);
	if (ImGui::BeginCombo(label, preview_value)) {
		CodeInIfStatement();
		for (int n = 0; n < _list.size(); n++) {
			bool is_selected = (*ItemIndexVariable == n);
			if (ImGui::Selectable(_list[n].Name, is_selected))
				*ItemIndexVariable = n;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::PopStyleColor();
	if (length != 0.0f) ImGui::PopItemWidth();
}

static void ImGui::CustomCombo(const char* label, std::vector<const char*> _list, int* ItemIndexVariable, const char* preview_value, ImColor bg_color, float length, ImGuiComboFlags flags, std::function<void()>CodeInIfStatement)
{
	std::vector<CustomComboStruct> skibidi;
	for (int i = 0; i < _list.size(); i++) {
		skibidi.push_back({ _list[i] });
	}
	ImGui::CustomCombo<ImGui::CustomComboStruct>(label, skibidi, ItemIndexVariable, preview_value, bg_color, length, flags, CodeInIfStatement);
}