#pragma once
#include <string>
#include <vector>

namespace Zenin {

// -------------------------------------------------------------
// Rarity Grades matching CS2 / Standoff 2
// -------------------------------------------------------------
enum class ItemRarity {
    Covert,     // Red (#eb4b4b)
    Classified, // Pink (#d32ce6)
    Restricted, // Purple (#8847ff)
    MilSpec,    // Blue (#4b69ff)
    Extraordinary // Gold (#ffd700) for Knives & Gloves
};

struct SkinItem {
    std::string category;
    std::string weaponName;
    std::string skinName;
    ItemRarity rarity;
    int skinId;
    float wear;
    int seed;
    bool statTrack;
    int statTrackCount;
    std::string charmName;
    int stickerIds[4];
    float stickerWear[4];
};

struct AimbotConfig {
    bool enabled = false;
    bool silentAim = false;
    bool autoFire = false;
    bool autoScope = true;
    bool autoStopOnLand = true;
    bool lethalShot = false;
    float fov = 8.5f;
    float smooth = 3.5f;
    int targetBone = 0; // 0: Head, 1: Neck, 2: Chest, 3: Pelvis
    bool checkVisible = true;
    bool checkSmoke = true;
    bool checkFlash = true;
    bool rcsEnabled = true;
    float rcsPitch = 1.0f;
    float rcsYaw = 1.0f;
    int hitGroup = 0; // 0: All, 1: Upper Body, 2: Head Only
};

struct VisualsConfig {
    bool enabled = true;
    bool enemyOnly = true;
    
    // ESP
    bool boxEsp = true;
    int boxType = 1; // 0: 2D Full, 1: 2D Cornered, 2: 3D Box
    bool skeleton = true;
    bool healthBar = true;
    bool armorBar = true;
    bool weaponName = true;
    bool distanceTag = true;
    bool playerNames = true;
    bool snaplines = false;
    bool headDot = true;
    float boxThickness = 1.5f;

    // Colors
    float boxColor[4] = { 0.45f, 0.45f, 1.00f, 1.00f };
    float skeletonColor[4] = { 1.00f, 1.00f, 1.00f, 0.90f };
    float lethalColor[4] = { 1.00f, 0.20f, 0.20f, 1.00f };
    float pointColor[4] = { 0.20f, 1.00f, 0.40f, 1.00f };
    float startColor[4] = { 0.48f, 0.40f, 0.93f, 1.00f };

    // Chams
    bool chamsEnabled = true;
    int chamsStyle = 2; // 0: Disabled, 1: Flat, 2: Glossy, 3: Crystal, 4: Wireframe
    float wireThickness = 1.5f;
    float glossyGloss = 0.85f;
    float glossyFresnel = 0.50f;
    float crystalReflectivity = 0.70f;
    float crystalHueSpread = 0.35f;
    bool bloom = true;
    bool showBehindWalls = true;
    float chamsVisibleColor[4] = { 0.48f, 0.40f, 0.93f, 1.00f };
    float chamsHiddenColor[4] = { 0.90f, 0.15f, 0.35f, 0.75f };
};

struct WorldFxConfig {
    float scopeFov = 95.0f;
    bool weatherSnow = false;
    bool weatherRain = false;
    bool snowWind = true;
    bool snowSound = false;
    float snowDensity = 0.65f;
    float rainFall = 0.50f;
    float rainSplash = 0.40f;
    float summerIvyAmount = 0.25f;
    float grainIntensity = 0.12f;
    float vignetteSmoothness = 0.30f;
    float chromaticAmount = 0.08f;
    bool nightShadows = false;
    bool fogWisps = false;
    float fogColor[4] = { 0.12f, 0.14f, 0.22f, 1.00f };
    float skyboxColor[4] = { 0.08f, 0.09f, 0.14f, 1.00f };
};

struct SkinchangerConfig {
    bool enabled = true;
    int selectedCategory = 0; // 0: Knives, 1: Gloves, 2: Rifles, 3: Snipers, 4: Pistols
    int selectedIndex = 0;
    char searchFilter[64] = "";
    float modelRotX = 0.3f;
    float modelRotY = 0.8f;
    bool autoRotate = true;
    std::vector<SkinItem> knifeCatalog;
    std::vector<SkinItem> weaponCatalog;
};

struct MiscConfig {
    bool watermark = true;
    int watermarkProductType = 0; // 0: Zenin Alpha, 1: Zenin Release, 2: Minimalist
    bool watermarkFps = true;
    bool watermarkPing = true;
    bool watermarkTime = true;
    bool watermarkVersion = true;
    float watermarkAlpha = 0.92f;
    
    bool pingSpoof = false;
    int pingSpoofValue = 14;
    bool jumpCircle = true;
    bool hitMarker = true;
    int hitMarkerSound = 1; // 0: Off, 1: Skeet, 2: Rust, 3: Bell
    bool bombTimer = true;
    float scrollbarSize = 6.0f;
};

struct ConfigManager {
    std::vector<std::string> profileList = { "Default.cfg", "Legit_MM.cfg", "Rage_HVH.cfg", "CS2_Showcase.cfg" };
    int activeIndex = 0;
    char profileInput[64] = "MyCustomConfig";
};

class Menu {
public:
    static Menu& Get();

    void InitStyle();
    void Render();
    void RenderWatermark();

    bool isOpen = true;
    AimbotConfig aimbot;
    VisualsConfig visuals;
    WorldFxConfig world;
    SkinchangerConfig skinchanger;
    MiscConfig misc;
    ConfigManager configs;

private:
    Menu();
    int activeTab = 0; // 0: Legitbot, 1: Visuals, 2: Skinchanger, 3: World & FX, 4: Misc, 5: Configs
};

} // namespace Zenin
