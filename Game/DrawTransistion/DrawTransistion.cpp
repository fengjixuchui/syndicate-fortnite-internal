#include "DrawTransistion.h"

//double* (*GetWeaponTargetingTransformOriginal)(uint64_t* _this, double* Start, double* Direction);
//double* GetWeaponTargetingTransform_hk(uint64_t* _this, double* Start, double* Direction)
//{
//	double* Return = GetWeaponTargetingTransformOriginal(_this, Start, Direction);
//
//	if (Config.Aimbot.AimKey == 2 && Config.Misc.PSilent && Globals::ClosestPlayer && Globals::MyPlayer)
//	{
//		Direction[0] = Globals::AimLocation.X - Start[0];
//		Direction[1] = Globals::AimLocation.Y - Start[1];
//		Direction[2] = Globals::AimLocation.Z - Start[2];
//	}
//	return Return;
//}

//FRotator* (*GetControlRotationOriginal)(void*, FRotator*);
//FRotator* GetControlRotation(void* PlayerController, FRotator* Rotation)
//{
//	GetControlRotationOriginal(PlayerController, Rotation);
//
//	if (Rotation) {
//		if (Globals::ControlRotation = *Rotation) {
//			if (PlayerController && Globals::IsAiming && Globals::AimLocation && Globals::AimRotation)
//			{
//				*Rotation = Globals::AimRotation;
//			}
//		}
//	}
//
//	return Rotation;
//}

//void* pCustomVTABLE[1820];
//uint64_t* Page2 = 0;
//bool genetic_4(void* Object, void* HookFunction, void** HookOrig, DWORD Index)
//{
//	if (!Page2)
//		Page2 = (uint64_t*)LI_FN(VirtualAlloc).safe_cached()(0, 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
//
//	void* ObjectVTable = *(void**)((uint64_t)Object);
//	if (ObjectVTable == pCustomVTABLE)
//		return false;
//
//	custom_MemCpy(pCustomVTABLE, ObjectVTable, sizeof(pCustomVTABLE));
//
//	uint8_t HookTemplate[14] = { 0xFF, 0x25, 0, 0, 0, 0 };
//
//	*(void**)&HookTemplate[6] = HookFunction;
//	custom_MemCpy((void*)Page2, HookTemplate, sizeof(HookTemplate));
//
//	*(void**)&HookTemplate[6] = pCustomVTABLE[Index];
//	custom_MemCpy((void*)(Page2 + sizeof(HookTemplate)), HookTemplate, sizeof(HookTemplate));
//
//	*HookOrig = (void*)(Page2 + sizeof(HookTemplate));
//	pCustomVTABLE[Index] = Page2;
//
//	void* VT = (void*)pCustomVTABLE;
//	*(void**)((uint64_t)Object) = VT;
//
//	return true;
//}

#if 0
FRotator* GetControlRotation_hk(uint64_t* PlayerController, FRotator* Rotation)
{
	SpoofCaller<FRotator*>(Globals::GetControlRotationOriginal, PlayerController, Rotation);

	if (!Globals::IsAiming) {
		return Rotation;
	}

	FRotator LookRotation = Functions.FindLookAtRotation(vCamera.Location, Globals::AimLocation);

	//if (Globals::Smoothing > 0)
	//{
	LookRotation = SDK.RInterpTo(*Rotation, LookRotation, SDK.GetWorldDeltaSeconds(), 50.f - (float)Globals::Smoothing); // 50 is max smoothing in GUI.cpp
	//}

	FRotator AimRotation = *Rotation + (LookRotation - *Rotation);

	SDK.NormalizeAxis(AimRotation.Pitch);
	SDK.NormalizeAxis(AimRotation.Yaw);
	//AimRotation.Roll = 0.f;

	// Clamp the angles
	if (AimRotation.Yaw < -180.0f)
		AimRotation.Yaw += 360.0f;

	if (AimRotation.Yaw > 180.0f)
		AimRotation.Yaw -= 360.0f;

	if (AimRotation.Pitch < -74.0f)
		AimRotation.Pitch = -74.0f;

	if (AimRotation.Pitch > 74.0f)
		AimRotation.Pitch = 74.0f;

	*Rotation = AimRotation;

	return Rotation;
}


void (*ProcessEventOriginal)(uint64_t, uint64_t, void*);
static void ProcessEvent_hk(uint64_t Object, uint64_t Function, void* Args)
{
	static bool Init = false;
	if (!Init)
	{
		Init = true;

		dbgprint(xor_w(L"[Swyzz] ProcessEvent_hk hooked!\n"));
	}
	//dbgprint("[Fortnite] ProcessEvent_hk\n");
	if (Object && Function)
	{
		const wchar_t* ObjectName = SDK.GetObjectName(Object).c_str();
		const wchar_t* FunctionName = SDK.GetObjectName(Function).c_str();

		dbgprint(xor_w(L"[Swyzz] ProcessEvent_hk Object: %s Function: %s\n"), ObjectName, FunctionName);
		// compare FUnctionName with "DrawTransition" and "DrawTransitionOriginal"
		//if (wcscmp(FunctionName, xor_w(L"ServerSendAimbotDetectionStatus")) == 0)
		//{
		//	TArray<char>* Payload = static_cast<TArray<char>*>(Args);
		//	dbgprint(xor_w(L"[Swyzz] ServerSendAimbotDetectionStatus WRITTEN, SIZE: %d\n"), Payload->Num());

		//	return SpoofCaller<void>(ProcessEventOriginal, Object, Function, Payload);
		//}
	}

	return SpoofCaller<void>(ProcessEventOriginal, Object, Function, Args);

}
#endif
#ifndef RAID
void MyDrawTransition(void* Canvas) {

	Globals::PlayerController = SDK.GetPlayerController();
	if (!Globals::PlayerController) return;

	if ((Config.Misc.PanicKey == 2) && SDK.WasInputKeyJustPressed(Globals::PanicKey)) PanicEnabled = !PanicEnabled;
	if (PanicEnabled) return;

	if (Config.Misc.HudFocus && (SDK.GetViewportMouseCaptureMode() == EMouseCaptureMode::NoCapture)) return;

	float closestDistance = FLT_MAX;
	float closestDistanceForClose = FLT_MAX;
	float AutoFOV = 111;

	Globals::MyPlayer = NULL;
	Globals::ClosestPlayer = NULL;

	SDK.GetViewportSize(&Globals::Width, &Globals::Height);

	Globals::PlayerState = SDK.GetPlayerState();

	//if (Globals::PlayerState) {
		/*static uint64_t OldPlayerController = 0;
		if (camera != OldPlayerController)
		{
			Hook::NewHook().VMT((void*)camera, ProcessEvent_hk, 77, &ProcessEventOriginal);

			OldPlayerController = camera;
		}*/
	//}

	Globals::MyPlayer = SDK.K2_GetPawn();

	//Globals::InLobby = SDK.GetLootLevel() == 0;

	//TArray<uint64_t> SkinCharacterParts;
	//uint64_t CustomPartsByType[(int)EFortCustomPartType::NumTypes];

	GUI.UpdateSkins(/*SkinCharacterParts, CustomPartsByType*/);

	// Draw InLobby
	//auto BuildInLobby = SDK.BuildString_Int(xor_w(L""), xor_w(L"LOBBY: "), SDK.GetLootLevel(), xor_w(L""));
	//SDK.K2_DrawText(Globals::Burbank, BuildInLobby, FVector2D(10, 10), FVector2D(1, 1), FLinearColor(255, 255, 255, 1), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));

	int viz = 0, tot = 0, cwsmComerl = Config.Aimbot.Smooth, cstmfuv = Config.Aimbot.FOVRange, cstmskei = Config.Aimbot.BoneTarget;
	bool isShoty = false, isSniper = false, isAR = false, isSMG = false, isDeagel = false;

	vCamera = Functions.get_camera();

	if (Config.World.Enabled && Config.Visuals.Enabled) {
		Functions.World_Loop();
	}

	// show the number
	//SDK.K2_DrawText(Globals::Burbank, SDK.BuildString_Int(xor_w(L""), xor_w(L"ViewPortMouseCaptureMode: "), (int)viewPortMouseCaptureMode, xor_w(L"")), FVector2D(10, 10), FVector2D(1, 1), FLinearColor(255, 255, 255, 1), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));

	if (Globals::MyPlayer) {
		Globals::CurrentWeapon = SDK.GetCurrentWeapon(Globals::MyPlayer);

		if (Globals::CurrentWeapon) {

			//if (Globals::PlayerController != Globals::OldPlayerController)
			//{
			//	/*Hook::ShadowVMT APlayerControllerShadow;
			//	if (APlayerControllerShadow.Initialize((void*)Globals::PlayerController)) {
			//		GetControlRotationOriginal = APlayerControllerShadow.Insert<decltype(GetControlRotationOriginal)>(237, GetControlRotation);
			//	}
			//	APlayerControllerShadow.Finalize();*/

			//	genetic_4((void*)Globals::PlayerController, GetControlRotation, (void**)&GetControlRotationOriginal, 237);

			//	Globals::OldPlayerController = Globals::PlayerController;
			//}

			auto WeaponData = SDK.GetWeaponData(Globals::CurrentWeapon);
			if (WeaponData) {
				auto CoreAnimation = SDK.GetCoreAnimation(Globals::CurrentWeapon);
				Globals::CurrentWeaponType = SDK.GetItemType(WeaponData);
				auto CurrentWeaponName = Core.read<FText>(WeaponData + Offsets.ItemName).GetText();
				if (CurrentWeaponName) {
					// Draw Weapon Name
					//auto BuildWeaponName = SDK.Concat_StrStr(xor_w(L"Current Weapon: "), CurrentWeaponName);
					//SDK.K2_DrawText(Globals::Burbank, BuildWeaponName, FVector2D(10, 30), FVector2D(1, 1), FLinearColor(255, 255, 255, 1), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
					isShoty = SDK.Contains(CurrentWeaponName, xor_w(L"Shotgun"), false, false);
					isSniper = SDK.Contains(CurrentWeaponName, xor_w(L"Sniper"), false, false);
					isAR = SDK.Contains(CurrentWeaponName, xor_w(L"Assault Rifle"), false, false);
					isSMG = SDK.Contains(CurrentWeaponName, xor_w(L"SMG"), false, false) || SDK.Contains(CurrentWeaponName, xor_w(L"Submachine"), false, false);
					isDeagel = SDK.Contains(CurrentWeaponName, xor_w(L"Hand Cannon"), false, false);
				}
				// Draw CoreAnimation
				//auto BuildCoreAnimation = SDK.BuildString_Int(xor_w(L""), xor_w(L"CoreAnimation: "), (int)CoreAnimation.GetValue(), xor_w(L""));
				//SDK.K2_DrawText(Globals::Burbank, BuildCoreAnimation, FVector2D(10, 30), FVector2D(1, 1), FLinearColor(255, 255, 255, 1), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
				if (CoreAnimation == EFortWeaponCoreAnimation::Shotgun || CoreAnimation == EFortWeaponCoreAnimation::TacticalShotgun || isShoty) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.scwsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.scwfov;
					if (Config.WeaponConfig.cwbone) cstmskei = Config.WeaponConfig.scwbone;
				}
				// SMG
				else if (CoreAnimation == EFortWeaponCoreAnimation::MachinePistol || CoreAnimation == EFortWeaponCoreAnimation::DualWield || CoreAnimation == EFortWeaponCoreAnimation::SMG_P90 || isSMG) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.smgcwsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.smgcwfov;
					if (Config.WeaponConfig.cwbone) cstmskei = Config.WeaponConfig.smgcwbone;
				}
				// ARs
				else if (CoreAnimation == EFortWeaponCoreAnimation::Rifle ||
					CoreAnimation == EFortWeaponCoreAnimation::AssaultRifle ||
					CoreAnimation == EFortWeaponCoreAnimation::AR_BullPup ||
					CoreAnimation == EFortWeaponCoreAnimation::AR_ForwardGrip ||
					CoreAnimation == EFortWeaponCoreAnimation::AR_DrumGun || isAR) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.acwsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.acwfov;
					if (Config.WeaponConfig.cwbone) cstmskei = Config.WeaponConfig.acwbone;
				}
				// Snipers
				else if (CoreAnimation == EFortWeaponCoreAnimation::SniperRifle || isSniper || isDeagel) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.snprsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.snprfov;
					//if (cwbone) cstmskei = snprbone;
				}
#if FALSE
				if (Config.Misc.NoSpread) {
					if (Globals::CurrentWeaponType == EFortItemType::WeaponRanged)
					{
						auto ZeroReticle = [](uintptr_t CurrentWeapon, unsigned short ValueOffset, unsigned short TableOffset)
							{
								if (!CurrentWeapon) return;

								auto ValueIndex = *(unsigned char*)(CurrentWeapon + TableOffset + 1) - ValueOffset;
								auto TableIndex = *(unsigned char*)(CurrentWeapon + TableOffset);

								auto TableEntry = (CurrentWeapon + TableIndex * sizeof(unsigned long) + TableOffset - 0x10);
								if (!TableEntry) return;

								auto SpreadKey = ValueIndex & 0x82FFFFFE | 0x4C000001;
								if (!SpreadKey) return;

								auto TableValue = *(int*)(TableEntry);

								auto SpreadUInt = SpreadKey ^ TableValue;

								auto CurrentSpread = *(float*)(&SpreadUInt);

								if (CurrentSpread <= 0.0f)
								{
									// invalid value...
									// typically indicates we aren't using a weapon with spread values...
									return;
								}

								float Value = 0.135f;
								auto RealValue = *(int*)(&Value) ^ SpreadKey;
								*(int*)(TableEntry) = RealValue;
							};

						static const ReticlePair Pairs[] = {
						{ 0x406A, 0x1BAE },
						{ 0xC7BB, 0x1BC0 },
						{ 0xC7BB, 0x1B4A },
						{ 0xC7BB, 0x1B5C },
						{ 0xC7BB, 0x1B6E },
						{ 0xC7BB, 0x1B80 },
						};

						for (auto& RetPair : Pairs)
						{
							ZeroReticle(Globals::CurrentWeapon, RetPair.TableValue, RetPair.TableOffset);
						}
					}
				}
#endif
#if 0
				if (Config.Misc.PSilent) {
					if (!Config.Misc.PSilentShoty || (Config.Misc.PSilentShoty && isShoty)) {
						if (Globals::CurrentWeapon && Globals::CurrentWeapon != Globals::OldCurrentWeapon)
						{
							if (Globals::CurrentWeaponType == EFortItemType::WeaponRanged)
							{
								/*Hook::ShadowVMT AFortWeaponShadow;
								if (AFortWeaponShadow.Initialize((void*)Globals::PlayerController)) {
									GetControlRotationOriginal = AFortWeaponShadow.Insert<decltype(GetControlRotationOriginal)>(237, GetControlRotation);
								}
								AFortWeaponShadow.Finalize();*/

								genetic_4((void*)Globals::CurrentWeapon, GetWeaponTargetingTransform_hk, (void**)&GetWeaponTargetingTransformOriginal, 252);

								Globals::OldCurrentWeapon = Globals::CurrentWeapon;
							}
						}
					}
				}
#endif
			}
		}

		if (Config.InventoryChanger.Enabled && SDK.GetLootLevel() != 0) {
			//if (OldCurrentWeapon != Globals::CurrentWeapon) {
				//OldCurrentWeapon = Globals::CurrentWeapon;
				//if (Globals::CurrentWeapon) {
					bool apply_UpdateCharacterCustomization_t = false;
					auto PlayerState = SDK.AttemptGetPlayerStateForPawn(Globals::MyPlayer);
					if (PlayerState) {
						uint64_t* LocalCharacterParts = reinterpret_cast<uint64_t*>(PlayerState + Offsets.LocalCharacterParts); //AFortPlayerState
						if (Config.InventoryChanger.Character) {
							for (int j = 0; j < 7; j++) {
								uint64_t CurrentPart = Core.read<uint64_t>(reinterpret_cast<uint64_t>(LocalCharacterParts + j));
								if (Globals::CustomPartsByType[j] != 0 && CurrentPart != Globals::CustomPartsByType[j]) {
									Core.write(reinterpret_cast<uint64_t>(LocalCharacterParts + j), Globals::CustomPartsByType[j]);
									apply_UpdateCharacterCustomization_t = true;
								}
								else if (Globals::CustomPartsByType[j] == 0 && CurrentPart != 0) {
									Core.write(reinterpret_cast<uint64_t>(LocalCharacterParts + j), reinterpret_cast<uint64_t>(nullptr));
									apply_UpdateCharacterCustomization_t = true;
								}
							}
						}
						if (Config.InventoryChanger.Backpack)
						{
							auto CharacterParts = SDK.GetCharacterParts(Config.InventoryChanger.Backpack);
							if (/*CurrentPartBackpack && */CharacterParts.IsValidIndex(0)) {
								uint64_t CurrentPartBackpack = Core.read<uint64_t>(reinterpret_cast<uint64_t>(LocalCharacterParts + (int)EFortCustomPartType::Backpack));
								if (CurrentPartBackpack != CharacterParts[0]) {
									Core.write(reinterpret_cast<uint64_t>(LocalCharacterParts + (int)EFortCustomPartType::Backpack), CharacterParts[0]);
									apply_UpdateCharacterCustomization_t = true;
								}
							}
						}

						//if (Config.InventoryChanger.Pickaxe && Globals::CurrentWeapon)
						//{
						//	if (Globals::CurrentWeaponType == EFortItemType::WeaponHarvest) {
						//		auto WeaponDefinition = Core.read<uint64_t>(Config.InventoryChanger.Pickaxe + Offsets.UAthenaPickaxeItemDefinition_WeaponDefinition); //UAthenaPickaxeItemDefinition
						//		if (WeaponDefinition) {
						//			SDK.SetWeaponData(Globals::CurrentWeapon, WeaponDefinition); // WeaponDefinition

						//			auto CosmeticDataPlusPickaxe_Check = Core.read<uint64_t>(Globals::CurrentWeapon + Offsets.CosmeticData + 0x40); //AFortWeaponPickaxeAthena
						//			if (CosmeticDataPlusPickaxe_Check) {
						//				Core.write(Globals::CurrentWeapon + Offsets.CosmeticData + 0x40, Config.InventoryChanger.Pickaxe); // CosmeticData + Pickaxe

						//				Globals::InitWeaponCosmetics_t(Globals::CurrentWeapon);
						//				apply_UpdateCharacterCustomization_t = true;
						//			}
						//		}
						//	}
						//}

						if (SDK.GetLootLevel() != 0 && apply_UpdateCharacterCustomization_t) {
							Globals::STATIC_NeedUpdateCharacterCustomization_t = true;
						}

						if ((Globals::CurrentWeaponType == EFortItemType::WeaponHarvest || Globals::CurrentWeaponType == EFortItemType::WeaponRanged) && Globals::STATIC_NeedUpdateCharacterCustomization_t) {
							Globals::UpdateCharacterCustomization_t(Globals::MyPlayer);
							Globals::STATIC_NeedUpdateCharacterCustomization_t = false;
						}
					}
				//}
			//}
		}
	}

	if (Config.Visuals.Radar && Config.Visuals.Enabled) {
		Functions.Draw_RadarBackground();
	}

	/*if (Config.Misc.NoRecoil && !InitRecoil) {
		Core.write(Globals::EnableRecoil, false);
		InitRecoil = true;
	}
	else if (!Config.Misc.NoRecoil && InitRecoil) {
		Core.write(Globals::EnableRecoil, true);
		InitRecoil = false;
	}*/

	auto AllPlayers = SDK.GetFortPlayerPawns();

	uint64_t ClosestPlayer_DBNO = NULL;
	FVector AimLocation_DBNO;

	for (int i = 0; i < AllPlayers.Num(); i++) {
		if (!AllPlayers.IsValidIndex(i))
			continue;

		auto Enemy = AllPlayers[i];
		if (!Enemy) continue;

		bool g_isDead = SDK.IsDead(Enemy);
		if (g_isDead) continue;

		uint64_t g_mesh = Core.read<uint64_t>(Enemy + Offsets.Mesh);
		if (!g_mesh) continue;

		bool g_bIsDBNO = SDK.IsDBNO(Enemy);

		/*if (Config.Visuals.DrawSelf) {
			if (Globals::MyPlayer != Enemy && SDK.OnSameTeam(Globals::MyPlayer, Enemy)) continue;
		}
		else {*/
			if (SDK.OnSameTeam(Globals::MyPlayer, Enemy)) continue;
		//}

		tot = tot + 1;

		auto RootBone = SDK.GetSocketLocation(g_mesh, Globals::RootName);
		auto HeadBone = SDK.GetSocketLocation(g_mesh, Globals::HeadName);

		auto AimLocation = Functions.GetAllBones(g_mesh, cstmskei);

		bool visible = Config.Aimbot.VisCheck ? SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), AimLocation) : true;

		if (visible) viz = viz + 1;

		float distance = SDK.Vector_Distance(vCamera.Location, AimLocation) * 0.01;
		if (distance > Config.Visuals.OverallDistance) continue;

		auto BoxLineColor = visible ? Functions.GetColorFromOption(Config.Misc.ColorVisible).color : Functions.GetColorFromOption(Config.Misc.ColorInvisible).color;

		if (Config.Visuals.Enabled && Config.Visuals.Radar) {
			Functions.Draw_RadarPlayers(RootBone, BoxLineColor);
		}

		if (distance < closestDistanceForClose) {
			closestDistanceForClose = distance;
			if (distance < 10) {
				if (Config.Aimbot.AutoFOV) {
					AutoFOV = 900;
				}
				if (Config.Aimbot.CloseAim) {
					visible = true;
				}
			}
		}

		FVector2D AimLocation2D;

		bool foxhunter = Functions.WorldToScreen(AimLocation, &AimLocation2D);
		if (foxhunter) {
			if (Config.InventoryChanger.Enabled && SDK.GetLootLevel() == 0 && i == 0) {
				if (!Globals::MyPlayer) {
					bool call_UpdateCharacterCustomization_t = false;
					if (Config.InventoryChanger.Character) {
						for (int j = 0; j < 7; j++) {
							auto CustomPartType = Globals::CustomPartsByType[j];
							if (CustomPartType)
								SDK.ServerChoosePart(Enemy, (EFortCustomPartType)(j), CustomPartType);
							else
								SDK.ServerChoosePart(Enemy, (EFortCustomPartType)(j), reinterpret_cast<uint64_t>(nullptr));
						}
						call_UpdateCharacterCustomization_t = true;
					}
					if (Config.InventoryChanger.Backpack) {
						uint64_t CharacterPart = SDK.GetCharacterParts(Config.InventoryChanger.Backpack)[0];
						if (CharacterPart) {
							SDK.ServerChoosePart(Enemy, EFortCustomPartType::Backpack, CharacterPart);
							call_UpdateCharacterCustomization_t = true;
						}
					}

					if (call_UpdateCharacterCustomization_t && Enemy) Globals::UpdateCharacterCustomization_t(Enemy);
				}
			}

			if (Config.Visuals.Enabled) {

				if (g_bIsDBNO) BoxLineColor = Functions.GetColorFromOption(Config.Misc.ColorDowned).color;

				float x0 = FLT_MAX, y0 = FLT_MAX;
				float x1 = FLT_MIN, y1 = FLT_MIN;
				for (int i = 0; i < 22; i++)
				{
					FVector bone_1 = Globals::bones[i].location;

					x0 = min(x0, bone_1.X); // left
					x1 = max(x1, bone_1.X); // right
					y0 = min(y0, bone_1.Y); // top
					y1 = max(y1, bone_1.Y); // bottom
				}

				x0 = std::int32_t(SDK.Round(x0));
				y0 = std::int32_t(SDK.Round(y0));
				x1 = std::int32_t(SDK.Round(x1));
				y1 = std::int32_t(SDK.Round(y1));
				x0 -= (x1 - x0) * 0.3f;
				y0 -= (y1 - y0) * 0.10f;
				x1 += (x1 - x0) * 0.3f;
				y1 += (y1 - y0) * 0.07f;

				float X = x0, Y = y0, W = x1 - x0, H = y1 - y0;

				float heightA = SDK.Abs(H);
				float widthA = W;
				auto Size = FVector2D(widthA, heightA);
				auto Pos = FVector2D(X, Y - 2);

				auto topLeft = Pos;
				auto bottomRight = Pos + Size;
				auto theAdditionY = (bottomRight.Y - topLeft.Y) / (5.5f);
				auto theAdditionX = (bottomRight.X - topLeft.X) / 4.f;
				auto topRight = FVector2D(bottomRight.X, topLeft.Y);
				auto bottomLeft = FVector2D(topLeft.X, bottomRight.Y);
				auto ctup = FVector2D(Pos.X + (Size.X / 2), Pos.Y);

				if (Config.Visuals.BoxFill) {
					SDK.K2_DrawTexture(0, Pos, Size, FVector2D(), FVector2D(1.f, 1.f), FLinearColor(BoxLineColor.R * 255.f, BoxLineColor.G * 255.f, BoxLineColor.B * 255.f, 0.20f), EBlendMode::BLEND_Translucent, 0, FVector2D());
				}

				if (Config.Visuals.Box) {
					SDK.K2_DrawBox(Pos, Size, Config.Visuals.BoxSize, BoxLineColor);
				}

				if (Config.Visuals.CornerBox) {
					// Color
					SDK.K2_DrawLine(topLeft, FVector2D(topLeft.X, topLeft.Y + theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(topLeft, FVector2D(topLeft.X + theAdditionX, topLeft.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(topRight, FVector2D(topRight.X, topRight.Y + theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(topRight, FVector2D(topRight.X - theAdditionX, topRight.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomLeft, FVector2D(bottomLeft.X, bottomLeft.Y - theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomLeft, FVector2D(bottomLeft.X + theAdditionX, bottomLeft.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomRight, FVector2D(bottomRight.X, bottomRight.Y - theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomRight, FVector2D(bottomRight.X - theAdditionX, bottomRight.Y), Config.Visuals.BoxSize, BoxLineColor);
				}

				if (Config.Visuals.Bones) {
					// Head to Neck
					SDK.K2_DrawLine(FVector2D(Globals::FAKEvHeadBoneOut.X, Globals::FAKEvHeadBoneOut.Y), FVector2D(Globals::FAKEvNeckOut.X, Globals::FAKEvNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Pelvis to Neck
					SDK.K2_DrawLine(FVector2D(Globals::pelvisOut.X, Globals::pelvisOut.Y), FVector2D(Globals::FAKEvNeckOut.X, Globals::FAKEvNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Upper Arms to Neck
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmLeftOut.X, Globals::vUpperArmLeftOut.Y), FVector2D(Globals::FAKEvNeckOut.X, Globals::FAKEvNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmRightOut.X, Globals::vUpperArmRightOut.Y), FVector2D(Globals::FAKEvNeckOut.X, Globals::FAKEvNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Shoulders to Upper Arms
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmLeftOut.X, Globals::vUpperArmLeftOut.Y), FVector2D(Globals::vLeftHandOut.X, Globals::vLeftHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmRightOut.X, Globals::vUpperArmRightOut.Y), FVector2D(Globals::vRightHandOut.X, Globals::vRightHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Lower Arms to Hands
					SDK.K2_DrawLine(FVector2D(Globals::vLeftHandOut1.X, Globals::vLeftHandOut1.Y), FVector2D(Globals::vLeftHandOut.X, Globals::vLeftHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vRightHandOut1.X, Globals::vRightHandOut1.Y), FVector2D(Globals::vRightHandOut.X, Globals::vRightHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Thighs to Pelvis
					SDK.K2_DrawLine(FVector2D(Globals::vLeftThighOut.X, Globals::vLeftThighOut.Y), FVector2D(Globals::pelvisOut.X, Globals::pelvisOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vRightThighOut.X, Globals::vRightThighOut.Y), FVector2D(Globals::pelvisOut.X, Globals::pelvisOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Knees to Thighs
					SDK.K2_DrawLine(FVector2D(Globals::vLeftKneeOut.X, Globals::vLeftKneeOut.Y), FVector2D(Globals::vLeftThighOut.X, Globals::vLeftThighOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vRightKneeOut.X, Globals::vRightKneeOut.Y), FVector2D(Globals::vRightThighOut.X, Globals::vRightThighOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Feet to Knees
					SDK.K2_DrawLine(FVector2D(Globals::leftFeet2d.X, Globals::leftFeet2d.Y), FVector2D(Globals::vLeftKneeOut.X, Globals::vLeftKneeOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::rightFeet2d.X, Globals::rightFeet2d.Y), FVector2D(Globals::vRightKneeOut.X, Globals::vRightKneeOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Toes to Feet
					SDK.K2_DrawLine(FVector2D(Globals::leftFeetFinger2d.X, Globals::leftFeetFinger2d.Y), FVector2D(Globals::leftFeet2d.X, Globals::leftFeet2d.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::rightFeetFinger2d.X, Globals::rightFeetFinger2d.Y), FVector2D(Globals::rightFeet2d.X, Globals::rightFeet2d.Y), Config.Visuals.BoxSize, BoxLineColor);
				}

				FString NameString;
				FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
				if (Config.Visuals.Name && Enemy) {
					bool bIsBot = SDK.IsBotControlled(Enemy);
					//bool NPC = SDK.IsAnAthenaGameParticipant();
					FString BotName = xor_w(L"BOT");// NPC ? xor_w(L"NPC") : xor_w(L"Bot");

					if (bIsBot /*|| NPC*/) {
						NameString = BotName;
						if (Config.Visuals.Distance) {
							NameString = SDK.Concat_StrStr(NameString, StringDistance);
						}
					}
					else {
						FString PlayerName = SDK.GetHumanReadableName(Enemy);
						if (!PlayerName.IsEmpty() && !Functions.isNotName(PlayerName.c_str())) {
							NameString = Config.Visuals.Distance ? SDK.Concat_StrStr(PlayerName, StringDistance) : PlayerName;
						}
					}
				}
				else if (Config.Visuals.Distance) {
					NameString = StringDistance;
				}

				if (Config.Visuals.Kills || Config.Visuals.Platform) {
					auto PlayerState = SDK.AttemptGetPlayerStateForPawn(Enemy);
					if (Config.Visuals.Kills) {
						auto killsInt = Globals::MyPlayer ? SDK.GetKillScore(PlayerState) : 0;
						FString StringKills = SDK.BuildString_Int(xor_w(L""), xor_w(L" [+"), killsInt, xor_w(L"]"));
						NameString = Config.Visuals.Kills ? SDK.Concat_StrStr(NameString, StringKills) : NameString;
					}

					if (Config.Visuals.Platform) {
						auto platty = SDK.GetPlatform(PlayerState);
						if (!platty.IsEmpty()) {
							FString StringPlatform = xor_w(L" [");
							StringPlatform = SDK.Concat_StrStr(StringPlatform, platty);
							StringPlatform = SDK.Concat_StrStr(StringPlatform, xor_w(L"]"));
							NameString = Config.Visuals.Platform ? SDK.Concat_StrStr(NameString, StringPlatform) : NameString;
						}
					}
				}

				if (!NameString.IsEmpty()) {
					auto size = SDK.K2_TextSize(Globals::Burbank, NameString, FVector2D(0.5f, 0.5f));
					auto textLocation = FVector2D(ctup.X - (size.X / 2), ctup.Y - 20);
					SDK.K2_DrawText(Globals::Burbank, NameString, textLocation, FVector2D(0.5f, 0.5f), BoxLineColor, 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
				}

				if (Config.Visuals.Weapons) {
					auto CurrentWeapon = SDK.GetCurrentWeapon(Enemy);
					if (CurrentWeapon != 0) {
						auto ItemDefinition = SDK.GetWeaponData(CurrentWeapon);
						if (ItemDefinition != 0) {
							bool bIsReloadingWeapon = Core.read<bool>(CurrentWeapon + Offsets.bIsReloadingWeapon);
							if (bIsReloadingWeapon) {
								auto size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"[RELOADING]"), FVector2D(0.5f, 0.5f));
								SDK.K2_DrawText(Globals::Burbank, xor_w(L"[RELOADING]"), FVector2D(((topLeft.X + bottomRight.X) / 2.0f) - size.X / 2.0f - 5, bottomRight.Y + 5), FVector2D(0.5f, 0.5f), FLinearColor(200, 0.f, 0, 1.f), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
							}
							else {
								auto ItemName = Core.read<FText>(ItemDefinition + Offsets.ItemName).GetText();
								if (ItemName) {
									/*if (!Config.Visuals.Ammo) {
										auto nameSize = SDK.K2_TextSize(Globals::Burbank, ItemName, FVector2D(0.5f, 0.5f));
										auto textLocation = FVector2D(((topLeft.X + bottomRight.X) / 2.0f) - (nameSize.X / 2), bottomRight.Y + 5);
										SDK.K2_DrawText(Globals::Burbank, ItemName, textLocation, FVector2D(0.5f, 0.5f), Functions.GetItemColor(SDK.GetTier(ItemDefinition)), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
									}
									else {*/
										FString text;
										if (SDK.GetItemType(ItemDefinition) == EFortItemType::WeaponHarvest || SDK.GetItemType(ItemDefinition) == EFortItemType::Consumable) {
											text = SDK.Concat_StrStr(xor_w(L"["), FString(ItemName));
											text = SDK.Concat_StrStr(text, xor_w(L"]"));
										}
										else {
											FString ammoCount = SDK.BuildString_Int(xor_w(L""), xor_w(L" - "), SDK.GetMagazineAmmoCount(CurrentWeapon), xor_w(L"/"));
											FString bulletsPerClip = SDK.BuildString_Int(xor_w(L""), xor_w(L""), SDK.GetBulletsPerClip(CurrentWeapon), xor_w(L"]"));
											FString weaponAmmoInfo = SDK.Concat_StrStr(ammoCount, bulletsPerClip);
											text = SDK.Concat_StrStr(xor_w(L"["), FString(ItemName));
											text = SDK.Concat_StrStr(text, weaponAmmoInfo);
										}
										auto nameSize = SDK.K2_TextSize(Globals::Burbank, text, FVector2D(0.5f, 0.5f));
										auto textLocation = FVector2D(((topLeft.X + bottomRight.X) / 2.0f) - (nameSize.X / 2), bottomRight.Y + 1.f);
										SDK.K2_DrawText(Globals::Burbank, text, textLocation, FVector2D(0.5f, 0.5f), Functions.GetItemColor(SDK.GetTier(ItemDefinition)), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
									//}
								}
							}
						}
					}
				}
			}

			// Closest Player Check
			auto crosshairX = Globals::Width / 2;
			auto crosshairY = Globals::Height / 2;

			auto dist = SDK.Sqrt((Globals::vNeckOut.X - crosshairX) *
				(Globals::vNeckOut.X - crosshairX) + (Globals::vNeckOut.Y - crosshairY) *
				(Globals::vNeckOut.Y - crosshairY));

			if (visible) {
				if (dist < (Config.Aimbot.AutoFOV ? (double)AutoFOV : (double)cstmfuv)) {
					if (dist < closestDistance) {
						closestDistance = dist;
						//check if player is knocked out
						if (g_bIsDBNO) {
							ClosestPlayer_DBNO = Enemy;
							AimLocation_DBNO = AimLocation;
							//PotclosestBreh = breh;
						}
						else {
							Globals::ClosestPlayer = Enemy;
							Globals::AimLocation = AimLocation;
							//Globals::AimLocation2D = breh;
						}
					}
				}
			}
		}
	}

	if (Config.Aimbot.KnockedCheck && !Globals::ClosestPlayer && ClosestPlayer_DBNO) {
		Globals::ClosestPlayer = ClosestPlayer_DBNO;
		Globals::AimLocation = AimLocation_DBNO;
		//closestBreh = PotclosestBreh;
	}
	/*if (SDK.WasInputKeyJustPressed(Globals::F1)) {
		Config.Aimbot.AimKey = !Config.Aimbot.Enabled;
	}*/
	// toggle visuals
	if (SDK.WasInputKeyJustPressed(Globals::F2)) {
		Config.Visuals.Enabled = !Config.Visuals.Enabled;
	}
	if (SDK.WasInputKeyJustPressed(Globals::F5)) {
		if (Config.World.LootMinimalTier != 0) Config.World.LootMinimalTier--;
	}
	if (SDK.WasInputKeyJustPressed(Globals::F6)) {
		if (Config.World.LootMinimalTier != 7) Config.World.LootMinimalTier++;
	}
	if ((Config.Misc.MenuKey) == 2 && SDK.WasInputKeyJustPressed(Globals::MenuKey)) {
		Config.Misc.ShowMenu = !Config.Misc.ShowMenu;
	}

	if (Config.Visuals.DrawFOV && Config.Visuals.Enabled) {
		Functions.DrawCircle(Globals::Width / 2, Globals::Height / 2, (Config.Aimbot.AutoFOV ? (int)AutoFOV : cstmfuv), 1450, Functions.GetColorFromOption(Config.Visuals.DrawFOV).color);
		//Functions.DrawFilledCircle(Globals::Width / 2, Globals::Height / 2, (Config.Aimbot.AutoFOV ? (int)AutoFOV : cstmfuv), Functions.GetColorFromOption(Config.Visuals.DrawFOV).color);
	}

	if (Config.Visuals.Enabled && Config.Misc.ShowCounter && tot > 0) {
		auto mysoil = SDK.BuildString_Int(xor_w(L""), xor_w(L"[ ENEMIES: "), tot, xor_w(L" - VISIBLE: "));
		mysoil = SDK.BuildString_Int(mysoil, xor_w(L""), viz, xor_w(L" ]"));
		auto size = SDK.K2_TextSize(Globals::Burbank, mysoil, FVector2D(0.5f, 0.5f));
		SDK.K2_DrawText(Globals::Burbank, mysoil, FVector2D(Globals::Width / 2 - (size.X / 2), 2.50f), FVector2D(0.5f, 0.5f), FLinearColor(185, 160, 87, 1.f), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
	}

	if (Config.Misc.Crosshair && Config.Visuals.Enabled) {
		// +
		SDK.K2_DrawLine(FVector2D((Globals::Width / 2) - 10, Globals::Height / 2), FVector2D((Globals::Width / 2) + 10, Globals::Height / 2), 1.5f, FLinearColor(200, 0, 0, 1.f));
		SDK.K2_DrawLine(FVector2D(Globals::Width / 2, (Globals::Height / 2) - 10), FVector2D(Globals::Width / 2, (Globals::Height / 2) + 10), 1.5f, FLinearColor(200, 0, 0, 1.f));
	}

	if (Config.Misc.ShowMenu) {
		GUI.DrawMenu();
	}

#if 1
	if (!Functions.TB_AlsoCheckTarget(isShoty)) return;

	if (Globals::CurrentWeaponType != EFortItemType::WeaponRanged) return;

	if (Config.Aimbot.AimKey == 2) {
		if (Globals::CurrentWeapon && SDK.IsInputKeyDown(Globals::AimKey) /*&& !(Config.Aimbot.DisableOnSpectate && SDK.GetSpectatorCount() > 0)*/) {
			if (Config.Aimbot.ProjectilePrediction && Globals::CurrentWeaponType == EFortItemType::WeaponRanged) {
				auto ItemDefinition = SDK.GetWeaponData(Globals::CurrentWeapon);
				if (ItemDefinition) {
					Functions.Predict(ItemDefinition);
				}
			}
			Functions.InitializeAimbot(Globals::AimLocation, cwsmComerl);
		}
	}
#endif

#if 0

	if (!Functions.TB_AlsoCheckTarget(isShoty)) {
		if (Globals::IsAiming) {
			Globals::IsAiming = false;
		}
		return;
	}

	Globals::Smoothing = cwsmComerl;
	Globals::IsAiming = Config.Aimbot.AimKey == 2 && Globals::CurrentWeapon && SDK.IsInputKeyDown(Globals::AimKey);

	if (Globals::IsAiming) {
		if (Globals::CurrentWeaponType == EFortItemType::WeaponRanged) {
			auto ItemDefinition = SDK.GetWeaponData(Globals::CurrentWeapon);
			if (ItemDefinition) {
				Functions.Predict(ItemDefinition);
			}
		}

		if (Globals::ControlRotation) {
			FRotator TargetRotation = Functions.FindLookAtRotation(vCamera.Location, Globals::AimLocation);

			TargetRotation = SDK.RInterpTo(Globals::ControlRotation, TargetRotation, SDK.GetWorldDeltaSeconds(), 50.f - (float)cwsmComerl);

			TargetRotation = Globals::ControlRotation + (TargetRotation - Globals::ControlRotation);

			Globals::AimRotation = TargetRotation;
		}
	}
#endif
}
#else
void MyDrawTransition(void* Canvas) {

	Globals::PlayerController = SDK.GetPlayerController();
	if (!Globals::PlayerController) return;

	float closestDistance = FLT_MAX;
	float closestDistanceForClose = FLT_MAX;
	float AutoFOV = 111;

	Globals::MyPlayer = NULL;
	Globals::ClosestPlayer = NULL;

	SDK.GetViewportSize(&Globals::Width, &Globals::Height);

	Globals::PlayerState = SDK.GetPlayerState();

	Globals::MyPlayer = SDK.K2_GetPawn();

	int viz = 0, tot = 0, cwsmComerl = Config.Aimbot.Smooth, cstmfuv = Config.Aimbot.FOVRange, cstmskei = Config.Aimbot.BoneTarget;
	bool isShoty = false, isSniper = false, isAR = false, isSMG = false;

	vCamera = Functions.get_camera();

	if (Config.World.Enabled && Config.Visuals.Enabled) {
		Functions.World_Loop();
	}

	if (Globals::MyPlayer) {
		Globals::CurrentWeapon = SDK.GetCurrentWeapon(Globals::MyPlayer);

		if (Globals::CurrentWeapon) {
			auto WeaponData = SDK.GetWeaponData(Globals::CurrentWeapon);
			if (WeaponData) {
				auto CoreAnimation = SDK.GetCoreAnimation(Globals::CurrentWeapon);
				Globals::CurrentWeaponType = SDK.GetItemType(WeaponData);
				auto CurrentWeaponName = Core.read<FText>(WeaponData + Offsets.ItemName).GetText();
				if (CurrentWeaponName) {
					// Draw Weapon Name
					//auto BuildWeaponName = SDK.Concat_StrStr(xor_w(L"Current Weapon: "), CurrentWeaponName);
					//SDK.K2_DrawText(Globals::Burbank, BuildWeaponName, FVector2D(10, 30), FVector2D(1, 1), FLinearColor(255, 255, 255, 1), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
					isShoty = SDK.Contains(CurrentWeaponName, xor_w(L"Shotgun"), false, false);
					isSniper = SDK.Contains(CurrentWeaponName, xor_w(L"Sniper"), false, false);
					isAR = SDK.Contains(CurrentWeaponName, xor_w(L"Assault Rifle"), false, false);
					isSMG = SDK.Contains(CurrentWeaponName, xor_w(L"SMG"), false, false) || SDK.Contains(CurrentWeaponName, xor_w(L"Submachine"), false, false);
				}
				// Draw CoreAnimation
				//auto BuildCoreAnimation = SDK.BuildString_Int(xor_w(L""), xor_w(L"CoreAnimation: "), (int)CoreAnimation.GetValue(), xor_w(L""));
				//SDK.K2_DrawText(Globals::Burbank, BuildCoreAnimation, FVector2D(10, 30), FVector2D(1, 1), FLinearColor(255, 255, 255, 1), 1.0f, FLinearColor(0, 0, 0, 1.0), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
				if (CoreAnimation == EFortWeaponCoreAnimation::Shotgun || CoreAnimation == EFortWeaponCoreAnimation::TacticalShotgun || isShoty) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.scwsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.scwfov;
					if (Config.WeaponConfig.cwbone) cstmskei = Config.WeaponConfig.scwbone;
				}
				// SMG
				else if (CoreAnimation == EFortWeaponCoreAnimation::MachinePistol || CoreAnimation == EFortWeaponCoreAnimation::DualWield || CoreAnimation == EFortWeaponCoreAnimation::SMG_P90 || isSMG) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.smgcwsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.smgcwfov;
					if (Config.WeaponConfig.cwbone) cstmskei = Config.WeaponConfig.smgcwbone;
				}
				// ARs
				else if (CoreAnimation == EFortWeaponCoreAnimation::Rifle ||
					CoreAnimation == EFortWeaponCoreAnimation::AssaultRifle ||
					CoreAnimation == EFortWeaponCoreAnimation::AR_BullPup ||
					CoreAnimation == EFortWeaponCoreAnimation::AR_ForwardGrip ||
					CoreAnimation == EFortWeaponCoreAnimation::AR_DrumGun || isAR) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.acwsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.acwfov;
					if (Config.WeaponConfig.cwbone) cstmskei = Config.WeaponConfig.acwbone;
				}
				// Snipers
				else if (CoreAnimation == EFortWeaponCoreAnimation::SniperRifle || isSniper) {
					if (Config.WeaponConfig.cwsm) cwsmComerl = Config.WeaponConfig.snprsm;
					if (Config.WeaponConfig.cwfov) cstmfuv = Config.WeaponConfig.snprfov;
					//if (cwbone) cstmskei = snprbone;
				}
			}
		}
	}

	if (Config.Visuals.Radar && Config.Visuals.Enabled) {
		auto hscl = SDK.GetHUDScale(SDK.GetClientSettings());
		if (Globals::HudScale != hscl) {
			Globals::HudScale = hscl;
		}
	}

	auto AllPlayers = SDK.GetFortPlayerPawns();

	uint64_t ClosestPlayer_DBNO = NULL;
	FVector AimLocation_DBNO;

	for (int i = 0; i < AllPlayers.Num(); i++) {
		if (!AllPlayers.IsValidIndex(i))
			continue;

		auto Enemy = AllPlayers[i];
		if (!Enemy) continue;

		bool g_isDead = SDK.IsDead(Enemy);
		if (g_isDead) continue;

		uint64_t g_mesh = Core.read<uint64_t>(Enemy + Offsets.Mesh);
		if (!g_mesh) continue;

		bool g_bIsDBNO = SDK.IsDBNO(Enemy);

		/*if (Config.Visuals.DrawSelf) {
			if (Globals::MyPlayer != Enemy && SDK.OnSameTeam(Globals::MyPlayer, Enemy)) continue;
		}
		else {*/
		if (SDK.OnSameTeam(Globals::MyPlayer, Enemy)) continue;
		//}

		tot = tot + 1;

		auto RootBone = SDK.GetSocketLocation(g_mesh, Globals::RootName);
		auto HeadBone = SDK.GetSocketLocation(g_mesh, Globals::HeadName);

		auto AimLocation = Functions.GetAllBones(g_mesh, cstmskei);

		bool visible = Config.Aimbot.VisCheck ? SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), AimLocation) : true;

		if (visible) viz = viz + 1;

		float distance = SDK.Vector_Distance(vCamera.Location, AimLocation) * 0.01;
		if (distance > Config.Visuals.OverallDistance) continue;

		auto BoxLineColor = visible ? Functions.GetColorFromOption(4).color : Functions.GetColorFromOption(3).color;

		//if (Config.Visuals.Enabled && Config.Visuals.Radar) {
		//	Functions.Draw_RadarPlayers(RootBone, BoxLineColor);
		//}

		FVector2D AimLocation2D;

		bool foxhunter = Functions.WorldToScreen(AimLocation, &AimLocation2D);
		if (foxhunter) {
			if (Config.Visuals.Enabled) {

				if (g_bIsDBNO) BoxLineColor = Functions.GetColorFromOption(1).color;

				float x0 = FLT_MAX, y0 = FLT_MAX;
				float x1 = FLT_MIN, y1 = FLT_MIN;
				for (int i = 0; i < 22; i++)
				{
					FVector bone_1 = Globals::bones[i].location;

					x0 = min(x0, bone_1.X); // left
					x1 = max(x1, bone_1.X); // right
					y0 = min(y0, bone_1.Y); // top
					y1 = max(y1, bone_1.Y); // bottom
				}

				x0 = std::int32_t(SDK.Round(x0));
				y0 = std::int32_t(SDK.Round(y0));
				x1 = std::int32_t(SDK.Round(x1));
				y1 = std::int32_t(SDK.Round(y1));
				x0 -= (x1 - x0) * 0.2f;
				y0 -= (y1 - y0) * 0.05f;
				x1 += (x1 - x0) * 0.2f;
				y1 += (y1 - y0) * 0.04f;

				float X = x0, Y = y0, W = x1 - x0, H = y1 - y0;

				float heightA = SDK.Abs(H);
				float widthA = W;
				auto Size = FVector2D(widthA, heightA);
				auto Pos = FVector2D(X, Y - 2);

				auto topLeft = Pos;
				auto bottomRight = Pos + Size;
				auto theAdditionY = (bottomRight.Y - topLeft.Y) / 4.f;
				auto theAdditionX = (bottomRight.X - topLeft.X) / 3.f;
				auto topRight = FVector2D(bottomRight.X, topLeft.Y);
				auto bottomLeft = FVector2D(topLeft.X, bottomRight.Y);
				auto ctup = FVector2D(Pos.X + (Size.X / 2), Pos.Y);

				if (Config.Visuals.Box) {
					SDK.K2_DrawBox(Pos, Size, Config.Visuals.BoxSize, BoxLineColor);
				}

				if (Config.Visuals.CornerBox) {
					// Color
					SDK.K2_DrawLine(topLeft, FVector2D(topLeft.X, topLeft.Y + theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(topLeft, FVector2D(topLeft.X + theAdditionX, topLeft.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(topRight, FVector2D(topRight.X, topRight.Y + theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(topRight, FVector2D(topRight.X - theAdditionX, topRight.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomLeft, FVector2D(bottomLeft.X, bottomLeft.Y - theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomLeft, FVector2D(bottomLeft.X + theAdditionX, bottomLeft.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomRight, FVector2D(bottomRight.X, bottomRight.Y - theAdditionY), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(bottomRight, FVector2D(bottomRight.X - theAdditionX, bottomRight.Y), Config.Visuals.BoxSize, BoxLineColor);
				}

				if (Config.Visuals.Bones) {
					// Head to Neck
					SDK.K2_DrawLine(FVector2D(Globals::vHeadBoneOut.X, Globals::vHeadBoneOut.Y), FVector2D(Globals::vNeckOut.X, Globals::vNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Pelvis to Neck
					SDK.K2_DrawLine(FVector2D(Globals::pelvisOut.X, Globals::pelvisOut.Y), FVector2D(Globals::vNeckOut.X, Globals::vNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Upper Arms to Neck
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmLeftOut.X, Globals::vUpperArmLeftOut.Y), FVector2D(Globals::vNeckOut.X, Globals::vNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmRightOut.X, Globals::vUpperArmRightOut.Y), FVector2D(Globals::vNeckOut.X, Globals::vNeckOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Shoulders to Upper Arms
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmLeftOut.X, Globals::vUpperArmLeftOut.Y), FVector2D(Globals::vLeftHandOut.X, Globals::vLeftHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vUpperArmRightOut.X, Globals::vUpperArmRightOut.Y), FVector2D(Globals::vRightHandOut.X, Globals::vRightHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Lower Arms to Hands
					SDK.K2_DrawLine(FVector2D(Globals::vLeftHandOut1.X, Globals::vLeftHandOut1.Y), FVector2D(Globals::vLeftHandOut.X, Globals::vLeftHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vRightHandOut1.X, Globals::vRightHandOut1.Y), FVector2D(Globals::vRightHandOut.X, Globals::vRightHandOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Thighs to Pelvis
					SDK.K2_DrawLine(FVector2D(Globals::vLeftThighOut.X, Globals::vLeftThighOut.Y), FVector2D(Globals::pelvisOut.X, Globals::pelvisOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vRightThighOut.X, Globals::vRightThighOut.Y), FVector2D(Globals::pelvisOut.X, Globals::pelvisOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Knees to Thighs
					SDK.K2_DrawLine(FVector2D(Globals::vLeftKneeOut.X, Globals::vLeftKneeOut.Y), FVector2D(Globals::vLeftThighOut.X, Globals::vLeftThighOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::vRightKneeOut.X, Globals::vRightKneeOut.Y), FVector2D(Globals::vRightThighOut.X, Globals::vRightThighOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Feet to Knees
					SDK.K2_DrawLine(FVector2D(Globals::leftFeet2d.X, Globals::leftFeet2d.Y), FVector2D(Globals::vLeftKneeOut.X, Globals::vLeftKneeOut.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::rightFeet2d.X, Globals::rightFeet2d.Y), FVector2D(Globals::vRightKneeOut.X, Globals::vRightKneeOut.Y), Config.Visuals.BoxSize, BoxLineColor);

					// Toes to Feet
					SDK.K2_DrawLine(FVector2D(Globals::leftFeetFinger2d.X, Globals::leftFeetFinger2d.Y), FVector2D(Globals::leftFeet2d.X, Globals::leftFeet2d.Y), Config.Visuals.BoxSize, BoxLineColor);
					SDK.K2_DrawLine(FVector2D(Globals::rightFeetFinger2d.X, Globals::rightFeetFinger2d.Y), FVector2D(Globals::rightFeet2d.X, Globals::rightFeet2d.Y), Config.Visuals.BoxSize, BoxLineColor);
				}

				if (Config.Visuals.Name) {
					auto PlayerName = SDK.GetHumanReadableName(Enemy);
					if (!PlayerName.IsEmpty() && !Functions.isNotName(PlayerName.c_str())) {

						PlayerName = SDK.Concat_StrStr(xor_w(L"[ "), PlayerName);
						PlayerName = SDK.Concat_StrStr(PlayerName, xor_w(L" ]"));

						auto size = SDK.K2_TextSize(Globals::HeadingNow, PlayerName, FVector2D(0.35f, 0.35f));
						auto textLocation = FVector2D(ctup.X - (size.X / 2), ctup.Y - 25);
						SDK.K2_DrawText(Globals::HeadingNow, PlayerName, textLocation, FVector2D(0.35f, 0.35f), BoxLineColor, 1.0f, FLinearColor(), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1));
					}
				}

				if (Config.Visuals.Distance || Config.Visuals.Kills || Config.Visuals.Platform) {
					auto plrstt = SDK.AttemptGetPlayerStateForPawn(Enemy);
					FString mysoil;
					if (Config.Visuals.Distance) {
						mysoil = SDK.Concat_StrStr(mysoil, xor_w(L"[ "));
						mysoil = SDK.Concat_StrStr(mysoil, SDK.BuildString_Int(xor_w(L""), xor_w(L""), distance, xor_w(L"")));
						mysoil = SDK.Concat_StrStr(mysoil, xor_w(L" M ]"));
					}
					if (plrstt && Globals::MyPlayer) {
						if (Config.Visuals.Platform) {
							auto platty = SDK.GetPlatform(plrstt);
							bool bIsBot = SDK.IsBotControlled(Enemy);
							if (bIsBot) {
								platty = SDK.Concat_StrStr(platty, xor_w(L"BOT"));
							}
							mysoil = SDK.Concat_StrStr(mysoil, xor_w(L"[ "));
							mysoil = SDK.Concat_StrStr(mysoil, platty);
							mysoil = SDK.Concat_StrStr(mysoil, xor_w(L" ]"));
						}
						if (Config.Visuals.Kills) {
							mysoil = SDK.Concat_StrStr(mysoil, xor_w(L"[ "));
							mysoil = SDK.Concat_StrStr(mysoil, SDK.BuildString_Int(xor_w(L""), xor_w(L""), SDK.GetKillScore(plrstt), xor_w(L"")));
							mysoil = SDK.Concat_StrStr(mysoil, xor_w(L" K ]"));
						}
					}
					auto size = SDK.K2_TextSize(Globals::HeadingNow, mysoil, FVector2D(0.35f, 0.35f));
					auto textLocation = FVector2D(ctup.X - (size.X / 2), bottomRight.Y + 1.f);
					SDK.K2_DrawText(Globals::HeadingNow, mysoil, textLocation, FVector2D(0.35f, 0.35f), BoxLineColor, 1.0f, FLinearColor(), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1));
				}
			}
			
			// Closest Player Check
			auto crosshairX = Globals::Width / 2;
			auto crosshairY = Globals::Height / 2;

			auto dist = SDK.Sqrt((Globals::vNeckOut.X - crosshairX) *
				(Globals::vNeckOut.X - crosshairX) + (Globals::vNeckOut.Y - crosshairY) *
				(Globals::vNeckOut.Y - crosshairY));

			if (visible) {
				if (dist < (Config.Aimbot.AutoFOV ? (double)AutoFOV : (double)cstmfuv)) {
					if (dist < closestDistance) {
						closestDistance = dist;
						//check if player is knocked out
						if (g_bIsDBNO) {
							ClosestPlayer_DBNO = Enemy;
							AimLocation_DBNO = AimLocation;
							//PotclosestBreh = breh;
						}
						else {
							Globals::ClosestPlayer = Enemy;
							Globals::AimLocation = AimLocation;
							//Globals::AimLocation2D = breh;
						}
					}
				}
			}
		}
	}

	if (Config.Aimbot.KnockedCheck && !Globals::ClosestPlayer && ClosestPlayer_DBNO) {
		Globals::ClosestPlayer = ClosestPlayer_DBNO;
		Globals::AimLocation = AimLocation_DBNO;
		//closestBreh = PotclosestBreh;
	}
	/*if (SDK.WasInputKeyJustPressed(Globals::F1)) {
		Config.Aimbot.AimKey = !Config.Aimbot.Enabled;
	}*/
	// toggle visuals
	/*if (SDK.WasInputKeyJustPressed(Globals::F2)) {
		Config.Visuals.Enabled = !Config.Visuals.Enabled;
	}
	if (SDK.WasInputKeyJustPressed(Globals::F5)) {
		if (Config.World.LootMinimalTier != 0) Config.World.LootMinimalTier--;
	}
	if (SDK.WasInputKeyJustPressed(Globals::F6)) {
		if (Config.World.LootMinimalTier != 7) Config.World.LootMinimalTier++;
	}*/
	if (SDK.WasInputKeyJustPressed(Globals::Insert)) {
		Config.Misc.ShowMenu = !Config.Misc.ShowMenu;
	}

	if (Config.Visuals.DrawFOV && Config.Visuals.Enabled) {
		Functions.DrawCircle(Globals::Width / 2, Globals::Height / 2, (Config.Aimbot.AutoFOV ? (int)AutoFOV : cstmfuv), 1450, FLinearColor(185, 160, 87, 1.f));
		//Functions.DrawFilledCircle(Globals::Width / 2, Globals::Height / 2, (Config.Aimbot.AutoFOV ? (int)AutoFOV : cstmfuv), Functions.GetColorFromOption(Config.Visuals.DrawFOV).color);
	}

	if (Config.Misc.ShowMenu) {
		GUI.DrawMenu();
	}

	if (Globals::CurrentWeaponType != EFortItemType::WeaponRanged) return;

	if (!Functions.TB_AlsoCheckTarget(isShoty)) return;

	if (Config.Aimbot.AimKey) {
		if (Globals::CurrentWeapon && SDK.IsInputKeyDown(Globals::AimKey) /*&& !(Config.Aimbot.DisableOnSpectate && SDK.GetSpectatorCount() > 0)*/) {
			if (Config.Aimbot.ProjectilePrediction && Globals::CurrentWeaponType == EFortItemType::WeaponRanged) {
				auto ItemDefinition = SDK.GetWeaponData(Globals::CurrentWeapon);
				if (ItemDefinition) {
					Functions.Predict(ItemDefinition);
				}
			}
			Functions.InitializeAimbot(Globals::AimLocation, cwsmComerl);
		}
	}
}
#endif
#if !SWYZZ
#include <wbemidl.h>
#include <comdef.h>
#include <fstream>
#include <iostream>
#include <TlHelp32.h>
#include <sstream>
#include <vector>

namespace Curl {
	size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	std::string getURLResponseStream(std::string url, std::string useragent = "")
	{
		CURL* curl_handle;
		CURLcode res;
		std::string readBuffer;

		curl_global_init(CURL_GLOBAL_ALL);
		curl_handle = curl_easy_init();
		curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuffer);
		if (!useragent.empty()) curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, useragent.c_str());
		res = curl_easy_perform(curl_handle);
		if (res != CURLE_OK) {
			return xor_a("PRONHUB");
			/*fprintf(stderr, xor_a("Failed to connect, error: %s\n"),
				curl_easy_strerror(res));*/
		}

		curl_easy_cleanup(curl_handle);

		curl_global_cleanup();

		return readBuffer;
	}
}

namespace Login {
	std::string WMIQuery(std::string query, std::wstring property) {

		HRESULT hres;
		IWbemLocator* pLoc = nullptr;
		IWbemServices* pSvc = nullptr;
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		//printf("CoInitializeEx: %d\n", hres);
		hres = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
		//printf("CoInitializeSecurity: %d\n", hres);
		hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
		//printf("CoCreateInstance: %d\n", hres);

		if (FAILED(hres)) {
			CoUninitialize();
			return xor_a("");
		}

		hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, nullptr, WBEM_FLAG_CONNECT_USE_MAX_WAIT, nullptr, nullptr, &pSvc);

		if (FAILED(hres)) {
			pLoc->Release();
			CoUninitialize();
			return xor_a("");
		}

		hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);

		if (FAILED(hres)) {
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return xor_a("");
		}

		IEnumWbemClassObject* pEnumerator = nullptr;
		hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t(query.c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator);

		if (FAILED(hres)) {
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return xor_a("");
		}

		IWbemClassObject* pclsObj = nullptr;
		ULONG uReturn = 0;
		std::string result = xor_a("");

		while (pEnumerator) {
			hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (!uReturn) {
				break;
			}

			VARIANT vtProp;
			hres = pclsObj->Get(property.c_str(), 0, &vtProp, 0, 0);
			result = (const char*)_bstr_t(vtProp.bstrVal);
			VariantClear(&vtProp);
			pclsObj->Release();
		}

		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();

		return result;
	}
	
	/*std::string WMIQuery(const std::string& query, const std::wstring& property) {
		HRESULT hres;
		IWbemLocator* pLoc = nullptr;
		IWbemServices* pSvc = nullptr;

		// Initialize COM
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres)) {
			//std::cerr << "Failed to initialize COM library. Error code = 0x" << std::hex << hres << std::endl;
			return "";
		}

		// Create WMI locator
		hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
		if (FAILED(hres)) {
			//std::cerr << "Failed to create IWbemLocator object. Error code = 0x" << std::hex << hres << std::endl;
			CoUninitialize();
			return "";
		}

		// Connect to the WMI namespace
		hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &pSvc);
		if (FAILED(hres)) {
			//std::cerr << "Could not connect to WMI namespace. Error code = 0x" << std::hex << hres << std::endl;
			pLoc->Release();
			CoUninitialize();
			return "";
		}

		// Set security blanket
		hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
		if (FAILED(hres)) {
			//std::cerr << "Could not set proxy blanket. Error code = 0x" << std::hex << hres << std::endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return "";
		}

		// Execute the query
		IEnumWbemClassObject* pEnumerator = nullptr;
		hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t(query.c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnumerator);
		if (FAILED(hres)) {
			//std::cerr << "WMI query failed. Error code = 0x" << std::hex << hres << std::endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return "";
		}

		// Retrieve the property value
		IWbemClassObject* pclsObj = nullptr;
		ULONG uReturn = 0;
		std::string result = "";

		while (pEnumerator) {
			hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (!uReturn) {
				break;
			}

			VARIANT vtProp;
			hres = pclsObj->Get(property.c_str(), 0, &vtProp, 0, 0);
			if (SUCCEEDED(hres) && (vtProp.vt == VT_BSTR)) {
				result = _bstr_t(vtProp.bstrVal);
			}
			VariantClear(&vtProp);
			pclsObj->Release();
		}

		// Clean up
		pEnumerator->Release();
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();

		return result;
	}*/

	std::string createJsonString(
		const std::string& processorName,
		//const std::string& processorId,
		//const std::string& motherboardManufacturer,
		//const std::string& motherboardProduct,
		//const std::string& motherboardSerial,
		const std::string& gpuManufacturer,
		const std::string& gpuName,
		const std::string& biosMode,
		const std::string& secureBootState) {
		std::stringstream json;
		json << xor_a("{")
			<< xor_a("\"processorName\":\"") << processorName << xor_a("\",")
			//<< "\"processorId\":\"" << processorId << "\","
			//<< "\"motherboardManufacturer\":\"" << motherboardManufacturer << "\","
			//<< "\"motherboardProduct\":\"" << motherboardProduct << "\","
			//<< "\"motherboardSerial\":\"" << motherboardSerial << "\","
			<< xor_a("\"gpuManufacturer\":\"") << gpuManufacturer << xor_a("\",")
			<< xor_a("\"gpuName\":\"") << gpuName << xor_a("\",")
			<< xor_a("\"biosMode\":\"") << biosMode << xor_a("\",")
			<< xor_a("\"secureBootState\":\"") << secureBootState << xor_a("\"")
			<< xor_a("}");
		return json.str();
	}

	std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::string base64Encode(std::vector<unsigned char> input_bytes) {
		std::string ret;
		int i = 0;
		int pos = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		for (auto& byte : input_bytes) {
			char_array_3[i++] = byte;
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i < 4); i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}
		if (i) {
			for (auto j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (auto j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];

			while ((i++ < 3))
				ret += '=';

		}
		return ret;
	}
	/*
	std::string generateHWID() {
		std::string processorName = WMIQuery(xor_a("SELECT * FROM Win32_Processor"), xor_w(L"Name"));
		//std::string processorId = WMIQuery(xor_a("SELECT * FROM Win32_Processor"), xor_w(L"ProcessorId"));
		//std::string motherboardManufacturer = WMIQuery(xor_a("SELECT * FROM Win32_BaseBoard"), xor_w(L"Manufacturer"));
		//std::string motherboardProduct = WMIQuery(xor_a("SELECT * FROM Win32_BaseBoard"), xor_w(L"Product"));
		//std::string motherboardSerial = WMIQuery(xor_a("SELECT * FROM Win32_BaseBoard"), xor_w(L"SerialNumber"));
		std::string gpuManufacturer = WMIQuery(xor_a("SELECT * FROM Win32_VideoController"), xor_w(L"AdapterCompatibility"));
		std::string gpuName = WMIQuery(xor_a("SELECT * FROM Win32_VideoController"), xor_w(L"VideoProcessor"));
		std::string biosMode = WMIQuery(xor_a("SELECT * FROM Win32_ComputerSystem"), xor_w(L"SystemType"));
		biosMode = biosMode.find(xor_a("x64-based")) != std::string::npos ? xor_a("UEFI") : xor_a("Legacy");
		std::string secureBootState = WMIQuery(xor_a("SELECT * FROM Win32_SecureBoot"), xor_w(L"SecureBoot"));
		secureBootState = (secureBootState == xor_a("1") ? xor_a("Enabled") : xor_a("Disabled"));
		std::string jsonString = createJsonString(
			processorName,
			//processorId,
			//motherboardManufacturer,
			//motherboardProduct,
			//motherboardSerial,
			gpuManufacturer,
			gpuName,
			biosMode,
			secureBootState);
		return jsonString;
	}*/

	std::string generateHWID() {
		/*std::string processorName = WMIQuery(xor_a("SELECT Name FROM Win32_Processor"));

		std::string gpuManufacturer = WMIQuery(xor_a("SELECT AdapterCompatibility FROM Win32_VideoController"));
		std::string gpuName = WMIQuery(xor_a("SELECT VideoProcessor FROM Win32_VideoController"));

		std::string biosMode = WMIQuery(xor_a("SELECT SystemType FROM Win32_ComputerSystem"));
		biosMode = biosMode.find(xor_a("x64-based")) != std::string::npos ? xor_a("UEFI") : xor_a("Legacy");
		std::string secureBootState = WMIQuery(xor_a("SELECT SecureBoot FROM Win32_SecureBoot"));
		secureBootState = (secureBootState == xor_a("1") ? xor_a("Enabled") : xor_a("Disabled"));*/

		std::string processorName = WMIQuery(xor_a("SELECT * FROM Win32_Processor"), xor_w(L"Name"));
		//printf("Processor Name: %s\n", processorName.c_str());
		//system("pause");
		std::string gpuManufacturer = WMIQuery(xor_a("SELECT * FROM Win32_VideoController"), xor_w(L"AdapterCompatibility"));
		//printf("GPU Manufacturer: %s\n", gpuManufacturer.c_str());
		//system("pause");
		std::string gpuName = WMIQuery(xor_a("SELECT * FROM Win32_VideoController"), xor_w(L"VideoProcessor"));
		//printf("GPU Name: %s\n", gpuName.c_str());
		//system("pause");
		std::string biosMode = WMIQuery(xor_a("SELECT * FROM Win32_ComputerSystem"), xor_w(L"SystemType"));
		//printf("BIOS Mode: %s\n", biosMode.c_str());
		//system("pause");
		biosMode = biosMode.find(xor_a("x64-based")) != std::string::npos ? xor_a("UEFI") : xor_a("Legacy");
		std::string secureBootState = WMIQuery(xor_a("SELECT * FROM Win32_SecureBoot"), xor_w(L"SecureBoot"));
		secureBootState = (secureBootState == xor_a("1") ? xor_a("Enabled") : xor_a("Disabled"));
		//printf("Secure Boot State: %s\n", secureBootState.c_str());
		//system("pause");

		std::string jsonString = createJsonString(
			processorName,
			//processorId,
			//motherboardManufacturer,
			//motherboardProduct,
			//motherboardSerial,
			gpuManufacturer,
			gpuName,
			biosMode,
			secureBootState);

		return jsonString;
	}
}
#endif

void DrawTransistion(void* UGameViewPortClient, void* Canvas) {
	Globals::UGameViewportClient = (uint64_t)UGameViewPortClient;
	Globals::UCanvas = (uint64_t)Canvas;

	if (!Globals::HasInitGlobals) {
#if !SWYZZ
		auto abc = Login::generateHWID();
		std::vector<unsigned char> json_bytes(abc.begin(), abc.end());
		std::string hwid = Login::base64Encode(json_bytes);
#ifndef RAID
		std::string UA = xor_a("YCm2l7567V0PGYUGzfpck564XZeHAnj95Y7C8pOT");
		std::string response = Curl::getURLResponseStream(xor_a("https://api.syninc.store/APU/") + hwid, UA);
		if (response != xor_a("4nOfNcKMDNWH98BfazDf")) {
			// cause crash
			Core.write<int>(0x12345678, 42);
			Core.write<int>(0x52342353, 42);
			return;
		}
#else
		std::string UA = xor_a("41p6DEHAlIHXW9JqLQFrXLxiMd3iWbpQKwgpTcl");
		std::string response = Curl::getURLResponseStream(xor_a("https://raide.annas.dev/OZU/") + hwid, UA);
		if (response != xor_a("AtHXs5BwGgvqaa622gYHSdTvUu")) {
			// cause crash
			Core.write<int>(0x12345678, 42);
			Core.write<int>(0x52342353, 42);
			return;
		}
#endif
#endif

		Core.InitKeys();
		Core.InitKeys_1();
		Core.InitKeys_2();
		Core.InitKeys_3();
		Core.InitKeys_4();
		Core.InitBones();
		// Print fname ids of all loaded objects
		/*
		dbgprint("[DUMPER] LeftMouseButton = %d,", Globals::LeftMouseButton.KeyName.comparison_index);
		dbgprint("[DUMPER] RightMouseButton = %d,", Globals::RightMouseButton.KeyName.comparison_index);
		dbgprint("[DUMPER] MiddleMouseButton = %d,", Globals::MiddleMouseButton.KeyName.comparison_index);
		dbgprint("[DUMPER] ThumbMouseButton = %d,", Globals::ThumbMouseButton.KeyName.comparison_index);
		dbgprint("[DUMPER] ThumbMouseButton2 = %d,", Globals::ThumbMouseButton2.KeyName.comparison_index);
		dbgprint("[DUMPER] BackSpace = %d,", Globals::BackSpace.KeyName.comparison_index);
		dbgprint("[DUMPER] Tab = %d,", Globals::Tab.KeyName.comparison_index);
		dbgprint("[DUMPER] Enter = %d,", Globals::Enter.KeyName.comparison_index);
		dbgprint("[DUMPER] Pause = %d,", Globals::Pause.KeyName.comparison_index);
		dbgprint("[DUMPER] CapsLock = %d,", Globals::CapsLock.KeyName.comparison_index);
		dbgprint("[DUMPER] Escape_ = %d,", Globals::Escape.KeyName.comparison_index);
		dbgprint("[DUMPER] SpaceBar = %d,", Globals::SpaceBar.KeyName.comparison_index);
		dbgprint("[DUMPER] PageUp = %d,", Globals::PageUp.KeyName.comparison_index);
		dbgprint("[DUMPER] PageDown = %d,", Globals::PageDown.KeyName.comparison_index);
		dbgprint("[DUMPER] End = %d,", Globals::End.KeyName.comparison_index);
		dbgprint("[DUMPER] Home = %d,", Globals::Home.KeyName.comparison_index);
		dbgprint("[DUMPER] Left = %d,", Globals::Left.KeyName.comparison_index);
		dbgprint("[DUMPER] Up = %d,", Globals::Up.KeyName.comparison_index);
		dbgprint("[DUMPER] Right = %d,", Globals::Right.KeyName.comparison_index);
		dbgprint("[DUMPER] Down = %d,", Globals::Down.KeyName.comparison_index);
		dbgprint("[DUMPER] Insert = %d,", Globals::Insert.KeyName.comparison_index);
		dbgprint("[DUMPER] Delete = %d,", Globals::Delete.KeyName.comparison_index);
		dbgprint("[DUMPER] Zero = %d,", Globals::Zero.KeyName.comparison_index);
		dbgprint("[DUMPER] One = %d,", Globals::One.KeyName.comparison_index);
		dbgprint("[DUMPER] Two = %d,", Globals::Two.KeyName.comparison_index);
		dbgprint("[DUMPER] Three = %d,", Globals::Three.KeyName.comparison_index);
		dbgprint("[DUMPER] Four = %d,", Globals::Four.KeyName.comparison_index);
		dbgprint("[DUMPER] Five = %d,", Globals::Five.KeyName.comparison_index);
		dbgprint("[DUMPER] Six = %d,", Globals::Six.KeyName.comparison_index);
		dbgprint("[DUMPER] Seven = %d,", Globals::Seven.KeyName.comparison_index);
		dbgprint("[DUMPER] Eight = %d,", Globals::Eight.KeyName.comparison_index);
		dbgprint("[DUMPER] Nine = %d,", Globals::Nine.KeyName.comparison_index);
		dbgprint("[DUMPER] A = %d,", Globals::A.KeyName.comparison_index);
		dbgprint("[DUMPER] B = %d,", Globals::B.KeyName.comparison_index);
		dbgprint("[DUMPER] C = %d,", Globals::C.KeyName.comparison_index);
		dbgprint("[DUMPER] D = %d,", Globals::D.KeyName.comparison_index);
		dbgprint("[DUMPER] E = %d,", Globals::E.KeyName.comparison_index);
		dbgprint("[DUMPER] F = %d,", Globals::F.KeyName.comparison_index);
		dbgprint("[DUMPER] G = %d,", Globals::G.KeyName.comparison_index);
		dbgprint("[DUMPER] H = %d,", Globals::H.KeyName.comparison_index);
		dbgprint("[DUMPER] I = %d,", Globals::I.KeyName.comparison_index);
		dbgprint("[DUMPER] J = %d,", Globals::J.KeyName.comparison_index);
		dbgprint("[DUMPER] K = %d,", Globals::K.KeyName.comparison_index);
		dbgprint("[DUMPER] L = %d,", Globals::L.KeyName.comparison_index);
		dbgprint("[DUMPER] M = %d,", Globals::M.KeyName.comparison_index);
		dbgprint("[DUMPER] N = %d,", Globals::N.KeyName.comparison_index);
		dbgprint("[DUMPER] O = %d,", Globals::O.KeyName.comparison_index);
		dbgprint("[DUMPER] P = %d,", Globals::P.KeyName.comparison_index);
		dbgprint("[DUMPER] Q = %d,", Globals::Q.KeyName.comparison_index);
		dbgprint("[DUMPER] R = %d,", Globals::R.KeyName.comparison_index);
		dbgprint("[DUMPER] S = %d,", Globals::S.KeyName.comparison_index);
		dbgprint("[DUMPER] T = %d,", Globals::T.KeyName.comparison_index);
		dbgprint("[DUMPER] U = %d,", Globals::U.KeyName.comparison_index);
		dbgprint("[DUMPER] V = %d,", Globals::V.KeyName.comparison_index);
		dbgprint("[DUMPER] W = %d,", Globals::W.KeyName.comparison_index);
		dbgprint("[DUMPER] X = %d,", Globals::X.KeyName.comparison_index);
		dbgprint("[DUMPER] Y = %d,", Globals::Y.KeyName.comparison_index);
		dbgprint("[DUMPER] Z = %d,", Globals::Z.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadZero = %d,", Globals::NumPadZero.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadOne = %d,", Globals::NumPadOne.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadTwo = %d,", Globals::NumPadTwo.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadThree = %d,", Globals::NumPadThree.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadFour = %d,", Globals::NumPadFour.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadFive = %d,", Globals::NumPadFive.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadSix = %d,", Globals::NumPadSix.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadSeven = %d,", Globals::NumPadSeven.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadEight = %d,", Globals::NumPadEight.KeyName.comparison_index);
		dbgprint("[DUMPER] NumPadNine = %d,", Globals::NumPadNine.KeyName.comparison_index);
		dbgprint("[DUMPER] Multiply = %d,", Globals::Multiply.KeyName.comparison_index);
		dbgprint("[DUMPER] Add = %d,", Globals::Add.KeyName.comparison_index);
		dbgprint("[DUMPER] Subtract = %d,", Globals::Subtract.KeyName.comparison_index);
		dbgprint("[DUMPER] Decimal = %d,", Globals::Decimal.KeyName.comparison_index);
		dbgprint("[DUMPER] Divide = %d,", Globals::Divide.KeyName.comparison_index);
		dbgprint("[DUMPER] F1 = %d,", Globals::F1.KeyName.comparison_index);
		dbgprint("[DUMPER] F2 = %d,", Globals::F2.KeyName.comparison_index);
		dbgprint("[DUMPER] F3 = %d,", Globals::F3.KeyName.comparison_index);
		dbgprint("[DUMPER] F4 = %d,", Globals::F4.KeyName.comparison_index);
		dbgprint("[DUMPER] F5 = %d,", Globals::F5.KeyName.comparison_index);
		dbgprint("[DUMPER] F6 = %d,", Globals::F6.KeyName.comparison_index);
		dbgprint("[DUMPER] F7 = %d,", Globals::F7.KeyName.comparison_index);
		dbgprint("[DUMPER] F8 = %d,", Globals::F8.KeyName.comparison_index);
		dbgprint("[DUMPER] F9 = %d,", Globals::F9.KeyName.comparison_index);
		dbgprint("[DUMPER] F10 = %d,", Globals::F10.KeyName.comparison_index);
		dbgprint("[DUMPER] F11 = %d,", Globals::F11.KeyName.comparison_index);
		dbgprint("[DUMPER] F12 = %d,", Globals::F12.KeyName.comparison_index);
		dbgprint("[DUMPER] NumLock = %d,", Globals::NumLock.KeyName.comparison_index);
		dbgprint("[DUMPER] ScrollLock = %d,", Globals::ScrollLock.KeyName.comparison_index);
		dbgprint("[DUMPER] LeftShift = %d,", Globals::LeftShift.KeyName.comparison_index);
		dbgprint("[DUMPER] RightShift = %d,", Globals::RightShift.KeyName.comparison_index);
		dbgprint("[DUMPER] LeftControl = %d,", Globals::LeftControl.KeyName.comparison_index);
		dbgprint("[DUMPER] RightControl = %d,", Globals::RightControl.KeyName.comparison_index);
		dbgprint("[DUMPER] LeftAlt = %d,", Globals::LeftAlt.KeyName.comparison_index);
		dbgprint("[DUMPER] RightAlt = %d,", Globals::RightAlt.KeyName.comparison_index);
		dbgprint("[DUMPER] LeftCommand = %d,", Globals::LeftCommand.KeyName.comparison_index);
		dbgprint("[DUMPER] RightCommand = %d,", Globals::RightCommand.KeyName.comparison_index);
		dbgprint("[DUMPER] Semicolon = %d,", Globals::Semicolon.KeyName.comparison_index);
		dbgprint("[DUMPER] Equals = %d,", Globals::Equals.KeyName.comparison_index);
		dbgprint("[DUMPER] Comma = %d,", Globals::Comma.KeyName.comparison_index);
		dbgprint("[DUMPER] Underscore = %d,", Globals::Underscore.KeyName.comparison_index);
		dbgprint("[DUMPER] Hyphen = %d,", Globals::Hyphen.KeyName.comparison_index);
		dbgprint("[DUMPER] Period = %d,", Globals::Period.KeyName.comparison_index);
		dbgprint("[DUMPER] Slash = %d,", Globals::Slash.KeyName.comparison_index);
		dbgprint("[DUMPER] Tilde = %d,", Globals::Tilde.KeyName.comparison_index);
		dbgprint("[DUMPER] LeftBracket = %d,", Globals::LeftBracket.KeyName.comparison_index);
		dbgprint("[DUMPER] LeftParantheses = %d,", Globals::LeftParantheses.KeyName.comparison_index);
		dbgprint("[DUMPER] Backslash = %d,", Globals::Backslash.KeyName.comparison_index);
		dbgprint("[DUMPER] RightBracket = %d,", Globals::RightBracket.KeyName.comparison_index);
		dbgprint("[DUMPER] RightParantheses = %d,", Globals::RightParantheses.KeyName.comparison_index);
		dbgprint("[DUMPER] Apostrophe = %d,", Globals::Apostrophe.KeyName.comparison_index);
		dbgprint("[DUMPER] Quote = %d,", Globals::Quote.KeyName.comparison_index);
		dbgprint("[DUMPER] Asterix = %d,", Globals::Asterix.KeyName.comparison_index);
		dbgprint("[DUMPER] Ampersand = %d,", Globals::Ampersand.KeyName.comparison_index);
		dbgprint("[DUMPER] Caret = %d,", Globals::Caret.KeyName.comparison_index);
		dbgprint("[DUMPER] Dollar = %d,", Globals::Dollar.KeyName.comparison_index);
		dbgprint("[DUMPER] Exclamation = %d,", Globals::Exclamation.KeyName.comparison_index);
		dbgprint("[DUMPER] Colon = %d,", Globals::Colon.KeyName.comparison_index);
		dbgprint("[DUMPER] Section = %d,", Globals::Section.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_Left2D = %d,", Globals::Gamepad_Left2D.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftX = %d,", Globals::Gamepad_LeftX.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftY = %d,", Globals::Gamepad_LeftY.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_Right2D = %d,", Globals::Gamepad_Right2D.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightX = %d,", Globals::Gamepad_RightX.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightY = %d,", Globals::Gamepad_RightY.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftTriggerAxis = %d,", Globals::Gamepad_LeftTriggerAxis.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightTriggerAxis = %d,", Globals::Gamepad_RightTriggerAxis.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftThumbstick = %d,", Globals::Gamepad_LeftThumbstick.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightThumbstick = %d,", Globals::Gamepad_RightThumbstick.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_Special_Left = %d,", Globals::Gamepad_Special_Left.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_Special_Left_X = %d,", Globals::Gamepad_Special_Left_X.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_Special_Left_Y = %d,", Globals::Gamepad_Special_Left_Y.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_Special_Right = %d,", Globals::Gamepad_Special_Right.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_FaceButton_Bottom = %d,", Globals::Gamepad_FaceButton_Bottom.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_FaceButton_Right = %d,", Globals::Gamepad_FaceButton_Right.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_FaceButton_Left = %d,", Globals::Gamepad_FaceButton_Left.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_FaceButton_Top = %d,", Globals::Gamepad_FaceButton_Top.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftShoulder = %d,", Globals::Gamepad_LeftShoulder.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightShoulder = %d,", Globals::Gamepad_RightShoulder.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftTrigger = %d,", Globals::Gamepad_LeftTrigger.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightTrigger = %d,", Globals::Gamepad_RightTrigger.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_DPad_Up = %d,", Globals::Gamepad_DPad_Up.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_DPad_Down = %d,", Globals::Gamepad_DPad_Down.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_DPad_Right = %d,", Globals::Gamepad_DPad_Right.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_DPad_Left = %d,", Globals::Gamepad_DPad_Left.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftStick_Up = %d,", Globals::Gamepad_LeftStick_Up.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftStick_Down = %d,", Globals::Gamepad_LeftStick_Down.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftStick_Right = %d,", Globals::Gamepad_LeftStick_Right.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_LeftStick_Left = %d,", Globals::Gamepad_LeftStick_Left.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightStick_Up = %d,", Globals::Gamepad_RightStick_Up.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightStick_Down = %d,", Globals::Gamepad_RightStick_Down.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightStick_Right = %d,", Globals::Gamepad_RightStick_Right.KeyName.comparison_index);
		dbgprint("[DUMPER] Gamepad_RightStick_Left = %d,", Globals::Gamepad_RightStick_Left.KeyName.comparison_index);*/


		Globals::HasInitGlobals = true;
	}

	Globals::World = Core.read<uint64_t>(Globals::UGameViewportClient + Offsets.World);

	if (UGameViewPortClient && Canvas) {
		MyDrawTransition(Canvas);
	}

	Globals::DrawTransition(UGameViewPortClient, Canvas);
}