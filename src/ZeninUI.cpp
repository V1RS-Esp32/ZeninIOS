#include "ZeninUI.h"
#include "imgui.h"
#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>

namespace Zenin {

Menu& Menu::Get() {
    static Menu instance;
    return instance;
}

Menu::Menu() {
    // 1:1 Knives recovered from Zenin binary BundleContent
    skinchanger.knifeCatalog = {
        { "Knives", "M9 Bayonet", "Doppler (Ruby Marbleized)", ItemRarity::Covert, 1001, 0.005f, 412, true, 2841, "Zenin Dragon", { 101, 102, 103, 104 }, { 0.0f, 0.1f, 0.0f, 0.0f } },
        { "Knives", "Karambit", "Claw Fade", ItemRarity::Covert, 1002, 0.012f, 777, true, 9999, "Gold Cat", { 201, 202, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Butterfly Knife", "Starfall (CS2)", ItemRarity::Covert, 1003, 0.001f, 1337, true, 5420, "CS2 Diamond", { 301, 302, 303, 304 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Talon Knife", "Damascus Steel", ItemRarity::Classified, 1004, 0.045f, 98, true, 310, "Titan Foil", { 401, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Flip Knife", "Autotronic", ItemRarity::Classified, 1005, 0.080f, 62, false, 0, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Stiletto Knife", "Doppler (Sapphire)", ItemRarity::Covert, 1006, 0.002f, 420, true, 1890, "Howl", { 501, 502, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Ursus Knife", "Ultraviolet", ItemRarity::Restricted, 1007, 0.065f, 12, false, 0, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Skeleton Knife", "Crimson Web", ItemRarity::Covert, 1008, 0.035f, 888, true, 442, "Crown Foil", { 601, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Classic Knife", "Slaughter", ItemRarity::Classified, 1009, 0.020f, 250, true, 715, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Navaja Knife", "Tiger Tooth", ItemRarity::Restricted, 1010, 0.009f, 319, false, 0, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Kukri", "Case Hardened (Blue Gem)", ItemRarity::Classified, 1011, 0.015f, 661, true, 890, "Zenin Skull", { 701, 702, 703, 704 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Survival Knife", "Stained", ItemRarity::MilSpec, 1012, 0.120f, 45, false, 0, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Paracord Knife", "Night Stripe", ItemRarity::MilSpec, 1013, 0.150f, 82, false, 0, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Gut Knife", "Lore", ItemRarity::Restricted, 1014, 0.070f, 19, true, 120, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Push Daggers", "Zenin Custom (CS2)", ItemRarity::Extraordinary, 1015, 0.001f, 1, true, 13337, "Cat Ear", { 801, 802, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Katana", "Vanilla Black", ItemRarity::Extraordinary, 1016, 0.000f, 0, true, 666, "Demon Mask", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Chainsaw", "Bloody Rust (CS2)", ItemRarity::Extraordinary, 1017, 0.450f, 999, true, 2024, "Biohazard", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Battle Axe", "Nordic Gold", ItemRarity::Classified, 1018, 0.050f, 55, false, 0, "Rune", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Crowbar", "Half-Life Hazard", ItemRarity::Restricted, 1019, 0.220f, 3, false, 0, "Lambda", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Knives", "Tanto", "Sakura Blossom", ItemRarity::Covert, 1020, 0.004f, 108, true, 1150, "Cherry", { 901, 902, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } }
    };

    // CS2 Ported Guns & SO2 Weapons
    skinchanger.weaponCatalog = {
        { "Rifles", "AKR", "Necromancer", ItemRarity::Covert, 2001, 0.018f, 54, true, 1420, "Zenin Eye", { 11, 12, 13, 14 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Rifles", "M4", "Samurai", ItemRarity::Classified, 2002, 0.035f, 190, true, 920, "Dragon Breath", { 21, 22, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Rifles", "M4A1", "Cyberpunk", ItemRarity::Covert, 2003, 0.002f, 88, true, 3100, "Neon City", { 31, 32, 33, 34 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Snipers", "AWP (CS2)", "Dragon Lore Port", ItemRarity::Extraordinary, 3001, 0.001f, 420, true, 8888, "Golden Crown", { 41, 42, 43, 44 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Snipers", "AWM", "Genesis", ItemRarity::Covert, 3002, 0.008f, 315, true, 4120, "Phoenix", { 51, 52, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Snipers", "SCAR20 (CS2)", "Enforcer", ItemRarity::Restricted, 3003, 0.045f, 71, false, 0, "None", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Snipers", "G3SG1 (CS2)", "Chronos", ItemRarity::Restricted, 3004, 0.025f, 13, true, 140, "Clockwork", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Snipers", "SSG08 (CS2)", "Blood in the Water", ItemRarity::Classified, 3005, 0.060f, 92, true, 730, "Shark Bite", { 61, 62, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Pistols", "Deagle", "Morgan", ItemRarity::Classified, 4001, 0.010f, 102, true, 650, "Ace", { 71, 72, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Pistols", "R8 Revolver (CS2)", "Fade", ItemRarity::Covert, 4002, 0.003f, 412, true, 380, "Wild West", { 81, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Pistols", "USP", "Genesis", ItemRarity::Classified, 4003, 0.015f, 219, true, 1250, "Silencer", { 91, 92, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Gloves", "Zenin Agent Gloves", "Black & Violet Edition", ItemRarity::Extraordinary, 5001, 0.010f, 7, false, 0, "Zenin Logo", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Gloves", "Sport Gloves", "Vice", ItemRarity::Extraordinary, 5002, 0.025f, 111, false, 0, "Vice", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } },
        { "Gloves", "Specialist Gloves", "Crimson Kimono", ItemRarity::Extraordinary, 5003, 0.030f, 661, false, 0, "Red Sun", { 0, 0, 0, 0 }, { 0.0f, 0.0f, 0.0f, 0.0f } }
    };
}

static ImU32 GetRarityColor(ItemRarity rarity) {
    switch (rarity) {
        case ItemRarity::Extraordinary: return IM_COL32(255, 215, 0, 255);   // Gold
        case ItemRarity::Covert:        return IM_COL32(235, 75, 75, 255);    // Red
        case ItemRarity::Classified:    return IM_COL32(211, 44, 230, 255);   // Pink
        case ItemRarity::Restricted:    return IM_COL32(136, 71, 255, 255);   // Purple
        case ItemRarity::MilSpec:       return IM_COL32(75, 105, 255, 255);   // Blue
        default:                        return IM_COL32(180, 180, 190, 255);
    }
}

void Menu::InitStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 12.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;

    style.WindowPadding = ImVec2(16, 16);
    style.FramePadding = ImVec2(12, 7);
    style.ItemSpacing = ImVec2(12, 9);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.ScrollbarSize = misc.scrollbarSize;

    ImVec4* colors = style.Colors;
    // Premium Obsidian & Electric Violet Palette
    colors[ImGuiCol_Text]                  = ImVec4(0.96f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.48f, 0.50f, 0.62f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.06f, 0.07f, 0.10f, 0.97f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.09f, 0.10f, 0.15f, 0.94f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.09f, 0.14f, 0.98f);
    colors[ImGuiCol_Border]                = ImVec4(0.18f, 0.20f, 0.30f, 0.75f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.13f, 0.14f, 0.22f, 0.85f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.20f, 0.22f, 0.35f, 0.95f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.28f, 0.44f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.09f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.12f, 0.13f, 0.20f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.08f, 0.09f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.08f, 0.40f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.25f, 0.23f, 0.42f, 0.85f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.38f, 0.34f, 0.62f, 0.95f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.48f, 0.42f, 0.80f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.50f, 0.42f, 0.95f, 1.00f); // Zenin Violet
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.50f, 0.42f, 0.95f, 0.90f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.65f, 0.56f, 1.00f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.15f, 0.16f, 0.26f, 0.85f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.28f, 0.44f, 0.95f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.46f, 0.40f, 0.88f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.18f, 0.20f, 0.32f, 0.80f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.28f, 0.30f, 0.46f, 0.90f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.45f, 0.38f, 0.85f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.18f, 0.19f, 0.28f, 0.80f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.28f, 0.30f, 0.45f, 0.90f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.50f, 0.42f, 0.95f, 1.00f);
}

// -------------------------------------------------------------
// Interactive HUD Watermark (Top-Left Pill Capsule)
// -------------------------------------------------------------
void Menu::RenderWatermark() {
    if (!misc.watermark) return;

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* drawList = ImGui::GetForegroundDrawList();

    time_t rawtime;
    struct tm* timeinfo;
    char timeBuffer[16];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timeinfo);

    char bannerText[128];
    snprintf(bannerText, sizeof(bannerText), "ZENIN  |  FPS: %.0f  |  Ping: %dms  |  %s  |  v0.17",
             io.Framerate, misc.pingSpoof ? misc.pingSpoofValue : 14, timeBuffer);

    ImVec2 textSize = ImGui::CalcTextSize(bannerText);
    ImVec2 pad = ImVec2(16, 8);
    ImVec2 pos = ImVec2(24, 20);
    ImVec2 pMax = ImVec2(pos.x + textSize.x + pad.x * 2 + 16, pos.y + textSize.y + pad.y * 2);

    // Invisible trigger button behind watermark
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(ImVec2(pMax.x - pos.x, pMax.y - pos.y));
    ImGuiWindowFlags wmFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    
    ImGui::Begin("##WatermarkOverlay", nullptr, wmFlags);
    if (ImGui::InvisibleButton("##WatermarkBtn", ImVec2(pMax.x - pos.x, pMax.y - pos.y))) {
        isOpen = !isOpen; // Tap to toggle menu!
    }
    bool isHovered = ImGui::IsItemHovered();
    ImGui::End();

    // Render glassmorphic pill background
    ImU32 bgCol = isHovered ? IM_COL32(22, 24, 38, 245) : IM_COL32(12, 14, 22, (int)(misc.watermarkAlpha * 255));
    ImU32 borderCol = isHovered ? IM_COL32(140, 120, 255, 255) : IM_COL32(70, 65, 105, 220);

    drawList->AddRectFilled(pos, pMax, bgCol, 8.0f);
    drawList->AddRect(pos, pMax, borderCol, 8.0f, 0, 1.5f);
    
    // Pulsing live status dot
    float pulse = (sinf((float)ImGui::GetTime() * 4.0f) + 1.0f) * 0.5f;
    ImU32 dotCol = IM_COL32(125, 95 + (int)(pulse * 40), 255, 255);
    drawList->AddCircleFilled(ImVec2(pos.x + 14, pos.y + pad.y + textSize.y * 0.5f), 4.0f, dotCol);
    drawList->AddCircle(ImVec2(pos.x + 14, pos.y + pad.y + textSize.y * 0.5f), 4.0f + pulse * 2.5f, IM_COL32(140, 110, 255, (int)((1.0f - pulse) * 180)), 16, 1.5f);

    drawList->AddText(ImVec2(pos.x + 26, pos.y + pad.y), IM_COL32(245, 245, 255, 255), bannerText);
}

// -------------------------------------------------------------
// Interactive 3D Wireframe Mesh Engine & Wear-Bracket Bar
// -------------------------------------------------------------
struct Vec3D { float x, y, z; };

static ImVec2 Project3D(const Vec3D& v, const ImVec2& center, float scale, float rotX, float rotY) {
    // Rotate Y (Yaw)
    float cosY = cosf(rotY), sinY = sinf(rotY);
    float x1 = v.x * cosY + v.z * sinY;
    float z1 = -v.x * sinY + v.z * cosY;

    // Rotate X (Pitch)
    float cosX = cosf(rotX), sinX = sinX = sinf(rotX);
    float y2 = v.y * cosX - z1 * sinX;
    float z2 = v.y * sinX + z1 * cosX;

    // Perspective Projection
    float dist = 3.5f;
    float factor = scale / (z2 + dist);
    return ImVec2(center.x + x1 * factor, center.y - y2 * factor);
}

static void DrawSkinInspectCard(SkinItem& item, const ImVec2& size, float& rotX, float& rotY, bool autoRot) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(p0.x + size.x, p0.y + size.y);

    // Interactive Drag to Rotate 3D Model
    ImGui::InvisibleButton("##InspectDrag", size);
    bool isHovered = ImGui::IsItemHovered();
    bool isActive = ImGui::IsItemActive();
    if (isActive) {
        ImGuiIO& io = ImGui::GetIO();
        rotY += io.MouseDelta.x * 0.015f;
        rotX += io.MouseDelta.y * 0.015f;
    } else if (autoRot) {
        rotY += 0.008f;
    }

    // Card Background Gradient
    ImU32 colTop = IM_COL32(18, 20, 32, 255);
    ImU32 colBottom = IM_COL32(10, 11, 18, 255);
    drawList->AddRectFilledMultiColor(p0, p1, colTop, colTop, colBottom, colBottom);

    // Rarity Color Left Border Accent
    ImU32 rarityCol = GetRarityColor(item.rarity);
    drawList->AddRectFilled(p0, ImVec2(p0.x + 4.0f, p1.y), rarityCol, 6.0f);
    drawList->AddRect(p0, p1, isHovered ? IM_COL32(80, 85, 125, 255) : IM_COL32(40, 44, 65, 200), 8.0f, 0, 1.5f);

    // Background Subtle Tech Grid
    for (float x = p0.x + 25; x < p1.x; x += 30)
        drawList->AddLine(ImVec2(x, p0.y + 4), ImVec2(x, p1.y - 4), IM_COL32(255, 255, 255, 4));
    for (float y = p0.y + 20; y < p1.y; y += 30)
        drawList->AddLine(ImVec2(p0.x + 4, y), ImVec2(p1.x - 4), y, IM_COL32(255, 255, 255, 4));

    // ---------------------------------------------------------
    // 3D Knife / Weapon Mesh Model (Curved Karambit Geometry)
    // ---------------------------------------------------------
    ImVec2 meshCenter = ImVec2((p0.x + p1.x) * 0.5f, (p0.y + p1.y) * 0.45f);
    float meshScale = 140.0f;

    // 3D Vertices defining blade curvature, spine, handle, and finger ring
    Vec3D verts[] = {
        { -0.9f, -0.1f,  0.00f }, // 0: Ring base
        { -0.6f, -0.05f, 0.05f }, // 1: Handle start
        { -0.2f,  0.02f, 0.04f }, // 2: Handle grip
        {  0.1f,  0.10f, 0.03f }, // 3: Guard
        {  0.4f,  0.22f, 0.02f }, // 4: Blade spine mid
        {  0.8f,  0.05f, 0.01f }, // 5: Blade curve tip
        {  0.5f, -0.15f, 0.02f }, // 6: Cutting edge mid
        {  0.1f, -0.08f, 0.03f }, // 7: Choil
        { -0.6f, -0.05f,-0.05f }, // 8: Handle back side
        { -0.2f,  0.02f,-0.04f }, // 9: Grip back side
        {  0.1f,  0.10f,-0.03f }, // 10: Guard back side
        {  0.4f,  0.22f,-0.02f }  // 11: Blade spine back side
    };
    int nVerts = sizeof(verts) / sizeof(verts[0]);
    ImVec2 p[12];
    for (int i = 0; i < nVerts; ++i) {
        p[i] = Project3D(verts[i], meshCenter, meshScale, rotX, rotY);
    }

    // Shaded facets with dynamic lighting
    ImU32 bladeFill = IM_COL32(110, 85, 225, 45);
    ImU32 bladeGlow = IM_COL32(145, 125, 255, 240);
    ImU32 handleFill = IM_COL32(35, 38, 55, 160);

    drawList->AddTriangleFilled(p[3], p[4], p[6], bladeFill);
    drawList->AddTriangleFilled(p[4], p[5], p[6], bladeFill);
    drawList->AddTriangleFilled(p[1], p[2], p[7], handleFill);

    // Neon edge lines
    drawList->AddLine(p[3], p[4], bladeGlow, 2.0f);
    drawList->AddLine(p[4], p[5], bladeGlow, 2.0f);
    drawList->AddLine(p[5], p[6], bladeGlow, 2.0f);
    drawList->AddLine(p[6], p[7], bladeGlow, 1.8f);
    drawList->AddLine(p[7], p[3], bladeGlow, 1.8f);

    drawList->AddLine(p[0], p[1], IM_COL32(90, 95, 130, 220), 1.8f);
    drawList->AddLine(p[1], p[2], IM_COL32(90, 95, 130, 220), 1.8f);
    drawList->AddLine(p[2], p[3], IM_COL32(90, 95, 130, 220), 1.8f);
    drawList->AddCircle(p[0], 12.0f, IM_COL32(130, 115, 255, 220), 16, 2.0f);

    // Title & Skin Rarity Header
    char title[128];
    snprintf(title, sizeof(title), "%s  |  %s", item.weaponName.c_str(), item.skinName.c_str());
    drawList->AddText(ImVec2(p0.x + 16, p0.y + 12), IM_COL32(245, 245, 255, 255), title);

    // StatTrak Counter Badge
    if (item.statTrack) {
        char stBuf[32];
        snprintf(stBuf, sizeof(stBuf), "StatTrak™ %06d", item.statTrackCount);
        ImVec2 stPos = ImVec2(p0.x + 16, p0.y + 36);
        drawList->AddRectFilled(stPos, ImVec2(stPos.x + 130, stPos.y + 20), IM_COL32(220, 100, 15, 230), 4.0f);
        drawList->AddText(ImVec2(stPos.x + 8, stPos.y + 3), IM_COL32(255, 255, 255, 255), stBuf);
    }

    // ---------------------------------------------------------
    // CS2 Wear-Condition Bracket Bar [FN | MW | FT | WW | BS]
    // ---------------------------------------------------------
    float barW = size.x - 32.0f;
    float barH = 7.0f;
    ImVec2 barPos = ImVec2(p0.x + 16, p1.y - 36);

    // Brackets: FN (0-0.07), MW (0.07-0.15), FT (0.15-0.38), WW (0.38-0.45), BS (0.45-1.0)
    float bFN = barW * 0.07f;
    float bMW = barW * 0.15f;
    float bFT = barW * 0.38f;
    float bWW = barW * 0.45f;

    drawList->AddRectFilled(barPos, ImVec2(barPos.x + bFN, barPos.y + barH), IM_COL32(75, 185, 95, 255)); // Green (FN)
    drawList->AddRectFilled(ImVec2(barPos.x + bFN, barPos.y), ImVec2(barPos.x + bMW, barPos.y + barH), IM_COL32(120, 205, 75, 255)); // Lime (MW)
    drawList->AddRectFilled(ImVec2(barPos.x + bMW, barPos.y), ImVec2(barPos.x + bFT, barPos.y + barH), IM_COL32(235, 180, 50, 255)); // Orange (FT)
    drawList->AddRectFilled(ImVec2(barPos.x + bFT, barPos.y), ImVec2(barPos.x + bWW, barPos.y + barH), IM_COL32(230, 110, 45, 255)); // Deep Orange (WW)
    drawList->AddRectFilled(ImVec2(barPos.x + bWW, barPos.y), ImVec2(barPos.x + barW, barPos.y + barH), IM_COL32(210, 60, 60, 255)); // Red (BS)

    // Current Float Pointer Arrow
    float pointerX = barPos.x + barW * std::clamp(item.wear, 0.0f, 1.0f);
    drawList->AddTriangleFilled(ImVec2(pointerX, barPos.y - 1), ImVec2(pointerX - 4, barPos.y - 6), ImVec2(pointerX + 4, barPos.y - 6), IM_COL32(255, 255, 255, 255));

    // Float Value & Condition String
    const char* wearName = "Factory New";
    if (item.wear > 0.45f) wearName = "Battle-Scarred";
    else if (item.wear > 0.38f) wearName = "Well-Worn";
    else if (item.wear > 0.15f) wearName = "Field-Tested";
    else if (item.wear > 0.07f) wearName = "Minimal Wear";

    char wearLabel[96];
    snprintf(wearLabel, sizeof(wearLabel), "%s (Float: %.5f)  |  Seed: %d", wearName, item.wear, item.seed);
    drawList->AddText(ImVec2(p0.x + 16, p1.y - 24), IM_COL32(170, 175, 195, 255), wearLabel);

    if (!item.charmName.empty() && item.charmName != "None") {
        char charmBuf[64];
        snprintf(charmBuf, sizeof(charmBuf), "Charm: %s", item.charmName.c_str());
        drawList->AddText(ImVec2(p1.x - 170, p1.y - 24), IM_COL32(190, 170, 250, 255), charmBuf);
    }
}

// -------------------------------------------------------------
// Main Zenin Window Render Function
// -------------------------------------------------------------
void Menu::Render() {
    RenderWatermark();

    if (!isOpen) return;

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(870, 560), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f - 435, io.DisplaySize.y * 0.5f - 280), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    if (ImGui::Begin("Zenin  |  Standoff 2 (CS2 Engine)", &isOpen, flags)) {

        // Top Horizontal Tabs with Violet Accent Pills
        ImGui::BeginChild("##TabBar", ImVec2(0, 48), true, ImGuiWindowFlags_NoScrollbar);
        const char* tabs[] = { "Aimbot", "Visuals", "Skinchanger", "World & FX", "Misc", "Profiles" };
        for (int i = 0; i < 6; ++i) {
            if (i > 0) ImGui::SameLine();
            bool isCurrent = (activeTab == i);
            if (isCurrent) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.48f, 0.40f, 0.93f, 0.95f));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.13f, 0.22f, 0.80f));
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.72f, 0.74f, 0.86f, 1.0f));
            }
            if (ImGui::Button(tabs[i], ImVec2(133, 34))) {
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
            ImGui::SetColumnWidth(0, 415);

            ImGui::BeginChild("##AimGeneral", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● AIMBOT TARGETING");
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

            const char* bones[] = { "Head Only", "Neck", "Upper Chest", "Pelvis" };
            ImGui::Combo("Target Hitbox", &aimbot.targetBone, bones, IM_ARRAYSIZE(bones));
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##AimRecoil", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● RECOIL COMPENSATION (RCS) & CHECKS");
            ImGui::Separator();
            ImGui::Checkbox("Visible Check", &aimbot.checkVisible);
            ImGui::Checkbox("Smoke Check", &aimbot.checkSmoke);
            ImGui::Checkbox("Flashbang Check", &aimbot.checkFlash);

            ImGui::Spacing();
            ImGui::Checkbox("Recoil Compensation System", &aimbot.rcsEnabled);
            if (aimbot.rcsEnabled) {
                ImGui::SliderFloat("RCS Pitch Compensation", &aimbot.rcsPitch, 0.0f, 2.0f, "%.2f");
                ImGui::SliderFloat("RCS Yaw Compensation", &aimbot.rcsYaw, 0.0f, 2.0f, "%.2f");
            }
            ImGui::EndChild();
            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 1: VISUALS (ESP & CHAMS)
        // -------------------------------------------------------------
        else if (activeTab == 1) {
            ImGui::Columns(2, "VisualsCol", false);
            ImGui::SetColumnWidth(0, 415);

            ImGui::BeginChild("##PlayerEsp", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● PLAYER OVERLAY & ESP");
            ImGui::Separator();
            ImGui::Checkbox("Enable Visuals", &visuals.enabled);
            ImGui::Checkbox("Enemies Only", &visuals.enemyOnly);
            ImGui::Checkbox("Bounding Box", &visuals.boxEsp);
            
            const char* boxStyles[] = { "2D Full Outline", "2D Cornered Box", "3D Wireframe Box" };
            ImGui::Combo("Box Style", &visuals.boxType, boxStyles, IM_ARRAYSIZE(boxStyles));
            ImGui::SliderFloat("Box Thickness", &visuals.boxThickness, 1.0f, 3.5f, "%.1f px");

            ImGui::Checkbox("Player Skeleton Wireframe", &visuals.skeleton);
            ImGui::Checkbox("Health Bar Indicator", &visuals.healthBar);
            ImGui::Checkbox("Armor Bar Indicator", &visuals.armorBar);
            ImGui::Checkbox("Active Weapon Name", &visuals.weaponName);
            ImGui::Checkbox("Distance Tag", &visuals.distanceTag);
            ImGui::Checkbox("Head Target Dot", &visuals.headDot);
            ImGui::Checkbox("Snaplines", &visuals.snaplines);

            ImGui::Spacing();
            ImGui::ColorEdit4("Box Color", visuals.boxColor);
            ImGui::ColorEdit4("Skeleton Color", visuals.skeletonColor);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##ChamsBlock", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● CHAMS SHADERS & LIGHTING");
            ImGui::Separator();
            ImGui::Checkbox("Enable Chams", &visuals.chamsEnabled);
            ImGui::Checkbox("Show Behind Walls (Occlusion)", &visuals.showBehindWalls);
            ImGui::Checkbox("Zenin Chams Bloom FX", &visuals.bloom);

            const char* chamsStyles[] = { "Disabled", "Flat Solid", "Glossy / Fresnel", "Crystal Iridescent", "Wireframe Grid" };
            ImGui::Combo("Material Shader", &visuals.chamsStyle, chamsStyles, IM_ARRAYSIZE(chamsStyles));

            if (visuals.chamsStyle == 2) {
                ImGui::SliderFloat("Glossiness", &visuals.glossyGloss, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat("Fresnel Power", &visuals.glossyFresnel, 0.0f, 1.0f, "%.2f");
            } else if (visuals.chamsStyle == 3) {
                ImGui::SliderFloat("Crystal Reflectivity", &visuals.crystalReflectivity, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat("Hue Spread", &visuals.crystalHueSpread, 0.0f, 1.0f, "%.2f");
            } else if (visuals.chamsStyle == 4) {
                ImGui::SliderFloat("Wire Thickness", &visuals.wireThickness, 0.5f, 5.0f, "%.1f px");
            }

            ImGui::Spacing();
            ImGui::ColorEdit4("Visible Geometry Color", visuals.chamsVisibleColor);
            ImGui::ColorEdit4("Occluded Geometry Color", visuals.chamsHiddenColor);
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 2: SKINS (CS2 & STANDOFF 2)
        // -------------------------------------------------------------
        else if (activeTab == 2) {
            ImGui::Columns(2, "SkinCol", false);
            ImGui::SetColumnWidth(0, 310);

            ImGui::BeginChild("##SkinList", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● INVENTORY ROSTER");
            ImGui::Separator();

            const char* cats[] = { "Knives (20 CS2 / SO2)", "Weapons & Gloves (14)" };
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

            ImGui::BeginChild("##SkinInspect", ImVec2(0, 430), true);
            std::vector<SkinItem>& list2 = (skinchanger.selectedCategory == 0) ? skinchanger.knifeCatalog : skinchanger.weaponCatalog;
            if (skinchanger.selectedIndex >= 0 && skinchanger.selectedIndex < (int)list2.size()) {
                SkinItem& item = list2[skinchanger.selectedIndex];

                // 3D Wireframe Rotating Inspect Viewport with Wear-Condition Bar
                DrawSkinInspectCard(item, ImVec2(ImGui::GetContentRegionAvail().x, 210), skinchanger.modelRotX, skinchanger.modelRotY, skinchanger.autoRotate);

                ImGui::Spacing();
                ImGui::Checkbox("Auto-Rotate 3D Preview", &skinchanger.autoRotate);

                ImGui::Spacing();
                ImGui::SliderFloat("Float Wear Value", &item.wear, 0.0001f, 1.0000f, "%.5f");
                ImGui::SliderInt("Pattern Seed", &item.seed, 1, 1000);

                ImGui::Checkbox("StatTrak™ Module", &item.statTrack);
                if (item.statTrack) {
                    ImGui::SameLine();
                    ImGui::InputInt("Confirmed Kills", &item.statTrackCount);
                }

                // 4 Interactive Sticker Slots
                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.70f, 0.65f, 0.95f, 1.0f), "Sticker Slots:");
                for (int s = 0; s < 4; ++s) {
                    if (s > 0) ImGui::SameLine();
                    char stBtn[32];
                    snprintf(stBtn, sizeof(stBtn), "Slot %d##%d", s + 1, s);
                    ImGui::Button(stBtn, ImVec2(78, 26));
                }
            }
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 3: WORLD & ATMOSPHERE
        // -------------------------------------------------------------
        else if (activeTab == 3) {
            ImGui::Columns(2, "WorldCol", false);
            ImGui::SetColumnWidth(0, 415);

            ImGui::BeginChild("##WeatherBox", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● DYNAMIC WEATHER SIMULATION");
            ImGui::Separator();
            ImGui::Checkbox("Zenin Weather: Falling Snow", &world.weatherSnow);
            if (world.weatherSnow) {
                ImGui::Indent();
                ImGui::Checkbox("Snow Wind Dynamics", &world.snowWind);
                ImGui::Checkbox("Snow Ambient Sound", &world.snowSound);
                ImGui::SliderFloat("Snow Flake Density", &world.snowDensity, 0.1f, 1.0f);
                ImGui::Unindent();
            }

            ImGui::Spacing();
            ImGui::Checkbox("Zenin Weather: Rain & Reflections", &world.weatherRain);
            if (world.weatherRain) {
                ImGui::Indent();
                ImGui::SliderFloat("Rain Intensity", &world.rainFall, 0.1f, 1.0f);
                ImGui::SliderFloat("Surface Splash FX", &world.rainSplash, 0.1f, 1.0f);
                ImGui::Unindent();
            }

            ImGui::Spacing();
            ImGui::Checkbox("Zenin Night Shadows", &world.nightShadows);
            ImGui::Checkbox("Fog Wisps Effect", &world.fogWisps);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##PostFxBox", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● POST-PROCESSING SHADERS & FOV");
            ImGui::Separator();
            ImGui::SliderFloat("Scope Field of View (FOV)", &world.scopeFov, 60.0f, 130.0f, "%.1f°");
            ImGui::SliderFloat("Summer Ivy Density", &world.summerIvyAmount, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Film Grain Intensity (_ZPGrainTex)", &world.grainIntensity, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Vignette Smoothness (ZP_VIGNETTE)", &world.vignetteSmoothness, 0.0f, 1.0f, "%.2f");
            ImGui::SliderFloat("Chromatic Aberration (_ZPChromaticAmount)", &world.chromaticAmount, 0.0f, 0.5f, "%.2f");

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
            ImGui::SetColumnWidth(0, 415);

            ImGui::BeginChild("##WatermarkSettings", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● WATERMARK & HUD CONTROLS");
            ImGui::Separator();
            ImGui::Checkbox("Show Watermark Banner", &misc.watermark);
            ImGui::Checkbox("Display FPS Counter", &misc.watermarkFps);
            ImGui::Checkbox("Display Ping Counter", &misc.watermarkPing);
            ImGui::Checkbox("Display Real Time", &misc.watermarkTime);
            ImGui::Checkbox("Display Version Code", &misc.watermarkVersion);
            ImGui::SliderFloat("Watermark Opacity", &misc.watermarkAlpha, 0.2f, 1.0f, "%.2f");

            ImGui::Spacing();
            ImGui::Checkbox("Bomb Timer Indicator", &misc.bombTimer);
            ImGui::Checkbox("Zenin Jump Circle Particle FX", &misc.jumpCircle);
            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##NetworkAndAudio", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● NETWORK SPOOFING & HITMARKERS");
            ImGui::Separator();
            ImGui::Checkbox("Network Ping Spoofing", &misc.pingSpoof);
            if (misc.pingSpoof) {
                ImGui::SliderInt("Spoofed Ping Value (ms)", &misc.pingSpoofValue, 1, 99);
            }

            ImGui::Spacing();
            ImGui::Checkbox("Custom Hitmarker Effect", &misc.hitMarker);
            const char* hitSounds[] = { "Disabled", "Skeet Crack", "Rust Headshot", "Bell Ding" };
            ImGui::Combo("Hit Sound FX", &misc.hitMarkerSound, hitSounds, IM_ARRAYSIZE(hitSounds));

            ImGui::Spacing();
            ImGui::SliderFloat("Scrollbar Width", &misc.scrollbarSize, 4.0f, 12.0f, "%.0f px");
            ImGui::EndChild();

            ImGui::Columns(1);
        }
        // -------------------------------------------------------------
        // TAB 5: PROFILES
        // -------------------------------------------------------------
        else if (activeTab == 5) {
            ImGui::BeginChild("##ProfilesBox", ImVec2(0, 430), true);
            ImGui::TextColored(ImVec4(0.60f, 0.52f, 1.0f, 1.0f), "● ZENIN LOCAL CONFIGURATION MANAGER");
            ImGui::Separator();

            for (size_t i = 0; i < configs.profileList.size(); ++i) {
                bool isSelected = (configs.activeIndex == (int)i);
                if (ImGui::Selectable(configs.profileList[i].c_str(), isSelected)) {
                    configs.activeIndex = (int)i;
                }
            }

            ImGui::Spacing();
            ImGui::Separator();
            if (ImGui::Button("Load Configuration", ImVec2(165, 34))) {
                // Profile loaded
            }
            ImGui::SameLine();
            if (ImGui::Button("Save Configuration", ImVec2(165, 34))) {
                // Profile saved
            }

            ImGui::Spacing();
            ImGui::InputText("New Profile Name", configs.profileInput, sizeof(configs.profileInput));
            ImGui::SameLine();
            if (ImGui::Button("Create Profile", ImVec2(140, 28))) {
                configs.profileList.push_back(std::string(configs.profileInput) + ".cfg");
            }
            ImGui::EndChild();
        }
    }
    ImGui::End();
}

} // namespace Zenin
