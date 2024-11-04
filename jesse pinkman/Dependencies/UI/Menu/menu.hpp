#pragma once
#include "../../../Includes/includes.hpp"
#include "../Fonts/Extras/colors.h"
#include "../../../Includes/Definitions/c_definitions.hpp"
#include <d3d11.h>
#include <wrl/client.h>
#include <wincodec.h>
#include <D3DX11tex.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <wrl/client.h>
#include <vector>
#include <fstream>
#include <D3DX11tex.h>
//#include "../Renderer/c_overlay.h"
using namespace ImGui;
using namespace C_Players;
using namespace C_Aimbot;

inline void c_draw_fov()
{
    if (c_circle) {
       
        GetBackgroundDrawList( ) -> AddCircle( ImVec2( C_Overlay::c_screen_width / 2, C_Overlay::c_screen_height / 2) , c_fov, ImColor( 255, 255, 255 ), 64, 1 );
    }
}

inline static void vis_tab() {
    ImGui::BeginGroup();
    ImGui::Checkbox("Player ESP", &c_enable_esp);
    ImGui::Checkbox("Player box", &c_enable_box);
    if (c_enable_box) {
        ImGui::Combo("##Box Type", &c_box, "Static\0Filled\0Cornered\0\0");
    }
    ImGui::Checkbox("Player Skeleton", &c_skeleton);
    ImGui::Checkbox("Player Distance", &c_distance);
    ImGui::Checkbox("Player Weapon", &c_weapon);
    ImGui::Checkbox("Player Username", &c_username);
    ImGui::Checkbox("Player Rank esp", &c_rank_esp);
    ImGui::Checkbox("Player Platform", &c_platform);
    ImGui::Checkbox("Player Arrows", &c_arrows);
    ImGui::Checkbox("Player Target", &c_target);
    ImGui::Checkbox("Risk Detection", &c_threat);
    ImGui::SliderFloat("Max Distance", &c_max_render_distance, 1.0f, 275.0f);
    ImGui::EndGroup();
}

inline static void aim_tab() {
    ImGui::BeginGroup();
    ImGui::Checkbox("Enable Aimbot", &c_enable);
    ImGui::Checkbox("Aimbot Fov", &c_circle);
    ImGui::Checkbox("Visible Check", &c_visible_check);
    ImGui::Checkbox("Enable Deadzone", &c_dead_zone);
    ImGui::Checkbox("Ignore Knocked", &c_knocked);
    ImGui::Combo("Hitbox", &c_hitbox, "Head\0Neck\0Pelvis\0Random\0\0");
    ImGui::Checkbox("Humanized aim", &c_humanized);
    ImGui::SliderFloat("Smoothness", &c_smooth, 1.0f, 20.0f);
    ImGui::SliderFloat("Field Of View", &c_fov, 1.0f, 300.0f);
    ImGui::SliderFloat("Deadzone Value", &c_custom_dead_zone, 0, 1);
    ImGui::Combo("Mouse type", &c_aim1, "Input\0\rMouse\0\rHumanized\0\0");
    ImGui::Combo("Keybind", &c_aim_key, "LMB\0\rRMB\0\rMB2\0\rMB1\0\rLShift\0\rLStrg\0\rLAlt\0\0");
    ImGui::EndGroup();
}

inline static void trigger_tab() {
    ImGui::BeginGroup();
    ImGui::Checkbox("Triggerbot (Shotgun Only)", &c_triggggger);
    ImGui::SliderInt("Max distance", &max_trig_distance, 0, 50);
    ImGui::SliderInt("Delay", &trig_delay, 0, 5);
    ImGui::Combo("Keybind", &c_trig_key, "LMB\0\rRMB\0\rMB2\0\rMB1\0\rLShift\0\rLStrg\0\rLAlt\0\0");
    ImGui::EndGroup();
}

inline static void theme1() {
    ImVec4* colors = GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.0353f, 0.1882f, 0.1569f, 0.75f); // Updated to gradient start color
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.1373f, 0.4784f, 0.3412f, 0.75f); // Updated to gradient end color
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0353f, 0.1882f, 0.1569f, 0.75f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    ImGuiStyle& style = GetStyle();
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    //style.FrameBorderSize = 1;
    style.WindowRounding = 4;
    style.ChildRounding = 4;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.WindowTitleAlign = ImVec2(0.5, 0.5);
}

inline void draw_menu() {
    theme1();

    static int page = 0;
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);

    if (ImGui::Begin("external", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
        SetWindowPos(ImVec2(600, 600), ImGuiCond_Once);
        SetWindowSize(ImVec2(375, 500), ImGuiCond_Once);
        ImDrawList* draw_list = GetWindowDrawList();
        ImVec2 p = GetWindowPos();
        ImVec2 size = GetWindowSize();
        ImU32 col1 = GetColorU32(ImVec4(0.0353f, 0.1882f, 0.1569f, 1.0f));
        ImU32 col2 = GetColorU32(ImVec4(0.1373f, 0.4784f, 0.3412f, 1.0f));
        draw_list->AddRectFilledMultiColor(ImVec2(p.x, p.y), ImVec2(p.x + size.x, p.y + size.y), col1, col2, col2, col1);

        ImGui::BeginChild("##sidebar", ImVec2(150, 0), true);
        ImGuiStyle& style = ImGui::GetStyle();
        style.ItemSpacing.y = 5; 
        style.ItemInnerSpacing.x = 10; 

        ImVec4 tab_normal = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
        ImVec4 tab_selected = ImVec4(0.1373f, 0.4784f, 0.3412f, 1.0f);
        ImVec4 tab_hovered = ImVec4(0.2f, 0.4f, 0.2f, 1.0f);

        const char* tabs[] = { "Aimbot", "Visuals", "Trigger", "Movement", "Settings", "Skins" };
        for (int i = 0; i < IM_ARRAYSIZE(tabs); i++) {
            if (page == i)
                ImGui::PushStyleColor(ImGuiCol_Text, tab_selected);

            else
                ImGui::PushStyleColor(ImGuiCol_Text, tab_normal);

            if (ImGui::Selectable(tabs[i], page == i))
                page = i;

            ImGui::PopStyleColor();
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("##main", ImVec2(0, 0), true);
        if (page == 0) aim_tab();
        else if (page == 1) vis_tab();
        else if (page == 2) trigger_tab();
        ImGui::EndChild();

        ImGui::End();
    }
}