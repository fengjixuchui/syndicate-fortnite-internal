#pragma once
#include "../stdafx.h"

namespace Globals {
	/* My Initializations */
	inline bool HasInitGlobals = FALSE;
	inline int Width = 0;
	inline int Height = 0;
	inline float HudScale = 0;
	inline int Smoothing = 0;
	inline bool IsAiming = FALSE;

	/* For Skin Changer */
	//inline TArray<uint64_t> SkinCharacterParts;
	inline std::vector<uint64_t> SkinCharacterParts;
	inline uint64_t CustomPartsByType[(int)EFortCustomPartType::NumTypes];

	/* Main Addresses */
	inline uint64_t base_address = NULL;

	/* Game Address */
	inline void(*DrawTransition)(void* pObject, void* pCanvas);
	inline uint64_t UGameViewportClient = NULL;
	inline uint64_t UCanvas = NULL;
	inline uintptr_t GWorld = NULL;
	inline uintptr_t World = NULL;
	//inline uintptr_t EnableRecoil = NULL;
	//inline uintptr_t UEngine = NULL;
	inline void* (*StaticFindFirstObject_t)(void* Class, WCHAR* Name, UINT64 Options, UINT64 AmbiguousMessageVerbosity, const TCHAR* InCurrentOperation);
	inline void* (*StaticLoadObject_t)(void* ObjectClass, void* InOuter, const TCHAR* InName, const TCHAR* Filename, UINT64 LoadFlags, void* Sandbox, bool bAllowObjectReconciliation, void* InstancingContext);
	inline void* (*UpdateCharacterCustomization_t)(uint64_t AFortPlayerPawn);
	inline void* (*GetObjectsOfClass_t)(uint64_t Class, TArray<uint64_t>* results, bool includederived, int excludeflags, int excludeflagsinternal);
	//inline void* (*InitWeaponCosmetics_t)(uint64_t CurrentWeapon);
	//inline void(*SetControlRotationOriginal)(uint64_t* _this, FRotator Rotation);
	//inline FRotator* (*GetControlRotationOriginal)(uint64_t* PlayerController, FRotator* Rotation);

	//inline uintptr_t TranslucentMaterial = NULL;
	inline FName Blank;
	inline uintptr_t PlayerController = NULL;
	inline uintptr_t OldPlayerController = NULL;
	inline uint64_t PlayerCameraManager = NULL;
	inline uint64_t RootComponent = NULL;
	inline uint64_t PlayerState = NULL;
	inline uint64_t MyPlayer = NULL;
	inline uint64_t LastEnemyAddress = NULL;
	inline uint64_t CurrentWeapon = NULL;
	inline uint64_t OldCurrentWeapon = NULL;
	inline uint64_t ClosestPlayer = NULL;
	inline EFortItemType CurrentWeaponType = EFortItemType::Max_None;
	inline FVector AimLocation;
	inline FRotator ControlRotation;
	inline FRotator AimRotation;
	inline FVector2D AimLocation2D;
	inline FVector PredictedAimLocation;
	inline int colorOrder = 1;
	inline bool STATIC_NeedUpdateCharacterCustomization_t = false;
	//inline bool InLobby = true;
	inline double playersSavedColors[100][3]{};
	//inline TArray<FKey> Keys;
	inline TArray<uint64_t> SkinCIDS;
	inline TArray<uint64_t> BackpackCIDS;
	//inline TArray<uint64_t> PickaxeCIDS;
	//inline uint64_t FortWeaponMeleeItemDefinition = NULL;
	inline uint64_t AthenaCharacterItemDefinition = NULL;
	inline uint64_t AthenaBackpackItemDefinition = NULL;
	//inline uint64_t AthenaPickaxeItemDefinition = NULL;

	// Fonts
	//inline uint64_t Roboto = NULL;
	//inline uint64_t NotoSans = NULL;
	inline uint64_t Burbank = NULL;
	inline uint64_t HeadingNow = NULL;

	// classes
	inline uint64_t AFortAIPawn = NULL;
	inline uint64_t FortPickup = NULL;
	inline uint64_t FortAthenaSKVehicle = NULL;
	inline uint64_t FortAthenaSupplyDrop = NULL;
	inline uint64_t BuildingContainer = NULL;
	//inline uint64_t BuildingActor = NULL;
	//inline uint64_t BuildingTrap = NULL;
	inline uint64_t ScalableFloatUtils = NULL;

	// FKeys
	inline FKey MouseScrollUp;
	inline FKey MouseScrollDown;
	inline FKey MouseWheelAxis;
	inline FKey LeftMouseButton;
	inline FKey RightMouseButton;
	inline FKey MiddleMouseButton;
	inline FKey ThumbMouseButton;
	inline FKey ThumbMouseButton2;
	inline FKey BackSpace;
	inline FKey Tab;
	inline FKey Enter;
	inline FKey Pause;
	inline FKey CapsLock;
	inline FKey Escape;
	inline FKey SpaceBar;
	inline FKey PageUp;
	inline FKey PageDown;
	inline FKey End;
	inline FKey Home;
	inline FKey Left;
	inline FKey Up;
	inline FKey Right;
	inline FKey Down;
	inline FKey Insert;
	inline FKey Delete;
	inline FKey Zero;
	inline FKey One;
	inline FKey Two;
	inline FKey Three;
	inline FKey Four;
	inline FKey Five;
	inline FKey Six;
	inline FKey Seven;
	inline FKey Eight;
	inline FKey Nine;
	inline FKey A;
	inline FKey B;
	inline FKey C;
	inline FKey D;
	inline FKey E;
	inline FKey F;
	inline FKey G;
	inline FKey H;
	inline FKey I;
	inline FKey J;
	inline FKey K;
	inline FKey L;
	inline FKey M;
	inline FKey N;
	inline FKey O;
	inline FKey P;
	inline FKey Q;
	inline FKey R;
	inline FKey S;
	inline FKey T;
	inline FKey U;
	inline FKey V;
	inline FKey W;
	inline FKey X;
	inline FKey Y;
	inline FKey Z;
	inline FKey NumPadZero;
	inline FKey NumPadOne;
	inline FKey NumPadTwo;
	inline FKey NumPadThree;
	inline FKey NumPadFour;
	inline FKey NumPadFive;
	inline FKey NumPadSix;
	inline FKey NumPadSeven;
	inline FKey NumPadEight;
	inline FKey NumPadNine;
	inline FKey Multiply;
	inline FKey Add;
	inline FKey Subtract;
	inline FKey Decimal;
	inline FKey Divide;
	inline FKey F1;
	inline FKey F2;
	inline FKey F3;
	inline FKey F4;
	inline FKey F5;
	inline FKey F6;
	inline FKey F7;
	inline FKey F8;
	inline FKey F9;
	inline FKey F10;
	inline FKey F11;
	inline FKey F12;
	inline FKey NumLock;
	inline FKey ScrollLock;
	inline FKey LeftShift;
	inline FKey RightShift;
	inline FKey LeftControl;
	inline FKey RightControl;
	inline FKey LeftAlt;
	inline FKey RightAlt;
	inline FKey LeftCommand;
	inline FKey RightCommand;
	inline FKey Semicolon;
	inline FKey Equals;
	inline FKey Comma;
	inline FKey Underscore;
	inline FKey Hyphen;
	inline FKey Period;
	inline FKey Slash;
	inline FKey Tilde;
	inline FKey LeftBracket;
	inline FKey LeftParantheses;
	inline FKey Backslash;
	inline FKey RightBracket;
	inline FKey RightParantheses;
	inline FKey Apostrophe;
	inline FKey Quote;
	inline FKey Asterix;
	inline FKey Ampersand;
	inline FKey Caret;
	inline FKey Dollar;
	inline FKey Exclamation;
	inline FKey Colon;
	inline FKey Section;
	inline FKey Gamepad_Left2D;
	inline FKey Gamepad_LeftX;
	inline FKey Gamepad_LeftY;
	inline FKey Gamepad_Right2D;
	inline FKey Gamepad_RightX;
	inline FKey Gamepad_RightY;
	inline FKey Gamepad_LeftTriggerAxis;
	inline FKey Gamepad_RightTriggerAxis;
	inline FKey Gamepad_LeftThumbstick;
	inline FKey Gamepad_RightThumbstick;
	inline FKey Gamepad_Special_Left;
	inline FKey Gamepad_Special_Left_X;
	inline FKey Gamepad_Special_Left_Y;
	inline FKey Gamepad_Special_Right;
	inline FKey Gamepad_FaceButton_Bottom;
	inline FKey Gamepad_FaceButton_Right;
	inline FKey Gamepad_FaceButton_Left;
	inline FKey Gamepad_FaceButton_Top;
	inline FKey Gamepad_LeftShoulder;
	inline FKey Gamepad_RightShoulder;
	inline FKey Gamepad_LeftTrigger;
	inline FKey Gamepad_RightTrigger;
	inline FKey Gamepad_DPad_Up;
	inline FKey Gamepad_DPad_Down;
	inline FKey Gamepad_DPad_Right;
	inline FKey Gamepad_DPad_Left;
	inline FKey Gamepad_LeftStick_Up;
	inline FKey Gamepad_LeftStick_Down;
	inline FKey Gamepad_LeftStick_Right;
	inline FKey Gamepad_LeftStick_Left;
	inline FKey Gamepad_RightStick_Up;
	inline FKey Gamepad_RightStick_Down;
	inline FKey Gamepad_RightStick_Right;
	inline FKey Gamepad_RightStick_Left;

	// Menu FKeys
	inline FKey MenuKey;
	inline FKey PanicKey;
	inline FKey TriggerKey;
	inline FKey AimKey;
	//inline FKey LootPickerKey;
	//inline FKey LootDestroyerKey;

	// Fnames
	inline FName HeadName;
	inline FName RootName;
	inline FName NeckName;
	inline FName LowerNeckName;
	inline FName ChestName;
	inline FName PelvisName;
	inline FName Upperarm_lName;
	inline FName Upperarm_rName;
	inline FName Lowerarm_lName;
	inline FName Lowerarm_rName;
	inline FName Hand_lName;
	inline FName Hand_rName;
	inline FName Thigh_lName;
	inline FName Thigh_rName;
	inline FName Calf_lName;
	inline FName Calf_rName;
	inline FName LowerCalf_lName;
	inline FName LowerCalf_rName;
	inline FName Foot_lName;
	inline FName Foot_rName;
	inline FName Toe_lName;
	inline FName Toe_rName;

	inline FVector vRootOut,
		vHeadBoneOut, 
		vNeckOut, 
		FAKEvHeadBoneOut, 
		FAKEvNeckOut,
		vLowerNeckOut,
		vChestOut, 
		pelvisOut, 
		vUpperArmLeftOut, 
		vUpperArmRightOut,
		vLeftHandOut,
		vRightHandOut, 
		vLeftHandOut1, 
		vRightHandOut1, 
		vRightThighOut,
		vLeftThighOut, 
		vRightKneeOut, 
		vLeftKneeOut, 
		vLeftLowCalfOut, 
		vRightLowCalfOut,
		leftFeet2d,
		rightFeet2d, 
		leftFeetFinger2d, 
		rightFeetFinger2d;

	struct Bone {
		FName name;
		FVector location;
		FVector socketLoc;
	};
	inline Bone bones[22];
}