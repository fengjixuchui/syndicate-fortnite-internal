#pragma once
#include "../../stdafx.h"

#define M_PI 3.14159265358979323846264338327950288419716939937510582f

class SDK {
private:

	static void ProcessEvent(uint64_t Object, uint64_t Function, void* Args) {
		if (!Object)
			return;

		auto index = *reinterpret_cast<void***>(Object); if (!index) return;
		auto fProcessEvent = static_cast<void(*)(void* Object, void* Function, void* Args)>(index[0x4E]); if (!fProcessEvent) return;
		fProcessEvent((void*)Object, (void*)Function, (void*)Args);
	}

public:
	// UWorld
	uint64_t K2_GetWorldSettings();

	// GameplayStatics
	uint64_t GetGameInstance();
	uint64_t GetPlayerController();
	uint64_t GetPlayerCameraManager();
	uint64_t GetPlayerState();
	void GetAllActorsOfClass(uint64_t ActorClass, TArray<uint64_t*>* OutActors);
	double GetTimeSeconds();
	EMouseCaptureMode GetViewportMouseCaptureMode();
	bool ObjectIsA(uintptr_t Object, uintptr_t ObjectClass);
	double GetWorldDeltaSeconds();

	// PlayerController
	void GetViewportSize(int* SizeX, int* SizeY);
	bool WasInputKeyJustPressed(const struct FKey& Key);
	bool WasInputKeyJustReleased(const struct FKey& Key);
	bool IsInputKeyDown(const struct FKey& Key);
	bool GetMousePosition(float* LocationX, float* LocationY);
	FVector2D VectorGetMousePosition();

	// FortPlayerController
	FVector GetLocationUnderReticle();
	uint64_t GetClientSettings();

	// Controller
	uint64_t K2_GetPawn();

	// Actor
	uint64_t K2_GetRootComponent(uint64_t actor);
	FVector K2_GetActorLocation(uint64_t Actor);
	FRotator K2_GetActorRotation(uint64_t Actor);
	FVector GetVelocity(uint64_t Actor);
	void GetActorBounds(uint64_t Actor, bool bOnlyCollidingComponents, bool bIncludeFromChildActors, struct FVector* Origin, struct FVector* BoxExtent);

	// FortClientSettingsRecord
	float GetHUDScale(uint64_t ClientSettingsRecord);

	// FortKismetLibrary
	TArray<uint64_t> GetFortPlayerPawns();
	int GetLootLevel();
	FString GetHumanReadableName(uint64_t Actor);
	bool OnSameTeam(uint64_t ActorA, uint64_t ActorB);

	// Pawn
	bool IsBotControlled(uint64_t Actor);

	// FortPawn
	bool IsDead(uint64_t object);
	bool IsDBNO(uint64_t object);
	uint64_t GetCurrentWeapon(uint64_t Actor);
	void PawnStopFire();
	void PawnStartFire();

	//CharacterMovementComponent
	FVector GetLastUpdateVelocity(uint64_t CharacterMovement);

	// FortWeapon
	uint64_t GetWeaponData(uint64_t CurrentWeapon);
	void SetWeaponData(uint64_t CurrentWeapon, uint64_t InWeaponData);
	int GetMagazineAmmoCount(uint64_t CurrentWeapon);
	int GetBulletsPerClip(uint64_t CurrentWeapon);
	FVector GetTargetingSourceLocation(uint64_t CurrentWeapon);
	float GetProjectileSpeed(uint64_t CurrentWeapon, float ChargePercent);
	float GetChargePercent(uint64_t CurrentWeapon);
	TEnumAsByte<EFortWeaponCoreAnimation> GetCoreAnimation(uint64_t Weapon);

	// PlayerState
	bool IsABot();
	uint64_t GetPlayerControllerFromPlayerState(uint64_t playerState);

	// FortPlayerState
	FString GetPlatform(uint64_t PlayerState);
	uint64_t GetCurrentPawn(uint64_t PlayerState);

	// FortPlayerStateAthena
	bool IsAnAthenaGameParticipant();
	int GetKillScore(uint64_t PlayerState);

	// FortPlayerStateZone
	int GetSpectatorCount();

	// FortPickup
	uint64_t GetPrimaryItemDefinition(uint64_t Actor);

	// FortItemDefinition
	EFortItemTier GetTier(uint64_t ItemDefinition);
	EFortItemType GetItemType(uint64_t ItemDefinition);
	FFortColorPalette GetRarityOrSeriesColors(uint64_t ItemDefinition);
	TSoftObjectPtr<UObject> GetSmallPreviewImage(uint64_t ItemDefinition);

	// UItemDefinitionBase
	FText GetDisplayName(uint64_t ItemDefinition);

	// FortWeaponRangedItemDefinition
	uint64_t GetProjectileTemplate(uint64_t WeaponData);
	bool HasLightweightProjectile(uint64_t WeaponData);
	bool IsProjectileWeapon(uint64_t CurrentWeapon);

	// AthenaCharacterPartItemDefinition
	TArray<uint64_t> GetCharacterParts(uint64_t ItemDefinition);

	// FortScalableFloatUtils
	float GetValue(FScalableFloat& Input);
	float GetValueAtLevel(FScalableFloat Input, int Level);

	// BuildingTrap
	bool HasDurability(uint64_t Actor);
	float GetArmTime(uint64_t Actor);

	// SceneComponent
	FVector GetSocketLocation(uint64_t object, const struct FName& InSocketName);
	FVector GetComponentVelocity(uint64_t RootComponent);
	FRotator K2_GetComponentRotation(uint64_t RootComponent);

	// PrimitiveComponent
	int GetNumMaterials(uint64_t Mesh);
	void SetMaterial(uint64_t Mesh, int ElementIndex, uintptr_t Material);
	void SetRenderCustomDepth(uint64_t Mesh, bool bValue);
	void SetCustomDepthStencilValue(uint64_t Mesh, int Value);
	uint64_t GetMaterial(uint64_t Mesh, int ElementIndex);
	uint64_t CreateDynamicMaterialInstance(uint64_t Mesh, int ElementIndex, uint64_t SourceMaterial, const struct FName& OptionalName);

	uintptr_t CreateDynamicMaterialInstance(uint64_t Parent);
	uintptr_t GetBaseMaterial(uintptr_t MaterialInterface);

	// MaterialInstanceDynamic
	void SetVectorParameterValue(uint64_t MaterialInstanceDynamic, const struct FName& ParameterName, const struct FLinearColor& Value);

	// FortAthenaVehicle
	FString VehicleGetDisplayName(uint64_t Actor);
	bool CanContainPlayers(uint64_t Actor);

	// BuildingActor
	void SetQuestHighlight(bool Enabled);

	// Canvas
	FVector K2_Project(const struct FVector& WorldLocation);
	void K2_DrawLine(FVector2D A, FVector2D B, float Thickness, FLinearColor Color);
	void K2_DrawBox(const struct FVector2D& ScreenPosition, const struct FVector2D& ScreenSize, float Thickness, const struct FLinearColor& RenderColor);
	FVector2D K2_TextSize(uint64_t font, const struct FString& RenderText, const struct FVector2D& Scale);
	FVector2D K2_StrLen(uint64_t RenderFont, const struct FString& RenderText);
	void K2_DrawText(uint64_t font, const struct FString& RenderText, const struct FVector2D& ScreenPosition, const struct FVector2D& Scale, const struct FLinearColor& RenderColor, double Kerning, const struct FLinearColor& ShadowColor, const struct FVector2D& ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, const struct FLinearColor& OutlineColor);
	void K2_DrawPolygon(uintptr_t RenderTexture, const struct FVector2D& ScreenPosition, const struct FVector2D& Radius, int NumberOfSides, const struct FLinearColor& RenderColor);
	void K2_DrawTexture(uintptr_t RenderTexture, const struct FVector2D& ScreenPosition, const struct FVector2D& ScreenSize, const struct FVector2D& CoordinatePosition, const struct FVector2D& CoordinateSize, const struct FLinearColor& RenderColor, TEnumAsByte<EBlendMode> BlendMode, float Rotation, const struct FVector2D& PivotPoint);

	// KismetSystemLibrary
	bool LineTraceSingle(const struct FVector& Start, const struct FVector& End);
	FString GetObjectName(uint64_t Object);
	void GetComponentBounds(uint64_t Component, struct FVector* Origin, struct FVector* BoxExtent, float* SphereRadius);
	uintptr_t GetOuterObject(uintptr_t Object);

	// KismetMathLibrary
	double asin(double A);
	double Atan2(double Y, double X);
	__int32 Round(double A);
	double Abs(double A);
	double Cos(double A);
	double Sin(double A);
	double Sqrt(double A);
	double Vector_Distance(const struct FVector& v1, const struct FVector& v2);
	FRotator FindLookAtRotation(const struct FVector& Start, const struct FVector& Target);
	FVector Quat_RotateVector(const struct FQuat& Q, const struct FVector& V);
	FVector Subtract_VectorVector(const struct FVector& A, const struct FVector& B);
	double VSize(const struct FVector& A);
	FVector Add_VectorVector(const struct FVector& A, const struct FVector& B);
	FRotator RInterpTo(const FRotator& Current, const FRotator& Target, float DeltaTime, float InterpSpeed);
	FRotator RInterpTo_Constant(FRotator& Current, FRotator& Target, float DeltaTime, float InterpSpeed);
	float NormalizeAxis(float Angle);

	// KismetStringLibrary
	FName Conv_StringToName(const struct FString& InString);
	FString Conv_NameToString(const FName& InName);
	FString Concat_StrStr(const struct FString& A, const struct FString& B);
	FString BuildString_Int(const struct FString& AppendTo, const struct FString& Prefix, int32_t inInt, const struct FString& Suffix);
	FString BuildString_Double(const struct FString& AppendTo, const struct FString& Prefix, double InDouble, const struct FString& Suffix);
	bool Contains(const struct FString& SearchIn, const struct FString& Substring, bool bUseCase, bool bSearchFromEnd);

	// FortKismetLibrary
	uint64_t AttemptGetPlayerStateForPawn(uint64_t FortPawn);
	void ApplyCharacterCosmetics(uint64_t PlayerState, TArray<UObject*> CharacterParts);

	// KismetRenderingLibrary
	uint64_t ImportFileAsTexture2D(const struct FString& Filename);

	// FortMcpProfileAthena //
	void ApplyCosmeticLoadout(uint64_t pawn);
	FText GetSubType(uint64_t hero);
	void ServerChoosePart(uint64_t pawn, TEnumAsByte<EFortCustomPartType> Part, uint64_t ChosenCharacterPart);
	void ServerChooseGender(uint64_t pawn, TEnumAsByte<EFortCustomGender> Gender);
} inline SDK;