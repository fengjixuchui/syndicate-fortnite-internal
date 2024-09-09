#include "SDK.h"

uint64_t SDK::K2_GetWorldSettings()
{
	static uint64_t fnK2_GetWorldSettings = NULL;
	if (!fnK2_GetWorldSettings) {
		fnK2_GetWorldSettings = Core.pFindObject(xor_w(L"World.K2_GetWorldSettings"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(Globals::World, fnK2_GetWorldSettings, &params);

	return params.ReturnValue;
}



// GameplayStatics //
uint64_t SDK::GetGameInstance()
{
	static uint64_t fnGetGameInstance = NULL;
	if (!fnGetGameInstance) {
		fnGetGameInstance = Core.pFindObject(xor_w(L"GameplayStatics.GetGameInstance"));
	}

	static uint64_t GameplayStatistics = Core.pFindObject(xor_w(L"Engine.Default__GameplayStatics"));

	struct {
		uint64_t WorldContextObject;
		uint64_t ReturnValue;
	} params;

	params.WorldContextObject = Globals::GWorld;

	ProcessEvent(GameplayStatistics, fnGetGameInstance, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetPlayerController()
{
	static uint64_t fnGetPlayerController = NULL;
	if (!fnGetPlayerController) {
		fnGetPlayerController = Core.pFindObject(xor_w(L"GameplayStatics.GetPlayerController"));
	}

	struct {
		uintptr_t WorldContextObject;
		int PlayerIndex;
		uint64_t ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;
	params.PlayerIndex = 0;

	ProcessEvent(Globals::UGameViewportClient, fnGetPlayerController, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetPlayerCameraManager()
{
	static uint64_t fnGetPlayerCameraManager = NULL;
	if (!fnGetPlayerCameraManager) {
		fnGetPlayerCameraManager = Core.pFindObject(xor_w(L"GameplayStatics.GetPlayerCameraManager"));
	}

	struct {
		uintptr_t WorldContextObject;
		int PlayerIndex;
		uint64_t ReturnValue;
	} params;

	params.WorldContextObject = Globals::World;
	params.PlayerIndex = 0;

	ProcessEvent(Globals::UGameViewportClient, fnGetPlayerCameraManager, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetPlayerState()
{
	static uint64_t fnGetPlayerState = NULL;
	if (!fnGetPlayerState) {
		fnGetPlayerState = Core.pFindObject(xor_w(L"GameplayStatics.GetPlayerState"));
	}

	struct {
		uintptr_t WorldContextObject;
		int PlayerStateIndex;
		uint64_t ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;
	params.PlayerStateIndex = 0;

	ProcessEvent(Globals::UGameViewportClient, fnGetPlayerState, &params);

	return params.ReturnValue;
}
void SDK::GetAllActorsOfClass(uint64_t ActorClass, TArray<uint64_t*>* OutActors)
{
	static uint64_t fnGetAllActorsOfClass = NULL;
	if (!fnGetAllActorsOfClass) {
		fnGetAllActorsOfClass = Core.pFindObject(xor_w(L"GameplayStatics.GetAllActorsOfClass"));
	}

	struct {
		uintptr_t WorldContextObject;
		uint64_t ActorClass;
		TArray<uint64_t*> OutActors;
	} params;
	params.WorldContextObject = Globals::World;
	params.ActorClass = ActorClass;

	ProcessEvent(Globals::UGameViewportClient, fnGetAllActorsOfClass, &params);

	if (OutActors != nullptr)
		*OutActors = params.OutActors;
}
double SDK::GetTimeSeconds()
{
	static uint64_t fnGetTimeSeconds = NULL;
	if (!fnGetTimeSeconds) {
		fnGetTimeSeconds = Core.pFindObject(xor_w(L"GameplayStatics.GetTimeSeconds"));
	}

	struct {
		uintptr_t WorldContextObject;
		double ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;

	ProcessEvent(Globals::UGameViewportClient, fnGetTimeSeconds, &params);

	return params.ReturnValue;
}
EMouseCaptureMode SDK::GetViewportMouseCaptureMode()
{
	static uint64_t fnGetViewportMouseCaptureMode = NULL;
	if (!fnGetViewportMouseCaptureMode) {
		fnGetViewportMouseCaptureMode = Core.pFindObject(xor_w(L"GameplayStatics.GetViewportMouseCaptureMode"));
	}

	struct {
		uintptr_t WorldContextObject;
		EMouseCaptureMode ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;

	ProcessEvent(Globals::UGameViewportClient, fnGetViewportMouseCaptureMode, &params);

	return params.ReturnValue;
}
bool SDK::ObjectIsA(uintptr_t Object, uintptr_t ObjectClass)
{
	static uint64_t fnObjectIsA = NULL;
	if (!fnObjectIsA) {
		fnObjectIsA = Core.pFindObject(xor_w(L"GameplayStatics.ObjectIsA"));
	}

	struct {
		uintptr_t Object;
		uintptr_t ObjectClass;
		bool ReturnValue;
	} params;
	params.Object = Object;
	params.ObjectClass = ObjectClass;

	ProcessEvent(Globals::UGameViewportClient, fnObjectIsA, &params);

	return params.ReturnValue;
}
double SDK::GetWorldDeltaSeconds()
{
	static uint64_t fnGetWorldDeltaSeconds = NULL;
	if (!fnGetWorldDeltaSeconds) {
		fnGetWorldDeltaSeconds = Core.pFindObject(xor_w(L"GameplayStatics.GetWorldDeltaSeconds"));
	}

	struct {
		uintptr_t WorldContextObject;
		double ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;

	ProcessEvent(Globals::UGameViewportClient, fnGetWorldDeltaSeconds, &params);

	return params.ReturnValue;
}

// PlayerController //
void SDK::GetViewportSize(int* SizeX, int* SizeY)
{
	static uint64_t fnGetViewportSize = NULL;
	if (!fnGetViewportSize) {
		fnGetViewportSize = Core.pFindObject(xor_w(L"PlayerController.GetViewportSize"));
	}

	struct {
		int SizeX;
		int SizeY;
	} params;

	ProcessEvent(Globals::PlayerController, fnGetViewportSize, &params);

	if (SizeX != nullptr)
		*SizeX = params.SizeX;
	if (SizeY != nullptr)
		*SizeY = params.SizeY;
}
bool SDK::WasInputKeyJustPressed(const struct FKey& Key)
{
	static uint64_t fnWasInputKeyJustPressed = NULL;
	if (!fnWasInputKeyJustPressed) {
		fnWasInputKeyJustPressed = Core.pFindObject(xor_w(L"PlayerController.WasInputKeyJustPressed"));
	}

	struct {
		struct FKey Key;
		bool ReturnValue;
	} params;
	params.Key = Key;

	ProcessEvent(Globals::PlayerController, fnWasInputKeyJustPressed, &params);

	return params.ReturnValue;
}
bool SDK::WasInputKeyJustReleased(const struct FKey& Key)
{
	static uint64_t fnWasInputKeyJustReleased = NULL;
	if (!fnWasInputKeyJustReleased) {
		fnWasInputKeyJustReleased = Core.pFindObject(xor_w(L"PlayerController.WasInputKeyJustReleased"));
	}

	struct {
		struct FKey Key;
		bool ReturnValue;
	} params;
	params.Key = Key;

	ProcessEvent(Globals::PlayerController, fnWasInputKeyJustReleased, &params);

	return params.ReturnValue;
}
bool SDK::IsInputKeyDown(const struct FKey& Key)
{
	static uint64_t fnIsInputKeyDown = NULL;
	if (!fnIsInputKeyDown) {
		fnIsInputKeyDown = Core.pFindObject(xor_w(L"PlayerController.IsInputKeyDown"));
	}

	struct {
		struct FKey Key;
		bool ReturnValue;
	} params;
	params.Key = Key;

	ProcessEvent(Globals::PlayerController, fnIsInputKeyDown, &params);

	return params.ReturnValue;
}
bool SDK::GetMousePosition(float* LocationX, float* LocationY)
{
	static uint64_t fnGetMousePosition = NULL;
	if (!fnGetMousePosition) {
		fnGetMousePosition = Core.pFindObject(xor_w(L"PlayerController.GetMousePosition"));
	}

	struct {
		float LocationX;
		float LocationY;
		bool ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerController, fnGetMousePosition, &params);

	if (LocationX != nullptr)
		*LocationX = params.LocationX;
	if (LocationY != nullptr)
		*LocationY = params.LocationY;

	return params.ReturnValue;
}
FVector2D SDK::VectorGetMousePosition()
{
	static uint64_t fnVectorGetMousePosition = NULL;
	if (!fnVectorGetMousePosition) {
		fnVectorGetMousePosition = Core.pFindObject(xor_w(L"PlayerController.GetMousePosition"));
	}

	struct {
		float LocationX;
		float LocationY;
	} params;

	ProcessEvent(Globals::PlayerController, fnVectorGetMousePosition, &params);

	return FVector2D((double)params.LocationX, (double)params.LocationY);
}

// FortPlayerController //
FVector SDK::GetLocationUnderReticle()
{
	static uint64_t fnGetLocationUnderReticle = NULL;
	if (!fnGetLocationUnderReticle) {
		fnGetLocationUnderReticle = Core.pFindObject(xor_w(L"FortPlayerController.GetLocationUnderReticle"));
	}

	struct {
		FVector ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerController, fnGetLocationUnderReticle, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetClientSettings()
{
	static uint64_t fnGetClientSettings = NULL;
	if (!fnGetClientSettings) {
		fnGetClientSettings = Core.pFindObject(xor_w(L"FortPlayerController.GetClientSettings"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerController, fnGetClientSettings, &params);

	return params.ReturnValue;
}

// Controller //
uint64_t SDK::K2_GetPawn()
{
	static uint64_t fnGetPawn = NULL;
	if (!fnGetPawn) {
		fnGetPawn = Core.pFindObject(xor_w(L"Controller.K2_GetPawn"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerController, fnGetPawn, &params);

	return params.ReturnValue;
}

// Actor //
uint64_t SDK::K2_GetRootComponent(uint64_t actor)
{
	static uint64_t fnGetRootComponent = NULL;
	if (!fnGetRootComponent) {
		fnGetRootComponent = Core.pFindObject(xor_w(L"Actor.K2_GetRootComponent"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(actor, fnGetRootComponent, &params);

	return params.ReturnValue;
}

FVector SDK::K2_GetActorLocation(uint64_t Actor)
{
	static uint64_t fnGetActorLocation = NULL;
	if (!fnGetActorLocation) {
		fnGetActorLocation = Core.pFindObject(xor_w(L"Actor.K2_GetActorLocation"));
	}

	struct {
		struct FVector ReturnValue;
	} params;

	ProcessEvent(Actor, fnGetActorLocation, &params);

	return params.ReturnValue;
}
FRotator SDK::K2_GetActorRotation(uint64_t Actor)
{
	static uint64_t fnGetActorRotation = NULL;
	if (!fnGetActorRotation) {
		fnGetActorRotation = Core.pFindObject(xor_w(L"Actor.K2_GetActorRotation"));
	}

	struct {
		struct FRotator ReturnValue;
	} params;

	ProcessEvent(Actor, fnGetActorRotation, &params);

	return params.ReturnValue;
}
FVector SDK::GetVelocity(uint64_t Actor)
{
	static uint64_t fnGetVelocity = NULL;
	if (!fnGetVelocity) {
		fnGetVelocity = Core.pFindObject(xor_w(L"Actor.GetVelocity"));
	}

	struct {
		struct FVector ReturnValue;
	} params;

	ProcessEvent(Actor, fnGetVelocity, &params);

	return params.ReturnValue;
}
void SDK::GetActorBounds(uint64_t Actor, bool bOnlyCollidingComponents, bool bIncludeFromChildActors, struct FVector* Origin, struct FVector* BoxExtent)
{
	static uint64_t fnGetActorBounds = NULL;
	if (!fnGetActorBounds) {
		fnGetActorBounds = Core.pFindObject(xor_w(L"Actor.GetActorBounds"));
	}

	struct {
		bool bOnlyCollidingComponents;
		FVector Origin;
		FVector BoxExtent;
		bool bIncludeFromChildActors;
	} params;
	params.bOnlyCollidingComponents = bOnlyCollidingComponents;
	params.bIncludeFromChildActors = bIncludeFromChildActors;

	ProcessEvent(Actor, fnGetActorBounds, &params);

	if (Origin != nullptr)
		*Origin = params.Origin;
	if (BoxExtent != nullptr)
		*BoxExtent = params.BoxExtent;
}

// FortClientSettingsRecord //
float SDK::GetHUDScale(uint64_t ClientSettingsRecord)
{
	static uint64_t fnGetHUDScale = NULL;
	if (!fnGetHUDScale) {
		fnGetHUDScale = Core.pFindObject(xor_w(L"FortClientSettingsRecord.GetHUDScale"));
	}

	struct {
		float ReturnValue;
	} params;

	ProcessEvent(ClientSettingsRecord, fnGetHUDScale, &params);

	return params.ReturnValue;
}

// FortKismetLibrary //
TArray<uint64_t> SDK::GetFortPlayerPawns()
{
	static uint64_t fnGetFortPlayerPawns = NULL;
	if (!fnGetFortPlayerPawns) {
		fnGetFortPlayerPawns = Core.pFindObject(xor_w(L"FortKismetLibrary.GetFortPlayerPawns"));
	}

	struct {
		uint64_t WorldContextObject;
		TArray<uint64_t> Return;
	} params;
	params.WorldContextObject = Globals::World;

	ProcessEvent(Globals::UGameViewportClient, fnGetFortPlayerPawns, &params);

	return params.Return;
}
int SDK::GetLootLevel()
{
	static uint64_t fnGetLootLevel = NULL;
	if (!fnGetLootLevel) {
		fnGetLootLevel = Core.pFindObject(xor_w(L"FortKismetLibrary.GetLootLevel"));
	}

	struct {
		uint64_t WorldContextObject;
		int Return;
	} params;
	params.WorldContextObject = Globals::World;

	ProcessEvent(Globals::UGameViewportClient, fnGetLootLevel, &params);

	return params.Return;
}
FString SDK::GetHumanReadableName(uint64_t Actor)
{
	static uint64_t fnGetHumanReadableName = NULL;
	if (!fnGetHumanReadableName) {
		fnGetHumanReadableName = Core.pFindObject(xor_w(L"FortKismetLibrary.GetHumanReadableName"));
	}

	struct {
		uint64_t Actor;
		struct FString ReturnValue;
	} params;
	params.Actor = Actor;

	ProcessEvent(Globals::UGameViewportClient, fnGetHumanReadableName, &params);

	return params.ReturnValue;
}
bool SDK::OnSameTeam(uint64_t ActorA, uint64_t ActorB)
{
	static uint64_t fnOnSameTeam = NULL;
	if (!fnOnSameTeam) {
		fnOnSameTeam = Core.pFindObject(xor_w(L"FortKismetLibrary.OnSameTeam"));
	}

	struct {
		uint64_t ActorA;
		uint64_t ActorB;
		bool ReturnValue;
	} params;
	params.ActorA = ActorA;
	params.ActorB = ActorB;

	ProcessEvent(Globals::UGameViewportClient, fnOnSameTeam, &params);

	return params.ReturnValue;
}

// Pawn //
bool SDK::IsBotControlled(uint64_t Actor)
{
	static uint64_t fnIsBotControlled = NULL;
	if (!fnIsBotControlled) {
		fnIsBotControlled = Core.pFindObject(xor_w(L"Pawn.IsBotControlled"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(Actor, fnIsBotControlled, &params);

	return params.ReturnValue;
}

// FortPawn //
bool SDK::IsDead(uint64_t object)
{
	static uint64_t fnIsDead = NULL;
	if (!fnIsDead) {
		fnIsDead = Core.pFindObject(xor_w(L"FortPawn.IsDead"));
	}
	
	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(object, fnIsDead, &params);

	return params.ReturnValue;
}
bool SDK::IsDBNO(uint64_t object)
{
	static uint64_t fnIsDBNO = NULL;
	if (!fnIsDBNO) {
		fnIsDBNO = Core.pFindObject(xor_w(L"FortPawn.IsDBNO"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(object, fnIsDBNO, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetCurrentWeapon(uint64_t Actor)
{
	static uint64_t fnGetCurrentWeapon = NULL;
	if (!fnGetCurrentWeapon) {
		fnGetCurrentWeapon = Core.pFindObject(xor_w(L"FortPawn.GetCurrentWeapon"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(Actor, fnGetCurrentWeapon, &params);

	return params.ReturnValue;
}
void SDK::PawnStopFire()
{
	static uint64_t fnPawnStopFire = NULL;
	if (!fnPawnStopFire) {
		fnPawnStopFire = Core.pFindObject(xor_w(L"FortPawn.PawnStopFire"));
	}

	struct {
		unsigned char FireModeNum;
	} params;
	params.FireModeNum = 0;

	ProcessEvent(Globals::MyPlayer, fnPawnStopFire, &params);
}
void SDK::PawnStartFire()
{
	static uint64_t fnPawnStartFire = NULL;
	if (!fnPawnStartFire) {
		fnPawnStartFire = Core.pFindObject(xor_w(L"FortPawn.PawnStartFire"));
	}

	struct {
		unsigned char FireModeNum;
	} params;
	params.FireModeNum = 0;

	ProcessEvent(Globals::MyPlayer, fnPawnStartFire, &params);
}

// CharacterMovementComponent //
FVector SDK::GetLastUpdateVelocity(uint64_t CharacterMovement)
{
	static uint64_t fnGetLastUpdateVelocity = NULL;
	if (!fnGetLastUpdateVelocity) {
		fnGetLastUpdateVelocity = Core.pFindObject(xor_w(L"CharacterMovementComponent.GetLastUpdateVelocity"));
	}

	struct {
		FVector ReturnValue;
	} params;

	ProcessEvent(CharacterMovement, fnGetLastUpdateVelocity, &params);

	return params.ReturnValue;
}

// FortWeapon //
uint64_t SDK::GetWeaponData(uint64_t CurrentWeapon)
{
	static uint64_t fnGetWeaponData = NULL;
	if (!fnGetWeaponData) {
		fnGetWeaponData = Core.pFindObject(xor_w(L"FortWeapon.GetWeaponData"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(CurrentWeapon, fnGetWeaponData, &params);

	return params.ReturnValue;
}
void SDK::SetWeaponData(uint64_t CurrentWeapon, uint64_t InWeaponData)
{
	static uint64_t fnSetWeaponData = NULL;
	if (!fnSetWeaponData) {
		fnSetWeaponData = Core.pFindObject(xor_w(L"FortWeapon.SetWeaponData"));
	}

	struct {
		uint64_t InWeaponData;
	} params;
	params.InWeaponData = InWeaponData;

	ProcessEvent(CurrentWeapon, fnSetWeaponData, &params);
}
int SDK::GetMagazineAmmoCount(uint64_t CurrentWeapon)
{
	static uint64_t fnGetRemainingAmmo = NULL;
	if (!fnGetRemainingAmmo) {
		fnGetRemainingAmmo = Core.pFindObject(xor_w(L"FortWeapon.GetMagazineAmmoCount"));
	}

	struct {
		int ReturnValue;
	} params;

	ProcessEvent(CurrentWeapon, fnGetRemainingAmmo, &params);

	return params.ReturnValue;
}
int SDK::GetBulletsPerClip(uint64_t CurrentWeapon)
{
	static uint64_t fnGetBulletsPerClip = NULL;
	if (!fnGetBulletsPerClip) {
		fnGetBulletsPerClip = Core.pFindObject(xor_w(L"FortWeapon.GetBulletsPerClip"));
	}

	struct {
		int ReturnValue;
	} params;

	ProcessEvent(CurrentWeapon, fnGetBulletsPerClip, &params);

	return params.ReturnValue;
}
FVector SDK::GetTargetingSourceLocation(uint64_t CurrentWeapon)
{
	static uint64_t fnGetTargetingSourceLocation = NULL;
	if (!fnGetTargetingSourceLocation) {
		fnGetTargetingSourceLocation = Core.pFindObject(xor_w(L"FortWeapon.GetTargetingSourceLocation"));
	}

	struct {
		FVector ReturnValue;
	} params;

	ProcessEvent(CurrentWeapon, fnGetTargetingSourceLocation, &params);

	return params.ReturnValue;
}
float SDK::GetProjectileSpeed(uint64_t CurrentWeapon, float ChargePercent)
{
	static uint64_t fnGetProjectileSpeed = NULL;
	if (!fnGetProjectileSpeed) {
		fnGetProjectileSpeed = Core.pFindObject(xor_w(L"FortWeapon.GetProjectileSpeed"));
	}

	struct {
		float ChargePercent;
		float ReturnValue;
	} params;
	params.ChargePercent = ChargePercent;

	ProcessEvent(CurrentWeapon, fnGetProjectileSpeed, &params);

	return params.ReturnValue;
}
float SDK::GetChargePercent(uint64_t CurrentWeapon)
{
	static uint64_t fnGetChargePercent = NULL;
	if (!fnGetChargePercent) {
		fnGetChargePercent = Core.pFindObject(xor_w(L"FortWeapon.GetChargePercent"));
	}

	struct {
		float ReturnValue;
	} params;

	ProcessEvent(CurrentWeapon, fnGetChargePercent, &params);

	return params.ReturnValue;
}
TEnumAsByte<EFortWeaponCoreAnimation> SDK::GetCoreAnimation(uint64_t Weapon)
{
	static uint64_t fnGetCoreAnimation = NULL;
	if (!fnGetCoreAnimation) {
		fnGetCoreAnimation = Core.pFindObject(xor_w(L"FortWeapon.GetCoreAnimation"));
	}

	struct {
		TEnumAsByte<EFortWeaponCoreAnimation> ReturnValue;
	} params;

	ProcessEvent(Weapon, fnGetCoreAnimation, &params);

	return params.ReturnValue;
}

// PlayerState //
bool SDK::IsABot()
{
	static uint64_t fnIsABot = NULL;
	if (!fnIsABot) {
		fnIsABot = Core.pFindObject(xor_w(L"PlayerState.IsABot"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerState, fnIsABot, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetPlayerControllerFromPlayerState(uint64_t playerState)
{
	static uint64_t fnGetPlayerController = NULL;
	if (!fnGetPlayerController) {
		fnGetPlayerController = Core.pFindObject(xor_w(L"PlayerState.GetPlayerController"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(playerState, fnGetPlayerController, &params);

	return params.ReturnValue;
}

// FortPlayerState //
FString SDK::GetPlatform(uint64_t PlayerState)
{
	static uint64_t fnGetPlatform = NULL;
	if (!fnGetPlatform) {
		fnGetPlatform = Core.pFindObject(xor_w(L"FortPlayerState.GetPlatform"));
	}

	struct {
		FString ReturnValue;
	} params;

	ProcessEvent(PlayerState, fnGetPlatform, &params);

	return params.ReturnValue;
}
uint64_t SDK::GetCurrentPawn(uint64_t PlayerState)
{
	static uint64_t fnGetCurrentPawn = NULL;
	if (!fnGetCurrentPawn) {
		fnGetCurrentPawn = Core.pFindObject(xor_w(L"FortPlayerState.GetCurrentPawn"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(PlayerState, fnGetCurrentPawn, &params);

	return params.ReturnValue;
}

// FortPlayerStateAthena //
bool SDK::IsAnAthenaGameParticipant()
{
	static uint64_t fnIsAnAthenaGameParticipant = NULL;
	if (!fnIsAnAthenaGameParticipant) {
		fnIsAnAthenaGameParticipant = Core.pFindObject(xor_w(L"FortPlayerStateAthena.IsAnAthenaGameParticipant"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerState, fnIsAnAthenaGameParticipant, &params);

	return params.ReturnValue;
}
int SDK::GetKillScore(uint64_t PlayerState)
{
	static uint64_t fnGetKillScore = NULL;
	if (!fnGetKillScore) {
		fnGetKillScore = Core.pFindObject(xor_w(L"FortPlayerStateAthena.GetKillScore"));
	}

	struct {
		int ReturnValue;
	} params;

	ProcessEvent(PlayerState, fnGetKillScore, &params);

	return params.ReturnValue;
}

// FortPlayerStateZone //
int SDK::GetSpectatorCount()
{
	static uint64_t fnGetSpectatorCount = NULL;
	if (!fnGetSpectatorCount) {
		fnGetSpectatorCount = Core.pFindObject(xor_w(L"FortPlayerStateZone.GetSpectatorCount"));
	}

	struct {
		int ReturnValue;
	} params;

	ProcessEvent(Globals::PlayerState, fnGetSpectatorCount, &params);

	return params.ReturnValue;
}

// FortPickup //
uint64_t SDK::GetPrimaryItemDefinition(uint64_t Actor)
{
	static uint64_t fnGetPrimaryItemDefinition = NULL;
	if (!fnGetPrimaryItemDefinition) {
		fnGetPrimaryItemDefinition = Core.pFindObject(xor_w(L"FortPickup.GetPrimaryItemDefinition"));
	}

	struct {
		uint64_t ReturnValue;
	} params;

	ProcessEvent(Actor, fnGetPrimaryItemDefinition, &params);

	return params.ReturnValue;
}

// FortItemDefinition //
EFortItemTier SDK::GetTier(uint64_t ItemDefinition)
{
	static uint64_t fnGetTier = NULL;
	if (!fnGetTier) {
		fnGetTier = Core.pFindObject(xor_w(L"FortItemDefinition.GetTier"));
	}

	struct {
		EFortItemTier ReturnValue;
	} params;

	ProcessEvent(ItemDefinition, fnGetTier, &params);

	return params.ReturnValue;
}
EFortItemType SDK::GetItemType(uint64_t ItemDefinition)
{
	static uint64_t fnGetItemType = NULL;
	if (!fnGetItemType) {
		fnGetItemType = Core.pFindObject(xor_w(L"FortItemDefinition.GetItemType"));
	}

	struct {
		EFortItemType ReturnValue;
	} params;

	ProcessEvent(ItemDefinition, fnGetItemType, &params);

	return params.ReturnValue;
}
FFortColorPalette SDK::GetRarityOrSeriesColors(uint64_t ItemDefinition)
{
	static uint64_t fnGetRarityOrSeriesColors = NULL;
	if (!fnGetRarityOrSeriesColors) {
		fnGetRarityOrSeriesColors = Core.pFindObject(xor_w(L"FortItemDefinition.GetRarityOrSeriesColors"));
	}


	struct {
		FFortColorPalette ReturnValue;
	} params;

	ProcessEvent(ItemDefinition, fnGetRarityOrSeriesColors, &params);

	return params.ReturnValue;
}
TSoftObjectPtr<UObject> SDK::GetSmallPreviewImage(uint64_t ItemDefinition)
{
	static uint64_t GetSmallPreviewImage = NULL;
	if (!GetSmallPreviewImage) {
		GetSmallPreviewImage = Core.pFindObject(xor_w(L"FortItemDefinition.GetSmallPreviewImage"));
	}

	struct {
		TSoftObjectPtr<UObject> ReturnValue;
	} params;

	ProcessEvent(ItemDefinition, GetSmallPreviewImage, &params);

	return params.ReturnValue;
}

// UItemDefinitionBase //
FText SDK::GetDisplayName(uint64_t ItemDefinition)
{
	static uint64_t fnGetDisplayName = NULL;
	if (!fnGetDisplayName) {
		fnGetDisplayName = Core.pFindObject(xor_w(L"ItemDefinitionBase.GetDisplayName"));
	}

	struct {
		FText ReturnValue;
	} params;

	ProcessEvent(ItemDefinition, fnGetDisplayName, &params);

	return params.ReturnValue;
}

// FortWeaponRangedItemDefinition //
uint64_t SDK::GetProjectileTemplate(uint64_t WeaponData)
{
	static uint64_t fnGetProjectileTemplate = NULL;
	if (!fnGetProjectileTemplate) {
		fnGetProjectileTemplate = Core.pFindObject(xor_w(L"FortWeaponRangedItemDefinition.GetProjectileTemplate"));
	}

	struct {
		uint64_t ReturnValue;
	} params;
	
	ProcessEvent(WeaponData, fnGetProjectileTemplate, &params);

	return params.ReturnValue;
}
bool SDK::HasLightweightProjectile(uint64_t WeaponData)
{
	static uint64_t fnHasLightweightProjectile = NULL;
	if (!fnHasLightweightProjectile) {
		fnHasLightweightProjectile = Core.pFindObject(xor_w(L"FortWeaponRangedItemDefinition.HasLightweightProjectile"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(WeaponData, fnHasLightweightProjectile, &params);

	return params.ReturnValue;
}
bool SDK::IsProjectileWeapon(uint64_t CurrentWeapon)
{
	static uint64_t fnIsProjectileWeapon = NULL;
	if (!fnIsProjectileWeapon) {
		fnIsProjectileWeapon = Core.pFindObject(xor_w(L"FortWeaponRangedItemDefinition.IsProjectileWeapon"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(CurrentWeapon, fnIsProjectileWeapon, &params);

	return params.ReturnValue;
}

// AthenaCharacterPartItemDefinition //
TArray<uint64_t> SDK::GetCharacterParts(uint64_t ItemDefinition)
{
	static uint64_t fnGetCharacterParts = NULL;
	if (!fnGetCharacterParts) {
		fnGetCharacterParts = Core.pFindObject(xor_w(L"AthenaCharacterPartItemDefinition.GetCharacterParts"));
	}

	struct {
		TArray<uint64_t> ReturnValue;
	} params;

	ProcessEvent(ItemDefinition, fnGetCharacterParts, &params);

	return params.ReturnValue;
}

// FortScalableFloatUtils //
float SDK::GetValue(FScalableFloat& Input)
{
	static uint64_t fnGetValue = NULL;
	if (!fnGetValue) {
		fnGetValue = Core.pFindObject(xor_w(L"FortScalableFloatUtils.GetValue"));
	}

	struct {
		FScalableFloat& Input;
		float ReturnValue;
	} params = { Input };

	ProcessEvent(Globals::ScalableFloatUtils, fnGetValue, &params);

	return params.ReturnValue;
}
float SDK::GetValueAtLevel(FScalableFloat Input, int Level)
{
	static uint64_t fnGetValueAtLevel = NULL;
	if (!fnGetValueAtLevel) {
		fnGetValueAtLevel = Core.pFindObject(xor_w(L"FortScalableFloatUtils.GetValueAtLevel"));
	}

	struct {
		FScalableFloat Input;
		int Level;
		float ReturnValue;
	} params = { Input, Level };

	ProcessEvent(Globals::ScalableFloatUtils, fnGetValueAtLevel, &params);

	return params.ReturnValue;
}
	
// BuildingTrap //
bool SDK::HasDurability(uint64_t Actor)
{
	static uint64_t fnHasDurability = NULL;
	if (!fnHasDurability) {
		fnHasDurability = Core.pFindObject(xor_w(L"BuildingTrap.HasDurability"));
	}

	struct {
		float ReturnValue;
	} params;

	ProcessEvent(Actor, fnHasDurability, &params);

	return params.ReturnValue;
}
float SDK::GetArmTime(uint64_t Actor)
{
	static uint64_t fnGetArmTime = NULL;
	if (!fnGetArmTime) {
		fnGetArmTime = Core.pFindObject(xor_w(L"BuildingTrap.GetArmTime"));
	}

	struct {
		float ReturnValue;
	} params;

	ProcessEvent(Actor, fnGetArmTime, &params);

	return params.ReturnValue;
}

// SceneComponent //
FVector SDK::GetSocketLocation(uint64_t object, const FName& InSocketName)
{
	static uint64_t fnGetSocketLocation = NULL;
	if (!fnGetSocketLocation) {
		fnGetSocketLocation = Core.pFindObject(xor_w(L"SceneComponent.GetSocketLocation"));
	}

	struct {
		struct FName                                       InSocketName;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		struct FVector                                     ReturnValue;
	} params;
	params.InSocketName = InSocketName;

	ProcessEvent(object, fnGetSocketLocation, &params);

	return params.ReturnValue;
}
FVector SDK::GetComponentVelocity(uint64_t RootComponent)
{
	static uint64_t fnGetSocketLocation = NULL;
	if (!fnGetSocketLocation) {
		fnGetSocketLocation = Core.pFindObject(xor_w(L"SceneComponent.GetComponentVelocity"));
	}

	struct {
		struct FVector ReturnValue;
	} params;

	ProcessEvent(RootComponent, fnGetSocketLocation, &params);

	return params.ReturnValue;
}
FRotator SDK::K2_GetComponentRotation(uint64_t RootComponent)
{
	static uint64_t fnGetComponentRotation = NULL;
	if (!fnGetComponentRotation) {
		fnGetComponentRotation = Core.pFindObject(xor_w(L"SceneComponent.K2_GetComponentRotation"));
	}

	struct {
		struct FRotator ReturnValue;
	} params;

	ProcessEvent(RootComponent, fnGetComponentRotation, &params);

	return params.ReturnValue;
}

// PrimitiveComponent //
int SDK::GetNumMaterials(uint64_t Mesh)
{
	static uint64_t fnGetNumMaterials = NULL;
	if (!fnGetNumMaterials) {
		fnGetNumMaterials = Core.pFindObject(xor_w(L"PrimitiveComponent.GetNumMaterials"));
	}

	struct {
		int ReturnValue;
	} params;

	ProcessEvent(Mesh, fnGetNumMaterials, &params);

	return params.ReturnValue;
}
void SDK::SetMaterial(uint64_t Mesh, int ElementIndex, uintptr_t Material)
{
	static uint64_t fnSetMaterial = NULL;
	if (!fnSetMaterial) {
		fnSetMaterial = Core.pFindObject(xor_w(L"PrimitiveComponent.SetMaterial"));
	}

	struct {
		int ElementIndex;
		uintptr_t Material;
	} params;
	params.ElementIndex = ElementIndex;
	params.Material = Material;

	ProcessEvent(Mesh, fnSetMaterial, &params);
}
void SDK::SetRenderCustomDepth(uint64_t Mesh, bool bValue)
{
	static uint64_t fnSetRenderCustomDepth = NULL;
	if (!fnSetRenderCustomDepth) {
		fnSetRenderCustomDepth = Core.pFindObject(xor_w(L"PrimitiveComponent.SetRenderCustomDepth"));
	}

	struct {
		bool bValue;
	} params;
	params.bValue = bValue;

	ProcessEvent(Mesh, fnSetRenderCustomDepth, &params);
}
void SDK::SetCustomDepthStencilValue(uint64_t Mesh, int Value)
{
	static uint64_t fnSetCustomDepthStencilValue = NULL;
	if (!fnSetCustomDepthStencilValue) {
		fnSetCustomDepthStencilValue = Core.pFindObject(xor_w(L"PrimitiveComponent.SetCustomDepthStencilValue"));
	}

	struct {
		int Value;
	} params;
	params.Value = Value;

	ProcessEvent(Mesh, fnSetCustomDepthStencilValue, &params);
}
uint64_t SDK::GetMaterial(uint64_t Mesh, int ElementIndex)
{
	static uint64_t fnGetMaterial = NULL;
	if (!fnGetMaterial) {
		fnGetMaterial = Core.pFindObject(xor_w(L"PrimitiveComponent.GetMaterial"));
	}
	
	struct {
		int ElementIndex;
		uint64_t ReturnValue;
	} params;
	params.ElementIndex = ElementIndex;

	ProcessEvent(Mesh, fnGetMaterial, &params);

	return params.ReturnValue;
}
uint64_t SDK::CreateDynamicMaterialInstance(uint64_t Mesh, int ElementIndex, uint64_t SourceMaterial, const struct FName& OptionalName)
{
	static uint64_t fnCreateDynamicMaterialInstance = NULL;
	if (!fnCreateDynamicMaterialInstance) {
		fnCreateDynamicMaterialInstance = Core.pFindObject(xor_w(L"PrimitiveComponent.CreateDynamicMaterialInstance"));
	}

	struct {
		int ElementIndex;
		uint64_t SourceMaterial;
		FName OptionalName;
		uint64_t ReturnValue;
	} params;
	params.ElementIndex = ElementIndex;
	params.SourceMaterial = SourceMaterial;
	params.OptionalName = OptionalName;

	ProcessEvent(Mesh, fnCreateDynamicMaterialInstance, &params);

	return params.ReturnValue;
}


uintptr_t SDK::CreateDynamicMaterialInstance(uint64_t Parent)
{
	static uint64_t fnCreateDynamicMaterialInstance = NULL;
	if (!fnCreateDynamicMaterialInstance) {
		fnCreateDynamicMaterialInstance = Core.pFindObject(xor_w(L"KismetMaterialLibrary.CreateDynamicMaterialInstance"));
	}

	struct {
		uint64_t WorldContextObject;
		uint64_t Parent;                            
		uint64_t ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;
	params.Parent = Parent;
	
	ProcessEvent(Globals::UGameViewportClient, fnCreateDynamicMaterialInstance, &params);

	return params.ReturnValue;
}
uintptr_t SDK::GetBaseMaterial(uintptr_t MaterialInterface)
{
	static uint64_t fnGetBaseMaterial = NULL;
	if (!fnGetBaseMaterial) {
		fnGetBaseMaterial = Core.pFindObject(xor_w(L"MaterialInterface.GetBaseMaterial"));
	}

	struct {
		uintptr_t ReturnValue;
	} params;

	ProcessEvent(MaterialInterface, fnGetBaseMaterial, &params);

	return params.ReturnValue;
}


// MaterialInstanceDynamic //
void SDK::SetVectorParameterValue(uint64_t MaterialInstanceDynamic, const struct FName& ParameterName, const struct FLinearColor& Value)
{
	static uint64_t fnSetVectorParameterValue = NULL;
	if (!fnSetVectorParameterValue) {
		fnSetVectorParameterValue = Core.pFindObject(xor_w(L"MaterialInstanceDynamic.SetVectorParameterValue"));
	}

	struct {
		FName ParameterName;
		FLinearColor Value;
	} params;
	params.ParameterName = ParameterName;
	params.Value = Value;

	ProcessEvent(MaterialInstanceDynamic, fnSetVectorParameterValue, &params);
}

// FortAthenaVehicle //
FString SDK::VehicleGetDisplayName(uint64_t Actor)
{
	static uint64_t fnVehicleGetDisplayName = NULL;
	if (!fnVehicleGetDisplayName) {
		fnVehicleGetDisplayName = Core.pFindObject(xor_w(L"FortAthenaVehicle.GetDisplayName"));
	}

	struct {
		FString ReturnValue;
	} params;

	ProcessEvent(Actor, fnVehicleGetDisplayName, &params);

	return params.ReturnValue;
}
bool SDK::CanContainPlayers(uint64_t Actor)
{
	static uint64_t fnCanContainPlayers = NULL;
	if (!fnCanContainPlayers) {
		fnCanContainPlayers = Core.pFindObject(xor_w(L"FortAthenaVehicle.CanContainPlayers"));
	}

	struct {
		bool ReturnValue;
	} params;

	ProcessEvent(Actor, fnCanContainPlayers, &params);

	return params.ReturnValue;
}

//void SDK::SetQuestHighlight(bool Enabled)
//{
//	static uint64_t fnSetQuestHighlight = NULL;
//	if (!fnSetQuestHighlight) {
//		fnSetQuestHighlight = Core.pFindObject(xor_w(L"BuildingActor.SetQuestHighlight"));
//	}
//
//	struct {
//		bool Enabled;
//	} params;
//	params.Enabled = Enabled;
//
//	ProcessEvent(Globals::BuildingActor, fnSetQuestHighlight, &params);
//}

// Canvas //
FVector SDK::K2_Project(const FVector& WorldLocation)
{
	static uint64_t fnK2_Project = NULL;
	if (!fnK2_Project) {
		fnK2_Project = Core.pFindObject(xor_w(L"Canvas.K2_Project"));
	}

	struct {
		struct FVector WorldLocation;
		struct FVector ReturnValue;
	} params;
	params.WorldLocation = WorldLocation;

	ProcessEvent(Globals::UCanvas, fnK2_Project, &params);

	return params.ReturnValue;
}
void SDK::K2_DrawLine(FVector2D A, FVector2D B, float Thickness, FLinearColor Color)
{
	static uint64_t fnK2_DrawLine = NULL;
	if (!fnK2_DrawLine) {
		fnK2_DrawLine = Core.pFindObject(xor_w(L"Canvas.K2_DrawLine"));
	}

	struct {
		struct FVector2D ScreenPositionA;
		struct FVector2D ScreenPositionB;
		float Thickness;
		struct FLinearColor RenderColor;
	} params;
	params.ScreenPositionA = A;
	params.ScreenPositionB = B;
	params.Thickness = Thickness;
	params.RenderColor = Color;

	ProcessEvent(Globals::UCanvas, fnK2_DrawLine, &params);
}
void SDK::K2_DrawBox(const FVector2D& ScreenPosition, const FVector2D& ScreenSize, float Thickness, const FLinearColor& RenderColor)
{
	static uint64_t fnK2_DrawBox = NULL;
	if (!fnK2_DrawBox) {
		fnK2_DrawBox = Core.pFindObject(xor_w(L"Canvas.K2_DrawBox"));
	}

	struct {
		struct FVector2D ScreenPosition;
		struct FVector2D ScreenSize;
		float Thickness;
		struct FLinearColor RenderColor;
	} params;
	params.ScreenPosition = ScreenPosition;
	params.ScreenSize = ScreenSize;
	params.Thickness = Thickness;
	params.RenderColor = RenderColor;

	ProcessEvent(Globals::UCanvas, fnK2_DrawBox, &params);
}
FVector2D SDK::K2_TextSize(uint64_t font, const FString& RenderText, const FVector2D& Scale)
{
	static uint64_t fnK2_TextSize = NULL;
	if (!fnK2_TextSize) {
		fnK2_TextSize = Core.pFindObject(xor_w(L"Canvas.K2_TextSize"));
	}

	struct{
		uint64_t RenderFont;
		struct FString RenderText;
		struct FVector2D Scale;
		struct FVector2D ReturnValue;
	} params;
	params.RenderFont = font;
	params.RenderText = RenderText;
	params.Scale = Scale;

	ProcessEvent(Globals::UCanvas, fnK2_TextSize, &params);

	return params.ReturnValue;
}
FVector2D SDK::K2_StrLen(uint64_t RenderFont, const struct FString& RenderText)
{
	static uint64_t fnK2_StrLen = NULL;
	if (!fnK2_StrLen) {
		fnK2_StrLen = Core.pFindObject(xor_w(L"Canvas.K2_StrLen"));
	}

	struct {
		uint64_t RenderFont;
		struct FString RenderText;
		struct FVector2D ReturnValue;
	} params;
	params.RenderFont = RenderFont;
	params.RenderText = RenderText;

	ProcessEvent(Globals::UCanvas, fnK2_StrLen, &params);

	return params.ReturnValue;
}
void SDK::K2_DrawText(uint64_t font, const FString& RenderText, const FVector2D& ScreenPosition, const FVector2D& Scale, const FLinearColor& RenderColor, double Kerning, const FLinearColor& ShadowColor, const FVector2D& ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, const FLinearColor& OutlineColor)
{
	static uint64_t fnK2_DrawText = NULL;
	if (!fnK2_DrawText) {
		fnK2_DrawText = Core.pFindObject(xor_w(L"Canvas.K2_DrawText"));
	}

	struct {
		uint64_t RenderFont;
		struct FString RenderText;
		struct FVector2D ScreenPosition;
		struct FVector2D Scale;
		struct FLinearColor RenderColor;
		double Kerning;
		struct FLinearColor ShadowColor;
		struct FVector2D ShadowOffset;
		bool bCentreX;
		bool bCentreY;
		bool bOutlined;
		struct FLinearColor OutlineColor;
	} params;

	params.RenderFont = font;
	params.RenderText = RenderText;
	params.ScreenPosition = ScreenPosition;
	params.Scale = Scale;
	params.RenderColor = RenderColor;
	params.Kerning = Kerning;
	params.ShadowColor = ShadowColor;
	params.ShadowOffset = ShadowOffset;
	params.bCentreX = bCentreX;
	params.bCentreY = bCentreY;
	params.bOutlined = bOutlined;
	params.OutlineColor = OutlineColor;

	ProcessEvent(Globals::UCanvas, fnK2_DrawText, &params);
}
void SDK::K2_DrawPolygon(uintptr_t RenderTexture, const struct FVector2D& ScreenPosition, const struct FVector2D& Radius, int NumberOfSides, const struct FLinearColor& RenderColor)
{
	static uint64_t fnK2_DrawPolygon = NULL;
	if (!fnK2_DrawPolygon) {
		fnK2_DrawPolygon = Core.pFindObject(xor_w(L"Canvas.K2_DrawPolygon"));
	}

	struct {
		uintptr_t RenderTexture;
		struct FVector2D ScreenPosition;
		struct FVector2D Radius;
		int NumberOfSides;
		struct FLinearColor RenderColor;
	} params;
	params.RenderTexture = RenderTexture;
	params.ScreenPosition = ScreenPosition;
	params.Radius = Radius;
	params.NumberOfSides = NumberOfSides;
	params.RenderColor = RenderColor;

	ProcessEvent(Globals::UCanvas, fnK2_DrawPolygon, &params);
}
void SDK::K2_DrawTexture(uintptr_t RenderTexture, const struct FVector2D& ScreenPosition, const struct FVector2D& ScreenSize, const struct FVector2D& CoordinatePosition, const struct FVector2D& CoordinateSize, const struct FLinearColor& RenderColor, TEnumAsByte<EBlendMode> BlendMode, float Rotation, const struct FVector2D& PivotPoint)
{
	static uint64_t fnK2_DrawTexture = NULL;
	if (!fnK2_DrawTexture) {
		fnK2_DrawTexture = Core.pFindObject(xor_w(L"Canvas.K2_DrawTexture"));
	}

	struct {
		uintptr_t RenderTexture;
		struct FVector2D ScreenPosition;
		struct FVector2D ScreenSize;
		struct FVector2D CoordinatePosition;
		struct FVector2D CoordinateSize;
		struct FLinearColor RenderColor;
		EBlendMode BlendMode;
		float Rotation;
		struct FVector2D PivotPoint;		
	} params;
	params.RenderTexture = RenderTexture;
	params.ScreenPosition = ScreenPosition;
	params.ScreenSize = ScreenSize;
	params.CoordinatePosition = CoordinatePosition;
	params.CoordinateSize = CoordinateSize;
	params.RenderColor = RenderColor;
	params.BlendMode = BlendMode;
	params.Rotation = Rotation;
	params.PivotPoint = PivotPoint;

	ProcessEvent(Globals::UCanvas, fnK2_DrawTexture, &params);
}

// KismetSystemLibrary //
bool SDK::LineTraceSingle(const FVector& Start, const FVector& End)
{
	static uint64_t fnLineTraceSingle = NULL;
	if (!fnLineTraceSingle) {
		fnLineTraceSingle = Core.pFindObject(xor_w(L"KismetSystemLibrary.LineTraceSingle"));
	}

	struct {
		uint64_t WorldContextObject;                                       // (ConstParm, Parm, ZeroConstructor)
		struct FVector                                     Start;                                                    // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		struct FVector                                     End;                                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<ETraceTypeQuery>                       TraceChannel;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		bool                                               bTraceComplex;                                            // (Parm, ZeroConstructor, IsPlainOldData)
		TArray<uint64_t>								   ActorsToIgnore;                                           // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
		TEnumAsByte<EDrawDebugTrace>                       DrawDebugType;                                            // (Parm, ZeroConstructor, IsPlainOldData)
		struct FHitResult                                  OutHit;                                                   // (Parm, OutParm, IsPlainOldData)
		bool                                               bIgnoreSelf;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		struct FLinearColor                                TraceColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
		struct FLinearColor                                TraceHitColor;                                            // (Parm, ZeroConstructor, IsPlainOldData)
		float                                              DrawTime;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
		unsigned char                                      Padding[0x8];                                       // 0x00AE(0x0002) MISSED OFFSET
		bool                                               ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;
	params.Start = Start;
	params.End = End;
	params.TraceChannel = ETraceTypeQuery::TraceTypeQuery2;
	params.bTraceComplex = true;
	params.ActorsToIgnore = TArray<uint64_t>();
	params.DrawDebugType = EDrawDebugTrace::None;
	params.bIgnoreSelf = true;
	params.TraceColor = FLinearColor();
	params.TraceHitColor = FLinearColor();
	params.DrawTime = 0.0f;

	ProcessEvent(Globals::UGameViewportClient, fnLineTraceSingle, &params);

	return !params.ReturnValue;
}
FString SDK::GetObjectName(uint64_t Object)
{
	static uint64_t fnGetObjectName = NULL;
	if (!fnGetObjectName) {
		fnGetObjectName = Core.pFindObject(xor_w(L"KismetSystemLibrary.GetObjectName"));
	}

	struct {
		uint64_t Object;
		struct FString ReturnValue;
	} params;
	params.Object = Object;

	ProcessEvent(Globals::UGameViewportClient, fnGetObjectName, &params);

	return params.ReturnValue;
}
void SDK::GetComponentBounds(uint64_t Component, struct FVector* Origin, struct FVector* BoxExtent, float* SphereRadius)
{
	static uint64_t fnGetComponentBounds = NULL;
	if (!fnGetComponentBounds) {
		fnGetComponentBounds = Core.pFindObject(xor_w(L"KismetSystemLibrary.GetComponentBounds"));
	}
	
	struct {
		uint64_t Component;
		struct FVector Origin;
		struct FVector BoxExtent;
		float SphereRadius;
	} params;
	params.Component = Component;

	ProcessEvent(Globals::UGameViewportClient, fnGetComponentBounds, &params);

	if (Origin != nullptr)
		*Origin = params.Origin;
	if (BoxExtent != nullptr)
		*BoxExtent = params.BoxExtent;
	if (SphereRadius != nullptr)
		*SphereRadius = params.SphereRadius;
}
uintptr_t SDK::GetOuterObject(uintptr_t Object)
{
	static uint64_t fnGetOuterObject = NULL;
	if (!fnGetOuterObject) {
		fnGetOuterObject = Core.pFindObject(xor_w(L"KismetSystemLibrary.GetOuterObject"));
	}

	static uint64_t KismetSystemLibrary = Core.pFindObject(xor_w(L"Engine.Default__KismetSystemLibrary"));

	struct {
		uintptr_t Object;
		uintptr_t ReturnValue;
	} params;
	params.Object = Object;

	ProcessEvent(KismetSystemLibrary, fnGetOuterObject, &params);

	return params.ReturnValue;
}

// KismetMathLibrary //
double SDK::asin(double A)
{
	static uint64_t fnasin = NULL;
	if (!fnasin) {
		fnasin = Core.pFindObject(xor_w(L"KismetMathLibrary.asin"));
	}

	struct {
		double A;
		double ReturnValue;
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnasin, &params);

	return params.ReturnValue;
}
double SDK::Atan2(double Y, double X)
{
	static uint64_t fnAtan2 = NULL;
	if (!fnAtan2) {
		fnAtan2 = Core.pFindObject(xor_w(L"KismetMathLibrary.Atan2"));
	}

	struct {
		double Y;
		double X;
		double ReturnValue;
	} params;
	params.Y = Y;
	params.X = X;

	ProcessEvent(Globals::UGameViewportClient, fnAtan2, &params);

	return params.ReturnValue;
}
__int32 SDK::Round(double A)
{
	static uint64_t fnRound = NULL;
	if (!fnRound) {
		fnRound = Core.pFindObject(xor_w(L"KismetMathLibrary.Round"));
	}

	struct {
		double                                       A;                                                 // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		__int32                                        ReturnValue;                                       // 0x8(0x4)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		__int8                                        Pad_999[0x4];
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnRound, &params);

	return params.ReturnValue;
}
double SDK::Abs(double A)
{
	static uint64_t fnAbs = NULL;
	if (!fnAbs) {
		fnAbs = Core.pFindObject(xor_w(L"KismetMathLibrary.Abs"));
	}

	struct {
		double A;
		double ReturnValue;
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnAbs, &params);

	return params.ReturnValue;
}
double SDK::Cos(double A)
{
	static uint64_t fnCos = NULL;
	if (!fnCos) {
		fnCos = Core.pFindObject(xor_w(L"KismetMathLibrary.Cos"));
	}

	struct {
		double A;
		double ReturnValue;
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnCos, &params);

	return params.ReturnValue;
}
double SDK::Sin(double A)
{
	static uint64_t fnSin = NULL;
	if (!fnSin) {
		fnSin = Core.pFindObject(xor_w(L"KismetMathLibrary.Sin"));
	}

	struct {
		double A;
		double ReturnValue;
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnSin, &params);

	return params.ReturnValue;
}
double SDK::Sqrt(double A)
{
	static uint64_t fnSqrt = NULL;
	if (!fnSqrt) {
		fnSqrt = Core.pFindObject(xor_w(L"KismetMathLibrary.Sqrt"));
	}

	struct {
		double A;
		double ReturnValue;
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnSqrt, &params);

	return params.ReturnValue;
}
double SDK::Vector_Distance(const FVector& v1, const FVector& v2)
{
	static uint64_t fnVectorDistance = NULL;
	if (!fnVectorDistance) {
		fnVectorDistance = Core.pFindObject(xor_w(L"KismetMathLibrary.Vector_Distance"));
	}

	struct {
		struct FVector                                     v1;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
		struct FVector                                     v2;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
		double                                             ReturnValue;
	} params;
	params.v1 = v1;
	params.v2 = v2;

	ProcessEvent(Globals::UGameViewportClient, fnVectorDistance, &params);

	return params.ReturnValue;
}
FRotator SDK::FindLookAtRotation(const struct FVector& Start, const struct FVector& Target)
{
	static uint64_t fnFindLookAtRotation = NULL;
	if (!fnFindLookAtRotation) {
		fnFindLookAtRotation = Core.pFindObject(xor_w(L"KismetMathLibrary.FindLookAtRotation"));
	}

	struct {
		FVector Start;
		FVector Target;
		FRotator ReturnValue;
	} params;
	params.Start = Start;
	params.Target = Target;

	ProcessEvent(Globals::UGameViewportClient, fnFindLookAtRotation, &params);

	return params.ReturnValue;
}
FVector SDK::Quat_RotateVector(const struct FQuat& Q, const struct FVector& V)
{
	static uint64_t fnQuat_RotateVector = NULL;
	if (!fnQuat_RotateVector) {
		fnQuat_RotateVector = Core.pFindObject(xor_w(L"KismetMathLibrary.Quat_RotateVector"));
	}

	struct {
		FQuat Q;
		FVector V;
		FVector ReturnValue;
	} params;
	params.Q = Q;
	params.V = V;

	ProcessEvent(Globals::UGameViewportClient, fnQuat_RotateVector, &params);

	return params.ReturnValue;
}
FVector SDK::Subtract_VectorVector(const struct FVector& A, const struct FVector& B)
{
	static uint64_t fnSubtract_VectorVector = NULL;
	if (!fnSubtract_VectorVector) {
		fnSubtract_VectorVector = Core.pFindObject(xor_w(L"KismetMathLibrary.Subtract_VectorVector"));
	}

	struct {
		FVector A;
		FVector B;
		FVector ReturnValue;
	} params;
	params.A = A;
	params.B = B;

	ProcessEvent(Globals::UGameViewportClient, fnSubtract_VectorVector, &params);

	return params.ReturnValue;
}
double SDK::VSize(const struct FVector& A)
{
	static uint64_t fnVSize = NULL;
	if (!fnVSize) {
		fnVSize = Core.pFindObject(xor_w(L"KismetMathLibrary.VSize"));
	}

	struct {
		FVector A;
		double ReturnValue;
	} params;
	params.A = A;

	ProcessEvent(Globals::UGameViewportClient, fnVSize, &params);

	return params.ReturnValue;
}
FVector SDK::Add_VectorVector(const struct FVector& A, const struct FVector& B)
{
	static uint64_t fnAdd_VectorVector = NULL;
	if (!fnAdd_VectorVector) {
		fnAdd_VectorVector = Core.pFindObject(xor_w(L"KismetMathLibrary.Add_VectorVector"));
	}

	struct {
		FVector A;
		FVector B;
		FVector ReturnValue;
	} params;
	params.A = A;
	params.B = B;

	ProcessEvent(Globals::UGameViewportClient, fnAdd_VectorVector, &params);

	return params.ReturnValue;
}
FRotator SDK::RInterpTo(const struct FRotator& Current, const struct FRotator& Target, float DeltaTime, float InterpSpeed)
{
	static uint64_t fnRInterpTo = NULL;
	if (!fnRInterpTo) {
		fnRInterpTo = Core.pFindObject(xor_w(L"KismetMathLibrary.RInterpTo"));
	}

	struct {
		FRotator Current;
		FRotator Target;
		float DeltaTime;
		float InterpSpeed;
		FRotator ReturnValue;
	} params;
	params.Current = Current;
	params.Target = Target;
	params.DeltaTime = DeltaTime;
	params.InterpSpeed = InterpSpeed;

	ProcessEvent(Globals::UGameViewportClient, fnRInterpTo, &params);

	return params.ReturnValue;
}
FRotator SDK::RInterpTo_Constant(FRotator& Current, FRotator& Target, float DeltaTime, float InterpSpeed)
{

	static uint64_t fnRInterpTo_Constant = NULL;
	if (!fnRInterpTo_Constant) {
		fnRInterpTo_Constant = Core.pFindObject(xor_w(L"KismetMathLibrary.RInterpTo_Constant"));
	}

	struct {
		FRotator Current;
		FRotator Target;
		float DeltaTime;
		float InterpSpeed;
		FRotator ReturnValue;
	} params;
	params.Current = Current;
	params.Target = Target;
	params.DeltaTime = DeltaTime;
	params.InterpSpeed = InterpSpeed;

	ProcessEvent(Globals::UGameViewportClient, fnRInterpTo_Constant, &params);

	return params.ReturnValue;
}
float SDK::NormalizeAxis(float Angle)
{
	static uint64_t fnNormalizeAxis = NULL;
	if (!fnNormalizeAxis) {
		fnNormalizeAxis = Core.pFindObject(xor_w(L"KismetMathLibrary.NormalizeAxis"));
	}

	struct {
		float Angle;
		float ReturnValue;
	} params;
	params.Angle = Angle;

	ProcessEvent(Globals::UGameViewportClient, fnNormalizeAxis, &params);

	return params.ReturnValue;
}

// KismetStringLibrary //
FName SDK::Conv_StringToName(const FString& InString)
{
	static uint64_t fnConv_StringToName = NULL;
	if (!fnConv_StringToName) {
		fnConv_StringToName = Core.pFindObject(xor_w(L"KismetStringLibrary.Conv_StringToName"));
	}

	static uint64_t KismetStringLibrary = Core.pFindObject(xor_w(L"Engine.Default__KismetStringLibrary"));

	struct {
		struct FString InString;
		struct FName ReturnValue;
	} params;
	params.InString = InString;

	ProcessEvent(KismetStringLibrary, fnConv_StringToName, &params);

	return params.ReturnValue;
}
FString SDK::Conv_NameToString(const FName& InName)
{
	static uint64_t fnConv_NameToString = NULL;
	if (!fnConv_NameToString) {
		fnConv_NameToString = Core.pFindObject(xor_w(L"KismetStringLibrary.Conv_NameToString"));
	}

	struct {
		struct FName InName;
		struct FString ReturnValue;
	} params;
	params.InName = InName;

	ProcessEvent(Globals::UGameViewportClient, fnConv_NameToString, &params);

	return params.ReturnValue;
}
FString SDK::Concat_StrStr(const FString& A, const FString& B)
{
	static uint64_t fnConcat_StrStr = NULL;
	if (!fnConcat_StrStr) {
		fnConcat_StrStr = Core.pFindObject(xor_w(L"KismetStringLibrary.Concat_StrStr"));
	}

	struct {
		struct FString A;
		struct FString B;
		struct FString ReturnValue;
	} params;
	params.A = A;
	params.B = B;

	ProcessEvent(Globals::UGameViewportClient, fnConcat_StrStr, &params);

	return params.ReturnValue;
}
FString SDK::BuildString_Int(const FString& AppendTo, const FString& Prefix, int32_t inInt, const FString& Suffix)
{
	static uint64_t fnBuildString_Int = NULL;
	if (!fnBuildString_Int) {
		fnBuildString_Int = Core.pFindObject(xor_w(L"KismetStringLibrary.BuildString_Int"));
	}

	struct {
		struct FString AppendTo;
		struct FString Prefix;
		int32_t inInt;
		struct FString Suffix;
		struct FString ReturnValue;
	} params;
	params.AppendTo = AppendTo;
	params.Prefix = Prefix;
	params.inInt = inInt;
	params.Suffix = Suffix;

	ProcessEvent(Globals::UGameViewportClient, fnBuildString_Int, &params);

	return params.ReturnValue;
}
FString SDK::BuildString_Double(const struct FString& AppendTo, const struct FString& Prefix, double InDouble, const struct FString& Suffix)
{
	static uint64_t fnBuildString_Double = NULL;
	if (!fnBuildString_Double) {
		fnBuildString_Double = Core.pFindObject(xor_w(L"KismetStringLibrary.BuildString_Double"));
	}
	
	struct {
		struct FString AppendTo;
		struct FString Prefix;
		double InDouble;
		struct FString Suffix;
		struct FString ReturnValue;
	} params;
	params.AppendTo = AppendTo;
	params.Prefix = Prefix;
	params.InDouble = InDouble;
	params.Suffix = Suffix;

	ProcessEvent(Globals::UGameViewportClient, fnBuildString_Double, &params);

	return params.ReturnValue;
}
bool SDK::Contains(const struct FString& SearchIn, const struct FString& Substring, bool bUseCase, bool bSearchFromEnd)
{
	static uint64_t fnContains = NULL;
	if (!fnContains) {
		fnContains = Core.pFindObject(xor_w(L"KismetStringLibrary.Contains"));
	}

	struct {
		struct FString SearchIn;
		struct FString Substring;
		bool bUseCase;
		bool bSearchFromEnd;
		bool ReturnValue;
	} params;
	params.SearchIn = SearchIn;
	params.Substring = Substring;
	params.bUseCase = bUseCase;
	params.bSearchFromEnd = bSearchFromEnd;

	ProcessEvent(Globals::UGameViewportClient, fnContains, &params);

	return params.ReturnValue;
}

// FortKismetLibrary //
uint64_t SDK::AttemptGetPlayerStateForPawn(uint64_t FortPawn)
{
	static uint64_t fnAttemptGetPlayerStateForPawn = NULL;
	if (!fnAttemptGetPlayerStateForPawn) {
		fnAttemptGetPlayerStateForPawn = Core.pFindObject(xor_w(L"FortKismetLibrary.AttemptGetPlayerStateForPawn"));
	}

	struct {
		uint64_t FortPawn;
		uint64_t ReturnValue;
	} params;
	params.FortPawn = FortPawn;

	ProcessEvent(Globals::UGameViewportClient, fnAttemptGetPlayerStateForPawn, &params);

	return params.ReturnValue;
}
void SDK::ApplyCharacterCosmetics(uint64_t PlayerState, TArray<UObject*> CharacterParts)
{
	static uint64_t fnApplyCharacterCosmetics = NULL;
	if (!fnApplyCharacterCosmetics) {
		fnApplyCharacterCosmetics = Core.pFindObject(xor_w(L"FortKismetLibrary.ApplyCharacterCosmetics"));
	}

	struct {
		uint64_t WorldContextObject;
		TArray<UObject*> CharacterParts;
		uint64_t PlayerState;
		uint64_t bSuccess;
	} params;
	params.WorldContextObject = Globals::World;
	params.CharacterParts = CharacterParts;
	params.PlayerState = PlayerState;

	ProcessEvent(Globals::UGameViewportClient, fnApplyCharacterCosmetics, &params);

	//if (bSuccess != nullptr)
		//*bSuccess = params.bSuccess;
}

// KismetRenderingLibrary //
uint64_t SDK::ImportFileAsTexture2D(const struct FString& Filename)
{
	static uint64_t fnImportFileAsTexture2D = NULL;
	if (!fnImportFileAsTexture2D) {
		fnImportFileAsTexture2D = Core.pFindObject(xor_w(L"KismetRenderingLibrary.ImportFileAsTexture2D"));
	}

	struct {
		uintptr_t WorldContextObject;
		FString Filename;
		uint64_t ReturnValue;
	} params;
	params.WorldContextObject = Globals::World;
	params.Filename = Filename;

	ProcessEvent(Globals::UGameViewportClient, fnImportFileAsTexture2D, &params);

	return params.ReturnValue;
}

// ScriptStruct McpProfileSys.BaseUrlContext
// Size: 0x80 (Inherited: 0x00)
struct FBaseUrlContext {
	char pad_0[0x80]; // 0x00(0x80)
};

// ScriptStruct McpProfileSys.ClientUrlContext
// Size: 0x80 (Inherited: 0x80)
struct FClientUrlContext : FBaseUrlContext {
};

// FortMcpProfileAthena //
void SDK::ApplyCosmeticLoadout(uint64_t pawn)
{
	static uint64_t fnApplyCosmeticLoadout = NULL;
	if (!fnApplyCosmeticLoadout) {
		fnApplyCosmeticLoadout = Core.pFindObject(xor_w(L"FortPlayerPawn.ApplyCosmeticLoadout"));
	}

	struct {
	} params;

	ProcessEvent(pawn, fnApplyCosmeticLoadout, &params);
}
FText SDK::GetSubType(uint64_t hero)
{
	static uint64_t fnGetSubType = NULL;
	if (!fnGetSubType) {
		fnGetSubType = Core.pFindObject(xor_w(L"FortHeroType.GetSubType"));
	}

	struct {
		struct FText                          ReturnValue;                                              // (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm)
	} params;

	ProcessEvent(hero, fnGetSubType, &params);

	return params.ReturnValue;
}

void SDK::ServerChoosePart(uint64_t pawn, TEnumAsByte<EFortCustomPartType> Part, uint64_t ChosenCharacterPart)
{
	static uint64_t fnServerChoosePart = NULL;
	if (!fnServerChoosePart) {
		fnServerChoosePart = Core.pFindObject(xor_w(L"FortPlayerPawn.ServerChoosePart"));
	}

	struct {
		TEnumAsByte<EFortCustomPartType>                   Part;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
		uint64_t ChosenCharacterPart;                                      // (Parm, ZeroConstructor)
	} params;
	params.Part = Part;
	params.ChosenCharacterPart = ChosenCharacterPart;

	ProcessEvent(pawn, fnServerChoosePart, &params);
}
void SDK::ServerChooseGender(uint64_t pawn, TEnumAsByte<EFortCustomGender> Gender)
{
	static uint64_t fnServerChooseGender = NULL;
	if (!fnServerChooseGender) {
		fnServerChooseGender = Core.pFindObject(xor_w(L"FortPlayerPawn.ServerChooseGender"));
	}

	struct {
		TEnumAsByte<EFortCustomGender>                   Gender;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	} params;
	params.Gender = Gender;

	ProcessEvent(pawn, fnServerChooseGender, &params);
}
