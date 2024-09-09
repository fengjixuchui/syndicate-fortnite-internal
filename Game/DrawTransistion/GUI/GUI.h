#pragma once
#include "../../../stdafx.h"

#ifndef RAID
class GUI {
private:
	FVector2D MenuSize = FVector2D(/*511*/615, 630); //Menu Size
	FVector2D MenuPosition = FVector2D(69.6969, 0); //Menu Pos
	bool IsDragging = false;
	FVector2D DragOffset = FVector2D(0, 0);
	int CurrentOption = 0;
	int CurrentTab = 2;
	int SpecialOption = 0;

public:
	bool Left_WasInputKeyJustPressed = false;
	FVector2D MousePosition = FVector2D(0, 0); //Menu Pos

	bool IsMouseHovering(FVector2D position, FVector2D size);
	void UpdateSkins();
	void AddSkinsOption(FVector2D* Rudolf, int* id, const wchar_t* optionName, TArray<uint64_t> Cosmetics, bool* isTyping, FString* input, uint64_t* OutCosmetic);
	void AddOption(FVector2D* Rudolf, int* id, const wchar_t* Kai/*optionName*/, int Meshulam/*type*/, bool* Soudeh = nullptr/*toggle*/, int* optionValue = nullptr, int increaseBy = 1, int min = 0, int max = 0, FKey& specia2 = Globals::AimKey);
	//void DrawSkinList(TArray<uint64_t> Cosmetics, bool* Typing, FString* InputText, uint64_t* OutCosmetic);
	void InitOptions(FVector2D Rudolfy);
	void HandleMenuMouse();
	void DrawMenu();
} inline GUI;

#else

class GUI {
private:
	int SelectedOptionIndex = 0;
	int iShowDuplicateMenu = 0;  // Flag to control the visibility of the duplicated menu
	int SelectedOptionIndexDuplicate = 0;  // Selected option index for the duplicated menu
	float MenuWidth = 290.f;
	float DuplicateMenuMenuHeight = 35.f;
	FLinearColor OptionTextColor = { 255.f, 255.f, 255.f, 1.f };  // White color
	FLinearColor OptionRectColorInactive = { 0.f, 0.f, 0.f, 0.f };  // No rect when inactive
	FLinearColor OptionRectColorActive = { 220.f, 0.f, 0.f, 1.f };  // Theme color (when active/selected and for titles)
	int RenderFKey_Busy = -1;

public:
	void AddOption(FVector2D DuplicateMenuPosition, int& OptionIndex, double DuplicateTitleSizeY, wchar_t* OptionName, bool& OptionValue);
	void AddOption(FVector2D DuplicateMenuPosition, int& OptionIndex, double DuplicateTitleSizeY, wchar_t* OptionName, int& OptionValue, int min = 1, int max = 1, bool isFastInt = false, bool isBonesOption = false);
	void setFKey(FKey Key, FKey& OptionValue);
	void AddOption(FVector2D DuplicateMenuPosition, int& OptionIndex, double DuplicateTitleSizeY, const wchar_t* OptionName, FKey& OptionValue);

	void DrawMenu();
} inline GUI;

#endif