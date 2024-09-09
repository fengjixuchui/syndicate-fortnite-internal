#include "OffsetFinder.h"

uintptr_t OffsetFinder::World = 0;
uintptr_t OffsetFinder::OwningGameInstance = 0;
uintptr_t OffsetFinder::LocalPlayers = 0;
uintptr_t OffsetFinder::ViewportClient = 0;
uintptr_t OffsetFinder::BaseCharacterParts = 0;
uintptr_t OffsetFinder::CharacterPartType = 0;
uintptr_t OffsetFinder::LocalCharacterParts = 0;
uintptr_t OffsetFinder::Mesh = 0;
uintptr_t OffsetFinder::bIsReloadingWeapon = 0;
uintptr_t OffsetFinder::ItemName = 0;
uintptr_t OffsetFinder::bAlreadySearched = 0;
uintptr_t OffsetFinder::UAthenaPickaxeItemDefinition_WeaponDefinition = 0;
uintptr_t OffsetFinder::CosmeticData = 0;
uintptr_t OffsetFinder::MaxTargetingAimAdjustPerSecond = 0;

uintptr_t OffsetFinder::find_offset(const wchar_t* Class, const wchar_t* Field) {
    auto object = Core.pFindObject(Class);
    if (object) {
        for (auto Property = *(uint64_t*)(object + 0x50); Property != 0; Property = *(uint64_t*)(Property + 0x18)) {
            auto PropertyName = *(FName*)(Property + 0x20);
            auto Offset = *(DWORD*)(Property + 0x3C);
            auto NameIndex = PropertyName.comparison_index;
            auto FieldIndex = SDK.Conv_StringToName(Field).comparison_index;

            if (NameIndex > 0 && Offset != 0) {
                if (NameIndex == FieldIndex) {
                    return Offset;
                }
            }
        }
    }
    return 0; // Return 0 if offset is not found
}

//void PrintOffsets(const wchar_t* Class, const wchar_t* Field, bool justOffset = false) {
//	auto offset = OffsetFinder::find_offset(Class, Field);
//	if (offset) {
//        if (justOffset) {
//			dbgprint(L"[DUMPER] 0x%X", offset);
//			return;
//		}
//		dbgprint(L"[DUMPER] %s = 0x%X,\n", Field, offset);
//	}
//	else {
//        dbgprint(L"[DUMPER] %s -> %s: Not found\n", Class, Field);
//	}
//}

void OffsetFinder::fetch_offsets() {
    World = find_offset(xor_w(L"GameViewportClient"), xor_w(L"World"));
    OwningGameInstance = find_offset(xor_w(L"World"), xor_w(L"OwningGameInstance"));
    LocalPlayers = find_offset(xor_w(L"GameInstance"), xor_w(L"LocalPlayers"));
    ViewportClient = find_offset(xor_w(L"LocalPlayer"), xor_w(L"ViewportClient"));
    BaseCharacterParts = find_offset(xor_w(L"AthenaCharacterItemDefinition"), xor_w(L"BaseCharacterParts"));
    CharacterPartType = find_offset(xor_w(L"CustomCharacterPart"), xor_w(L"CharacterPartType"));
    LocalCharacterParts = find_offset(xor_w(L"FortPlayerState"), xor_w(L"LocalCharacterParts"));
    Mesh = find_offset(xor_w(L"Character"), xor_w(L"Mesh"));
    bIsReloadingWeapon = find_offset(xor_w(L"FortWeapon"), xor_w(L"bIsReloadingWeapon"));
    ItemName = find_offset(xor_w(L"ItemDefinitionBase"), xor_w(L"ItemName"));
    bAlreadySearched = find_offset(xor_w(L"BuildingContainer"), xor_w(L"bAlreadySearched"));
    UAthenaPickaxeItemDefinition_WeaponDefinition = find_offset(xor_w(L"AthenaPickaxeItemDefinition"), xor_w(L"WeaponDefinition"));
    CosmeticData = find_offset(xor_w(L"FortWeaponPickaxeAthena"), xor_w(L"CosmeticData"));
    MaxTargetingAimAdjustPerSecond = find_offset(xor_w(L"FortWeaponRanged"), xor_w(L"MaxTargetingAimAdjustPerSecond"));


    // Special offsets:

    //PrintOffsets(L"World", L"OwningGameInstance");
    //PrintOffsets(L"World", L"GameState");
    //PrintOffsets(L"Actor", L"RootComponent");
    //PrintOffsets(L"World", L"PersistentLevel");
    //PrintOffsets(L"Player", L"PlayerController");
    //PrintOffsets(L"GameStateBase", L"PlayerArray");
    //PrintOffsets(L"Level", L"WorldSettings");
    //PrintOffsets(L"GameInstance", L"LocalPlayers");
    //PrintOffsets(L"PlayerController", L"AcknowledgedPawn");
    //PrintOffsets(L"FortPlayerController", L"TargetedFortPawn");
    //PrintOffsets(L"PlayerController", L"PlayerInput");

    //dbgprint(L"[DUMPER] PlayerController_FOV = ");
    //PrintOffsets(L"PlayerController", L"SmoothTargetViewRotationSpeed", true); dbgprint(L"[DUMPER] +0x4,");

    //dbgprint(L"[DUMPER] HiddenInput = "); PrintOffsets(L"PlayerInput", L"InvertedAxis", true); dbgprint(L"[DUMPER] +0x100,\n");

    //PrintOffsets(L"PlayerState", L"PawnPrivate");
    //PrintOffsets(L"FortPlayerStateAthena", L"TeamIndex");
    //PrintOffsets(L"PlayerState", L"bIsABot");
    //PrintOffsets(L"FortPlayerStateAthena", L"KillScore");
    //PrintOffsets(L"FortPlayerState", L"Platform");
    //PrintOffsets(L"FortPawn", L"CurrentWeapon");
    //PrintOffsets(L"Character", L"Mesh");
    //PrintOffsets(L"Character", L"CharacterMovement");
    //PrintOffsets(L"CharacterMovementComponent", L"LastUpdateVelocity");
    //PrintOffsets(L"FortWeapon", L"WeaponData");
    //PrintOffsets(L"FortTandemCharacterData", L"DisplayName");
    //PrintOffsets(L"FortItemDefinition", L"Rarity");
    //PrintOffsets(L"PrimitiveComponent", L"bRenderCustomDepth");
    //PrintOffsets(L"PrimitiveComponent", L"CustomDepthStencilValue");

    //PrintOffsets(L"FortPlayerPawn", L"CharacterPartSkeletalMeshComponents");

    //PrintOffsets(L"FortPawn", L"bIsDying");
    //PrintOffsets(L"FortPawn", L"bIsDBNO");
    //PrintOffsets(L"SceneComponent", L"RelativeLocation");
    //PrintOffsets(L"FortAthenaVehicle", L"bUseGravity");
    //PrintOffsets(L"FortAthenaVehicle", L"bAllowInteractBetweenFortVolumes");
    //PrintOffsets(L"FortAthenaVehicle", L"CachedFuelComponent");
    //PrintOffsets(L"FortVehicleFuelComponent", L"ServerFuel");
    //PrintOffsets(L"FortPlayerPawn", L"CurrentVehicle");
}
