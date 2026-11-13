#include "ZeninUI.h"
#include "imgui.h"
#include <cstdio>
#include <cmath>

namespace Zenin {

Menu& Menu::Get() {
    static Menu instance;
    return instance;
}

Menu::Menu() {
    skinchanger.weapons = {
        { "AKR | Necromancer", 101, 0.02f, 1337, true, 42 },
        { "M4 | Samurai", 102, 0.05f, 750, true, 19 },
        { "AWM | Genesis", 103, 0.001f, 4200, true, 88 },
        { "Deagle | Morgan", 104, 0.12f, 310, false, 5 },
        { "Karambit | Claw", 201, 0.01f, 9999, true, 777 },
        { "Butterfly | Starfall", 202, 0.04f, 542, true, 123 },
        { "Gloves | Champion", 301, 0.08f, 0, false, 99 }
    };
}

void Menu::InitStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.WindowRounding = 10.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;

    style.WindowPadding = ImVec2(16, 16);
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(12, 10);
    style.ItemInnerSpacing = ImVec2(8, 6);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                  = ImVec4(0.92f, 0.94f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.54f, 0.62f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.10f, 0.14f, 0.95f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.12f, 0.13f, 0.18f, 0.85f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.11f, 0.12f, 0.16f, 0.98f);
    colors[ImGuiCol_Border]                = ImVec4(0.20f, 0.22f, 0.30f, 0.60f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.16f, 0.18f, 0.24f, 0.80f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.22f, 0.25f, 0.34f, 0.90f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.30f, 0.40f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.10f, 0.11f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.14f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.12f, 0.13f, 0.18f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.08f, 0.09f, 0.12f, 0.50f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.22f, 0.26f, 0.35f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.30f, 0.35f, 0.48f, 0.90f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.38f, 0.45f, 0.60f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.35f, 0.70f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.35f, 0.70f, 1.00f, 0.90f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.18f, 0.21f, 0.28f, 0.85f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.25f, 0.30f, 0.42f, 0.95f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.32f, 0.38f, 0.52f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.20f, 0.24f, 0.33f, 0.80f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.28f, 0.33f, 0.45f, 0.90f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.35f, 0.42f, 0.58f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.20f, 0.23f, 0.30f, 0.70f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.30f, 0.35f, 0.48f, 0.90f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40f, 0.48f, 0.65f, 1.00f);
}

// Renders an interactive placeholder skin preview badge
static void DrawSkinPlaceholderCard(const char* label, const ImVec2& size, float wear, bool statTrack) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(p0.x + size.x, p0.y + size.y);

    // Gradient background
    ImU32 colTop = IM_COL32(24, 28, 38, 255);
    ImU32 colBottom = IM_COL32(14, 16, 22, 255);
    drawList->AddRectFilledMultiColor(p0, p1, colTop, colTop, colBottom, colBottom);
    drawList->AddRect(p0, p1, IM_COL32(50, 56, 75, 255), 8.0f, 0, 1.5f);

    // Grid lines for visual depth
    for (float x = p0.x + 20; x < p1.x; x += 30) {
        drawList->AddLine(ImVec2(x, p0.y), ImVec2(x, p1.y), IM_COL32(255, 255, 255, 8));
    }
    for (float y = p0.y + 20; y < p1.y; y += 30) {
        drawList->AddLine(ImVec2(p0.x, y), ImVec2(p1.x, y), IM_COL32(255, 255, 255, 8));
    }

    // Stylized silhouette placeholder for 3D model
    ImVec2 center = ImVec2((p0.x + p1.x) * 0.5f, (p0.y + p1.y) * 0.5f);
    drawList->AddCircleFilled(center, 42.0f, IM_COL32(40, 48, 68, 180));
    drawList->AddCircle(center, 42.0f, IM_COL32(90, 160, 255, 200), 32, 2.0f);
    drawList->AddText(ImVec2(center.x - 30, center.y - 8), IM_COL32(200, 220, 255, 255), "[3D MESH]");

    // StatTrack counter badge
    if (statTrack) {
        ImVec2 stPos = ImVec2(p0.x + 12, p0.y + 12);
        drawList->AddRectFilled(stPos, ImVec2(stPos.x + 75, stPos.y + 22), IM_COL32(230, 110, 20, 220), 4.0f);
        drawList->AddText(ImVec2(stPos.x + 6, stPos.y + 3), IM_COL32(255, 255, 255, 255), "StatTrak™");
    }

    // Wear condition indicator
    char wearText[32];
    snprintf(wearText, sizeof(wearText), "Wear: %.4f", wear);
    drawList->AddText(ImVec2(p0.x + 12, p1.y - 24), IM_COL32(160, 170, 190, 255), wearText);

    ImGui::Dummy(size);
}

void Menu::Render() {
    if (!isOpen) return;

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(780, 500), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f - 390, io.DisplaySize.y * 0.5f - 250), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("Zenin iOS Showcase · Standalone Shell", &isOpen, flags)) {

        // Top Navigation Bar
        ImGui::BeginChild("##NavBar", ImVec2(0, 46), true, ImGuiWindowFlags_NoScrollbar);
        const char* tabs[] = { "Visuals", "Skinchanger", "World & FX", "Profiles", "About" };
        for (int i = 0; i < 5; ++i) {
            if (i > 0) ImGui::SameLine();
            bool isSelected = (currentTab == i);
            if (isSelected) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.50f, 0.90f, 0.85f));
            }
            if (ImGui::Button(tabs[i], ImVec2(130, 32))) {
                currentTab = i;
            }
            if (isSelected) {
                ImGui::PopStyleColor();
            }
        }
        ImGui::EndChild();

        ImGui::Spacing();

        // Content Region
        if (currentTab == 0) {
            // Visuals / Chams
            ImGui::Columns(2, "VisualsCol", false);
            ImGui::SetColumnWidth(0, 370);

            ImGui::BeginChild("##ChamsSettings", ImVec2(0, 370), true);
            ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "PLAYER CHAMS");
            ImGui::Separator();
            ImGui::Checkbox("Enable Chams", &visuals.enabled);

            const char* chamsStyles[] = { "Disabled", "Flat Solid", "Glossy / Fresnel", "Crystal Iridescent", "Wireframe Grid" };
            ImGui::Combo("Style", &visuals.chamsType, chamsStyles, IM_ARRAYSIZE(chamsStyles));

            if (visuals.chamsType == 2) { // Glossy
                ImGui::SliderFloat("Glossiness", &visuals.glossyGloss, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat("Fresnel Power", &visuals.glossyFresnel, 0.0f, 1.0f, "%.2f");
            } else if (visuals.chamsType == 3) { // Crystal
                ImGui::SliderFloat("Reflectivity", &visuals.crystalReflectivity, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat("Hue Spread", &visuals.crystalHueSpread, 0.0f, 1.0f, "%.2f");
            } else if (visuals.chamsType == 4) { // Wireframe
                ImGui::SliderFloat("Wire Thickness", &visuals.wireThickness, 0.5f, 5.0f, "%.1f px");
            }

            ImGui::Spacing();
            ImGui::ColorEdit4("Visible Color", visuals.chamsColorVisible);
            ImGui::ColorEdit4("Hidden Color", visuals.chamsColorHidden);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##EspSettings", ImVec2(0, 370), true);
            ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "OVERLAY & ESP");
            ImGui::Separator();
            ImGui::Checkbox("Bounding Box", &visuals.boxEsp);
            ImGui::Checkbox("Health Bar Indicator", &visuals.healthBar);
            ImGui::Checkbox("Armor Indicator", &visuals.armorBar);
            ImGui::Checkbox("Active Weapon Name", &visuals.weaponName);
            ImGui::Checkbox("Distance Tag", &visuals.distanceText);
            ImGui::Spacing();
            ImGui::ColorEdit4("ESP Color", visuals.espColor);
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        else if (currentTab == 1) {
            // Skinchanger
            ImGui::Columns(2, "SkinCol", false);
            ImGui::SetColumnWidth(0, 280);

            ImGui::BeginChild("##WeaponList", ImVec2(0, 370), true);
            ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "INVENTORY LOADOUT");
            ImGui::Separator();
            for (size_t i = 0; i < skinchanger.weapons.size(); ++i) {
                bool isSelected = (skinchanger.selectedWeaponIndex == (int)i);
                if (ImGui::Selectable(skinchanger.weapons[i].name.c_str(), isSelected)) {
                    skinchanger.selectedWeaponIndex = (int)i;
                }
            }
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##SkinEditor", ImVec2(0, 370), true);
            if (skinchanger.selectedWeaponIndex >= 0 && skinchanger.selectedWeaponIndex < (int)skinchanger.weapons.size()) {
                SkinItem& item = skinchanger.weapons[skinchanger.selectedWeaponIndex];

                ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "CUSTOMIZE: %s", item.name.c_str());
                ImGui::Separator();

                // Interactive preview card
                DrawSkinPlaceholderCard(item.name.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 150), item.wear, item.statTrackEnabled);

                ImGui::Spacing();
                ImGui::SliderFloat("Float / Wear", &item.wear, 0.0001f, 1.0000f, "%.4f");
                ImGui::SliderInt("Seed / Pattern", &item.seed, 1, 1000);

                ImGui::Checkbox("StatTrak™ Module", &item.statTrackEnabled);
                if (item.statTrackEnabled) {
                    ImGui::SameLine();
                    ImGui::InputInt("Kills", &item.statTrackCount);
                }
            }
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        else if (currentTab == 2) {
            // World & Atmosphere
            ImGui::BeginChild("##WorldBox", ImVec2(0, 370), true);
            ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "WORLD ATMOSPHERE & SHADERS");
            ImGui::Separator();

            ImGui::SliderFloat("Field of View (Scope FOV)", &world.scopeFov, 60.0f, 130.0f, "%.1f°");

            ImGui::Spacing();
            ImGui::Checkbox("Weather: Falling Snow Effect", &world.snowWind);
            if (world.snowWind) {
                ImGui::Indent();
                ImGui::SliderFloat("Snow Density", &world.snowDensity, 0.1f, 1.0f);
                ImGui::Unindent();
            }

            ImGui::Checkbox("Weather: Rain & Wet Surfaces", &world.rainFall);
            if (world.rainFall) {
                ImGui::Indent();
                ImGui::SliderFloat("Rain Intensity", &world.rainDensity, 0.1f, 1.0f);
                ImGui::Unindent();
            }

            ImGui::Spacing();
            ImGui::SliderFloat("Summer Ivy Amount", &world.summerIvyAmount, 0.0f, 1.0f);
            ImGui::SliderFloat("Film Grain Intensity", &world.grainIntensity, 0.0f, 1.0f);
            ImGui::SliderFloat("Vignette Smoothness", &world.vignetteSmoothness, 0.0f, 1.0f);

            ImGui::Spacing();
            ImGui::ColorEdit4("Skybox Ambient Tint", world.skyboxColor);
            ImGui::EndChild();
        }
        else if (currentTab == 3) {
            // Profiles / Config
            ImGui::BeginChild("##ConfigBox", ImVec2(0, 370), true);
            ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "CONFIG PROFILE MANAGER");
            ImGui::Separator();

            for (size_t i = 0; i < configs.profileNames.size(); ++i) {
                bool isSelected = (configs.selectedProfile == (int)i);
                if (ImGui::Selectable(configs.profileNames[i].c_str(), isSelected)) {
                    configs.selectedProfile = (int)i;
                }
            }

            ImGui::Spacing();
            ImGui::Separator();
            if (ImGui::Button("Load Profile", ImVec2(120, 30))) {
                // Profile loaded
            }
            ImGui::SameLine();
            if (ImGui::Button("Save Current", ImVec2(120, 30))) {
                // Profile saved
            }

            ImGui::Spacing();
            ImGui::InputText("New Profile", configs.newProfileName, sizeof(configs.newProfileName));
            ImGui::SameLine();
            if (ImGui::Button("Create Profile", ImVec2(120, 24))) {
                configs.profileNames.push_back(std::string(configs.newProfileName));
            }
            ImGui::EndChild();
        }
        else if (currentTab == 4) {
            // About
            ImGui::BeginChild("##AboutBox", ImVec2(0, 370), true);
            ImGui::TextColored(ImVec4(0.4f, 0.75f, 1.0f, 1.0f), "ABOUT ZENIN IOS SHOWCASE");
            ImGui::Separator();
            ImGui::TextWrapped("This is a clean, standalone iOS showcase shell recreating the Zenin Dear ImGui interface layout.");
            ImGui::BulletText("Target OS: iOS 15.0+ (Metal 2.0 / 3.0)");
            ImGui::BulletText("Renderer: Apple Metal via MTKView");
            ImGui::BulletText("State: Standalone UI Demonstration (Zero injection / Zero offsets)");
            ImGui::BulletText("CI Pipeline: GitHub Actions (macOS runner, automatic IPA generation)");
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::TextDisabled("Built for testing and visual parity evaluation.");
            ImGui::EndChild();
        }
    }
    ImGui::End();
}

} // namespace Zenin
