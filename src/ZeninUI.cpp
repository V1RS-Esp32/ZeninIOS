#include "ZeninUI.h"
#include "imgui.h"
#include <cstdio>
#include <cmath>
#include <ctime>

namespace Zenin {

Menu& Menu::Get() {
    static Menu instance;
    return instance;
}

Menu::Menu() {
    // 1:1 Knives recovered from Zenin binary BundleContent
    skinchanger.knifeCatalog = {
        { "Knives", "M9 Bayonet", "Doppler (Ruby Marbleized)", 1001, 0.005f, 412, true, 2841, "Zenin Dragon", { 101, 102, 103, 104 } },
        { "Knives", "Karambit", "Claw Fade", 1002, 0.012f, 777, true, 9999, "Gold Cat", { 201, 202, 0, 0 } },
        { "Knives", "Butterfly Knife", "Starfall (CS2)", 1003, 0.001f, 1337, true, 5420, "CS2 Diamond", { 301, 302, 303, 304 } },
        { "Knives", "Talon Knife", "Damascus Steel", 1004, 0.045f, 98, true, 310, "Titan Foil", { 401, 0, 0, 0 } },
        { "Knives", "Flip Knife", "Autotronic", 1005, 0.080f, 62, false, 0, "None", { 0, 0, 0, 0 } },
        { "Knives", "Stiletto Knife", "Doppler (Sapphire)", 1006, 0.002f, 420, true, 1890, "Howl", { 501, 502, 0, 0 } },
        { "Knives", "Ursus Knife", "Ultraviolet", 1007, 0.065f, 12, false, 0, "None", { 0, 0, 0, 0 } },
        { "Knives", "Skeleton Knife", "Crimson Web", 1008, 0.035f, 888, true, 442, "Crown Foil", { 601, 0, 0, 0 } },
        { "Knives", "Classic Knife", "Slaughter", 1009, 0.020f, 250, true, 715, "None", { 0, 0, 0, 0 } },
        { "Knives", "Navaja Knife", "Tiger Tooth", 1010, 0.009f, 319, false, 0, "None", { 0, 0, 0, 0 } },
        { "Knives", "Kukri", "Case Hardened (Blue Gem)", 1011, 0.015f, 661, true, 890, "Zenin Skull", { 701, 702, 703, 704 } },
        { "Knives", "Survival Knife", "Stained", 1012, 0.120f, 45, false, 0, "None", { 0, 0, 0, 0 } },
        { "Knives", "Paracord Knife", "Night Stripe", 1013, 0.150f, 82, false, 0, "None", { 0, 0, 0, 0 } },
        { "Knives", "Gut Knife", "Lore", 1014, 0.070f, 19, true, 120, "None", { 0, 0, 0, 0 } },
        { "Knives", "Push Daggers", "Zenin Custom (CS2)", 1015, 0.001f, 1, true, 13337, "Cat Ear", { 801, 802, 0, 0 } },
        { "Knives", "Katana", "Vanilla Black", 1016, 0.000f, 0, true, 666, "Demon Mask", { 0, 0, 0, 0 } },
        { "Knives", "Chainsaw", "Bloody Rust (CS2)", 1017, 0.450f, 999, true, 2024, "Biohazard", { 0, 0, 0, 0 } },
        { "Knives", "Battle Axe", "Nordic Gold", 1018, 0.050f, 55, false, 0, "Rune", { 0, 0, 0, 0 } },
        { "Knives", "Crowbar", "Half-Life Hazard", 1019, 0.220f, 3, false, 0, "Lambda", { 0, 0, 0, 0 } },
        { "Knives", "Tanto", "Sakura Blossom", 1020, 0.004f, 108, true, 1150, "Cherry", { 901, 902, 0, 0 } }
    };

    // CS2 Ported Guns & SO2 Weapons
    skinchanger.weaponCatalog = {
        { "Rifles", "AKR", "Necromancer", 2001, 0.018f, 54, true, 1420, "Zenin Eye", { 11, 12, 13, 14 } },
        { "Rifles", "M4", "Samurai", 2002, 0.035f, 190, true, 920, "Dragon Breath", { 21, 22, 0, 0 } },
        { "Rifles", "M4A1", "Cyberpunk", 2003, 0.002f, 88, true, 3100, "Neon City", { 31, 32, 33, 34 } },
        { "Snipers", "AWP (CS2)", "Dragon Lore Port", 3001, 0.001f, 420, true, 8888, "Golden Crown", { 41, 42, 43, 44 } },
        { "Snipers", "AWM", "Genesis", 3002, 0.008f, 315, true, 4120, "Phoenix", { 51, 52, 0, 0 } },
        { "Snipers", "SCAR20 (CS2)", "Enforcer", 3003, 0.045f, 71, false, 0, "None", { 0, 0, 0, 0 } },
        { "Snipers", "G3SG1 (CS2)", "Chronos", 3004, 0.025f, 13, true, 140, "Clockwork", { 0, 0, 0, 0 } },
        { "Snipers", "SSG08 (CS2)", "Blood in the Water", 3005, 0.060f, 92, true, 730, "Shark Bite", { 61, 62, 0, 0 } },
        { "Pistols", "Deagle", "Morgan", 4001, 0.010f, 102, true, 650, "Ace", { 71, 72, 0, 0 } },
        { "Pistols", "R8 Revolver (CS2)", "Fade", 4002, 0.003f, 412, true, 380, "Wild West", { 81, 0, 0, 0 } },
        { "Pistols", "USP", "Genesis", 4003, 0.015f, 219, true, 1250, "Silencer", { 91, 92, 0, 0 } },
        { "Gloves", "Zenin Agent Gloves", "Black & Violet Edition", 5001, 0.010f, 7, false, 0, "Zenin Logo", { 0, 0, 0, 0 } },
        { "Gloves", "Sport Gloves", "Vice", 5002, 0.025f, 111, false, 0, "Vice", { 0, 0, 0, 0 } },
        { "Gloves", "Specialist Gloves", "Crimson Kimono", 5003, 0.030f, 661, false, 0, "Red Sun", { 0, 0, 0, 0 } }
    };
}

void Menu::InitStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 8.0f;
    style.ChildRounding = 6.0f;
    style.FrameRounding = 5.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 5.0f;
    style.TabRounding = 5.0f;

    style.WindowPadding = ImVec2(14, 14);
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(10, 8);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.ScrollbarSize = misc.scrollbarSize;

    ImVec4* colors = style.Colors;
    // Zenin Dark Obsidian & Electric Purple Palette
    colors[ImGuiCol_Text]                  = ImVec4(0.95f, 0.95f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.45f, 0.46f, 0.58f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.06f, 0.07f, 0.10f, 0.96f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.09f, 0.10f, 0.15f, 0.90f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.09f, 0.13f, 0.98f);
    colors[ImGuiCol_Border]                = ImVec4(0.18f, 0.19f, 0.28f, 0.70f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.13f, 0.14f, 0.22f, 0.85f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.20f, 0.22f, 0.34f, 0.95f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.28f, 0.42f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.09f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.11f, 0.12f, 0.18f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.08f, 0.09f, 0.13f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.08f, 0.40f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.24f, 0.22f, 0.40f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.35f, 0.32f, 0.58f, 0.90f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.45f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.48f, 0.40f, 0.93f, 1.00f); // Zenin Violet
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.48f, 0.40f, 0.93f, 0.90f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.60f, 0.52f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.15f, 0.16f, 0.25f, 0.85f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.25f, 0.27f, 0.42f, 0.95f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.45f, 0.38f, 0.85f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.18f, 0.19f, 0.30f, 0.80f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.28f, 0.44f, 0.90f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.42f, 0.36f, 0.82f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.16f, 0.17f, 0.25f, 0.80f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.26f, 0.28f, 0.42f, 0.90f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.48f, 0.40f, 0.93f, 1.00f);
}

// 1:1 Interactive Watermark in the Top HUD
void Menu::RenderWatermark() {
    if (!misc.watermark) return;

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    // Time string
    time_t rawtime;
    struct tm* timeinfo;
    char timeBuffer[16];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timeinfo);

    char bannerText[128];
    snprintf(bannerText, sizeof(bannerText), "[🐱 Zenin] Standoff 2  |  FPS: %.0f  |  Ping: %dms  |  %s  |  v0.17",
             io.Framerate, misc.pingSpoof ? misc.pingSpoofValue : 14, timeBuffer);

    ImVec2 textSize = ImGui::CalcTextSize(bannerText);
    ImVec2 pad = ImVec2(14, 8);
    ImVec2 pos = ImVec2(24, 20);
    ImVec2 pMax = ImVec2(pos.x + textSize.x + pad.x * 2, pos.y + textSize.y + pad.y * 2);

    // Interactive button behind the watermark
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(ImVec2(pMax.x - pos.x, pMax.y - pos.y));
    ImGuiWindowFlags wmFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    
    ImGui::Begin("##WatermarkOverlay", nullptr, wmFlags);
    if (ImGui::InvisibleButton("##WatermarkBtn", ImVec2(pMax.x - pos.x, pMax.y - pos.y))) {
        isOpen = !isOpen; // Toggle menu on watermark tap!
    }
    bool isHovered = ImGui::IsItemHovered();
    ImGui::End();

    // Render watermark geometry
    ImU32 bgCol = isHovered ? IM_COL32(20, 22, 34, 240) : IM_COL32(12, 13, 20, 220);
    ImU32 borderCol = isHovered ? IM_COL32(130, 110, 250, 255) : IM_COL32(60, 55, 90, 200);

    drawList->AddRectFilled(pos, pMax, bgCol, 6.0f);
    drawList->AddRect(pos, pMax, borderCol, 6.0f, 0, 1.5f);
    
    // Glowing accent pip
    drawList->AddCircleFilled(ImVec2(pos.x + 12, pos.y + pad.y + textSize.y * 0.5f), 3.5f, IM_COL32(115, 95, 245, 255));
    drawList->AddText(ImVec2(pos.x + 22, pos.y + pad.y), IM_COL32(240, 240, 250, 255), bannerText);
}

// 1:1 Weapon Preview Card with 3D Wireframe Silhouette
static void DrawSkinInspectCard(const SkinItem& item, const ImVec2& size) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(p0.x + size.x, p0.y + size.y);

    // Background gradient & outline
    ImU32 colTop = IM_COL32(18, 19, 30, 255);
    ImU32 colBottom = IM_COL32(10, 11, 16, 255);
    drawList->AddRectFilledMultiColor(p0, p1, colTop, colTop, colBottom, colBottom);
    drawList->AddRect(p0, p1, IM_COL32(45, 48, 70, 200), 6.0f, 0, 1.5f);

    // Grid wire overlay
    for (float x = p0.x + 20; x < p1.x; x += 25)
        drawList->AddLine(ImVec2(x, p0.y), ImVec2(x, p1.y), IM_COL32(255, 255, 255, 5));
    for (float y = p0.y + 20; y < p1.y; y += 25)
        drawList->AddLine(ImVec2(p0.x, y), ImVec2(p1.y, y), IM_COL32(255, 255, 255, 5));

    // Dynamic 3D Knife/Gun wireframe sketch based on seed
    ImVec2 center = ImVec2((p0.x + p1.x) * 0.5f, (p0.y + p1.y) * 0.5f - 10);
    float angle = item.seed * 0.05f;
    ImVec2 pBlade1 = ImVec2(center.x - 70 * cosf(angle), center.y - 70 * sinf(angle));
    ImVec2 pBlade2 = ImVec2(center.x + 90 * cosf(angle), center.y + 90 * sinf(angle));
    ImVec2 pSpine = ImVec2(center.x + 60 * cosf(angle + 0.3f), center.y + 60 * sinf(angle + 0.3f));

    drawList->AddTriangleFilled(pBlade1, pBlade2, pSpine, IM_COL32(110, 90, 230, 60));
    drawList->AddTriangle(pBlade1, pBlade2, pSpine, IM_COL32(130, 115, 255, 220), 2.0f);
    drawList->AddCircle(center, 40.0f, IM_COL32(90, 80, 170, 150), 32, 1.5f);

    // Category / Weapon Title
    char title[128];
    snprintf(title, sizeof(title), "%s  |  %s", item.weaponName.c_str(), item.skinName.c_str());
    drawList->AddText(ImVec2(p0.x + 14, p0.y + 12), IM_COL32(230, 230, 250, 255), title);

    // StatTrak Counter
    if (item.statTrack) {
        char stBuf[32];
        snprintf(stBuf, sizeof(stBuf), "StatTrak™ %06d", item.statTrackCount);
        ImVec2 stPos = ImVec2(p0.x + 14, p0.y + 34);
        drawList->AddRectFilled(stPos, ImVec2(stPos.x + 125, stPos.y + 18), IM_COL32(215, 95, 15, 220), 3.0f);
        drawList->AddText(ImVec2(stPos.x + 6, stPos.y + 2), IM_COL32(255, 255, 255, 255), stBuf);
    }

    // Wear condition
    char wearBuf[64];
    snprintf(wearBuf, sizeof(wearBuf), "Wear: %.4f (Seed: %d)", item.wear, item.seed);
    drawList->AddText(ImVec2(p0.x + 14, p1.y - 24), IM_COL32(140, 145, 170, 255), wearBuf);

    // Charm info
    if (!item.charmName.empty() && item.charmName != "None") {
        char charmBuf[64];
        snprintf(charmBuf, sizeof(charmBuf), "Charm: %s", item.charmName.c_str());
        drawList->AddText(ImVec2(p1.x - 160, p1.y - 24), IM_COL32(180, 160, 240, 255), charmBuf);
    }

    ImGui::Dummy(size);
}

void Menu::Render() {
    RenderWatermark();

    if (!isOpen) return;

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(840, 540), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f - 420, io.DisplaySize.y * 0.5f - 270), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    if (ImGui::Begin("Zenin  |  Standoff 2 (CS2 Edition)", &isOpen, flags)) {

        // Top Sidebar Navigation Bar
        ImGui::BeginChild("##TabBar", ImVec2(0, 48), true, ImGuiWindowFlags_NoScrollbar);
        const char* tabs[] = { "Aimbot", "Visuals", "Skinchanger", "World & FX", "Misc", "Profiles" };
        for (int i = 0; i < 6; ++i) {
            if (i > 0) ImGui::SameLine();
            bool isCurrent = (activeTab == i);
            if (isCurrent) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.42f, 0.35f, 0.85f, 0.90f));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.13f, 0.20f, 0.75f));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.70f, 0.72f, 0.82f, 1.0f));
            }
            if (ImGui::Button(tabs[i], ImVec2(128, 34))) {
                activeTab = i;
            }
            ImGui::PopStyleColor(2);
        }
        ImGui::EndChild();

        ImGui::Spacing();

        // -------------------------------------------------------------
        // TAB 0: AIMBOT
        // -------------------------------------------------------------
        if (activeTab == 0) {
            ImGui::Columns(2, "AimbotCol", false);
            ImGui::SetColumnWidth(0, 400);

            ImGui::BeginChild("##AimGeneral", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "AIMBOT CORE");
            ImGui::Separator();
            ImGui::Checkbox("Enable Aimbot", &aimbot.enabled);
            ImGui::Checkbox("Silent Aim", &aimbot.silentAim);
            ImGui::Checkbox("Auto Fire", &aimbot.autoFire);
            ImGui::Checkbox("Auto Scope", &aimbot.autoScope);
            ImGui::Checkbox("Auto Stop on Land", &aimbot.autoStopOnLand);
            ImGui::Checkbox("Lethal Shot", &aimbot.lethalShot);

            ImGui::Spacing();
            ImGui::SliderFloat("FOV Radius", &aimbot.fov, 1.0f, 30.0f, "%.1f°");
            ImGui::SliderFloat("Smoothing", &aimbot.smooth, 1.0f, 20.0f, "%.1f");

            const char* bones[] = { "Head", "Neck", "Chest", "Pelvis" };
            ImGui::Combo("Target Bone", &aimbot.targetBone, bones, IM_ARRAYSIZE(bones));
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##AimChecks", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "RECOIL & FILTERS");
            ImGui::Separator();
            ImGui::Checkbox("Visible Check", &aimbot.checkVisible);
            ImGui::Checkbox("Smoke Check", &aimbot.checkSmoke);
            ImGui::Checkbox("Flash Check", &aimbot.checkFlash);

            ImGui::Spacing();
            ImGui::Checkbox("Recoil Compensation (RCS)", &aimbot.rcsEnabled);
            if (aimbot.rcsEnabled) {
                ImGui::SliderFloat("RCS Pitch", &aimbot.rcsPitch, 0.0f, 2.0f, "%.2f");
                ImGui::SliderFloat("RCS Yaw", &aimbot.rcsYaw, 0.0f, 2.0f, "%.2f");
            }
            ImGui::EndChild();
            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 1: VISUALS
        // -------------------------------------------------------------
        else if (activeTab == 1) {
            ImGui::Columns(2, "VisualsCol", false);
            ImGui::SetColumnWidth(0, 400);

            ImGui::BeginChild("##PlayerEsp", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "PLAYER ESP");
            ImGui::Separator();
            ImGui::Checkbox("Enable Visuals", &visuals.enabled);
            ImGui::Checkbox("Enemies Only", &visuals.enemyOnly);
            ImGui::Checkbox("Bounding Box", &visuals.boxEsp);
            
            const char* boxStyles[] = { "2D Outline", "2D Cornered", "3D Box" };
            ImGui::Combo("Box Style", &visuals.boxType, boxStyles, IM_ARRAYSIZE(boxStyles));
            
            ImGui::Checkbox("Player Skeleton", &visuals.skeleton);
            ImGui::Checkbox("Health Bar Indicator", &visuals.healthBar);
            ImGui::Checkbox("Armor Bar Indicator", &visuals.armorBar);
            ImGui::Checkbox("Weapon Text", &visuals.weaponName);
            ImGui::Checkbox("Distance Tag", &visuals.distanceTag);
            ImGui::Checkbox("Head Target Dot", &visuals.headDot);
            ImGui::Checkbox("Snaplines", &visuals.snaplines);

            ImGui::Spacing();
            ImGui::ColorEdit4("Box Color", visuals.boxColor);
            ImGui::ColorEdit4("Skeleton Color", visuals.skeletonColor);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##ChamsBlock", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "PLAYER CHAMS & SHADERS");
            ImGui::Separator();
            ImGui::Checkbox("Enable Chams", &visuals.chamsEnabled);
            ImGui::Checkbox("Show Behind Walls", &visuals.showBehindWalls);
            ImGui::Checkbox("Chams Bloom FX", &visuals.bloom);

            const char* chamsStyles[] = { "Disabled", "Flat Solid", "Glossy / Fresnel", "Crystal Iridescent", "Wireframe Grid" };
            ImGui::Combo("Chams Material", &visuals.chamsStyle, chamsStyles, IM_ARRAYSIZE(chamsStyles));

            if (visuals.chamsStyle == 2) {
                ImGui::SliderFloat("Glossiness", &visuals.glossyGloss, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat("Fresnel Power", &visuals.glossyFresnel, 0.0f, 1.0f, "%.2f");
            } else if (visuals.chamsStyle == 3) {
                ImGui::SliderFloat("Reflectivity", &visuals.crystalReflectivity, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat("Hue Spread", &visuals.crystalHueSpread, 0.0f, 1.0f, "%.2f");
            } else if (visuals.chamsStyle == 4) {
                ImGui::SliderFloat("Wire Thickness", &visuals.wireThickness, 0.5f, 5.0f, "%.1f px");
            }

            ImGui::Spacing();
            ImGui::ColorEdit4("Visible Color", visuals.chamsVisibleColor);
            ImGui::ColorEdit4("Hidden Color", visuals.chamsHiddenColor);
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 2: SKINS (CS2 & STANDOFF 2)
        // -------------------------------------------------------------
        else if (activeTab == 2) {
            ImGui::Columns(2, "SkinCol", false);
            ImGui::SetColumnWidth(0, 310);

            ImGui::BeginChild("##SkinList", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "INVENTORY OVERRIDE");
            ImGui::Separator();

            const char* cats[] = { "Knives (20)", "Weapons (14)" };
            ImGui::Combo("Category", &skinchanger.selectedCategory, cats, IM_ARRAYSIZE(cats));

            std::vector<SkinItem>& list = (skinchanger.selectedCategory == 0) ? skinchanger.knifeCatalog : skinchanger.weaponCatalog;

            for (size_t i = 0; i < list.size(); ++i) {
                bool isSelected = (skinchanger.selectedIndex == (int)i);
                char label[128];
                snprintf(label, sizeof(label), "%s - %s", list[i].weaponName.c_str(), list[i].skinName.c_str());
                if (ImGui::Selectable(label, isSelected)) {
                    skinchanger.selectedIndex = (int)i;
                }
            }
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##SkinEditor", ImVec2(0, 410), true);
            std::vector<SkinItem>& list2 = (skinchanger.selectedCategory == 0) ? skinchanger.knifeCatalog : skinchanger.weaponCatalog;
            if (skinchanger.selectedIndex >= 0 && skinchanger.selectedIndex < (int)list2.size()) {
                SkinItem& item = list2[skinchanger.selectedIndex];

                // 3D Silhouette inspect card
                DrawSkinInspectCard(item, ImVec2(ImGui::GetContentRegionAvail().x, 170));

                ImGui::Spacing();
                ImGui::SliderFloat("Float Wear", &item.wear, 0.0001f, 1.0000f, "%.4f");
                ImGui::SliderInt("Pattern Seed", &item.seed, 1, 1000);

                ImGui::Checkbox("StatTrak™ Module", &item.statTrack);
                if (item.statTrack) {
                    ImGui::SameLine();
                    ImGui::InputInt("Kills", &item.statTrackCount);
                }

                ImGui::Spacing();
                ImGui::Text("Charm: %s", item.charmName.c_str());
            }
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 3: WORLD & ATMOSPHERE
        // -------------------------------------------------------------
        else if (activeTab == 3) {
            ImGui::Columns(2, "WorldCol", false);
            ImGui::SetColumnWidth(0, 400);

            ImGui::BeginChild("##WeatherBox", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "DYNAMIC WEATHER SYSTEM");
            ImGui::Separator();
            ImGui::Checkbox("Zenin Weather: Falling Snow", &world.weatherSnow);
            if (world.weatherSnow) {
                ImGui::Indent();
                ImGui::Checkbox("Snow Wind Dynamics", &world.snowWind);
                ImGui::Checkbox("Snow Sound Ambience", &world.snowSound);
                ImGui::SliderFloat("Snow Flake Density", &world.snowDensity, 0.1f, 1.0f);
                ImGui::Unindent();
            }

            ImGui::Spacing();
            ImGui::Checkbox("Zenin Weather: Rain & Reflections", &world.weatherRain);
            if (world.weatherRain) {
                ImGui::Indent();
                ImGui::SliderFloat("Rain Intensity", &world.rainFall, 0.1f, 1.0f);
                ImGui::SliderFloat("Splash Particle FX", &world.rainSplash, 0.1f, 1.0f);
                ImGui::Unindent();
            }

            ImGui::Spacing();
            ImGui::Checkbox("Zenin Night Shadows", &world.nightShadows);
            ImGui::Checkbox("Fog Wisps Effect", &world.fogWisps);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##PostFxBox", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "POST-PROCESSING & SHADERS");
            ImGui::Separator();
            ImGui::SliderFloat("Scope Field of View (FOV)", &world.scopeFov, 60.0f, 130.0f, "%.1f°");
            ImGui::SliderFloat("Summer Ivy Density", &world.summerIvyAmount, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Film Grain Intensity", &world.grainIntensity, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Vignette Smoothness", &world.vignetteSmoothness, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Chromatic Aberration", &world.chromaticAmount, 0.0f, 0.5f, "%.2f");

            ImGui::Spacing();
            ImGui::ColorEdit4("Skybox Tint", world.skyboxColor);
            ImGui::ColorEdit4("Fog Ambient Tint", world.fogColor);
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 4: MISC
        // -------------------------------------------------------------
        else if (activeTab == 4) {
            ImGui::Columns(2, "MiscCol", false);
            ImGui::SetColumnWidth(0, 400);

            ImGui::BeginChild("##WatermarkSettings", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "WATERMARK & HUD");
            ImGui::Separator();
            ImGui::Checkbox("Show Watermark Banner", &misc.watermark);
            ImGui::Checkbox("Display FPS Counter", &misc.watermarkFps);
            ImGui::Checkbox("Display Ping Counter", &misc.watermarkPing);
            ImGui::Checkbox("Display Real Time", &misc.watermarkTime);
            ImGui::Checkbox("Display Version Code", &misc.watermarkVersion);
            ImGui::SliderFloat("Watermark Opacity", &misc.watermarkAlpha, 0.2f, 1.0f, "%.2f");

            ImGui::Spacing();
            ImGui::Checkbox("Bomb Timer Indicator", &misc.bombTimer);
            ImGui::Checkbox("Zenin Jump Circle FX", &misc.jumpCircle);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##NetworkAndAudio", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "NETWORK & AUDIO");
            ImGui::Separator();
            ImGui::Checkbox("Spoof Network Ping", &misc.pingSpoof);
            if (misc.pingSpoof) {
                ImGui::SliderInt("Fake Ping Value (ms)", &misc.pingSpoofValue, 1, 99);
            }

            ImGui::Spacing();
            ImGui::Checkbox("Custom Hitmarker", &misc.hitMarker);
            const char* hitSounds[] = { "Disabled", "Skeet", "Rust Headshot", "Bell Ding" };
            ImGui::Combo("Hit Sound", &misc.hitMarkerSound, hitSounds, IM_ARRAYSIZE(hitSounds));

            ImGui::Spacing();
            ImGui::SliderFloat("Scrollbar Width", &misc.scrollbarSize, 4.0f, 12.0f, "%.0f px");
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 5: PROFILES
        // -------------------------------------------------------------
        else if (activeTab == 5) {
            ImGui::BeginChild("##ProfilesBox", ImVec2(0, 410), true);
            ImGui::TextColored(ImVec4(0.6f, 0.5f, 1.0f, 1.0f), "LOCAL STORAGE PROFILE MANAGER");
            ImGui::Separator();

            for (size_t i = 0; i < configs.profileList.size(); ++i) {
                bool isSelected = (configs.activeIndex == (int)i);
                if (ImGui::Selectable(configs.profileList[i].c_str(), isSelected)) {
                    configs.activeIndex = (int)i;
                }
            }

            ImGui::Spacing();
            ImGui::Separator();
            if (ImGui::Button("Load Configuration", ImVec2(160, 32))) {
                // Profile loaded
            }
            ImGui::SameLine();
            if (ImGui::Button("Save Configuration", ImVec2(160, 32))) {
                // Profile saved
            }

            ImGui::Spacing();
            ImGui::InputText("New Profile Name", configs.profileInput, sizeof(configs.profileInput));
            ImGui::SameLine();
            if (ImGui::Button("Create Profile", ImVec2(130, 26))) {
                configs.profileList.push_back(std::string(configs.profileInput) + ".cfg");
            }
            ImGui::EndChild();
        }
    }
    ImGui::End();
}

} // namespace Zenin
