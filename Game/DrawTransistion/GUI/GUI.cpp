#include "GUI.h"

#ifndef RAID
bool RclickFix = false;
bool LclickFix = false;
int OldLootLevel = 67;

bool GUI::IsMouseHovering(FVector2D position, FVector2D size) {
	if (MousePosition.X > position.X && MousePosition.X < position.X + size.X &&
		MousePosition.Y > position.Y && MousePosition.Y < position.Y + size.Y) {
		return true;
	}
	return false;
}


void GUI::UpdateSkins() {
	if (!Config.InventoryChanger.Enabled) return;

	if (OldLootLevel != SDK.GetLootLevel()) {
		OldLootLevel = SDK.GetLootLevel();
		Globals::SkinCIDS.Clear();
		Globals::BackpackCIDS.Clear();
		//Globals::PickaxeCIDS.Clear();

		Globals::SkinCIDS = Core.pFindObjectsOfClass(Globals::AthenaCharacterItemDefinition);
		Globals::BackpackCIDS = Core.pFindObjectsOfClass(Globals::AthenaBackpackItemDefinition);
		//Globals::PickaxeCIDS = Core.pFindObjectsOfClass(Globals::AthenaPickaxeItemDefinition);
	}
	
	if (Config.InventoryChanger.Character)
	{
		for (int i = 0; i < (int)EFortCustomPartType::NumTypes; i++) {
			if (Globals::CustomPartsByType[i] != 0) Globals::CustomPartsByType[i] = 0;
		}

		TArray<TSoftObjectPtr<UObject>> BaseCharacterParts = Core.read<TArray<TSoftObjectPtr<UObject>>>(Config.InventoryChanger.Character + Offsets.BaseCharacterParts); //UAthenaCharacterItemDefinition

		for (int i = 0; i < BaseCharacterParts.Num(); i++) {
			uint64_t CharacterPart = Core.pLoadObject(SDK.Conv_NameToString(BaseCharacterParts[i].ObjectID.AssetPathName).c_str());
			Globals::SkinCharacterParts.push_back(CharacterPart);

			auto CharacterPartType = *(EFortCustomPartType*)(CharacterPart + Offsets.CharacterPartType);
			Globals::CustomPartsByType[(int)CharacterPartType] = CharacterPart;
		}
	}
}

void GUI::AddSkinsOption(FVector2D* Rudolf, int* id, const wchar_t* optionName, TArray<uint64_t> Cosmetics, bool* isTyping, FString* input, uint64_t* OutCosmetic) {
	//static bool initFirstTime = false;
	static TArray<FKey> Keys;

	if (!Keys.Count) {
		Keys.PushBack(Globals::A);
		Keys.PushBack(Globals::B);
		Keys.PushBack(Globals::C);
		Keys.PushBack(Globals::D);
		Keys.PushBack(Globals::E);
		Keys.PushBack(Globals::F);
		Keys.PushBack(Globals::G);
		Keys.PushBack(Globals::H);
		Keys.PushBack(Globals::I);
		Keys.PushBack(Globals::J);
		Keys.PushBack(Globals::K);
		Keys.PushBack(Globals::L);
		Keys.PushBack(Globals::M);
		Keys.PushBack(Globals::N);
		Keys.PushBack(Globals::O);
		Keys.PushBack(Globals::P);
		Keys.PushBack(Globals::Q);
		Keys.PushBack(Globals::R);
		Keys.PushBack(Globals::S);
		Keys.PushBack(Globals::T);
		Keys.PushBack(Globals::U);
		Keys.PushBack(Globals::V);
		Keys.PushBack(Globals::W);
		Keys.PushBack(Globals::X);
		Keys.PushBack(Globals::Y);
		Keys.PushBack(Globals::Z);
		Keys.PushBack(Globals::SpaceBar);
		Keys.PushBack(Globals::BackSpace);

		*input = SDK.Concat_StrStr(xor_w(L""), xor_w(L"H"));

		input->backspace();
	}

	*Rudolf += FVector2D(0, 35);
	*id += 1;

	//*input = SDK.Concat_StrStr(*input, xor_w(L"raider"));

	auto fullString = SDK.Concat_StrStr(optionName, xor_w(L": "));
	if (*isTyping) {
		for (int i = 0; i < Keys.Num(); i++)
		{
			FKey Key = Keys[i];

			if (SDK.WasInputKeyJustPressed(Key))
			{
				if (Key == Globals::SpaceBar)
				{
					*input = SDK.Concat_StrStr(*input, xor_w(L" "));
				}
				else if (Key == Globals::BackSpace)
				{
					input->backspace();
				}
				else
				{
					*input = SDK.Concat_StrStr(*input, SDK.Conv_NameToString(Key.KeyName));
				}
			}
		}

		if (!input->IsValid() || input->IsEmpty()) {
		}
		else {
			if (input->IsEmpty()) fullString = SDK.Concat_StrStr(fullString, xor_w(L"ALL"));
			else fullString = SDK.Concat_StrStr(fullString, *input);
		}
	}
	else {
		if (!*isTyping && !input->IsValid()){
			fullString = SDK.Concat_StrStr(fullString, xor_w(L"ALL"));
		}
		else {
			if (input->IsEmpty()) fullString = SDK.Concat_StrStr(fullString, xor_w(L"ALL"));
			else fullString = SDK.Concat_StrStr(fullString, *input);
		}
	}

	auto Pio = *Rudolf + FVector2D(480, 4) + FVector2D(62, 0) + FVector2D(20, 0); /*initOn*/ /*RIGHT ARROW*/

	auto Asclepius = FLinearColor(255, 255, 255, 1.f); /*color On*/

	// Set it as CurrentOption if the whole line is hovered by mouse
	if (MousePosition.X > Rudolf->X && MousePosition.X < Pio.X + 20 && MousePosition.Y > Rudolf->Y && MousePosition.Y < Rudolf->Y + 20) CurrentOption = *id;

	if (CurrentOption == *id) {
		Asclepius = FLinearColor(185, 160, 87, 1.f);

		*isTyping = true;

		fullString = SDK.Concat_StrStr(fullString, xor_w(L"..."));
	}
	else {
		if (*isTyping) *isTyping = false;
	}


	SDK.K2_DrawText(Globals::Burbank, fullString, *Rudolf, FVector2D(0.7f, 0.7f), Asclepius, 1.0f, FLinearColor(), FVector2D(), false, false, CurrentOption == *id ? true : false, FLinearColor());

	*Rudolf += FVector2D(0, 35);

	wchar_t* DisplayName = nullptr;
	auto TheOldShit = *Rudolf;
	for (int i = 0; i < Cosmetics.Num(); i++)
	{
		FVector2D OldOffset = *Rudolf;
		FVector2D Position = OldOffset;
		if (Position.Y + 35 > MenuPosition.Y + MenuSize.Y)
			continue;

		bool isActive = false;

		uint64_t Cosmetic = Cosmetics[i];
		if (!Cosmetic)
			continue;
		
		auto DisplayName = (*(FText*)(Cosmetic + 0x40)).GetText();

		/*if (!Functions.isValidWcharString(DisplayName))
			continue;*/

		if (input->IsValid())
		{
			if (DisplayName)
			{
				if (!SDK.Contains(DisplayName, *input, false, false))
					continue;
			}
			else
			{
				continue;
			}
		}
		
		TSoftObjectPtr<UObject> SmallPreviewImage = SDK.GetSmallPreviewImage((uint64_t)Cosmetic);

		auto size = SDK.K2_TextSize(Globals::Burbank, DisplayName, FVector2D(0.6f, 0.6f));

		uint64_t Texture = Core.pLoadObject(SDK.Conv_NameToString(SmallPreviewImage.ObjectID.AssetPathName).c_str());

		if ((Position.X + (Texture ? 35 : 0) + size.X + 10 + 1) > (MenuPosition.X + MenuSize.X)) {
			*Rudolf = FVector2D(TheOldShit.X, OldOffset.Y + 35);
			Position = *Rudolf;
			if (Position.Y + 35 > MenuPosition.Y + MenuSize.Y)
				continue;
		}

		if (IsMouseHovering(Position, FVector2D((Texture ? 35 : 0) + size.X + 10, 30)))
		{
			isActive = true;

			if (SDK.WasInputKeyJustPressed(Globals::LeftMouseButton))
			{
				*OutCosmetic = Cosmetic;
			}
		}

		if (Texture)
		{
			SDK.K2_DrawTexture(Texture, Position, FVector2D(35, 30), FVector2D(), FVector2D(1.f, 1.f), FLinearColor(255, 255, 255), EBlendMode::BLEND_Translucent, 0, FVector2D());
			Functions.DrawFilledRect(Position + FVector2D(35, 0), size.X + 10, 30, FLinearColor(12, 13, 16));
			SDK.K2_DrawBox(Position, FVector2D(35 + size.X + 10, 30), 1, FLinearColor(12, 13, 16));
			SDK.K2_DrawText(Globals::Burbank, DisplayName, Position + FVector2D(38, 2), FVector2D(0.6f, 0.6f), isActive ? FLinearColor(185, 160, 87) : FLinearColor(255, 255, 255), 1.0f, FLinearColor(0, 0, 0), FVector2D(), false, false, isActive ? true : false, FLinearColor(0, 0, 0));
			// Draw rect around the whole block
			if (isActive) SDK.K2_DrawBox(Position, FVector2D(35 + size.X + 10, 30), 2, FLinearColor(185, 160, 87));
		}
		else
		{
			Functions.DrawFilledRect(Position, size.X + 10, 30, FLinearColor(12, 13, 16));
			SDK.K2_DrawText(Globals::Burbank, DisplayName, Position + FVector2D(3, 2), FVector2D(0.6f, 0.6f), isActive ? FLinearColor(185, 160, 87) : FLinearColor(255, 255, 255), 1.0f, FLinearColor(0, 0, 0), FVector2D(), false, false, isActive ? true : false, FLinearColor(0, 0, 0));
			// Draw rect around the whole block
			if (isActive) SDK.K2_DrawBox(Position, FVector2D(size.X + 10, 30), 2, FLinearColor(185, 160, 87));
		}

		*Rudolf += FVector2D((Texture ? 50 : 15) + size.X, 0);
	}
}

void GUI::AddOption(FVector2D* Rudolf, int* id, const wchar_t* Kai/*optionName*/, int Meshulam/*type*/, bool* Soudeh/*toggle*/, int* optionValue, int increaseBy, int min, int max, struct FKey& SpecialOption2) {
	// type 1 is toggle
	// type 2 is float increase/decrease

	*Rudolf += FVector2D(0, 35);
	*id += 1;

	int theSizeOfShit = 400;
	//if (SpecialOption == 2) theSizeOfShit = 400;

	auto Pio = *Rudolf + FVector2D(480, 4) + FVector2D(62, 0) + FVector2D(20, 0); /*initOn*/ /*RIGHT ARROW*/
	auto Elchanan = *Rudolf + FVector2D(theSizeOfShit, 4) - FVector2D(60, 0) + FVector2D(20, 0); /*initOff*/ /*LEFT ARROW*/
	auto Asclepius = FLinearColor(255, 255, 255, 1.f); /*color On*/
	auto lhami = FLinearColor(255, 255, 255, 1.f); /*color off*/
	auto Inna = FLinearColor(255, 255, 255, 1); /*onOffTextColor*/

	// Set it as CurrentOption if the whole line is hovered by mouse
	if (MousePosition.X > Rudolf->X && MousePosition.X < Pio.X + 20 && MousePosition.Y > Rudolf->Y && MousePosition.Y < Rudolf->Y + 20) CurrentOption = *id;

	auto MouseClickedRight = false;
	auto MouseClickedLeft = false;

	if (Left_WasInputKeyJustPressed || (Meshulam == 2 && max > 299.f && SDK.IsInputKeyDown(Globals::LeftMouseButton))) {
		if (MousePosition.X > Pio.X && MousePosition.X < Pio.X + 20 && MousePosition.Y > Pio.Y && MousePosition.Y < Pio.Y + 20) {
			MouseClickedLeft = true;
		}
		if (MousePosition.X > Elchanan.X && MousePosition.X < Elchanan.X + 20 && MousePosition.Y > Elchanan.Y && MousePosition.Y < Elchanan.Y + 20) {
			MouseClickedRight = true;
		}
	}

	if (CurrentOption != *id && SpecialOption == 2 && *optionValue == 1){
		*optionValue = 0;
	}

	if (CurrentOption == *id) {
		Asclepius = FLinearColor(185.f, 160.f, 87.f, 1.f);
		lhami = FLinearColor(224.f, 2.f, 2.f, 1.f);

		if (!RclickFix && (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right))) {
			RclickFix = true;
		}

		if (!LclickFix && SDK.WasInputKeyJustPressed(Globals::LeftMouseButton) && MouseClickedLeft) {
			LclickFix = true;
		}

		if (Meshulam == 2) {
			Inna = (*optionValue != 0) ? Asclepius : lhami;
			if (max > 299.f) {
				if (SDK.IsInputKeyDown(Globals::Right) || SDK.IsInputKeyDown(Globals::Gamepad_DPad_Right) || MouseClickedLeft) { if (*optionValue != max) { *optionValue += increaseBy; } }
				if (SDK.IsInputKeyDown(Globals::Left) || SDK.IsInputKeyDown(Globals::Gamepad_DPad_Left) || MouseClickedRight) { if (*optionValue != min) { *optionValue -= increaseBy; } }
			}
			else {
				if (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right) || MouseClickedLeft) {
					if (*optionValue != max) {
						if (SpecialOption == 2) {
							if (*optionValue == 0) {
								*optionValue = 1;
							}
						}
						else {
							*optionValue += increaseBy;
						}
					}
				}
				if (SDK.WasInputKeyJustPressed(Globals::Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left) || MouseClickedRight) {
					if (*optionValue != min) {
						if (SpecialOption == 2) {
							*optionValue = 0;
						}else{
							*optionValue -= increaseBy;
						}
					}
				}
			}
		}
		else {
			Inna = *Soudeh ? Asclepius : lhami;

			if (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right) || MouseClickedLeft) { *Soudeh = true; }
			if (SDK.WasInputKeyJustPressed(Globals::Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left) || MouseClickedRight) { *Soudeh = false; }
		}
	}

	// Toggle Text
	FString skid = xor_w(L"LELE");
	if (SpecialOption == 2) {
		if (*optionValue == 0) skid = SDK.Concat_StrStr(xor_w(L"OF"), xor_w(L"F"));
		else if (*optionValue == 1) {
			skid = SDK.Concat_StrStr(xor_w(L"."), xor_w(L".."));
			Inna = FLinearColor(255, 255, 0);

			if (SDK.WasInputKeyJustPressed(Globals::MouseScrollUp)) { SpecialOption2 = Globals::MouseScrollUp; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::MouseScrollDown)) { SpecialOption2 = Globals::MouseScrollDown; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::MouseWheelAxis)) { SpecialOption2 = Globals::MouseWheelAxis; *optionValue = 2; }
			if (!LclickFix && SDK.WasInputKeyJustPressed(Globals::LeftMouseButton)) { SpecialOption2 = Globals::LeftMouseButton; *optionValue = 2; LclickFix = true; }
			if (SDK.WasInputKeyJustPressed(Globals::RightMouseButton)) { SpecialOption2 = Globals::RightMouseButton; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::MiddleMouseButton)) { SpecialOption2 = Globals::MiddleMouseButton; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::ThumbMouseButton)) { SpecialOption2 = Globals::ThumbMouseButton; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::ThumbMouseButton2)) { SpecialOption2 = Globals::ThumbMouseButton2; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::BackSpace)) { SpecialOption2 = Globals::BackSpace; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Tab)) { SpecialOption2 = Globals::Tab; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Enter)) { SpecialOption2 = Globals::Enter; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Pause)) { SpecialOption2 = Globals::Pause; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::CapsLock)) { SpecialOption2 = Globals::CapsLock; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Escape)) { SpecialOption2 = Globals::Escape; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::SpaceBar)) { SpecialOption2 = Globals::SpaceBar; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::PageUp)) { SpecialOption2 = Globals::PageUp; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::PageDown)) { SpecialOption2 = Globals::PageDown; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::End)) { SpecialOption2 = Globals::End; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Home)) { SpecialOption2 = Globals::Home; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Left)) { SpecialOption2 = Globals::Left; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Up)) { SpecialOption2 = Globals::Up; *optionValue = 2; }
			if (!RclickFix && SDK.WasInputKeyJustPressed(Globals::Right)) { SpecialOption2 = Globals::Right; *optionValue = 2; RclickFix = true; }
			if (SDK.WasInputKeyJustPressed(Globals::Down)) { SpecialOption2 = Globals::Down; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Insert)) { SpecialOption2 = Globals::Insert; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Delete)) { SpecialOption2 = Globals::Delete; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Zero)) { SpecialOption2 = Globals::Zero; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::One)) { SpecialOption2 = Globals::One; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Two)) { SpecialOption2 = Globals::Two; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Three)) { SpecialOption2 = Globals::Three; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Four)) { SpecialOption2 = Globals::Four; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Five)) { SpecialOption2 = Globals::Five; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Six)) { SpecialOption2 = Globals::Six; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Seven)) { SpecialOption2 = Globals::Seven; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Eight)) { SpecialOption2 = Globals::Eight; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Nine)) { SpecialOption2 = Globals::Nine; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::A)) { SpecialOption2 = Globals::A; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::B)) { SpecialOption2 = Globals::B; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::C)) { SpecialOption2 = Globals::C; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::D)) { SpecialOption2 = Globals::D; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::E)) { SpecialOption2 = Globals::E; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F)) { SpecialOption2 = Globals::F; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::G)) { SpecialOption2 = Globals::G; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::H)) { SpecialOption2 = Globals::H; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::I)) { SpecialOption2 = Globals::I; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::J)) { SpecialOption2 = Globals::J; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::K)) { SpecialOption2 = Globals::K; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::L)) { SpecialOption2 = Globals::L; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::M)) { SpecialOption2 = Globals::M; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::N)) { SpecialOption2 = Globals::N; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::O)) { SpecialOption2 = Globals::O; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::P)) { SpecialOption2 = Globals::P; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Q)) { SpecialOption2 = Globals::Q; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::R)) { SpecialOption2 = Globals::R; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::S)) { SpecialOption2 = Globals::S; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::T)) { SpecialOption2 = Globals::T; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::U)) { SpecialOption2 = Globals::U; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::V)) { SpecialOption2 = Globals::V; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::W)) { SpecialOption2 = Globals::W; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::X)) { SpecialOption2 = Globals::X; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Y)) { SpecialOption2 = Globals::Y; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Z)) { SpecialOption2 = Globals::Z; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadZero)) { SpecialOption2 = Globals::NumPadZero; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadOne)) { SpecialOption2 = Globals::NumPadOne; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadTwo)) { SpecialOption2 = Globals::NumPadTwo; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadThree)) { SpecialOption2 = Globals::NumPadThree; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadFour)) { SpecialOption2 = Globals::NumPadFour; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadFive)) { SpecialOption2 = Globals::NumPadFive; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadSix)) { SpecialOption2 = Globals::NumPadSix; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadSeven)) { SpecialOption2 = Globals::NumPadSeven; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadEight)) { SpecialOption2 = Globals::NumPadEight; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumPadNine)) { SpecialOption2 = Globals::NumPadNine; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Multiply)) { SpecialOption2 = Globals::Multiply; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Add)) { SpecialOption2 = Globals::Add; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Subtract)) { SpecialOption2 = Globals::Subtract; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Decimal)) { SpecialOption2 = Globals::Decimal; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Divide)) { SpecialOption2 = Globals::Divide; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F1)) { SpecialOption2 = Globals::F1; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F2)) { SpecialOption2 = Globals::F2; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F3)) { SpecialOption2 = Globals::F3; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F4)) { SpecialOption2 = Globals::F4; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F5)) { SpecialOption2 = Globals::F5; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F6)) { SpecialOption2 = Globals::F6; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F7)) { SpecialOption2 = Globals::F7; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F8)) { SpecialOption2 = Globals::F8; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F9)) { SpecialOption2 = Globals::F9; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F10)) { SpecialOption2 = Globals::F10; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F11)) { SpecialOption2 = Globals::F11; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::F12)) { SpecialOption2 = Globals::F12; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::NumLock)) { SpecialOption2 = Globals::NumLock; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::ScrollLock)) { SpecialOption2 = Globals::ScrollLock; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::LeftShift)) { SpecialOption2 = Globals::LeftShift; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::RightShift)) { SpecialOption2 = Globals::RightShift; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::LeftControl)) { SpecialOption2 = Globals::LeftControl; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::RightControl)) { SpecialOption2 = Globals::RightControl; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::LeftAlt)) { SpecialOption2 = Globals::LeftAlt; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::RightAlt)) { SpecialOption2 = Globals::RightAlt; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::LeftCommand)) { SpecialOption2 = Globals::LeftCommand; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::RightCommand)) { SpecialOption2 = Globals::RightCommand; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Semicolon)) { SpecialOption2 = Globals::Semicolon; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Equals)) { SpecialOption2 = Globals::Equals; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Comma)) { SpecialOption2 = Globals::Comma; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Underscore)) { SpecialOption2 = Globals::Underscore; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Hyphen)) { SpecialOption2 = Globals::Hyphen; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Period)) { SpecialOption2 = Globals::Period; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Slash)) { SpecialOption2 = Globals::Slash; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Tilde)) { SpecialOption2 = Globals::Tilde; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::LeftBracket)) { SpecialOption2 = Globals::LeftBracket; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::LeftParantheses)) { SpecialOption2 = Globals::LeftParantheses; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Backslash)) { SpecialOption2 = Globals::Backslash; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::RightBracket)) { SpecialOption2 = Globals::RightBracket; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::RightParantheses)) { SpecialOption2 = Globals::RightParantheses; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Apostrophe)) { SpecialOption2 = Globals::Apostrophe; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Quote)) { SpecialOption2 = Globals::Quote; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Asterix)) { SpecialOption2 = Globals::Asterix; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Ampersand)) { SpecialOption2 = Globals::Ampersand; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Caret)) { SpecialOption2 = Globals::Caret; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Dollar)) { SpecialOption2 = Globals::Dollar; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Exclamation)) { SpecialOption2 = Globals::Exclamation; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Colon)) { SpecialOption2 = Globals::Colon; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Section)) { SpecialOption2 = Globals::Section; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_Left2D)) { SpecialOption2 = Globals::Gamepad_Left2D; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftX)) { SpecialOption2 = Globals::Gamepad_LeftX; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftY)) { SpecialOption2 = Globals::Gamepad_LeftY; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_Right2D)) { SpecialOption2 = Globals::Gamepad_Right2D; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightX)) { SpecialOption2 = Globals::Gamepad_RightX; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightY)) { SpecialOption2 = Globals::Gamepad_RightY; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftTriggerAxis)) { SpecialOption2 = Globals::Gamepad_LeftTriggerAxis; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightTriggerAxis)) { SpecialOption2 = Globals::Gamepad_RightTriggerAxis; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftThumbstick)) { SpecialOption2 = Globals::Gamepad_LeftThumbstick; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightThumbstick)) { SpecialOption2 = Globals::Gamepad_RightThumbstick; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_Special_Left)) { SpecialOption2 = Globals::Gamepad_Special_Left; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_Special_Left_X)) { SpecialOption2 = Globals::Gamepad_Special_Left_X; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_Special_Left_Y)) { SpecialOption2 = Globals::Gamepad_Special_Left_Y; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_Special_Right)) { SpecialOption2 = Globals::Gamepad_Special_Right; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_FaceButton_Bottom)) { SpecialOption2 = Globals::Gamepad_FaceButton_Bottom; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_FaceButton_Right)) { SpecialOption2 = Globals::Gamepad_FaceButton_Right; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_FaceButton_Left)) { SpecialOption2 = Globals::Gamepad_FaceButton_Left; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_FaceButton_Top)) { SpecialOption2 = Globals::Gamepad_FaceButton_Top; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftShoulder)) { SpecialOption2 = Globals::Gamepad_LeftShoulder; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightShoulder)) { SpecialOption2 = Globals::Gamepad_RightShoulder; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftTrigger)) { SpecialOption2 = Globals::Gamepad_LeftTrigger; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightTrigger)) { SpecialOption2 = Globals::Gamepad_RightTrigger; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Up)) { SpecialOption2 = Globals::Gamepad_DPad_Up; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Down)) { SpecialOption2 = Globals::Gamepad_DPad_Down; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right)) { SpecialOption2 = Globals::Gamepad_DPad_Right; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left)) { SpecialOption2 = Globals::Gamepad_DPad_Left; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftStick_Up)) { SpecialOption2 = Globals::Gamepad_LeftStick_Up; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftStick_Down)) { SpecialOption2 = Globals::Gamepad_LeftStick_Down; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftStick_Right)) { SpecialOption2 = Globals::Gamepad_LeftStick_Right; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_LeftStick_Left)) { SpecialOption2 = Globals::Gamepad_LeftStick_Left; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightStick_Up)) { SpecialOption2 = Globals::Gamepad_RightStick_Up; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightStick_Down)) { SpecialOption2 = Globals::Gamepad_RightStick_Down; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightStick_Right)) { SpecialOption2 = Globals::Gamepad_RightStick_Right; *optionValue = 2; }
			if (SDK.WasInputKeyJustPressed(Globals::Gamepad_RightStick_Left)) { SpecialOption2 = Globals::Gamepad_RightStick_Left; *optionValue = 2; }
		}
		else {
			if (SpecialOption2.KeyName.comparison_index)
				skid = SDK.Conv_NameToString(SpecialOption2.KeyName);
		}
	}
	else if (SpecialOption == 3) {
		if (*optionValue == 1) skid = SDK.Concat_StrStr(xor_w(L"HE"), xor_w(L"AD"));
		if (*optionValue == 2) skid = SDK.Concat_StrStr(xor_w(L"NE"), xor_w(L"CK"));
		if (*optionValue == 3) skid = SDK.Concat_StrStr(xor_w(L"BO"), xor_w(L"DY"));
		if (*optionValue == 4) skid = SDK.Concat_StrStr(xor_w(L"CLO"), xor_w(L"SEST"));
	}
	else if (SpecialOption == 53) {
		auto EFortTier = Functions.GetItemEFortTier(*optionValue);
		skid = SDK.Concat_StrStr(xor_w(L""), Functions.GetItemTierName(EFortTier).c_str());
		Inna = Functions.GetItemColor(EFortTier);
	}
	else if (SpecialOption == 585) {
		if (*optionValue == 1) skid = SDK.Concat_StrStr(xor_w(L"SK"), xor_w(L"IN"));
		if (*optionValue == 2) skid = SDK.Concat_StrStr(xor_w(L"BACK"), xor_w(L"PACK"));
		if (*optionValue == 3) skid = SDK.Concat_StrStr(xor_w(L"PIC"), xor_w(L"KAXE"));
	}
	else if (SpecialOption == 69) {
		if (*optionValue != 0) {
			skid = SDK.Concat_StrStr(xor_w(L""), Functions.GetColorFromOption(*optionValue).name);
			Inna = Functions.GetColorFromOption(*optionValue).color;
		}
		else {
			skid = SDK.Concat_StrStr(xor_w(L""), xor_w(L"OFF"));
		}
	}
	else if (Meshulam == 2) {
		//skid = SDK.Concat_StrStr(xor_w(L""), STATIC_Conv_IntToString(optionValue));
		skid = SDK.BuildString_Int(xor_w(L""), xor_w(L""), *optionValue, xor_w(L""));
	}
	else {
		skid = SDK.Concat_StrStr(xor_w(L""), *Soudeh ? xor_w(L"ON") : xor_w(L"OFF"));
	}

	SDK.K2_DrawText(Globals::Burbank, Kai, *Rudolf, FVector2D(0.7f, 0.7f), Inna, 1.0f, FLinearColor(), FVector2D(), false, false, CurrentOption == *id ? true : false, FLinearColor());

	double Silvia = (Pio.X - Elchanan.X) + 20/*20 is the width of arrow button*/; /*distanceBetweenRedGreen*/
	auto size = SDK.K2_TextSize(Globals::Burbank, skid, FVector2D(0.7f, 0.7f));
	SDK.K2_DrawText(Globals::Burbank, skid, FVector2D(Elchanan.X + (Silvia / 2) - (size.X / 2), Rudolf->Y), FVector2D(0.7f, 0.7f), Inna, 1.0f, FLinearColor(), FVector2D(), false, false, CurrentOption == *id ? true : false, FLinearColor());

	float Adelina = 0.5;
	float Adelinay = 1.0;
	for (int i = 0; i < 20; i++)
	{
		SDK.K2_DrawLine(Pio, Pio + FVector2D(0, 20) + FVector2D(Adelinay, 0) - FVector2D(0, Adelina), 1.0f, Asclepius);
		SDK.K2_DrawLine(Elchanan + FVector2D(20, 0), Elchanan + FVector2D(20, 20) - FVector2D(Adelinay, 0) - FVector2D(0, Adelina), 1.0f, lhami);
		Adelina += 0.5;
		Adelinay += 1.0;
	}
	SDK.K2_DrawLine(Pio, Pio + FVector2D(20, 10), 1.0f, Asclepius);
	SDK.K2_DrawLine(Pio, Pio + FVector2D(0, 20), 1.0f, Asclepius);
	SDK.K2_DrawLine(Pio + FVector2D(0, 20), Pio + FVector2D(20, 10), 1.0f, Asclepius);
	SDK.K2_DrawLine(Elchanan + FVector2D(20, 0), Elchanan + FVector2D(20, 20), 1.0f, lhami);
	SDK.K2_DrawLine(Elchanan + FVector2D(20, 0), Elchanan + FVector2D(0, 10), 1.0f, lhami);
	SDK.K2_DrawLine(Elchanan + FVector2D(20, 20), Elchanan + FVector2D(0, 10), 1.0f, lhami);

	if (RclickFix && (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right))) {
		RclickFix = false;
	}
}

void GUI::InitOptions(FVector2D Rudolfy) {
	int tutl = 0;
	auto Rudolf = Rudolfy; //Option Pos

	SpecialOption = 0;
	if (CurrentTab == 0) {
		//AddOption(&Rudolf, &tutl, xor_w(L"ENABLE AIMBOT (F1)"), 1, &radeo);
		//AddOption(&Rudolf, &tutl, xor_w(L"AIM LOCK"), 1, &aemluk);
		//AddOption(&Rudolf, &tutl, xor_w(L"WEAKSPOT AIM"), 1, &weekaem);
		SpecialOption = 2;
		AddOption(&Rudolf, &tutl, xor_w(L"AIM KEY"), 2, 0, &Config.Aimbot.AimKey, 1, 0, 19);
		AddOption(&Rudolf, &tutl, xor_w(L"TRIGGER KEY"), 2, 0, &Config.Aimbot.TriggerKey, 1, 0, 19, Globals::TriggerKey);
		SpecialOption = 0;
		AddOption(&Rudolf, &tutl, xor_w(L"SHOTGUN ONLY TRIGGER"), 1, &Config.Aimbot.ShotgunOnlyTrigger);
		AddOption(&Rudolf, &tutl, xor_w(L"ALWAYS TRIGGER (NO KEYBIND)"), 1, &Config.Aimbot.AlwaysTrigger);
		SpecialOption = 3;
		AddOption(&Rudolf, &tutl, xor_w(L"AIM BONE"), 2, 0, &Config.Aimbot.BoneTarget, 1, 1, 4);
		SpecialOption = 0;
		AddOption(&Rudolf, &tutl, xor_w(L"AIM SMOOTHING"), 2, 0, &Config.Aimbot.Smooth, 1, 0, 50);
		AddOption(&Rudolf, &tutl, xor_w(L"SPECTATE SMOOTHING"), 2, 0, &Config.Aimbot.SpectateSmooth, 1, 0, 50);
		//AddOption(&Rudolf, &tutl, xor_w(L"SILENT"), 1, &saylnt);
		AddOption(&Rudolf, &tutl, xor_w(L"AIM FOV SIZE"), 2, 0, &Config.Aimbot.FOVRange, 1, 1, 900);
		AddOption(&Rudolf, &tutl, xor_w(L"AUTO AIM FOV SIZE"), 1, &Config.Aimbot.AutoFOV);
		AddOption(&Rudolf, &tutl, xor_w(L"VISIBLE CHECK"), 1, &Config.Aimbot.VisCheck);
		AddOption(&Rudolf, &tutl, xor_w(L"CLOSE ENEMIES AIM"), 1, &Config.Aimbot.CloseAim);
		AddOption(&Rudolf, &tutl, xor_w(L"AIM AT KNOCKED"), 1, &Config.Aimbot.KnockedCheck);
		//AddOption(&Rudolf, &tutl, xor_w(L"AIM LINE ESP"), 1, &lineezpaim);
		AddOption(&Rudolf, &tutl, xor_w(L"SNIPER PREDICTION"), 1, &Config.Aimbot.ProjectilePrediction);
	}
	else if (CurrentTab == 1) {
		AddOption(&Rudolf, &tutl, xor_w(L"CUSTOM WEAPON SMOOTHING"), 1, &Config.WeaponConfig.cwsm);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SHOTGUN SMOOTHING"), 2, 0, &Config.WeaponConfig.scwsm, 1, 0, 50);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SMG SMOOTHING"), 2, 0, &Config.WeaponConfig.smgcwsm, 1, 0, 50);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] AR SMOOTHING"), 2, 0, &Config.WeaponConfig.acwsm, 1, 0, 50);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SNIPER SMOOTHING"), 2, 0, &Config.WeaponConfig.snprsm, 1, 0, 50);
		AddOption(&Rudolf, &tutl, xor_w(L"CUSTOM WEAPON FOV"), 1, &Config.WeaponConfig.cwfov);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SHOTGUN FOV"), 2, 0, &Config.WeaponConfig.scwfov, 1, 1, 900);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SMG FOV"), 2, 0, &Config.WeaponConfig.smgcwfov, 1, 1, 900);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] AR FOV"), 2, 0, &Config.WeaponConfig.acwfov, 1, 1, 900);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SNIPER FOV"), 2, 0, &Config.WeaponConfig.snprfov, 1, 1, 900);
		AddOption(&Rudolf, &tutl, xor_w(L"CUSTOM WEAPON AIM BONE"), 1, &Config.WeaponConfig.cwbone);
		SpecialOption = 3;
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SHOTGUN AIM BONE"), 2, 0, &Config.WeaponConfig.scwbone, 1, 1, 4);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] SMG AIM BONE"), 2, 0, &Config.WeaponConfig.smgcwbone, 1, 1, 4);
		AddOption(&Rudolf, &tutl, xor_w(L"[-] AR AIM BONE"), 2, 0, &Config.WeaponConfig.acwbone, 1, 1, 4);
		SpecialOption = 0;
	}
	else if (CurrentTab == 2) {
		AddOption(&Rudolf, &tutl, xor_w(L"ALL VISUALS (F2)"), 1, &Config.Visuals.Enabled);
		AddOption(&Rudolf, &tutl, xor_w(L"MAX VISUALS DISTANCE"), 2, 0, &Config.Visuals.OverallDistance, 1, 10, 300);
		AddOption(&Rudolf, &tutl, xor_w(L"BOX ESP"), 1, &Config.Visuals.Box);
		AddOption(&Rudolf, &tutl, xor_w(L"CORNER BOX"), 1, &Config.Visuals.CornerBox);
		AddOption(&Rudolf, &tutl, xor_w(L"BOX FILLED"), 1, &Config.Visuals.BoxFill);
		AddOption(&Rudolf, &tutl, xor_w(L"BOX/SKELETON THICKNESS"), 2, 0, &Config.Visuals.BoxSize, 1, 1, 5);
		AddOption(&Rudolf, &tutl, xor_w(L"SKELETON"), 1, &Config.Visuals.Bones);
		//AddOption(&Rudolf, &tutl, xor_w(L"SKELETON THICKNESS"), 2, 0, &dskltthik, 1, 1, 3);
		AddOption(&Rudolf, &tutl, xor_w(L"NAME ESP"), 1, &Config.Visuals.Name);
		AddOption(&Rudolf, &tutl, xor_w(L"DISTANCE ESP"), 1, &Config.Visuals.Distance);
		AddOption(&Rudolf, &tutl, xor_w(L"PLATFORM ESP"), 1, &Config.Visuals.Platform);
		AddOption(&Rudolf, &tutl, xor_w(L"KILLS ESP"), 1, &Config.Visuals.Kills);
		AddOption(&Rudolf, &tutl, xor_w(L"WEAPON ESP"), 1, &Config.Visuals.Weapons);
		SpecialOption = 69;
		AddOption(&Rudolf, &tutl, xor_w(L"VISIBLE COLOR"), 2, 0, &Config.Misc.ColorVisible, 1, 1, 6);
		AddOption(&Rudolf, &tutl, xor_w(L"INVISIBLE COLOR"), 2, 0, &Config.Misc.ColorInvisible, 1, 1, 6);
		AddOption(&Rudolf, &tutl, xor_w(L"DOWNED COLOR"), 2, 0, &Config.Misc.ColorDowned, 1, 1, 6);
		SpecialOption = 0;
		//SpecialOption = 4;
		//AddOption(&Rudolf, &tutl, xor_w(L"LOOT MINIMUM RARITY"), 2, 0, &chosrar, 1, 1, 7);
		//SpecialOption = 0;
	}
	else if (CurrentTab == 3) {
		AddOption(&Rudolf, &tutl, xor_w(L"ENABLE WORLD ESP"), 1, &Config.World.Enabled);
		AddOption(&Rudolf, &tutl, xor_w(L"WORLD ESP MAX DISTANCE"), 2, 0, &Config.World.WorldDistance, 1, 0, 1000);
		AddOption(&Rudolf, &tutl, xor_w(L"LOOT ESP"), 1, &Config.World.Pickup);
		AddOption(&Rudolf, &tutl, xor_w(L"CHESTS ESP"), 1, &Config.World.Chests);
		AddOption(&Rudolf, &tutl, xor_w(L"AMMO-BOX ESP"), 1, &Config.World.AmmoBox);
		AddOption(&Rudolf, &tutl, xor_w(L"VEHICLES ESP"), 1, &Config.World.Vehicles);
		AddOption(&Rudolf, &tutl, xor_w(L"LLAMA ESP"), 1, &Config.World.Llama);
		AddOption(&Rudolf, &tutl, xor_w(L"LLAMA MAX DISTANCE (0 = NO LIMIT)"), 2, 0, &Config.World.LlamaDistance, 1, 0, 1000);
		SpecialOption = 53;
		AddOption(&Rudolf, &tutl, xor_w(L"LOOT MIN TIER (F5/F6)"), 2, 0, &Config.World.LootMinimalTier, 1, 0, 7);
		SpecialOption = 0;
	}
	else if (CurrentTab == 4) {
		AddOption(&Rudolf, &tutl, xor_w(L"TOGGLE LOCKER CHANGER"), 1, &Config.InventoryChanger.Enabled);
		SpecialOption = 585;
		AddOption(&Rudolf, &tutl, xor_w(L"CATEGORY"), 2, 0, &Config.InventoryChanger.Category, 1, 1, 2);
		//AddOption(&Rudolf, &tutl, xor_w(L"CATEGORY"), 2, 0, &Config.InventoryChanger.Category, 1, 1, 3);
		SpecialOption = 0;
		static FString InputText;
		static bool isTyping = false;
		if (Config.InventoryChanger.Category == 1)
			AddSkinsOption(&Rudolf, &tutl, xor_w(L"Search Skin"), Globals::SkinCIDS, &isTyping, &InputText, &Config.InventoryChanger.Character);
		else if (Config.InventoryChanger.Category == 2)
			AddSkinsOption(&Rudolf, &tutl, xor_w(L"Search Backpack"), Globals::BackpackCIDS, &isTyping, &InputText, &Config.InventoryChanger.Backpack);
		/*else if (Config.InventoryChanger.Category == 3)
			AddSkinsOption(&Rudolf, &tutl, xor_w(L"Search Pickaxe"), Globals::PickaxeCIDS, &isTyping, &InputText, &Config.InventoryChanger.Pickaxe);*/
	}
	else if (CurrentTab == 5) {
		//AddOption(&Rudolf, &tutl, xor_w(L"VEHICLE FLY"), 2, 0, &vfley, 1, 0, 31, Globals::FLKey);
		//AddOption(&Rudolf, &tutl, xor_w(L"VEHICLE FLY BOOST"), 2, 0, &vfboost, 1, 0, 31, Globals::FLKeyBoost);
		//AddOption(&Rudolf, &tutl, xor_w(L"WALL STEALER"), 2, 0, &bstel, 1, 0, 31, Globals::WSteal);
		//AddOption(&Rudolf, &tutl, xor_w(L"SNIPER TP"), 1, &snprtpe);
		AddOption(&Rudolf, &tutl, xor_w(L"ENABLE HUD FOCUS"), 1, &Config.Misc.HudFocus);
		SpecialOption = 2;
		AddOption(&Rudolf, &tutl, xor_w(L"MENU KEY"), 2, 0, &Config.Misc.MenuKey, 1, 1, 27, Globals::MenuKey);
		AddOption(&Rudolf, &tutl, xor_w(L"PANIC KEY"), 2, 0, &Config.Misc.PanicKey, 1, 0, 27, Globals::PanicKey);
		//AddOption(&Rudolf, &tutl, xor_w(L"INSTANT LOOT PICKER"), 2, 0, &Config.Misc.LootPicker, 1, 0, 31, Globals::LootPickerKey);
		//AddOption(&Rudolf, &tutl, xor_w(L"INSTANT LOOT DESTROYER"), 2, 0, &Config.Misc.LootDestroyer, 1, 0, 31, Globals::LootDestroyerKey);
		SpecialOption = 0;
		//AddOption(&Rudolf, &tutl, xor_w(L"NO RECOIL [EXPLOIT]"), 1, &Config.Misc.NoRecoil);
#if SWYZZ
			//AddOption(&Rudolf, &tutl, xor_w(L"NO SPREAD [SWYZZ]"), 1, &Config.Misc.NoSpread);
#endif
		//AddOption(&Rudolf, &tutl, xor_w(L"PSILENT [EXPLOIT]"), 1, &Config.Misc.PSilent);
		//AddOption(&Rudolf, &tutl, xor_w(L"SHOTGUN ONLY PSILENT [EXPLOIT]"), 1, &Config.Misc.PSilentShoty);
		AddOption(&Rudolf, &tutl, xor_w(L"DRAW CROSSHAIR"), 1, &Config.Misc.Crosshair);
		AddOption(&Rudolf, &tutl, xor_w(L"SHOW WARNING CHECK"), 1, &Config.Misc.ShowCounter);
		SpecialOption = 69;
		AddOption(&Rudolf, &tutl, xor_w(L"SHOW FOV CIRCLE"), 2, 0, &Config.Visuals.DrawFOV, 1, 0, 6);
		SpecialOption = 0;
		AddOption(&Rudolf, &tutl, xor_w(L"DRAW RADAR"), 1, &Config.Visuals.Radar);
		//AddOption(&Rudolf, &tutl, xor_w(L"RADAR X"), 2, 0, &Config.Visuals.RadarX, 1, 1, Globals::Width - Config.Visuals.RadarSize);
		//AddOption(&Rudolf, &tutl, xor_w(L"RADAR Y"), 2, 0, &Config.Visuals.RadarY, 1, 1, Globals::Height - Config.Visuals.RadarSize);
		AddOption(&Rudolf, &tutl, xor_w(L"RADAR SIZE"), 2, 0, &Config.Visuals.RadarSize, 1, 10, 400);
		AddOption(&Rudolf, &tutl, xor_w(L"RADAR DOT SIZE"), 2, 0, &Config.Visuals.RadarDotSize, 1, 2, 10);
#if 0
		AddOption(&Rudolf, &tutl, xor_w(L"DEV NUMBER"), 2, 0, &Config.Misc.DevNumber, 1, 0, 90);
#endif
	}

	// menu control
	if (SDK.WasInputKeyJustPressed(Globals::Up) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Up)) {
		if (CurrentOption != 0) CurrentOption--;
	}
	if (SDK.WasInputKeyJustPressed(Globals::Down) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Down)) if (CurrentOption != tutl) CurrentOption++;
}

void GUI::HandleMenuMouse() {
	float a, b;
	auto MousePositionSDK = SDK.GetMousePosition(&a, &b);
	MousePosition.X = a; MousePosition.Y = b;

	Left_WasInputKeyJustPressed = SDK.WasInputKeyJustPressed(Globals::LeftMouseButton);

	if (Left_WasInputKeyJustPressed) {
		// Handle dragging of the menu
		if (MousePosition.X > MenuPosition.X && MousePosition.X < MenuPosition.X + MenuSize.X && MousePosition.Y > MenuPosition.Y && MousePosition.Y < MenuPosition.Y + 45) {
			IsDragging = true;
			DragOffset = MousePosition - MenuPosition;
		}
		// Handle presses of Aimbot tab
		if (MousePosition.X > MenuPosition.X && MousePosition.X < MenuPosition.X + (MenuSize.X / 6) && MousePosition.Y > MenuPosition.Y + 50 && MousePosition.Y < MenuPosition.Y + 85) {
			CurrentTab = 0;
			CurrentOption = 0;
		}
		// Handle presses of Weapons tab
		if (MousePosition.X > MenuPosition.X + (MenuSize.X / 6) && MousePosition.X < MenuPosition.X + (MenuSize.X / 6) * 2 && MousePosition.Y > MenuPosition.Y + 50 && MousePosition.Y < MenuPosition.Y + 85) {
			CurrentTab = 1;
			CurrentOption = 0;
		}
		// Handle presses of Visuals tab
		if (MousePosition.X > MenuPosition.X + (MenuSize.X / 6) * 2 && MousePosition.X < MenuPosition.X + (MenuSize.X / 6) * 3 && MousePosition.Y > MenuPosition.Y + 50 && MousePosition.Y < MenuPosition.Y + 85) {
			CurrentTab = 2;
			CurrentOption = 0;
		}
		// Handle presses of Skins tab
		if (MousePosition.X > MenuPosition.X + (MenuSize.X / 6) * 3 && MousePosition.X < MenuPosition.X + (MenuSize.X / 6) * 4 && MousePosition.Y > MenuPosition.Y + 50 && MousePosition.Y < MenuPosition.Y + 85) {
			CurrentTab = 3;
			CurrentOption = 0;
		}
		// Handle presses of Misc tab
		if (MousePosition.X > MenuPosition.X + (MenuSize.X / 6) * 4 && MousePosition.X < MenuPosition.X + (MenuSize.X / 6) * 5 && MousePosition.Y > MenuPosition.Y + 50 && MousePosition.Y < MenuPosition.Y + 85) {
			CurrentTab = 4;
			CurrentOption = 0;
		}
		// Handle presses of Misc tab
		if (MousePosition.X > MenuPosition.X + (MenuSize.X / 6) * 5 && MousePosition.X < MenuPosition.X + (MenuSize.X / 6) * 6 && MousePosition.Y > MenuPosition.Y + 50 && MousePosition.Y < MenuPosition.Y + 85) {
			CurrentTab = 5;
			CurrentOption = 0;
		}
	}
	if (SDK.WasInputKeyJustReleased(Globals::LeftMouseButton)) {
		IsDragging = false;
		LclickFix = false;
	}
	if (IsDragging) {
		auto newPosition = MousePosition - DragOffset;
		if (newPosition.X >= Globals::Width - MenuSize.X)
			newPosition.X = Globals::Width - MenuSize.X;
		if (newPosition.Y >= Globals::Height - MenuSize.Y)
			newPosition.Y = Globals::Height - MenuSize.Y;
		if (newPosition.X <= 0)
			newPosition.X = 0;
		if (newPosition.Y <= 0)
			newPosition.Y = 0;

		MenuPosition = newPosition;
	}
}

void GUI::DrawMenu() {
	// Menu background
	if (MenuPosition.X == 69.6969) MenuPosition = FVector2D(20, (Globals::Height / 2) - (MenuSize.Y / 2)); //Menu Pos

	//if (!Globals::InLobby) Globals::UpdateCharacterCustomization_t(Globals::MyPlayer);

	HandleMenuMouse();

	auto Rudolf = MenuPosition + FVector2D(10, 60); //Option Pos
	// Menu background
	Functions.DrawFilledRect(MenuPosition, MenuSize.X - 2, MenuSize.Y - 2, FLinearColor(28, 29, 37, 1.f));
	// Menu Title Rect
	// Title rect
	Functions.DrawFilledRect(MenuPosition, MenuSize.X - 2, 45, FLinearColor(12, 13, 16, 1.f));
	// Menu Title Text
#ifdef false
	auto size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"SWYZZICATE"), FVector2D(1.1f, 1.0f));
	SDK.K2_DrawText(Globals::Burbank, xor_w(L"SWYZZICATE"), MenuPosition + FVector2D((MenuSize.X / 2) - (size.X / 2), 3), FVector2D(1.1f, 1.0f), FLinearColor(185, 160, 87, 1), 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
#else
	auto size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"SYNDICATE"), FVector2D(1.1f, 1.0f));
	SDK.K2_DrawText(Globals::Burbank, xor_w(L"SYNDICATE"), MenuPosition + FVector2D((MenuSize.X / 2) - (size.X / 2), 3), FVector2D(1.1f, 1.0f), FLinearColor(185, 160, 87, 1), 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
#endif
	// Tabs rect
	Functions.DrawFilledRect(MenuPosition + FVector2D(0, 50), MenuSize.X - 2, 35, FLinearColor(12, 13, 16, 1.f));
	// Tabs
	{
		auto UnselectedTab = FLinearColor(255, 255, 255, 1.f); /*color On*/
		auto SelectedTab = FLinearColor(185, 160, 87, 1); /*color On*/
		if (CurrentOption == 0) {
			if (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right)) {
				if (CurrentTab != /*4*/5) CurrentTab++;
			}
			if (SDK.WasInputKeyJustPressed(Globals::Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left)) {
				if (CurrentTab != 0) CurrentTab--;
			}
		}
		auto tabSize = (MenuSize.X - 2) / 6;
		if (CurrentTab == 0) {
			Functions.DrawFilledRect(MenuPosition + FVector2D(0, 50), tabSize, 35, FLinearColor(28, 29, 37, 1.f));
			SDK.K2_DrawLine(MenuPosition + FVector2D(0, 50), MenuPosition + FVector2D(tabSize, 50), 1.f, FLinearColor(5, 5, 5, 1.f));
		}
		size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"AIMBOT"), FVector2D(0.7f, 0.7f));
		SDK.K2_DrawText(Globals::Burbank, xor_w(L"AIMBOT"), MenuPosition + FVector2D((tabSize / 2) - (size.X / 2), 54), FVector2D(0.7f, 0.7f), ((CurrentOption == 0) && (CurrentTab == 0)) ? SelectedTab : UnselectedTab, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

		if (CurrentTab == 1) {
			Functions.DrawFilledRect(MenuPosition + FVector2D(tabSize, 50), tabSize, 35, FLinearColor(28, 29, 37, 1.f));
			SDK.K2_DrawLine(MenuPosition + FVector2D(tabSize, 50), MenuPosition + FVector2D(tabSize * 2, 50), 1.f, FLinearColor(5, 5, 5, 1.f));
		}
		size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"WEAPONS"), FVector2D(0.7f, 0.7f));
		SDK.K2_DrawText(Globals::Burbank, xor_w(L"WEAPONS"), MenuPosition + FVector2D(tabSize + (tabSize / 2) - (size.X / 2), 54), FVector2D(0.7f, 0.7f), ((CurrentOption == 0) && (CurrentTab == 1)) ? SelectedTab : UnselectedTab, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

		if (CurrentTab == 2) {
			Functions.DrawFilledRect(MenuPosition + FVector2D(tabSize * 2, 50), tabSize, 35, FLinearColor(28, 29, 37, 1.f));
			SDK.K2_DrawLine(MenuPosition + FVector2D(tabSize * 2, 50), MenuPosition + FVector2D(tabSize * 3, 50), 1.f, FLinearColor(5, 5, 5, 1.f));
		}
		size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"VISUALS"), FVector2D(0.7f, 0.7f));
		SDK.K2_DrawText(Globals::Burbank, xor_w(L"VISUALS"), MenuPosition + FVector2D(tabSize * 2 + (tabSize / 2) - (size.X / 2), 54), FVector2D(0.7f, 0.7f), ((CurrentOption == 0) && (CurrentTab == 2)) ? SelectedTab : UnselectedTab, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

		if (CurrentTab == 3) {
			Functions.DrawFilledRect(MenuPosition + FVector2D(tabSize * 3, 50), tabSize, 35, FLinearColor(28, 29, 37, 1.f));
			SDK.K2_DrawLine(MenuPosition + FVector2D(tabSize * 3, 50), MenuPosition + FVector2D(tabSize * 4, 50), 1.f, FLinearColor(5, 5, 5, 1.f));

		}
		size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"WORLD"), FVector2D(0.7f, 0.7f));
		SDK.K2_DrawText(Globals::Burbank, xor_w(L"WORLD"), MenuPosition + FVector2D(tabSize * 3 + (tabSize / 2) - (size.X / 2), 54), FVector2D(0.7f, 0.7f), ((CurrentOption == 0) && (CurrentTab == 3)) ? SelectedTab : UnselectedTab, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		
		if (CurrentTab == 4) {
			Functions.DrawFilledRect(MenuPosition + FVector2D(tabSize * 4, 50), tabSize, 35, FLinearColor(28, 29, 37, 1.f));
			SDK.K2_DrawLine(MenuPosition + FVector2D(tabSize * 4, 50), MenuPosition + FVector2D(tabSize * 5, 50), 1.f, FLinearColor(5, 5, 5, 1.f));
		}
		size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"LOCKER"), FVector2D(0.7f, 0.7f));
		SDK.K2_DrawText(Globals::Burbank, xor_w(L"LOCKER"), MenuPosition + FVector2D(tabSize * 4 + (tabSize / 2) - (size.X / 2), 54), FVector2D(0.7f, 0.7f), ((CurrentOption == 0) && (CurrentTab == 4)) ? SelectedTab : UnselectedTab, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		
		if (CurrentTab == 5) {
			Functions.DrawFilledRect(MenuPosition + FVector2D(tabSize * 5, 50), tabSize, 35, FLinearColor(28, 29, 37, 1.f));
			SDK.K2_DrawLine(MenuPosition + FVector2D(tabSize * 5, 50), MenuPosition + FVector2D(tabSize * 6, 50), 1.f, FLinearColor(5, 5, 5, 1.f));
		}
		size = SDK.K2_TextSize(Globals::Burbank, xor_w(L"MISC"), FVector2D(0.7f, 0.7f));
		SDK.K2_DrawText(Globals::Burbank, xor_w(L"MISC"), MenuPosition + FVector2D(tabSize * 5 + (tabSize / 2) - (size.X / 2), 54), FVector2D(0.7f, 0.7f), ((CurrentOption == 0) && (CurrentTab == 5)) ? SelectedTab : UnselectedTab, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
	}

	// Line around all Menu
	SDK.K2_DrawBox(MenuPosition, FVector2D(MenuSize.X - 2, MenuSize.Y - 2), 1.0f, FLinearColor(12, 13, 16, 1.f));

	// Draw Options
	InitOptions(Rudolf);

	if (MousePosition.X && MousePosition.Y) Functions.DrawFilledRect(FVector2D(MousePosition.X - 4, MousePosition.Y - 4), 8, 8, FLinearColor(0,0,0));
}
#else
// Function overload for bool options
void GUI::AddOption(FVector2D DuplicateMenuPosition, int& OptionIndex, double DuplicateTitleSizeY, wchar_t* OptionName, bool& OptionValue) {
	FVector2D DuplicateOptionPosition = DuplicateMenuPosition + FVector2D(0.f, 35.f + OptionIndex * 35.f);
	bool bIsActiveOptionDuplicate = (OptionIndex == SelectedOptionIndexDuplicate);

	// Determine the color for the duplicated option rect based on whether it is active or not
	FLinearColor DuplicateOptionRectColor = bIsActiveOptionDuplicate ? OptionRectColorActive : OptionRectColorInactive;

	// Draw duplicated option rect
	Functions.DrawFilledRect(DuplicateOptionPosition, MenuWidth, DuplicateTitleSizeY, DuplicateOptionRectColor);

	// Draw duplicated option text with the value
	FString OptionText = SDK.Concat_StrStr(OptionName, OptionValue ? E(L": On") : E(L": Off"));
	SDK.K2_DrawText(Globals::HeadingNow, OptionText, DuplicateOptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

	// Handle input to toggle the option value
	if ((SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right)) && bIsActiveOptionDuplicate)
	{
		OptionValue = !OptionValue;
	}
	if ((SDK.WasInputKeyJustPressed(Globals::Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left)) && bIsActiveOptionDuplicate)
	{
		OptionValue = !OptionValue;
	}

	OptionIndex++;
}

void GUI::AddOption(FVector2D DuplicateMenuPosition, int& OptionIndex, double DuplicateTitleSizeY, wchar_t* OptionName, int& OptionValue, int min, int max, bool isFastInt, bool isBonesOption) {
	FVector2D DuplicateOptionPosition = DuplicateMenuPosition + FVector2D(0.f, 35.f + OptionIndex * 35.f);
	bool bIsActiveOptionDuplicate = (OptionIndex == SelectedOptionIndexDuplicate);

	// Determine the color for the duplicated option rect based on whether it is active or not
	FLinearColor DuplicateOptionRectColor = bIsActiveOptionDuplicate ? OptionRectColorActive : OptionRectColorInactive;

	// Draw duplicated option rect
	Functions.DrawFilledRect(DuplicateOptionPosition, MenuWidth, DuplicateTitleSizeY, DuplicateOptionRectColor);

	// Draw duplicated option text with the value

	FString OptionText;
	if (isBonesOption) {
		OptionText = SDK.Concat_StrStr(OptionName, E(L": "));
		if (OptionValue == 1) OptionText = SDK.Concat_StrStr(OptionText, E(L"Head"));
		if (OptionValue == 2) OptionText = SDK.Concat_StrStr(OptionText, E(L"Neck"));
		if (OptionValue == 3) OptionText = SDK.Concat_StrStr(OptionText, E(L"Body"));
		if (OptionValue == 4) OptionText = SDK.Concat_StrStr(OptionText, E(L"Auto"));
	}
	else {
		OptionText = SDK.Concat_StrStr(OptionName, E(L": "));
		OptionText = SDK.Concat_StrStr(OptionText, SDK.BuildString_Int(E(L""), E(L""), OptionValue, E(L"")));
	}

	SDK.K2_DrawText(Globals::HeadingNow, OptionText, DuplicateOptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

	if ((isFastInt ? (SDK.IsInputKeyDown(Globals::Right) || SDK.IsInputKeyDown(Globals::Gamepad_DPad_Right)) : (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right))) && bIsActiveOptionDuplicate)
	{
		OptionValue += 1;
		if (OptionValue > max) OptionValue = min;
		if (OptionValue < min) OptionValue = max;
	}
	if ((isFastInt ? (SDK.IsInputKeyDown(Globals::Left) || SDK.IsInputKeyDown(Globals::Gamepad_DPad_Left)) : (SDK.WasInputKeyJustPressed(Globals::Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left))) && bIsActiveOptionDuplicate)
	{
		OptionValue -= 1;
		if (OptionValue > max) OptionValue = min;
		if (OptionValue < min) OptionValue = max;
	}

	OptionIndex++;
}

void GUI::setFKey(FKey Key, FKey& OptionValue) {
	if (SDK.WasInputKeyJustPressed(Key)) { OptionValue = Key; RenderFKey_Busy = -1; }
}

void GUI::AddOption(FVector2D DuplicateMenuPosition, int& OptionIndex, double DuplicateTitleSizeY, const wchar_t* OptionName, FKey& OptionValue)
{
	FVector2D DuplicateOptionPosition = DuplicateMenuPosition + FVector2D(0.f, 35.f + OptionIndex * 35.f);
	bool bIsActiveOptionDuplicate = (OptionIndex == SelectedOptionIndexDuplicate);

	// Determine the color for the duplicated option rect based on whether it is active or not
	FLinearColor DuplicateOptionRectColor = bIsActiveOptionDuplicate ? OptionRectColorActive : OptionRectColorInactive;

	// Draw duplicated option rect
	Functions.DrawFilledRect(DuplicateOptionPosition, MenuWidth, DuplicateTitleSizeY, DuplicateOptionRectColor);

	auto isbusy = RenderFKey_Busy == OptionIndex;

	// Draw duplicated option text with the value
	FString OptionText = SDK.Concat_StrStr(OptionName, E(L": "));
	if (isbusy) {
		OptionText = SDK.Concat_StrStr(OptionText, E(L"..."));
	}
	else {
		if (OptionValue.KeyName == Globals::RightMouseButton.KeyName) {
			OptionText = SDK.Concat_StrStr(OptionText, E(L"RMB"));
		}
		else if (OptionValue.KeyName == Globals::LeftMouseButton.KeyName) {
			OptionText = SDK.Concat_StrStr(OptionText, E(L"LMB"));
		}
		else if (OptionValue.KeyName == Globals::MiddleMouseButton.KeyName) {
			OptionText = SDK.Concat_StrStr(OptionText, E(L"MMB"));
		}
		else if (OptionValue.KeyName == Globals::ThumbMouseButton.KeyName) {
			OptionText = SDK.Concat_StrStr(OptionText, E(L"TMB"));
		}
		else if (OptionValue.KeyName == Globals::ThumbMouseButton2.KeyName) {
			OptionText = SDK.Concat_StrStr(OptionText, E(L"TMB2"));
		}
		else {
			OptionText = SDK.Concat_StrStr(OptionText, SDK.Conv_NameToString(OptionValue.KeyName));
		}
	}
	SDK.K2_DrawText(Globals::HeadingNow, OptionText, DuplicateOptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

	// Handle input to change the option value
	if (bIsActiveOptionDuplicate)
	{
		// Example: Change the key when Right Arrow is pressed
		if (SDK.WasInputKeyJustPressed(Globals::Right) || SDK.WasInputKeyJustPressed(Globals::Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Left) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right))
		{
			if (RenderFKey_Busy == -1)
			{
				RenderFKey_Busy = OptionIndex;
			}
		}
		if (isbusy) {
			setFKey(Globals::MouseScrollUp, OptionValue);
			setFKey(Globals::MouseScrollDown, OptionValue);
			setFKey(Globals::MouseWheelAxis, OptionValue);
			setFKey(Globals::LeftMouseButton, OptionValue);
			setFKey(Globals::RightMouseButton, OptionValue);
			setFKey(Globals::MiddleMouseButton, OptionValue);
			setFKey(Globals::ThumbMouseButton, OptionValue);
			setFKey(Globals::ThumbMouseButton2, OptionValue);
			setFKey(Globals::BackSpace, OptionValue);
			setFKey(Globals::Tab, OptionValue);
			setFKey(Globals::Enter, OptionValue);
			setFKey(Globals::Pause, OptionValue);
			setFKey(Globals::CapsLock, OptionValue);
			setFKey(Globals::Escape, OptionValue);
			setFKey(Globals::SpaceBar, OptionValue);
			setFKey(Globals::PageUp, OptionValue);
			setFKey(Globals::PageDown, OptionValue);
			setFKey(Globals::End, OptionValue);
			setFKey(Globals::Home, OptionValue);
			setFKey(Globals::Left, OptionValue);
			setFKey(Globals::Up, OptionValue);
			setFKey(Globals::Right, OptionValue);
			setFKey(Globals::Down, OptionValue);
			setFKey(Globals::Insert, OptionValue);
			setFKey(Globals::Delete, OptionValue);
			setFKey(Globals::Zero, OptionValue);
			setFKey(Globals::One, OptionValue);
			setFKey(Globals::Two, OptionValue);
			setFKey(Globals::Three, OptionValue);
			setFKey(Globals::Four, OptionValue);
			setFKey(Globals::Five, OptionValue);
			setFKey(Globals::Six, OptionValue);
			setFKey(Globals::Seven, OptionValue);
			setFKey(Globals::Eight, OptionValue);
			setFKey(Globals::Nine, OptionValue);
			setFKey(Globals::A, OptionValue);
			setFKey(Globals::B, OptionValue);
			setFKey(Globals::C, OptionValue);
			setFKey(Globals::D, OptionValue);
			setFKey(Globals::E, OptionValue);
			setFKey(Globals::F, OptionValue);
			setFKey(Globals::G, OptionValue);
			setFKey(Globals::H, OptionValue);
			setFKey(Globals::I, OptionValue);
			setFKey(Globals::J, OptionValue);
			setFKey(Globals::K, OptionValue);
			setFKey(Globals::L, OptionValue);
			setFKey(Globals::M, OptionValue);
			setFKey(Globals::N, OptionValue);
			setFKey(Globals::O, OptionValue);
			setFKey(Globals::P, OptionValue);
			setFKey(Globals::Q, OptionValue);
			setFKey(Globals::R, OptionValue);
			setFKey(Globals::S, OptionValue);
			setFKey(Globals::T, OptionValue);
			setFKey(Globals::U, OptionValue);
			setFKey(Globals::V, OptionValue);
			setFKey(Globals::W, OptionValue);
			setFKey(Globals::X, OptionValue);
			setFKey(Globals::Y, OptionValue);
			setFKey(Globals::Z, OptionValue);
			setFKey(Globals::NumPadZero, OptionValue);
			setFKey(Globals::NumPadOne, OptionValue);
			setFKey(Globals::NumPadTwo, OptionValue);
			setFKey(Globals::NumPadThree, OptionValue);
			setFKey(Globals::NumPadFour, OptionValue);
			setFKey(Globals::NumPadFive, OptionValue);
			setFKey(Globals::NumPadSix, OptionValue);
			setFKey(Globals::NumPadSeven, OptionValue);
			setFKey(Globals::NumPadEight, OptionValue);
			setFKey(Globals::NumPadNine, OptionValue);
			setFKey(Globals::Multiply, OptionValue);
			setFKey(Globals::Add, OptionValue);
			setFKey(Globals::Subtract, OptionValue);
			setFKey(Globals::Decimal, OptionValue);
			setFKey(Globals::Divide, OptionValue);
			setFKey(Globals::F1, OptionValue);
			setFKey(Globals::F2, OptionValue);
			setFKey(Globals::F3, OptionValue);
			setFKey(Globals::F4, OptionValue);
			setFKey(Globals::F5, OptionValue);
			setFKey(Globals::F6, OptionValue);
			setFKey(Globals::F7, OptionValue);
			setFKey(Globals::F8, OptionValue);
			setFKey(Globals::F9, OptionValue);
			setFKey(Globals::F10, OptionValue);
			setFKey(Globals::F11, OptionValue);
			setFKey(Globals::F12, OptionValue);
			setFKey(Globals::NumLock, OptionValue);
			setFKey(Globals::ScrollLock, OptionValue);
			setFKey(Globals::LeftShift, OptionValue);
			setFKey(Globals::RightShift, OptionValue);
			setFKey(Globals::LeftControl, OptionValue);
			setFKey(Globals::RightControl, OptionValue);
			setFKey(Globals::LeftAlt, OptionValue);
			setFKey(Globals::RightAlt, OptionValue);
			setFKey(Globals::LeftCommand, OptionValue);
			setFKey(Globals::RightCommand, OptionValue);
			setFKey(Globals::Semicolon, OptionValue);
			setFKey(Globals::Equals, OptionValue);
			setFKey(Globals::Comma, OptionValue);
			setFKey(Globals::Underscore, OptionValue);
			setFKey(Globals::Hyphen, OptionValue);
			setFKey(Globals::Period, OptionValue);
			setFKey(Globals::Slash, OptionValue);
			setFKey(Globals::Tilde, OptionValue);
			setFKey(Globals::LeftBracket, OptionValue);
			setFKey(Globals::LeftParantheses, OptionValue);
			setFKey(Globals::Backslash, OptionValue);
			setFKey(Globals::RightBracket, OptionValue);
			setFKey(Globals::RightParantheses, OptionValue);
			setFKey(Globals::Apostrophe, OptionValue);
			setFKey(Globals::Quote, OptionValue);
			setFKey(Globals::Asterix, OptionValue);
			setFKey(Globals::Ampersand, OptionValue);
			setFKey(Globals::Caret, OptionValue);
			setFKey(Globals::Dollar, OptionValue);
			setFKey(Globals::Exclamation, OptionValue);
			setFKey(Globals::Colon, OptionValue);
			setFKey(Globals::Section, OptionValue);
			setFKey(Globals::Gamepad_Left2D, OptionValue);
			setFKey(Globals::Gamepad_LeftX, OptionValue);
			setFKey(Globals::Gamepad_LeftY, OptionValue);
			setFKey(Globals::Gamepad_Right2D, OptionValue);
			setFKey(Globals::Gamepad_RightX, OptionValue);
			setFKey(Globals::Gamepad_RightY, OptionValue);
			setFKey(Globals::Gamepad_LeftTriggerAxis, OptionValue);
			setFKey(Globals::Gamepad_RightTriggerAxis, OptionValue);
			setFKey(Globals::Gamepad_LeftThumbstick, OptionValue);
			setFKey(Globals::Gamepad_RightThumbstick, OptionValue);
			setFKey(Globals::Gamepad_Special_Left, OptionValue);
			setFKey(Globals::Gamepad_Special_Left_X, OptionValue);
			setFKey(Globals::Gamepad_Special_Left_Y, OptionValue);
			setFKey(Globals::Gamepad_Special_Right, OptionValue);
			setFKey(Globals::Gamepad_FaceButton_Bottom, OptionValue);
			setFKey(Globals::Gamepad_FaceButton_Right, OptionValue);
			setFKey(Globals::Gamepad_FaceButton_Left, OptionValue);
			setFKey(Globals::Gamepad_FaceButton_Top, OptionValue);
			setFKey(Globals::Gamepad_LeftShoulder, OptionValue);
			setFKey(Globals::Gamepad_RightShoulder, OptionValue);
			setFKey(Globals::Gamepad_LeftTrigger, OptionValue);
			setFKey(Globals::Gamepad_RightTrigger, OptionValue);
			setFKey(Globals::Gamepad_DPad_Up, OptionValue);
			setFKey(Globals::Gamepad_DPad_Down, OptionValue);
			setFKey(Globals::Gamepad_DPad_Right, OptionValue);
			setFKey(Globals::Gamepad_DPad_Left, OptionValue);
			setFKey(Globals::Gamepad_LeftStick_Up, OptionValue);
			setFKey(Globals::Gamepad_LeftStick_Down, OptionValue);
			setFKey(Globals::Gamepad_LeftStick_Right, OptionValue);
			setFKey(Globals::Gamepad_LeftStick_Left, OptionValue);
			setFKey(Globals::Gamepad_RightStick_Up, OptionValue);
			setFKey(Globals::Gamepad_RightStick_Down, OptionValue);
			setFKey(Globals::Gamepad_RightStick_Right, OptionValue);
			setFKey(Globals::Gamepad_RightStick_Left, OptionValue);
		}
	}

	OptionIndex++;
}

void GUI::DrawMenu() {
	FVector2D MenuPosition(10.f, 10.f);  // Adjust the position as needed
	FLinearColor MenuBackgroundColor(0.f, 0.f, 0.f, 1.f);  // Black color
	int NumOptions = 4;

	FVector2D TitlePosition = MenuPosition + FVector2D(MenuWidth / 2.f, 0.f);
	FLinearColor TitleColor(255.f, 255.f, 255.f, 1.f);  // White color

	// Option settings
	//FString OptionNames[] = { L"Aimbot Settings", L"All Game Visuals", L"Weapons Config", L"Miscellaneous" };

	float TotalOptionsHeight = NumOptions * 35.f;

	// Adjust the menu height based on the total options height
	float MenuHeight = TotalOptionsHeight + 10.f;  // Add some extra space for padding

	// Draw menu background
	Functions.DrawFilledRect(MenuPosition, MenuWidth, MenuHeight, MenuBackgroundColor);

	// Draw title
	auto TitleSize = SDK.K2_TextSize(Globals::HeadingNow, E(L"RAID"), FVector2D(0.7f, 0.7f));
	SDK.K2_DrawText(Globals::HeadingNow, E(L"RAID"), MenuPosition + FVector2D((MenuWidth / 2) - (TitleSize.X / 2), 2), FVector2D(0.7f, 0.7f), OptionRectColorActive, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

	// Draw options
	for (int OptionIndex = 0; OptionIndex < NumOptions; ++OptionIndex)
	{
		FVector2D OptionPosition = MenuPosition + FVector2D(0.f, 35.f + OptionIndex * 35.f);
		bool bIsActiveOption = (OptionIndex == SelectedOptionIndex);

		// Determine the color for the option rect based on whether it is active or not
		FLinearColor OptionRectColor = bIsActiveOption ? OptionRectColorActive : OptionRectColorInactive;

		// Draw option rect
		Functions.DrawFilledRect(OptionPosition, MenuWidth, TitleSize.Y, OptionRectColor);

		// Draw option text
		if (OptionIndex == 0) SDK.K2_DrawText(Globals::HeadingNow, E(L"Aimbot Settings"), OptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		if (OptionIndex == 1) SDK.K2_DrawText(Globals::HeadingNow, E(L"All Game Visuals"), OptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		if (OptionIndex == 2) SDK.K2_DrawText(Globals::HeadingNow, E(L"Weapons Config"), OptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		if (OptionIndex == 3) SDK.K2_DrawText(Globals::HeadingNow, E(L"Miscellaneous"), OptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		//K2_DrawText(Globals::HeadingNow, OptionNames[OptionIndex], OptionPosition + FVector2D(5.f, 1.f), FVector2D(0.5f, 0.5f), OptionTextColor, 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());

		// Check if the "Aimbot" option is selected and the Right Arrow key is pressed
		if ((SDK.WasInputKeyJustPressed(Globals::PageUp) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Right)) && bIsActiveOption && !iShowDuplicateMenu)
		{
			iShowDuplicateMenu = OptionIndex + 1;
		}
	}

	// Draw duplicated menu if the flag is set
	if (iShowDuplicateMenu)
	{
		FVector2D DuplicateMenuPosition = MenuPosition + FVector2D(MenuWidth + 5.f, 0.f);  // Adjust the position as needed

		// Draw duplicated menu background
		Functions.DrawFilledRect(DuplicateMenuPosition, MenuWidth, DuplicateMenuMenuHeight, MenuBackgroundColor);

		//auto TabName = OptionNames[iShowDuplicateMenu - 1];

		// Draw duplicated title
		FVector2D DuplicateTitleSize;
		if (iShowDuplicateMenu == 1) {
			DuplicateTitleSize = SDK.K2_TextSize(Globals::HeadingNow, E(L"Aimbot Settings"), FVector2D(0.7f, 0.7f));
			SDK.K2_DrawText(Globals::HeadingNow, E(L"Aimbot Settings"), DuplicateMenuPosition + FVector2D((MenuWidth / 2) - (DuplicateTitleSize.X / 2), 2), FVector2D(0.7f, 0.7f), FLinearColor(200, 0, 0, 1), 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		}
		else if (iShowDuplicateMenu == 2) {
			DuplicateTitleSize = SDK.K2_TextSize(Globals::HeadingNow, E(L"All Game Visuals"), FVector2D(0.7f, 0.7f));
			SDK.K2_DrawText(Globals::HeadingNow, E(L"All Game Visuals"), DuplicateMenuPosition + FVector2D((MenuWidth / 2) - (DuplicateTitleSize.X / 2), 2), FVector2D(0.7f, 0.7f), FLinearColor(200, 0, 0, 1), 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		}
		else if (iShowDuplicateMenu == 3) {
			DuplicateTitleSize = SDK.K2_TextSize(Globals::HeadingNow, E(L"Weapons Config"), FVector2D(0.7f, 0.7f));
			SDK.K2_DrawText(Globals::HeadingNow, E(L"Weapons Config"), DuplicateMenuPosition + FVector2D((MenuWidth / 2) - (DuplicateTitleSize.X / 2), 2), FVector2D(0.7f, 0.7f), FLinearColor(200, 0, 0, 1), 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		}
		else if (iShowDuplicateMenu == 4) {
			DuplicateTitleSize = SDK.K2_TextSize(Globals::HeadingNow, E(L"Miscellaneous"), FVector2D(0.7f, 0.7f));
			SDK.K2_DrawText(Globals::HeadingNow, E(L"Miscellaneous"), DuplicateMenuPosition + FVector2D((MenuWidth / 2) - (DuplicateTitleSize.X / 2), 2), FVector2D(0.7f, 0.7f), FLinearColor(200, 0, 0, 1), 1.0f, FLinearColor(), FVector2D(), false, false, false, FLinearColor());
		}

		int totalOptions = 0;

		if (iShowDuplicateMenu == 1) { // Aimbot Tab
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Toggle Aimbot"), Config.Aimbot.AimKey);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Aim Key"), Globals::AimKey);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Aim Bone"), Config.Aimbot.BoneTarget, 1, 4, false, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Aim FOV"), Config.Aimbot.FOVRange, 1, 1000, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Aim Smooth"), Config.Aimbot.Smooth, 0, 99);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Toggle Triggerbot"), Config.Aimbot.TriggerKey);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Trigger Key"), Globals::TriggerKey);
			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Auto Aim FOV"), gump);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Downed Check"), Config.Aimbot.KnockedCheck);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Visible Check"), Config.Aimbot.VisCheck);
			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Close Enemies Aim"), vcheqclose);
		}
		else if (iShowDuplicateMenu == 2) { // Visuals Tab
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Toggle Visuals"), Config.Visuals.Enabled);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Loot ESP"), Config.World.Enabled);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"FOV Circle"), Config.Visuals.DrawFOV);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Toggle Crosshair"), Config.Misc.Crosshair);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Enemy Platform"), Config.Visuals.Platform);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Enemy Name"), Config.Visuals.Name);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Enemy Distance"), Config.Visuals.Distance);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Enemy Kills"), Config.Visuals.Kills);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Enemy Box"), Config.Visuals.Box);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Cornered Box"), Config.Visuals.CornerBox);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Enemy Skeleton"), Config.Visuals.Bones);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"ESP Thickness"), Config.Visuals.BoxSize, 1, 10);

			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Player Visible Color"), clrV, 1, 6);
			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Player Invisible Color"), clrI, 1, 6);
			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Player Downed Color"), clrD, 1, 6);
			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Minimum Loot Rarity (F5/F6)"), chosrar, 1, 9);
		}
		else if (iShowDuplicateMenu == 3) { // Weapons Tab
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Custom Smoothing"), Config.WeaponConfig.cwsm);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"SMG Smoothing"), Config.WeaponConfig.smgcwsm, 0, 100);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Shotgun Smoothing"), Config.WeaponConfig.scwsm, 0, 100);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"AR Smoothing"), Config.WeaponConfig.acwsm, 0, 100);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Custom Bone"), Config.WeaponConfig.cwbone);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"SMG Bone"), Config.WeaponConfig.smgcwbone, 1, 4, false, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Shotgun Bone"), Config.WeaponConfig.scwfov, 1, 4, false, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"AR Bone"), Config.WeaponConfig.acwbone, 1, 4, false, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Custom FOV"), Config.WeaponConfig.cwfov);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"SMG FOV"), Config.WeaponConfig.smgcwfov, 1, 1000, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Shotgun FOV"), Config.WeaponConfig.scwfov, 1, 1000, true);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"AR FOV"), Config.WeaponConfig.acwfov, 1, 1000, true);
		}
		else if (iShowDuplicateMenu == 4) { // Misc Tab
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Toggle Panic Key"), Config.Misc.PanicKey);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Panic Key"), Globals::PanicKey);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Aim Prediction"), Config.Aimbot.ProjectilePrediction);
			//AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Minimap Radar"), minmep);
			AddOption(DuplicateMenuPosition, totalOptions, DuplicateTitleSize.Y, E(L"Menu Key"), Globals::MenuKey);
		}

		DuplicateMenuMenuHeight = totalOptions * 35.f + 10.f;  // Add some extra space for padding

		// Handle input to navigate through options of the duplicated menu
		if ((SDK.WasInputKeyJustPressed(Globals::Up) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Up)) && RenderFKey_Busy == -1)
		{
			SelectedOptionIndexDuplicate = (SelectedOptionIndexDuplicate - 1 + totalOptions) % totalOptions;
		}
		else if ((SDK.WasInputKeyJustPressed(Globals::Down) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Down)) && RenderFKey_Busy == -1)
		{
			SelectedOptionIndexDuplicate = (SelectedOptionIndexDuplicate + 1) % totalOptions;
		}

		if ((SDK.WasInputKeyJustPressed(Globals::PageDown) || SDK.WasInputKeyJustPressed(Globals::Gamepad_FaceButton_Right)) && RenderFKey_Busy == -1)
		{
			iShowDuplicateMenu = 0;
			SelectedOptionIndexDuplicate = 0;
		}

		return;
	}

	// Handle input to navigate through options of the first menu
	if ((SDK.WasInputKeyJustPressed(Globals::Up) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Up)))
	{
		SelectedOptionIndex = (SelectedOptionIndex - 1 + NumOptions) % NumOptions;
	}
	else if (SDK.WasInputKeyJustPressed(Globals::Down) || SDK.WasInputKeyJustPressed(Globals::Gamepad_DPad_Down))
	{
		SelectedOptionIndex = (SelectedOptionIndex + 1) % NumOptions;
	}
}
#endif