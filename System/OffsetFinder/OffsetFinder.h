#pragma once
#include "../../stdafx.h"

class OffsetFinder {
public:
    static uintptr_t find_offset(const wchar_t* Class, const wchar_t* Field);
    static void fetch_offsets();

    static uintptr_t World;
    static uintptr_t OwningGameInstance;
    static uintptr_t LocalPlayers;
    static uintptr_t ViewportClient;
    static uintptr_t BaseCharacterParts;
    static uintptr_t CharacterPartType;
    static uintptr_t LocalCharacterParts;
    static uintptr_t Mesh;
    static uintptr_t bIsReloadingWeapon;
    static uintptr_t ItemName;
    static uintptr_t bAlreadySearched;
    static uintptr_t UAthenaPickaxeItemDefinition_WeaponDefinition;
    static uintptr_t CosmeticData;
    static uintptr_t MaxTargetingAimAdjustPerSecond;
} inline Offsets;