#include "Functions.h"

Camera_Struct vCamera;
config Config;

void Functions::Draw2DBoundingBox(uint64_t Actor, FVector Bottom, FVector Top, FLinearColor Color) {
	FVector WorldOrigin, WorldBoxExtent;

	SDK.GetActorBounds(Actor, bool(Globals::MyPlayer), false, &WorldOrigin, &WorldBoxExtent);

	WorldBoxExtent.X *= 2.f;
	WorldBoxExtent.Y *= 2.f;
	WorldBoxExtent.Z *= 2.f;

	WorldOrigin.X -= WorldBoxExtent.X / 2.f;
	WorldOrigin.Y -= WorldBoxExtent.Y / 2.f;
	WorldOrigin.Z -= WorldBoxExtent.Z / 2.f;

	FVector one = WorldOrigin;
	FVector two = WorldOrigin; two.X += WorldBoxExtent.X;
	FVector three = WorldOrigin; three.X += WorldBoxExtent.X; three.Y += WorldBoxExtent.Y;
	FVector four = WorldOrigin; four.Y += WorldBoxExtent.Y;

	FVector five = one; five.Z += WorldBoxExtent.Z;
	FVector six = two; six.Z += WorldBoxExtent.Z;
	FVector seven = three; seven.Z += WorldBoxExtent.Z;
	FVector eight = four; eight.Z += WorldBoxExtent.Z;

	FVector s1, s2, s3, s4, s5, s6, s7, s8;
	s1 = SDK.K2_Project(one);
	s2 = SDK.K2_Project(two);
	s3 = SDK.K2_Project(three);
	s4 = SDK.K2_Project(four);
	s5 = SDK.K2_Project(five);
	s6 = SDK.K2_Project(six);
	s7 = SDK.K2_Project(seven);
	s8 = SDK.K2_Project(eight);

	

		double x_array[8] = { s1.X, s2.X, s3.X, s4.X, s5.X, s6.X, s7.X, s8.X };
		double right = x_array[0], left = x_array[0];

		for (int right_idx = 0; right_idx < 8; right_idx++)
			if (x_array[right_idx] > right)
				right = x_array[right_idx];

		for (int left_idx = 0; left_idx < 8; left_idx++)
			if (x_array[left_idx] < left)
				left = x_array[left_idx];


		float Width = right - left;
		float Height = Bottom.Y - Top.Y;

		FVector2D min, max, size;
		min.X = left;
		min.Y = Bottom.Y;

		max.X = right;
		max.Y = Top.Y;

		size.X = min.X - max.X;
		size.Y = min.Y - max.Y;

		SDK.K2_DrawBox(max, size, 2.5f, FLinearColor(0.f, 0.f, 0.f, 255.f));
		SDK.K2_DrawBox(max, size, 1.2f, Color);
	
}
/*
bool Functions::isValidWcharString(const wchar_t* str) {
	if (str == nullptr) {
		// The string is a null pointer, not valid.
		return false;
	}

	// First character must be a letter (A-Z, a-z).
	if (!((*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122))) {
		return false;
	}

	const wchar_t* temp = str;
	wchar_t prevChar = *temp;  // Start with the first character.

	for (temp = temp + 1; *temp; ++temp) {
		if ((*temp >= 65 && *temp <= 90) || (*temp >= 97 && *temp <= 122)) {
			// It's a letter, continue checking.
			prevChar = *temp;
		}
		else if (*temp == 32 && ((prevChar >= 65 && prevChar <= 90) || (prevChar >= 97 && prevChar <= 122))) {
			// It's a space, check next character for being a letter.
			const wchar_t* nextChar = temp + 1;
			if (!(*nextChar) || !((*nextChar >= 65 && *nextChar <= 90) || (*nextChar >= 97 && *nextChar <= 122))) {
				// Next character isn't a letter, mark invalid.
				return false;
			}
			// Valid space, continue checking.
			prevChar = *temp;
		}
		else {
			// Any non-letter and non-space character found.
			return false;
		}
	}

	// Ensure the last character is a letter.
	if (!((prevChar >= 65 && prevChar <= 90) || (prevChar >= 97 && prevChar <= 122))) {
		return false;
	}

	return true; // If loop completes without returning false, the string is valid.
}*/
#ifndef RAID
void Functions::World_Loop() {
	double distance;
	TArray<uint64_t*> BuildingContainer, Vehicle, AthenaSupplyDrop, Pickup;

	if (Config.World.Pickup) SDK.GetAllActorsOfClass(Globals::FortPickup, &Pickup);
	if (Config.World.Vehicles) SDK.GetAllActorsOfClass(Globals::FortAthenaSKVehicle, &Vehicle);
	if (Config.World.Chests || Config.World.AmmoBox) SDK.GetAllActorsOfClass(Globals::BuildingContainer, &BuildingContainer);
	//if (Config.World.Trap) SDK.GetAllActorsOfClass(Globals::BuildingTrap, &BuildingTrap);
	if (Config.World.Llama) SDK.GetAllActorsOfClass(Globals::FortAthenaSupplyDrop, &AthenaSupplyDrop);

	if (Config.World.Enabled) {
		if (Config.World.Chests || Config.World.AmmoBox) {
			for (int i = 0; i < BuildingContainer.Num(); i++) {
				uint64_t Container = (uint64_t)BuildingContainer[i];
				if (!Container) continue;

				auto bAlreadySearched = (Core.read<char>(Container + Offsets.bAlreadySearched) >> 2) & 1;
				if (bAlreadySearched) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(Container);
				FVector ScreenLocation;
				
				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				if (distance > Config.World.WorldDistance) continue;

				auto ObjectName = SDK.GetObjectName(Container).c_str();

				auto isChest = ObjectName != NULL && SDK.Contains(ObjectName, xor_w(L"Chest"), false, false);
				auto isAmmo = ObjectName != NULL && SDK.Contains(ObjectName, xor_w(L"Ammo"), false, false);

				if (Config.World.Chests) {
					if (isChest) {
						//SDK.SetQuestHighlight(true);

						FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
						FString ItemString = SDK.Concat_StrStr(FString(xor_w(L"Chest")), StringDistance);

						ScreenLocation = SDK.K2_Project(ActorLocation);
						if (IsValidScreenLoc(ScreenLocation)) {
							auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
							auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);					
							SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(236.0f, 252.0f, 3.0f, 0.95f), 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
						}
					}
				}
				if (Config.World.AmmoBox) {
					if (isAmmo) {
						FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
						FString ItemString = SDK.Concat_StrStr(FString(xor_w(L"AMMO BOX")), StringDistance);

						ScreenLocation = SDK.K2_Project(ActorLocation);
						if (IsValidScreenLoc(ScreenLocation)) {
							auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
							auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);											
							SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(123, 123, 123), 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
						}
					}
				}
			}
		}

		/*if (Config.World.Trap) {
			for (int i = 0; i < BuildingTrap.Num(); i++) {
				uint64_t Trap = (uint64_t)BuildingTrap[i];
				if (!Trap) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(Trap);
				FVector ScreenLocation;

				wchar_t* Name = NULL;

				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				if (distance > Config.World.TrapDistance) continue;

				if (SDK.HasDurability(Trap))
				{
					FString ItemString;

					FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
					ItemString = SDK.Concat_StrStr(FString(xor_w(L"TRAP")), StringDistance);				

					ScreenLocation = SDK.K2_Project(ActorLocation);
					if (IsValidScreenLoc(ScreenLocation)) {
						auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
						auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);				
						SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(123, 123, 123, 0.95f), 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
					}
				}
			}
		}*/

		if (Config.World.Vehicles) {
			for (int i = 0; i < Vehicle.Num(); i++) {
				uint64_t Vehicles = (uint64_t)Vehicle[i];
				if (!Vehicles) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(Vehicles);
				FVector ScreenLocation;

				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				if (distance > Config.World.WorldDistance) continue;

				FString Displayname = SDK.VehicleGetDisplayName(Vehicles);
				FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
				FString ItemString = SDK.Concat_StrStr(Displayname, StringDistance);

				auto Driveable = SDK.CanContainPlayers(Vehicles);
				if (Driveable) {
					ScreenLocation = SDK.K2_Project(ActorLocation);
					if (IsValidScreenLoc(ScreenLocation)) {
						auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
						auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);		
						SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(5, 128, 123), 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
					}
				}
			}
		}

		if (Config.World.Llama) {
			for (int i = 0; i < AthenaSupplyDrop.Num(); i++) {
				uint64_t SupplyDrop = (uint64_t)AthenaSupplyDrop[i];
				if (!SupplyDrop) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(SupplyDrop);
				FVector ScreenLocation;

				wchar_t* Name = NULL;

				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				if (distance != 0 && distance > Config.World.LlamaDistance) continue;

				auto ObjectName = SDK.GetObjectName(SupplyDrop).c_str();

				auto isLlamna = ObjectName != NULL && SDK.Contains(ObjectName, xor_w(L"LLAMA"), false, false);
				
				if (isLlamna) {
					FString ItemString;
					FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
					ItemString = SDK.Concat_StrStr(FString(xor_w(L"LLAMA")), StringDistance);

					ScreenLocation = SDK.K2_Project(ActorLocation);
					if (IsValidScreenLoc(ScreenLocation)) {
						auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
						auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);
						SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(66, 191, 249), 1.0f, FLinearColor(0, 0, 0), FVector2D(), false, false, true, FLinearColor(0, 0, 0));
					}
				}
			}
		}

		if (Config.World.Pickup) {
			for (int i = 0; i < Pickup.Num(); i++) {
				uint64_t LootItems = (uint64_t)Pickup[i];
				if (!LootItems) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(LootItems);
				FVector ScreenLocation;
				wchar_t* itemName = NULL;

				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				if (distance > Config.World.WorldDistance) continue;

				// Get The Actor DisplayName
				auto ItemDefinition = SDK.GetPrimaryItemDefinition(LootItems);
				auto ItemName = Core.read<FText>(ItemDefinition + Offsets.ItemName).GetText();
				if (ItemDefinition) itemName = ItemName;

				if (!itemName) continue;
				auto isAmmo = itemName != NULL && SDK.Contains(itemName, xor_w(L"Ammo"), false, false);
				auto isBrick = itemName != NULL && SDK.Contains(itemName, xor_w(L"Brick"), false, false);
				auto isWood = itemName != NULL && SDK.Contains(itemName, xor_w(L"Wood"), false, false);
				auto isMetal = itemName != NULL && SDK.Contains(itemName, xor_w(L"Metal"), false, false);
				auto isStone = itemName != NULL && SDK.Contains(itemName, xor_w(L"Stone"), false, false);
				auto isGold = itemName != NULL && SDK.Contains(itemName, xor_w(L"Gold"), false, false);
				auto isBounty = itemName != NULL && SDK.Contains(itemName, xor_w(L"Bounty"), false, false);
				if (isAmmo || isBrick || isWood || isMetal || isStone || isGold || isBounty) continue;

				if (ItemDefinition != NULL) {
					EFortItemTier Tier = SDK.GetTier(ItemDefinition);
					if (Tier < GetItemEFortTier(Config.World.LootMinimalTier)) continue;
					auto Color = GetItemColor(Tier);

					FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
					FString ItemString = SDK.Concat_StrStr(itemName, StringDistance);

					ScreenLocation = SDK.K2_Project(ActorLocation);
					if (IsValidScreenLoc(ScreenLocation)) {

						auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
						auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);				
						SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), Color, 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
					}
				}
			}
		}
	}
}
#else
void Functions::World_Loop() {
	double distance;
	TArray<uint64_t*> BuildingContainer, Vehicle, AthenaSupplyDrop, Pickup;

	if (Config.World.Pickup) SDK.GetAllActorsOfClass(Globals::FortPickup, &Pickup);
	//if (Config.World.Vehicles) SDK.GetAllActorsOfClass(Globals::FortAthenaSKVehicle, &Vehicle);
	if (Config.World.Chests || Config.World.AmmoBox) SDK.GetAllActorsOfClass(Globals::BuildingContainer, &BuildingContainer);
	//if (Config.World.Trap) SDK.GetAllActorsOfClass(Globals::BuildingTrap, &BuildingTrap);
	if (Config.World.Llama) SDK.GetAllActorsOfClass(Globals::FortAthenaSupplyDrop, &AthenaSupplyDrop);

	if (Config.World.Enabled) {
		if (Config.World.Chests || Config.World.AmmoBox) {
			for (int i = 0; i < BuildingContainer.Num(); i++) {
				uint64_t Container = (uint64_t)BuildingContainer[i];
				if (!Container) continue;

				auto bAlreadySearched = (Core.read<char>(Container + Offsets.bAlreadySearched) >> 2) & 1;
				if (bAlreadySearched) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(Container);
				FVector ScreenLocation;

				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				//if (distance > Config.World.ContainerDistance) continue;
				if (distance > 150.f) continue;

				auto ObjectName = SDK.GetObjectName(Container).c_str();

				auto isChest = ObjectName != NULL && SDK.Contains(ObjectName, xor_w(L"Chest"), false, false);
				auto isAmmo = ObjectName != NULL && SDK.Contains(ObjectName, xor_w(L"Ammo"), false, false);

				if (Config.World.Chests) {
					if (isChest) {
						//SDK.SetQuestHighlight(true);

						FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L""), distance, xor_w(L" M ]"));
						FString ItemString = SDK.Concat_StrStr(FString(xor_w(L"[ CHEST ")), StringDistance);

						ScreenLocation = SDK.K2_Project(ActorLocation);
						if (IsValidScreenLoc(ScreenLocation)) {
							auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
							auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);
							SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(236.0f, 252.0f, 3.0f, 0.95f), 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
						}
					}
				}
				if (Config.World.AmmoBox) {
					if (isAmmo) {
						FString StringDistance = SDK.BuildString_Int(xor_w(L""), xor_w(L" ["), distance, xor_w(L"m]"));
						FString ItemString = SDK.Concat_StrStr(FString(xor_w(L"AMMO BOX")), StringDistance);

						ScreenLocation = SDK.K2_Project(ActorLocation);
						if (IsValidScreenLoc(ScreenLocation)) {
							auto size = SDK.K2_TextSize(Globals::Burbank, ItemString, FVector2D(0.5f, 0.5f));
							auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);
							SDK.K2_DrawText(Globals::Burbank, ItemString, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), FLinearColor(123, 123, 123, 0.95f), 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
						}
					}
				}
			}
		}

		if (Config.World.Pickup) {
			for (int i = 0; i < Pickup.Num(); i++) {
				uint64_t LootItems = (uint64_t)Pickup[i];
				if (!LootItems) continue;

				FVector ActorLocation = SDK.K2_GetActorLocation(LootItems);
				FVector ScreenLocation;
				wchar_t* itemName = NULL;

				distance = SDK.Vector_Distance(vCamera.Location, ActorLocation) * 0.01;
				//if (distance > Config.World.PickupDistance) continue;
				if (distance > 150.f) continue;

				// Get The Actor DisplayName
				auto ItemDefinition = SDK.GetPrimaryItemDefinition(LootItems);
				auto ItemName = Core.read<FText>(ItemDefinition + Offsets.ItemName).GetText();
				if (ItemDefinition) itemName = ItemName;

				if (!itemName) continue;
				auto isAmmo = itemName != NULL && SDK.Contains(itemName, xor_w(L"Ammo"), false, false);
				auto isBrick = itemName != NULL && SDK.Contains(itemName, xor_w(L"Brick"), false, false);
				auto isWood = itemName != NULL && SDK.Contains(itemName, xor_w(L"Wood"), false, false);
				auto isMetal = itemName != NULL && SDK.Contains(itemName, xor_w(L"Metal"), false, false);
				auto isStone = itemName != NULL && SDK.Contains(itemName, xor_w(L"Stone"), false, false);
				auto isGold = itemName != NULL && SDK.Contains(itemName, xor_w(L"Gold"), false, false);
				auto isBounty = itemName != NULL && SDK.Contains(itemName, xor_w(L"Bounty"), false, false);
				if (isAmmo || isBrick || isWood || isMetal || isStone || isGold || isBounty) continue;

				if (ItemDefinition != NULL) {
					EFortItemTier Tier = SDK.GetTier(ItemDefinition);
					if (Tier < GetItemEFortTier(Config.World.LootMinimalTier)) continue;
					auto Color = GetItemColor(Tier);

					auto mysoil = SDK.Concat_StrStr(xor_w(L"[ "), itemName);
					mysoil = SDK.Concat_StrStr(mysoil, xor_w(L" "));
					mysoil = SDK.Concat_StrStr(mysoil, SDK.BuildString_Int(xor_w(L""), xor_w(L""), distance, xor_w(L"")));
					mysoil = SDK.Concat_StrStr(mysoil, xor_w(L" M ]"));

					ScreenLocation = SDK.K2_Project(ActorLocation);
					if (IsValidScreenLoc(ScreenLocation)) {

						auto size = SDK.K2_TextSize(Globals::Burbank, mysoil, FVector2D(0.5f, 0.5f));
						auto textLocation = FVector2D(ScreenLocation.X - (size.X / 2), ScreenLocation.Y);
						SDK.K2_DrawText(Globals::Burbank, mysoil, FVector2D(textLocation.X, textLocation.Y), FVector2D(0.5f, 0.5f), Color, 1.0f, FLinearColor(0, 0, 0, 1), FVector2D(), false, false, true, FLinearColor(0, 0, 0, 1.0f));
					}
				}
			}
		}
	}
}
#endif
#ifndef RAID
void Functions::Draw_RadarBackground() {
	// Handle Mouse
	FVector2D RadarPosition = FVector2D(Config.Visuals.RadarX, Config.Visuals.RadarY);

	if (Config.Misc.ShowMenu) {
		auto isMouseHovering = GUI.IsMouseHovering(RadarPosition, FVector2D(Config.Visuals.RadarSize, Config.Visuals.RadarSize));

		if (isMouseHovering) {
			if (GUI.Left_WasInputKeyJustPressed) {
				isRadarDragging = true;
				RadarDragOffset = GUI.MousePosition - RadarPosition;
			}
		}
		if (SDK.WasInputKeyJustReleased(Globals::LeftMouseButton)) {
			isRadarDragging = false;
		}
		if (isRadarDragging) {
			auto newPosition = GUI.MousePosition - RadarDragOffset;
			if (newPosition.X >= Globals::Width - Config.Visuals.RadarSize)
				newPosition.X = Globals::Width - Config.Visuals.RadarSize;
			if (newPosition.Y >= Globals::Height - Config.Visuals.RadarSize)
				newPosition.Y = Globals::Height - Config.Visuals.RadarSize;
			if (newPosition.X <= 0)
				newPosition.X = 0;
			if (newPosition.Y <= 0)
				newPosition.Y = 0;

			RadarPosition = newPosition;
			Config.Visuals.RadarX = newPosition.X;
			Config.Visuals.RadarY = newPosition.Y;
		}
	}

	float RadarSize = Config.Visuals.RadarSize;
	float RadarDotSize = Config.Visuals.RadarDotSize;

	FLinearColor grey(0, 0, 0, 127 / 255), greylight(80, 80, 80, 127 / 255),
		black(0, 0, 0, 1), white(255, 255, 255, 1);
	FVector2D box2 = RadarPosition;
	FVector2D vCross1(RadarPosition.X + (RadarSize / 2), RadarPosition.Y);
	FVector2D vCross2(RadarPosition.X + (RadarSize / 2), RadarPosition.Y + RadarSize);
	FVector2D hCross1(RadarPosition.X, RadarPosition.Y + (RadarSize / 2));
	FVector2D hCross2(RadarPosition.X + RadarSize, RadarPosition.Y + (RadarSize / 2));
	FVector2D MyBox(RadarPosition.X + (RadarSize / 2) - RadarDotSize, RadarPosition.Y + (RadarSize / 2) - RadarDotSize);

	box2.X += 1;
	box2.Y += 1;

	//BOX
	DrawFilledRect(RadarPosition, RadarSize, RadarSize, grey);
	DrawFilledRect(box2, RadarSize - 2, RadarSize - 2, greylight);

	//CROSS
	SDK.K2_DrawLine(vCross1, vCross2, 1, grey);
	SDK.K2_DrawLine(hCross1, hCross2, 1, grey);

	//My Player
	DrawFilledRect(MyBox, RadarDotSize * 2, RadarDotSize * 2, black);
}
SpecialStruct Functions::GetColorFromOption(int num) {
	SpecialStruct skid;
	if (num == 1) {
		skid.name = SDK.Concat_StrStr(xor_w(L"ORA"), xor_w(L"NGE"));
		skid.color = FLinearColor(255, 140, 0, 1.0f);
	}
	else if (num == 2) {
		skid.name = SDK.Concat_StrStr(xor_w(L"C"), xor_w(L"YAN"));
		skid.color = FLinearColor(3, 252, 252, 1.0f);
	}
	else if (num == 3) {
		skid.name = SDK.Concat_StrStr(xor_w(L"PURP"), xor_w(L"LE"));
		skid.color = FLinearColor(169, 3, 252, 1.0f);
	}
	else if (num == 4) {
		skid.name = SDK.Concat_StrStr(xor_w(L"YEL"), xor_w(L"LOW"));
		skid.color = FLinearColor(252, 235, 3, 1.0f);
	}
	else if (num == 5) {
		skid.name = SDK.Concat_StrStr(xor_w(L"GRE"), xor_w(L"EN"));
		skid.color = FLinearColor(0, 255, 0, 1.0f);
	}
	else if (num == 6) {
		skid.name = SDK.Concat_StrStr(xor_w(L"RE"), xor_w(L"D"));
		skid.color = FLinearColor(255, 0, 0, 1.0f);
	}
	else if (num == 7) {
		skid.name = SDK.Concat_StrStr(xor_w(L"WHI"), xor_w(L"TE"));
		skid.color = FLinearColor(255, 255, 255, 1.0f);
	}
	return skid;
}
#else
SpecialStruct Functions::GetColorFromOption(int num) {
	SpecialStruct skid;
	if (num == 1) {
		skid.name = SDK.Concat_StrStr(xor_w(L"MAR"), xor_w(L"OON"));
		skid.color = FLinearColor(128, 0, 0, 1.0f);
	}
	else if (num == 2) {
		skid.name = SDK.Concat_StrStr(xor_w(L"GRE"), xor_w(L"EN"));
		skid.color = FLinearColor(0, 255, 0, 1.0f);
	}
	else if (num == 3) {
		skid.name = SDK.Concat_StrStr(xor_w(L"RE"), xor_w(L"D"));
		skid.color = FLinearColor(255, 0, 0, 1.0f);
	}
	else if (num == 4) {
		skid.name = SDK.Concat_StrStr(xor_w(L"C"), xor_w(L"YAN"));
		skid.color = FLinearColor(3, 252, 252, 1.0f);
	}
	else if (num == 5) {
		skid.name = SDK.Concat_StrStr(xor_w(L"VIO"), xor_w(L"LET"));
		skid.color = FLinearColor(238, 130, 238, 1.0f);
	}
	else if (num == 6) {
		skid.name = SDK.Concat_StrStr(xor_w(L"IND"), xor_w(L"IGO"));
		skid.color = FLinearColor(75, 0, 130, 1.0f);
	}
	else if (num == 7) {
		skid.name = SDK.Concat_StrStr(xor_w(L"TEA"), xor_w(L"L"));
		skid.color = FLinearColor(0, 128, 128, 1.0f);
	}
	return skid;
}
#endif

FVector2D Functions::Grizel(FVector Cunigund, FRotator Garnett, FVector Location, double RadarX, double RadarY, int size)
{
	FVector2D Return;

	double CosYaw = SDK.Cos(Garnett.Yaw * M_PI / 180.f);
	double SinYaw = SDK.Sin(Garnett.Yaw * M_PI / 180.f);

	double DeltaX = Location.X - Cunigund.X;
	double DeltaY = Location.Y - Cunigund.Y;

	double LocationX = (DeltaY * CosYaw - DeltaX * SinYaw) / (200);
	double LocationY = (DeltaX * CosYaw + DeltaY * SinYaw) / (200);

	if (LocationX > ((size / 2) - 5.0f) - 2.5f)
		LocationX = ((size / 2) - 5.0f) - 2.5f;
	else if (LocationX < -(((size / 2) - 5.0f) - 2.5f))
		LocationX = -(((size / 2) - 5.0f) - 2.5f);

	if (LocationY > ((size / 2) - 5.0f) - 2.5f)
		LocationY = ((size / 2) - 5.0f) - 2.5f;
	else if (LocationY < -(((size / 2) - 5.0f) - 2.5f))
		LocationY = -(((size / 2) - 5.0f) - 2.5f);

	Return.X = LocationX + RadarX;
	Return.Y = -LocationY + RadarY;

	return Return;
}

void Functions::Draw_RadarPlayers(FVector ActorLoc, FLinearColor color) {
	FVector2D RadarPosition = FVector2D(Config.Visuals.RadarX, Config.Visuals.RadarY);
	float RadarDotSize = Config.Visuals.RadarDotSize;
	float RadarSize = Config.Visuals.RadarSize;

	FVector2D Linda = Grizel(vCamera.Location, vCamera.Rotation, ActorLoc, RadarPosition.X + (RadarSize / 2), RadarPosition.Y + (RadarSize / 2), RadarSize - 2);
	Linda -= FVector2D(RadarDotSize, RadarDotSize);

	DrawFilledRect(Linda, RadarDotSize * 2, RadarDotSize * 2, color);
}

void range(double* x, double* y, double range) {
	double distance = SDK.Sqrt((*x) * (*x) + (*y) * (*y));
	if (distance > range) {
		double angle = SDK.Atan2(*y, *x);
		*x = SDK.Cos(angle) * range;
		*y = SDK.Sin(angle) * range;
	}
}

Camera_Struct Functions::get_camera()
{
	Camera_Struct view;

	view.Location = Core.read<FVector>(Core.read<uint64_t>(Globals::World + 0x110));

	uint64_t rotation_ptr = Core.read<uint64_t>((uint64_t)Globals::World + 0x120);
	view.Rotation.Pitch = SDK.asin(Core.read<double>(rotation_ptr + 0x1D0)) * (180 / M_PI);
	view.Rotation.Yaw = (SDK.Atan2(Core.read<double>(rotation_ptr + 0x0) * -1, Core.read<double>(rotation_ptr + 0x20)) * (180 / M_PI)) * -1;
	view.Rotation.Yaw *= -1;

	return view;
}

FVector Functions::GetAimBone(uint64_t PlayerMesh, int AimBone) {
	if (AimBone == 1) return SDK.GetSocketLocation(PlayerMesh, Globals::HeadName);
	else if (AimBone == 2) return SDK.GetSocketLocation(PlayerMesh, Globals::NeckName);
	else if (AimBone == 3) return SDK.GetSocketLocation(PlayerMesh, Globals::ChestName);
	else return SDK.GetSocketLocation(PlayerMesh, Globals::HeadName);
}

FVector Functions::GetAllBones(uint64_t PlayerMesh, int AimBone)
{
	static const FName boneNames[] = {
		Globals::RootName, Globals::HeadName, Globals::NeckName, Globals::LowerNeckName, Globals::ChestName, Globals::PelvisName, Globals::Upperarm_lName, Globals::Upperarm_rName, Globals::Lowerarm_lName,
		Globals::Lowerarm_rName,Globals::Hand_lName, Globals::Hand_rName, Globals::Thigh_rName, Globals::Thigh_lName, Globals::Calf_rName, Globals::Calf_lName,
		Globals::LowerCalf_lName, Globals::LowerCalf_rName, Globals::Foot_lName, Globals::Foot_rName, Globals::Toe_lName, Globals::Toe_rName
	};

	double minDistance = 1000; // initialize to maximum double value
	FVector closes = GetAimBone(PlayerMesh, AimBone);

	for (int i = 0; i < 22; i++) {
		Globals::bones[i].name = boneNames[i];
		Globals::bones[i].location = SDK.GetSocketLocation(PlayerMesh, boneNames[i]);

		//Globals::bonesVisibility[i] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[i].location);
		Globals::bones[i].socketLoc = Globals::bones[i].location;

		Globals::bones[i].location = SDK.K2_Project(Globals::bones[i].location);

		if (AimBone == 4) {
			FVector2D offset = FVector2D(Globals::bones[i].location.X, Globals::bones[i].location.Y) - FVector2D(Globals::Width / 2, Globals::Height / 2);
			double distance = SDK.Sqrt(offset.X * offset.X + offset.Y * offset.Y);

			if (distance < minDistance) {
				minDistance = distance;
				closes = Globals::bones[i].socketLoc;
			}
		}
	}

	// Assign the correct values to the variables
	Globals::vRootOut = Globals::bones[0].location;
	Globals::vHeadBoneOut = Globals::bones[1].location;
	Globals::vNeckOut = Globals::bones[2].location;
	Globals::vLowerNeckOut = Globals::bones[3].location;
	Globals::vChestOut = Globals::bones[4].location;
	Globals::pelvisOut = Globals::bones[5].location;
	Globals::vUpperArmLeftOut = Globals::bones[6].location;
	Globals::vUpperArmRightOut = Globals::bones[7].location;
	Globals::vLeftHandOut = Globals::bones[8].location;
	Globals::vRightHandOut = Globals::bones[9].location;
	Globals::vLeftHandOut1 = Globals::bones[10].location;
	Globals::vRightHandOut1 = Globals::bones[11].location;
	Globals::vRightThighOut = Globals::bones[12].location;
	Globals::vLeftThighOut = Globals::bones[13].location;
	Globals::vRightKneeOut = Globals::bones[14].location;
	Globals::vLeftKneeOut = Globals::bones[15].location;
	Globals::vLeftLowCalfOut = Globals::bones[16].location;
	Globals::vRightLowCalfOut = Globals::bones[17].location;
	Globals::leftFeet2d = Globals::bones[18].location;
	Globals::rightFeet2d = Globals::bones[19].location;
	Globals::leftFeetFinger2d = Globals::bones[20].location;
	Globals::rightFeetFinger2d = Globals::bones[21].location;

	// Making the fake bones
	Globals::bones[1].socketLoc.Z = Globals::bones[2].socketLoc.Z;
	Globals::bones[2].socketLoc.Z -= 10.f;

	Globals::FAKEvHeadBoneOut = SDK.K2_Project(Globals::bones[1].socketLoc);
	Globals::FAKEvNeckOut = SDK.K2_Project(Globals::bones[2].socketLoc);

	return closes;
}
#ifndef RAID
bool Functions::TB_AlsoCheckTarget(bool isShoty) {
	static bool tbstrtd = false;

	if (tbstrtd && !Globals::ClosestPlayer && Globals::MyPlayer) {
		tbstrtd = false;
		SDK.PawnStopFire();
	}

	if (!Globals::ClosestPlayer || !Globals::MyPlayer) return false;

	if (Config.Aimbot.ShotgunOnlyTrigger && !isShoty) {
		return true;
	}

	if (tbstrtd && Config.Aimbot.TriggerKey == 2 && SDK.WasInputKeyJustReleased(Globals::TriggerKey)) {
		SDK.PawnStopFire();
	}

	/*if (Config.Misc.PSilent) {
		return true;
	}*/

	if (((Config.Aimbot.TriggerKey == 2) && SDK.IsInputKeyDown(Globals::TriggerKey)) || Config.Aimbot.AlwaysTrigger) {
		if (IsShootable(SDK.GetLocationUnderReticle(), Globals::AimLocation)) {
			tbstrtd = true;
			SDK.PawnStartFire();
			if (isShoty) {
				tbstrtd = false;
				SDK.PawnStopFire();
			}
		}
		else if (tbstrtd) {
			tbstrtd = false;
			SDK.PawnStopFire();
		}
	}
	return true;
}
#else
bool Functions::TB_AlsoCheckTarget(bool isShoty) {
	static bool tbstrtd = false;

	if (tbstrtd && !Globals::ClosestPlayer && Globals::MyPlayer) {
		tbstrtd = false;
		SDK.PawnStopFire();
	}

	if (!Globals::ClosestPlayer || !Globals::MyPlayer) return false;

	if (Config.Aimbot.ShotgunOnlyTrigger && !isShoty) {
		return true;
	}

	if (tbstrtd && Config.Aimbot.TriggerKey && SDK.WasInputKeyJustReleased(Globals::TriggerKey)) {
		SDK.PawnStopFire();
	}

	/*if (Config.Misc.PSilent) {
		return true;
	}*/

	if (((Config.Aimbot.TriggerKey) && SDK.IsInputKeyDown(Globals::TriggerKey)) || Config.Aimbot.AlwaysTrigger) {
		if (IsShootable(SDK.GetLocationUnderReticle(), Globals::AimLocation)) {
			tbstrtd = true;
			SDK.PawnStartFire();
			if (isShoty) {
				tbstrtd = false;
				SDK.PawnStopFire();
			}
		}
		else if (tbstrtd) {
			tbstrtd = false;
			SDK.PawnStopFire();
		}
	}
	return true;
}
#endif
//void Functions::GetAllBones(uint64_t PlayerMesh) {
//	
//
//	// Root
//	Globals::bones[0].name = Globals::RootName;
//	Globals::bones[0].location = SDK.GetSocketLocation(PlayerMesh, Globals::RootName);
//	Globals::bonesVisibility[0] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[0].location);
//	Globals::vRootOut = SDK.K2_Project(Globals::bones[0].location);
//
//	// Head
//	Globals::bones[1].name = Globals::HeadName;
//	Globals::bones[1].location = SDK.GetSocketLocation(PlayerMesh, Globals::HeadName);
//	Globals::bonesVisibility[1] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[1].location);
//	Globals::vHeadBoneOut = SDK.K2_Project(Globals::bones[1].location);
//
//	// Neck
//	Globals::bones[2].name = Globals::NeckName;
//	Globals::bones[2].location = SDK.GetSocketLocation(PlayerMesh, Globals::NeckName);
//	Globals::bonesVisibility[2] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[2].location);
//	Globals::vNeckOut = SDK.K2_Project(Globals::bones[2].location);
//
//	// Lower Neck
//	Globals::bones[3].name = Globals::LowerNeckName;
//	Globals::bones[3].location = SDK.GetSocketLocation(PlayerMesh, Globals::LowerNeckName);
//	Globals::bonesVisibility[3] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[3].location);
//	Globals::vLowerNeckOut = SDK.K2_Project(Globals::bones[3].location);
//
//	// Chest
//	Globals::bones[4].name = Globals::ChestName;
//	Globals::bones[4].location = SDK.GetSocketLocation(PlayerMesh, Globals::ChestName);
//	Globals::bonesVisibility[4] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[4].location);
//	Globals::vChestOut = SDK.K2_Project(Globals::bones[4].location);
//
//	// Pelvis
//	Globals::bones[5].name = Globals::PelvisName;
//	Globals::bones[5].location = SDK.GetSocketLocation(PlayerMesh, Globals::PelvisName);
//	Globals::bonesVisibility[5] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[5].location);
//	Globals::pelvisOut = SDK.K2_Project(Globals::bones[5].location);
//
//	// Upperarm_l
//	Globals::bones[6].name = Globals::Upperarm_lName;
//	Globals::bones[6].location = SDK.GetSocketLocation(PlayerMesh, Globals::Upperarm_lName);
//	Globals::bonesVisibility[6] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[6].location);
//	Globals::vUpperArmLeftOut = SDK.K2_Project(Globals::bones[6].location);
//
//	// Upperarm_r
//	Globals::bones[7].name = Globals::Upperarm_rName;
//	Globals::bones[7].location = SDK.GetSocketLocation(PlayerMesh, Globals::Upperarm_rName);
//	Globals::bonesVisibility[7] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[7].location);
//	Globals::vUpperArmRightOut = SDK.K2_Project(Globals::bones[7].location);
//
//	// Lowerarm_l
//	Globals::bones[8].name = Globals::Lowerarm_lName;
//	Globals::bones[8].location = SDK.GetSocketLocation(PlayerMesh, Globals::Lowerarm_lName);
//	Globals::bonesVisibility[8] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[8].location);
//	Globals::vLeftHandOut = SDK.K2_Project(Globals::bones[8].location);
//
//	// Lowerarm_r
//	Globals::bones[9].name = Globals::Lowerarm_rName;
//	Globals::bones[9].location = SDK.GetSocketLocation(PlayerMesh, Globals::Lowerarm_rName);
//	Globals::bonesVisibility[9] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[9].location);
//	Globals::vRightHandOut = SDK.K2_Project(Globals::bones[9].location);
//
//	// Hand_l
//	Globals::bones[10].name = Globals::Hand_lName;
//	Globals::bones[10].location = SDK.GetSocketLocation(PlayerMesh, Globals::Hand_lName);
//	Globals::bonesVisibility[10] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[10].location);
//	Globals::vLeftHandOut1 = SDK.K2_Project(Globals::bones[10].location);
//
//	// Hand_r
//	Globals::bones[11].name = Globals::Hand_rName;
//	Globals::bones[11].location = SDK.GetSocketLocation(PlayerMesh, Globals::Hand_rName);
//	Globals::bonesVisibility[11] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[11].location);
//	Globals::vRightHandOut1 = SDK.K2_Project(Globals::bones[11].location);
//
//	// Thigh_r
//	Globals::bones[12].name = Globals::Thigh_rName;
//	Globals::bones[12].location = SDK.GetSocketLocation(PlayerMesh, Globals::Thigh_rName);
//	Globals::bonesVisibility[12] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[12].location);
//	Globals::vRightThighOut = SDK.K2_Project(Globals::bones[12].location);
//
//	// Thigh_l
//	Globals::bones[13].name = Globals::Thigh_lName;
//	Globals::bones[13].location = SDK.GetSocketLocation(PlayerMesh, Globals::Thigh_lName);
//	Globals::bonesVisibility[13] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[13].location);
//	Globals::vLeftThighOut = SDK.K2_Project(Globals::bones[13].location);
//
//	// Calf_r
//	Globals::bones[14].name = Globals::Calf_rName;
//	Globals::bones[14].location = SDK.GetSocketLocation(PlayerMesh, Globals::Calf_rName);
//	Globals::bonesVisibility[14] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[14].location);
//	Globals::vRightKneeOut = SDK.K2_Project(Globals::bones[14].location);
//
//	// Calf_l
//	Globals::bones[15].name = Globals::Calf_lName;
//	Globals::bones[15].location = SDK.GetSocketLocation(PlayerMesh, Globals::Calf_lName);
//	Globals::bonesVisibility[15] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[15].location);
//	Globals::vLeftKneeOut = SDK.K2_Project(Globals::bones[15].location);
//
//	// LowerCalf_l
//	Globals::bones[16].name = Globals::LowerCalf_lName;
//	Globals::bones[16].location = SDK.GetSocketLocation(PlayerMesh, Globals::LowerCalf_lName);
//	Globals::bonesVisibility[16] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[16].location);
//	Globals::vLeftLowCalfOut = SDK.K2_Project(Globals::bones[16].location);
//
//	// LowerCalf_r
//	Globals::bones[17].name = Globals::LowerCalf_rName;
//	Globals::bones[17].location = SDK.GetSocketLocation(PlayerMesh, Globals::LowerCalf_rName);
//	Globals::bonesVisibility[17] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[17].location);
//	Globals::vRightLowCalfOut = SDK.K2_Project(Globals::bones[17].location);
//
//	// Foot_l
//	Globals::bones[18].name = Globals::Foot_lName;
//	Globals::bones[18].location = SDK.GetSocketLocation(PlayerMesh, Globals::Foot_lName);
//	Globals::bonesVisibility[18] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[18].location);
//	Globals::leftFeet2d = SDK.K2_Project(Globals::bones[18].location);
//
//	// Foot_r
//	Globals::bones[19].name = Globals::Foot_rName;
//	Globals::bones[19].location = SDK.GetSocketLocation(PlayerMesh, Globals::Foot_rName);
//	Globals::bonesVisibility[19] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[19].location);
//	Globals::rightFeet2d = SDK.K2_Project(Globals::bones[19].location);
//
//	// Toe_l
//	Globals::bones[20].name = Globals::Toe_lName;
//	Globals::bones[20].location = SDK.GetSocketLocation(PlayerMesh, Globals::Toe_lName);
//	Globals::bonesVisibility[20] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[20].location);
//	Globals::leftFeetFinger2d = SDK.K2_Project(Globals::bones[20].location);
//
//	// Toe_r
//	Globals::bones[21].name = Globals::Toe_rName;
//	Globals::bones[21].location = SDK.GetSocketLocation(PlayerMesh, Globals::Toe_rName);
//	Globals::bonesVisibility[21] = SDK.LineTraceSingle(FVector(vCamera.Location.X, vCamera.Location.Y, vCamera.Location.Z), Globals::bones[21].location);
//	Globals::rightFeetFinger2d = SDK.K2_Project(Globals::bones[21].location);
//
//	
//}

void Functions::DrawFilledRect(FVector2D initial_pos, float width, float height, FLinearColor color)
{
	for (float i = 0.0f; i < height; i += 1.0f)
		SDK.K2_DrawLine(FVector2D(initial_pos.X, initial_pos.Y + i), FVector2D(initial_pos.X + width, initial_pos.Y + i), 1.0f, color);
}

bool Functions::isNotName(const wchar_t* plrname) {
	if (plrname[0] == 80 && plrname[1] == 108 && plrname[2] == 97 && plrname[3] == 121 && plrname[4] == 101 && plrname[5] == 114
		&& plrname[6] == 80 && plrname[7] == 97 && plrname[8] == 119 && plrname[9] == 110 && plrname[10] == 95)
		return true;

	else if (plrname[0] == 66 && plrname[1] == 80 && plrname[2] == 95 && plrname[3] == 80 && plrname[4] == 108 && plrname[5] == 97 && plrname[6] == 121 && plrname[7] == 101 && plrname[8] == 114
		&& plrname[9] == 80 && plrname[10] == 97 && plrname[11] == 119 && plrname[12] == 110 && plrname[13] == 95)
		return true;

	return false;
}

bool Functions::IsValidScreenLoc(const FVector& Loc)
{
	// Check if the location is within the positive space and within the screen dimensions
	return Loc.X >= 0 && Loc.Y >= 0 && Loc.Z > 0 && Loc.X <= Globals::Width && Loc.Y <= Globals::Height;
}

bool Functions::WorldToScreen(FVector& WorldLocation, FVector2D* screenLocation)
{
	auto response = SDK.K2_Project(WorldLocation);

	if (!IsValidScreenLoc(response)) return false;

	*screenLocation = FVector2D(response.X, response.Y);

	return true;
}

bool Functions::IsShootable(FVector lur, FVector wl) {

	if (lur.X >= wl.X - 20 && lur.X <= wl.X + 20 && lur.Y >= wl.Y - 20 && lur.Y <= wl.Y + 20 && lur.Z >= wl.Z - 30 && lur.Z <= wl.Z + 30)
		return true;

	return false;
}

FLinearColor Functions::GetItemColor(EFortItemTier tier)
{
	switch (tier)
	{
	case EFortItemTier::I: // Common
		return FLinearColor{ 176, 176, 176, 1 }; // ITEM_COLOR_TIER_WHITE
	case EFortItemTier::II: // Uncommon
		return FLinearColor{ 30, 132, 0, 1 }; // ITEM_COLOR_TIER_GREEN
	case EFortItemTier::III: // Rare
		return FLinearColor{ 0, 109, 255, 1 }; // ITEM_COLOR_TIER_BLUE
	case EFortItemTier::IV: // Epic
		return FLinearColor{ 157, 25, 255, 1 }; // ITEM_COLOR_TIER_PURPLE
	case EFortItemTier::V: // Legendary
		return FLinearColor{ 245, 138, 31, 1 }; // ITEM_COLOR_TIER_ORANGE
	case EFortItemTier::VI: // Mythic
		return FLinearColor{ 255, 222, 97, 1 }; // ITEM_COLOR_TIER_GOLD
	case EFortItemTier::VII: // Exotic
		return FLinearColor{ 35, 238, 196, 1 }; // ITEM_COLOR_TIER_EXOTIC
	case EFortItemTier::VIII:// Transcendent
		return FLinearColor{ 230, 140, 140, 1 }; // ITEM_COLOR_MEDS
	case EFortItemTier::IX:
		return FLinearColor{ 89, 140, 217, 1 }; // ITEM_COLOR_SHIELDPOTION
	case EFortItemTier::X:
		return FLinearColor{ 242, 242, 0, 1 }; // ITEM_COLOR_CHEST
	default:
		return FLinearColor{ 123, 123, 123, 1 }; // default color
	}
}

std::wstring Functions::GetItemTierName(EFortItemTier tier)
{
	switch (tier)
	{
	case EFortItemTier::I: // Common
		return xor_w(L"COMMON"); // ITEM_COLOR_TIER_WHITE
	case EFortItemTier::II: // Uncommon
		return xor_w(L"UNCOMMON"); // ITEM_COLOR_TIER_GREEN
	case EFortItemTier::III: // Rare
		return xor_w(L"RARE"); // ITEM_COLOR_TIER_BLUE
	case EFortItemTier::IV: // Epic
		return xor_w(L"EPIC"); // ITEM_COLOR_TIER_PURPLE
	case EFortItemTier::V: // Legendary
		return xor_w(L"LEGENDARY"); // ITEM_COLOR_TIER_ORANGE
	case EFortItemTier::VI: // Mythic
		return xor_w(L"MYTHIC"); // ITEM_COLOR_TIER_GOLD
	case EFortItemTier::VII: // EXOTIC
		return xor_w(L"EXOTIC"); // ITEM_COLOR_TIER_UNKNOWN
	default:
		return xor_w(L"COMMON"); // ITEM_COLOR_MEDS
	}
}

EFortItemTier Functions::GetItemEFortTier(float tier)
{
	int tierI = (int)tier;
	switch (tierI)
	{
	case 1:
		return EFortItemTier::I;
	case 2:
		return EFortItemTier::II;
	case 3:
		return EFortItemTier::III;
	case 4:
		return EFortItemTier::IV;
	case 5:
		return EFortItemTier::V;
	case 6:
		return EFortItemTier::VI;
	case 7:
		return EFortItemTier::VII;
	default:
		return EFortItemTier::I;
	}
}

void Functions::DrawCircle(int x, int y, int radius, int sides, FLinearColor color)
{
	float Step = M_PI * 2.0 / sides;
	for (float a = 0; a < M_PI * 2.0; a += Step)
	{
		float X1 = radius * SDK.Cos(a) + x;
		float Y1 = radius * SDK.Sin(a) + y;
		float X2 = radius * SDK.Cos(a + Step) + x;
		float Y2 = radius * SDK.Sin(a + Step) + y;
		SDK.K2_DrawLine({ X1, Y1 }, { X2, Y2 }, 1.5f, color);
	}
}

void Functions::DrawFilledCircle(int x, int y, int radius, FLinearColor color)
{
	FVector2D ScreenPosition(x, y);
	FVector2D Radius(radius, radius);
	int NumberOfSides = 72;
	SDK.K2_DrawPolygon(0, ScreenPosition, Radius, NumberOfSides, color);
}

FRotator Functions::SmoothMe(FRotator startRotation, FRotator endRotation, float SmoothScale)
{
	FRotator ret = endRotation;

	ret.Pitch -= startRotation.Pitch;
	ret.Yaw -= startRotation.Yaw;

	//clamp
	if (ret.Yaw < -180.0f)
		ret.Yaw += 360.0f;

	if (ret.Yaw > 180.0f)
		ret.Yaw -= 360.0f;

	if (ret.Pitch < -74.0f)
		ret.Pitch = -74.0f;

	if (ret.Pitch > 74.0f)
		ret.Pitch = 74.0f;

	auto IsSpectate = SDK.GetSpectatorCount() > 0;
	auto overrideSmooth = IsSpectate ? Config.Aimbot.SpectateSmooth : SmoothScale;

	ret.Pitch = (ret.Pitch / overrideSmooth) + startRotation.Pitch;
	ret.Yaw = (ret.Yaw / overrideSmooth) + startRotation.Yaw;

	//clamp
	if (ret.Yaw < -180.0f)
		ret.Yaw += 360.0f;

	if (ret.Yaw > 180.0f)
		ret.Yaw -= 360.0f;

	if (ret.Pitch < -74.0f)
		ret.Pitch = -74.0f;

	if (ret.Pitch > 74.0f)
		ret.Pitch = 74.0f;

	return ret;
}

static float Pow(float b, float p)
{
	float Result = 1.0f;
	for (int i = 0; i < p; ++i)
	{
		Result *= b;
	}
	return Result;
}
/*
FVector Functions::Predict(FVector pos, FVector Velocity, uint64_t WeaponData, float distance)
{
	if (!WeaponData) return pos;

	uint64_t Template = SDK.GetProjectileTemplate(WeaponData);
	if (!Template) return pos;

	uint64_t Config = Core.read<uint64_t>(Template + 0x110);
	if (!Config) return pos;

	if (SDK.HasLightweightProjectile(WeaponData))
	{
		auto SpeedFloat = *(FScalableFloat*)(Config + 0x290);
		auto GravityFloat = *(FScalableFloat*)(Config + 0x2B8);

		if (SpeedFloat.Value && GravityFloat.Value)
		{
			auto Speed = SDK.GetValueAtLevel(SpeedFloat, 0);
			auto Gravity = SDK.GetValueAtLevel(GravityFloat, 0);

			float horizontalTime = distance / Speed;
			float verticalTime = distance / Speed;

			pos.X += Velocity.X * horizontalTime;
			pos.Y += Velocity.Y * horizontalTime;
			pos.Z += Velocity.Z * verticalTime + SDK.Abs(-980.f * Gravity) * 0.5f * (verticalTime * verticalTime);

			return pos;
		}
		else {
			// OG PREDICTION SHOULD GO HERE
			return pos;
		}
	}

	return pos;
}*/

void Functions::Predict(uint64_t WeaponData)
{
	if (!WeaponData) return;

	uint64_t Template = SDK.GetProjectileTemplate(WeaponData);
	if (!Template) return;

	uint64_t Config = Core.read<uint64_t>(Template + 0x110);
	if (!Config) return;

	float Speed = NULL;
	float Gravity = NULL;

	FVector Velocity = SDK.GetVelocity(Globals::ClosestPlayer);

	if (SDK.HasLightweightProjectile(WeaponData))
	{
		auto SpeedFloat = *(FScalableFloat*)(Config + 0x290);
		auto GravityFloat = *(FScalableFloat*)(Config + 0x2B8);

		if (SpeedFloat.Value && GravityFloat.Value)
		{
			Speed = SDK.GetValueAtLevel(SpeedFloat, 0);
			Gravity = SDK.GetValueAtLevel(GravityFloat, 0);
		}

		FVector StartLocation = SDK.GetTargetingSourceLocation(Globals::CurrentWeapon);
		float PlayerDistance = SDK.Vector_Distance(StartLocation, Globals::AimLocation);

		float TimeToTarget = PlayerDistance / Speed;

		Globals::AimLocation.X += Velocity.X * TimeToTarget;
		Globals::AimLocation.Y += Velocity.Y * TimeToTarget;

		float Difference = StartLocation.Z - Globals::AimLocation.Z;
		float HorizDistance = SDK.Sqrt(Pow(StartLocation.X - Globals::AimLocation.X, 2) + Pow(StartLocation.Y - Globals::AimLocation.Y, 2));
		float VertAngle = SDK.Atan2(SDK.Abs(Difference), HorizDistance);

		float Angle = VertAngle * (180.0 / M_PI);
		float Factor = SDK.Abs(Angle - 90) / 90;

		Gravity *= Factor;

		Globals::AimLocation.Z += Velocity.Z * TimeToTarget + (SDK.Abs(Gravity * -980.0) * (TimeToTarget * TimeToTarget)) * 0.5;

	}
	else {
		if (SDK.IsProjectileWeapon(Globals::CurrentWeapon)) {
			FVector Difference = SDK.Subtract_VectorVector(Globals::AimLocation, vCamera.Location);
			float fDistance = SDK.VSize(Difference);
			float TimeScale = 0.0193f;
			float Ping = 0;
			float ScaleValue = (float)(Ping)+(float)(fDistance * TimeScale);
			if (ScaleValue < 1.0f) ScaleValue = 1.0;
			float fVelocity;
			fVelocity = SDK.VSize(Velocity);

			if (fVelocity > 100.0f)
			{
				Velocity.X *= ScaleValue / fVelocity; Velocity.Y *= ScaleValue / fVelocity; Velocity.Z *= ScaleValue / fVelocity;
				Globals::AimLocation = SDK.Add_VectorVector(Globals::AimLocation, Velocity);
			}
		}
	}
}

//FRotator calculate_angle(FVector camera, FVector location) {
//
//	auto direction = camera - location;
//	float horizontalDistance = SDK.Sqrt(direction.X * direction.X + direction.Y * direction.Y);
//
//	FRotator rotation;
//	rotation.Yaw = SDK.Atan2(direction.Y, direction.X) * 57.295779513082f; // Convert from radians to degrees
//	rotation.Pitch = (SDK.Atan2(direction.Z, horizontalDistance) * 57.295779513082f) * -1.f; // Convert from radians to degrees and invert
//
//	if (direction.X >= 0.f) {
//		rotation.Yaw += 180.f;
//	}
//
//	return rotation;
//}

// Find a rotation for an object at Start location to point at Target location.
FRotator Functions::FindLookAtRotation(FVector& start, FVector& target) {
	FVector direction = target - start; // Direction vector from start to target
	direction = direction / SDK.Sqrt(direction.SizeSquared()); // Normalize the direction vector

	// Calculate yaw
	double yaw = SDK.Atan2(direction.Y, direction.X) * (180.0 / M_PI); // Convert radians to degrees

	// Invert the pitch calculation if necessary
	double pitch = SDK.Atan2(direction.Z, SDK.Sqrt(direction.X * direction.X + direction.Y * direction.Y)) * (180.0 / M_PI); // Convert radians to degrees

	// Return the FRotator with the calculated yaw and pitch, and a roll of 0
	return FRotator(pitch, yaw, 0.0);
}

void Functions::InitializeAimbot(FVector AimLocation, int cwsmComerl) {
	if (!Globals::CurrentWeapon) return;
#if 1
	auto AimLocationy = SDK.K2_Project(AimLocation);
	float smooth = (cwsmComerl + 1) / 1.5;
	auto CenterX = Globals::Width / 2;
	auto CenterY = Globals::Height / 2;
	FVector target = { 0, 0, 0 };

	if (AimLocationy.X > CenterX)
	{
		target.X = -(CenterX - AimLocationy.X) / 250.0 * 100 / smooth;
	}
	else if (AimLocationy.X < CenterX)
	{
		target.X = (AimLocationy.X - CenterX) / 250.0 * 100 / smooth;
	}

	if (AimLocationy.Y > CenterY)
	{
		target.Y = -(CenterY - AimLocationy.Y) / 250.0 * 100 / smooth;
	}
	else if (AimLocationy.Y < CenterY)
	{
		target.Y = (AimLocationy.Y - CenterY) / 250.0 * 100 / smooth;
	}
	Core.write<FVector>(Globals::CurrentWeapon + Offsets.MaxTargetingAimAdjustPerSecond + 0x30, FVector(target.Y * 2, -target.X * 2, 0));
#endif
#if 0

	FRotator AimRotation = FindLookAtRotation(vCamera.Location, AimLocation);

	if (cwsmComerl > 0) AimRotation = SmoothMe(vCamera.Rotation, AimRotation, cwsmComerl);

	AimRotation.Roll = 0.0f;

	/*auto reader = Core.read<FRotator>(Globals::CurrentWeapon + 0x1988);

	if (reader != FRotator()) {
		auto AimLocationy = SDK.K2_Project(AimLocation);
		float smooth = (cwsmComerl + 1) / 1.5;
		auto CenterX = Globals::Width / 2;
		auto CenterY = Globals::Height / 2;
		FVector target = { 0, 0, 0 };

		if (AimLocationy.X > CenterX)
		{
			target.X = -(CenterX - AimLocationy.X) / 250.0 * 100 / smooth;
		}
		else if (AimLocationy.X < CenterX)
		{
			target.X = (AimLocationy.X - CenterX) / 250.0 * 100 / smooth;
		}

		if (AimLocationy.Y > CenterY)
		{
			target.Y = -(CenterY - AimLocationy.Y) / 250.0 * 100 / smooth;
		}
		else if (AimLocationy.Y < CenterY)
		{
			target.Y = (AimLocationy.Y - CenterY) / 250.0 * 100 / smooth;
		}
		Core.write<FVector>(Globals::CurrentWeapon + Offsets.MaxTargetingAimAdjustPerSecond + 0x30, FVector(target.Y * 2, -target.X * 2, 0));
	}*/

	Core.write<FRotator>(Globals::CurrentWeapon + 0x1988, AimRotation);

#endif
	//AimRotation.Pitch = AimRotation.Pitch - vCamera.Rotation.Pitch;
	//AimRotation.Yaw = AimRotation.Yaw - vCamera.Rotation.Yaw;

	////// Normalize Yaw to be between -180 and 180
	//while (AimRotation.Yaw > 180.0f) AimRotation.Yaw -= 360.0f;
	//while (AimRotation.Yaw < -180.0f) AimRotation.Yaw += 360.0f;

	//// Check and scale Pitch if it exceeds the bounds
	//if (SDK.Abs(AimRotation.Pitch) > 0.68f) {
	//	float scaleFactorPitch = 0.68f / SDK.Abs(AimRotation.Pitch);
	//	AimRotation.Pitch *= scaleFactorPitch;
	//}
	//// Check and scale Yaw if it exceeds the bounds
	//if (SDK.Abs(AimRotation.Yaw) > 0.68f) {
	//	float scaleFactorYaw = 0.68f / SDK.Abs(AimRotation.Yaw);
	//	AimRotation.Yaw *= scaleFactorYaw;
	//}

	//Core.write<FRotator>(Globals::PlayerController + 0x988, AimRotation);
	//Core.write<FRotator>(Globals::PlayerController + 0x520, AimRotation);
}