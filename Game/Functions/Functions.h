#pragma once
#include "../../stdafx.h"

class SDK;

class Functions {
private:
	bool isRadarDragging = false;
	FVector2D RadarDragOffset = FVector2D(0, 0);

public:
	void Draw2DBoundingBox(uint64_t Actor, FVector Bottom, FVector Top, FLinearColor Color);

	//bool isValidWcharString(const wchar_t* str);

	void World_Loop();

	void Draw_RadarBackground();
	void Draw_RadarPlayers(FVector world_location, FLinearColor color);

	Camera_Struct get_camera();

	FVector GetAimBone(uint64_t PlayerMesh, int AimBone);

	FVector GetAllBones(uint64_t PlayerMesh, int AimBone);

	bool TB_AlsoCheckTarget(bool isShoty);

	void DrawFilledRect(FVector2D initial_pos, float width, float height, FLinearColor color);
	bool isNotName(const wchar_t* plrname);
	bool IsValidScreenLoc(const FVector& Loc);
	bool WorldToScreen(FVector& WorldLocation, FVector2D* screenLocation);
	bool IsShootable(FVector lur, FVector wl);

	SpecialStruct GetColorFromOption(int num);
	FVector2D Grizel(FVector Cunigund, FRotator Garnett, FVector Location, double RadarX, double RadarY, int size);

	FLinearColor GetItemColor(EFortItemTier tier);
	std::wstring GetItemTierName(EFortItemTier tier);
	EFortItemTier GetItemEFortTier(float tier);

	void DrawCircle(int x, int y, int radius, int sides, FLinearColor color);
	void DrawFilledCircle(int x, int y, int radius, FLinearColor color);

	FRotator SmoothMe(FRotator startRotation, FRotator endRotation, float SmoothScale);

	//FVector Predict(FVector pos, FVector Velocity, uint64_t WeaponData, float distance);
	void Predict(uint64_t WeaponData);

	FRotator FindLookAtRotation(FVector& start, FVector& target);
	void InitializeAimbot(FVector AimLocation, int cwsmComerl);
} inline Functions;

extern Camera_Struct vCamera;