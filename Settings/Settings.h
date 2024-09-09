#pragma once

struct config {
    struct Aimbot {
#ifndef RAID
        int AimKey = 2;
#else
        bool AimKey = true;
#endif
        bool AutoFOV = false;
        bool VisCheck = true;
        bool CloseAim = false;
        int FOVRange = 250;
        int Smooth = 7;
        int SpectateSmooth = 7;
        int BoneTarget = 1;
        bool ProjectilePrediction = true;
#ifndef RAID
        int TriggerKey = 0;
#else
        bool TriggerKey = false;
#endif
        bool KnockedCheck = true;
        bool ShotgunOnlyTrigger = false;
        bool AlwaysTrigger = false;
    } Aimbot;

    struct Visuals {
        bool Enabled = true;
        int OverallDistance = 500;
        bool Radar = true;
        bool Distance = true;
        bool Name = true;
        bool Box = false;
        bool BoxFill = true;
        bool CornerBox = true;
        bool Bones = true;
        bool Weapons = true;
        //bool Ammo = true;
        //bool AimLine = false;//TBA
        bool Kills = true;
        //bool DrawSelf = false;
        bool Platform = true;
#ifndef RAID
        int DrawFOV = 1;
#else
        bool DrawFOV = true;
#endif
        int RadarX = 50;
        int RadarY = 150;
        int RadarSize = 220.f;
        int RadarDotSize = 2.f;
        int RadarRange = 0.55f;
        int BoxSize = 3.f;
    } Visuals;

    struct World {
        bool Enabled = true;
        //int PickupDistance = 150;
        //int VehicleDistance = 150;
        //int ContainerDistance = 150;
        int WorldDistance = 250;
        int LlamaDistance = 0;
        bool Pickup = true;
        bool Chests = true;
        bool Vehicles = true;
        bool Trap = true;
        bool AmmoBox = false;
        bool Ammo = false;
        bool Llama = true;
        int LootMinimalTier = 2;
    } World;

    struct Misc {
        bool HudFocus = true;
        //bool NoRecoil = false;
        bool ShowMenu = true;
#ifndef RAID
        int PanicKey = 0;
#else
        bool PanicKey = false;
#endif
        bool ShowCounter = true;
        int ColorVisible = 2;
        int ColorInvisible = 3;
        int ColorDowned = 4;
        int MenuKey = 2;
        int DevNumber = 0;
        //int LootPicker = 0;
        //int LootDestroyer = 0;
        bool Crosshair = true;
        //bool NoSpread = false;
        //bool PSilent = false;
        //bool PSilentShoty = false;
    } Misc;

    struct InventoryChanger { // SWYZZ SKIN: Huntress Helsie
        bool Enabled = false;
        int Category = 1;

        uint64_t Character = 0;
        uint64_t Backpack = 0;
        uint64_t Pickaxe = 0;
    } InventoryChanger;

    struct WeaponConfig {
        int scwbone = 1, smgcwbone = 1, acwbone = 1, scwsm = 5, acwsm = 5, snprsm = 5, smgcwsm = 5, scwfov = 500, smgcwfov = 500, acwfov = 500, snprfov = 500;
        bool cwbone = false, cwfov = false, cwsm = false;
    } WeaponConfig;
};

extern config Config;