#pragma once
#include <string>
#include <vector>

namespace Zenin {

struct VisualSettings {
    bool enabled = true;
    int chamsType = 2; // 0: Disabled, 1: Flat, 2: Glossy, 3: Crystal, 4: Wireframe
    float wireThickness = 1.5f;
    float glossyGloss = 0.75f;
    float glossyFresnel = 0.45f;
    float crystalReflectivity = 0.60f;
    float crystalHueSpread = 0.30f;
    float chamsColorVisible[4] = { 0.20f, 0.75f, 1.00f, 1.00f };
    float chamsColorHidden[4] = { 0.90f, 0.20f, 0.40f, 0.80f };

    bool boxEsp = true;
    bool healthBar = true;
    bool armorBar = true;
    bool weaponName = true;
    bool distanceText = true;
    float espColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
};

struct WorldSettings {
    bool enabled = false;
    float scopeFov = 90.0f;
    bool snowWind = false;
    float snowDensity = 0.5f;
    bool rainFall = false;
    float rainDensity = 0.4f;
    float summerIvyAmount = 0.2f;
    float grainIntensity = 0.15f;
    float vignetteSmoothness = 0.35f;
    float skyboxColor[4] = { 0.10f, 0.12f, 0.16f, 1.0f };
};

struct SkinItem {
    std::string name;
    int skinId;
    float wear;
    int statTrackCount;
    bool statTrackEnabled;
    int seed;
};

struct SkinchangerSettings {
    bool enabled = true;
    int selectedWeaponIndex = 0;
    std::vector<SkinItem> weapons;
};

struct ConfigManager {
    std::vector<std::string> profileNames = { "Default", "Legit_Competitive", "Rage_HVH", "Cinematic_Skins" };
    int selectedProfile = 0;
    char newProfileName[64] = "MyCustomConfig";
};

class Menu {
public:
    static Menu& Get();

    void InitStyle();
    void Render();

    bool isOpen = true;
    VisualSettings visuals;
    WorldSettings world;
    SkinchangerSettings skinchanger;
    ConfigManager configs;

private:
    Menu();
    int currentTab = 0; // 0: Visuals, 1: Skinchanger, 2: World, 3: Profiles, 4: Info
};

} // namespace Zenin
