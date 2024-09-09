#include "Core.h"

void Core::InitKeys()
{
	// Mouse buttons
	Globals::MouseScrollUp = FKey(SDK.Conv_StringToName(xor_w(L"MouseScrollUp")));
	Globals::MouseScrollDown = FKey(SDK.Conv_StringToName(xor_w(L"MouseScrollDown")));
	Globals::MouseWheelAxis = FKey(SDK.Conv_StringToName(xor_w(L"MouseWheelAxis")));
	Globals::LeftMouseButton = FKey(SDK.Conv_StringToName(xor_w(L"LeftMouseButton")));
	Globals::RightMouseButton = FKey(SDK.Conv_StringToName(xor_w(L"RightMouseButton")));
	Globals::MiddleMouseButton = FKey(SDK.Conv_StringToName(xor_w(L"MiddleMouseButton")));
	Globals::ThumbMouseButton = FKey(SDK.Conv_StringToName(xor_w(L"ThumbMouseButton")));
	Globals::ThumbMouseButton2 = FKey(SDK.Conv_StringToName(xor_w(L"ThumbMouseButton2")));

	Globals::BackSpace = FKey(SDK.Conv_StringToName(xor_w(L"BackSpace")));
	Globals::Tab = FKey(SDK.Conv_StringToName(xor_w(L"Tab")));
	Globals::Enter = FKey(SDK.Conv_StringToName(xor_w(L"Enter")));
	Globals::Pause = FKey(SDK.Conv_StringToName(xor_w(L"Pause")));
	Globals::CapsLock = FKey(SDK.Conv_StringToName(xor_w(L"CapsLock")));
	Globals::Escape = FKey(SDK.Conv_StringToName(xor_w(L"Escape")));
	Globals::SpaceBar = FKey(SDK.Conv_StringToName(xor_w(L"SpaceBar")));
	Globals::PageUp = FKey(SDK.Conv_StringToName(xor_w(L"PageUp")));
	Globals::PageDown = FKey(SDK.Conv_StringToName(xor_w(L"PageDown")));
	Globals::End = FKey(SDK.Conv_StringToName(xor_w(L"End")));
	Globals::Home = FKey(SDK.Conv_StringToName(xor_w(L"Home")));
	Globals::Left = FKey(SDK.Conv_StringToName(xor_w(L"Left")));
	Globals::Up = FKey(SDK.Conv_StringToName(xor_w(L"Up")));
	Globals::Right = FKey(SDK.Conv_StringToName(xor_w(L"Right")));
	Globals::Down = FKey(SDK.Conv_StringToName(xor_w(L"Down")));
	Globals::Insert = FKey(SDK.Conv_StringToName(xor_w(L"Insert")));
	Globals::Delete = FKey(SDK.Conv_StringToName(xor_w(L"Delete")));
	Globals::Zero = FKey(SDK.Conv_StringToName(xor_w(L"Zero")));
	Globals::One = FKey(SDK.Conv_StringToName(xor_w(L"One")));
	Globals::Two = FKey(SDK.Conv_StringToName(xor_w(L"Two")));
	Globals::Three = FKey(SDK.Conv_StringToName(xor_w(L"Three")));
	Globals::Four = FKey(SDK.Conv_StringToName(xor_w(L"Four")));
	Globals::Five = FKey(SDK.Conv_StringToName(xor_w(L"Five")));
	Globals::Six = FKey(SDK.Conv_StringToName(xor_w(L"Six")));
	Globals::Seven = FKey(SDK.Conv_StringToName(xor_w(L"Seven")));
	Globals::Eight = FKey(SDK.Conv_StringToName(xor_w(L"Eight")));
	Globals::Nine = FKey(SDK.Conv_StringToName(xor_w(L"Nine")));
	Globals::A = FKey(SDK.Conv_StringToName(xor_w(L"A")));
	Globals::B = FKey(SDK.Conv_StringToName(xor_w(L"B")));
	Globals::C = FKey(SDK.Conv_StringToName(xor_w(L"C")));
	Globals::D = FKey(SDK.Conv_StringToName(xor_w(L"D")));
	Globals::E = FKey(SDK.Conv_StringToName(xor_w(L"E")));
	Globals::F = FKey(SDK.Conv_StringToName(xor_w(L"F")));
	Globals::G = FKey(SDK.Conv_StringToName(xor_w(L"G")));
	Globals::H = FKey(SDK.Conv_StringToName(xor_w(L"H")));
	Globals::I = FKey(SDK.Conv_StringToName(xor_w(L"I")));
	Globals::J = FKey(SDK.Conv_StringToName(xor_w(L"J")));
	Globals::K = FKey(SDK.Conv_StringToName(xor_w(L"K")));
	Globals::L = FKey(SDK.Conv_StringToName(xor_w(L"L")));
	Globals::M = FKey(SDK.Conv_StringToName(xor_w(L"M")));
	Globals::N = FKey(SDK.Conv_StringToName(xor_w(L"N")));
	Globals::O = FKey(SDK.Conv_StringToName(xor_w(L"O")));
	Globals::P = FKey(SDK.Conv_StringToName(xor_w(L"P")));
	Globals::Q = FKey(SDK.Conv_StringToName(xor_w(L"Q")));
	Globals::R = FKey(SDK.Conv_StringToName(xor_w(L"R")));
	Globals::S = FKey(SDK.Conv_StringToName(xor_w(L"S")));
	Globals::T = FKey(SDK.Conv_StringToName(xor_w(L"T")));
	Globals::U = FKey(SDK.Conv_StringToName(xor_w(L"U")));
	Globals::V = FKey(SDK.Conv_StringToName(xor_w(L"V")));
	Globals::W = FKey(SDK.Conv_StringToName(xor_w(L"W")));
	Globals::X = FKey(SDK.Conv_StringToName(xor_w(L"X")));
	Globals::Y = FKey(SDK.Conv_StringToName(xor_w(L"Y")));
	Globals::Z = FKey(SDK.Conv_StringToName(xor_w(L"Z")));

	//return HasInitKeys = true;
}
void Core::InitKeys_1()
{
	Globals::NumPadZero = FKey(SDK.Conv_StringToName(xor_w(L"NumPadZero")));
	Globals::NumPadOne = FKey(SDK.Conv_StringToName(xor_w(L"NumPadOne")));
	Globals::NumPadTwo = FKey(SDK.Conv_StringToName(xor_w(L"NumPadTwo")));
	Globals::NumPadThree = FKey(SDK.Conv_StringToName(xor_w(L"NumPadThree")));
	Globals::NumPadFour = FKey(SDK.Conv_StringToName(xor_w(L"NumPadFour")));
	Globals::NumPadFive = FKey(SDK.Conv_StringToName(xor_w(L"NumPadFive")));
	Globals::NumPadSix = FKey(SDK.Conv_StringToName(xor_w(L"NumPadSix")));
	Globals::NumPadSeven = FKey(SDK.Conv_StringToName(xor_w(L"NumPadSeven")));
	Globals::NumPadEight = FKey(SDK.Conv_StringToName(xor_w(L"NumPadEight")));
	Globals::NumPadNine = FKey(SDK.Conv_StringToName(xor_w(L"NumPadNine")));
	Globals::Multiply = FKey(SDK.Conv_StringToName(xor_w(L"Multiply")));
	Globals::Add = FKey(SDK.Conv_StringToName(xor_w(L"Add")));
	Globals::Subtract = FKey(SDK.Conv_StringToName(xor_w(L"Subtract")));
	Globals::Decimal = FKey(SDK.Conv_StringToName(xor_w(L"Decimal")));
	Globals::Divide = FKey(SDK.Conv_StringToName(xor_w(L"Divide")));
	Globals::F1 = FKey(SDK.Conv_StringToName(xor_w(L"F1")));
	Globals::F2 = FKey(SDK.Conv_StringToName(xor_w(L"F2")));
	Globals::F3 = FKey(SDK.Conv_StringToName(xor_w(L"F3")));
	Globals::F4 = FKey(SDK.Conv_StringToName(xor_w(L"F4")));
	Globals::F5 = FKey(SDK.Conv_StringToName(xor_w(L"F5")));
	Globals::F6 = FKey(SDK.Conv_StringToName(xor_w(L"F6")));
	Globals::F7 = FKey(SDK.Conv_StringToName(xor_w(L"F7")));
	Globals::F8 = FKey(SDK.Conv_StringToName(xor_w(L"F8")));
	Globals::F9 = FKey(SDK.Conv_StringToName(xor_w(L"F9")));
	Globals::F10 = FKey(SDK.Conv_StringToName(xor_w(L"F10")));
	Globals::F11 = FKey(SDK.Conv_StringToName(xor_w(L"F11")));
	Globals::F12 = FKey(SDK.Conv_StringToName(xor_w(L"F12")));

	//return HasInitKeys = true;
}
void Core::InitKeys_2()
{
	Globals::NumLock = FKey(SDK.Conv_StringToName(xor_w(L"NumLock")));
	Globals::ScrollLock = FKey(SDK.Conv_StringToName(xor_w(L"ScrollLock")));
	Globals::LeftShift = FKey(SDK.Conv_StringToName(xor_w(L"LeftShift")));
	Globals::RightShift = FKey(SDK.Conv_StringToName(xor_w(L"RightShift")));
	Globals::LeftControl = FKey(SDK.Conv_StringToName(xor_w(L"LeftControl")));
	Globals::RightControl = FKey(SDK.Conv_StringToName(xor_w(L"RightControl")));
	Globals::LeftAlt = FKey(SDK.Conv_StringToName(xor_w(L"LeftAlt")));
	Globals::RightAlt = FKey(SDK.Conv_StringToName(xor_w(L"RightAlt")));
	Globals::LeftCommand = FKey(SDK.Conv_StringToName(xor_w(L"LeftCommand")));
	Globals::RightCommand = FKey(SDK.Conv_StringToName(xor_w(L"RightCommand")));
	Globals::Semicolon = FKey(SDK.Conv_StringToName(xor_w(L"Semicolon")));
	Globals::Equals = FKey(SDK.Conv_StringToName(xor_w(L"Equals")));
	Globals::Comma = FKey(SDK.Conv_StringToName(xor_w(L"Comma")));
	Globals::Underscore = FKey(SDK.Conv_StringToName(xor_w(L"Underscore")));
	Globals::Hyphen = FKey(SDK.Conv_StringToName(xor_w(L"Hyphen")));
	Globals::Period = FKey(SDK.Conv_StringToName(xor_w(L"Period")));
	Globals::Slash = FKey(SDK.Conv_StringToName(xor_w(L"Slash")));
	Globals::Tilde = FKey(SDK.Conv_StringToName(xor_w(L"Tilde")));
	Globals::LeftBracket = FKey(SDK.Conv_StringToName(xor_w(L"LeftBracket")));
	Globals::LeftParantheses = FKey(SDK.Conv_StringToName(xor_w(L"LeftParantheses")));
	Globals::Backslash = FKey(SDK.Conv_StringToName(xor_w(L"Backslash")));
	Globals::RightBracket = FKey(SDK.Conv_StringToName(xor_w(L"RightBracket")));
	Globals::RightParantheses = FKey(SDK.Conv_StringToName(xor_w(L"RightParantheses")));
	Globals::Apostrophe = FKey(SDK.Conv_StringToName(xor_w(L"Apostrophe")));
	Globals::Quote = FKey(SDK.Conv_StringToName(xor_w(L"Quote")));
	Globals::Asterix = FKey(SDK.Conv_StringToName(xor_w(L"Asterix")));
	Globals::Ampersand = FKey(SDK.Conv_StringToName(xor_w(L"Ampersand")));
	Globals::Caret = FKey(SDK.Conv_StringToName(xor_w(L"Caret")));
	Globals::Dollar = FKey(SDK.Conv_StringToName(xor_w(L"Dollar")));
	Globals::Exclamation = FKey(SDK.Conv_StringToName(xor_w(L"Exclamation")));
	Globals::Colon = FKey(SDK.Conv_StringToName(xor_w(L"Colon")));
	Globals::Section = FKey(SDK.Conv_StringToName(xor_w(L"Section")));

	//return HasInitKeys = true;
}

void Core::InitKeys_3()
{
	Globals::Gamepad_Left2D = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_Left2D")));
	Globals::Gamepad_LeftX = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftX")));
	Globals::Gamepad_LeftY = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftY")));
	Globals::Gamepad_Right2D = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_Right2D")));
	Globals::Gamepad_RightX = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightX")));
	Globals::Gamepad_RightY = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightY")));
	Globals::Gamepad_LeftTriggerAxis = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftTriggerAxis")));
	Globals::Gamepad_RightTriggerAxis = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightTriggerAxis")));
	Globals::Gamepad_LeftThumbstick = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftThumbstick")));
	Globals::Gamepad_RightThumbstick = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightThumbstick")));
	Globals::Gamepad_Special_Left = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_Special_Left")));
	Globals::Gamepad_Special_Left_X = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_Special_Left_X")));
	Globals::Gamepad_Special_Left_Y = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_Special_Left_Y")));
	Globals::Gamepad_Special_Right = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_Special_Right")));
	Globals::Gamepad_FaceButton_Bottom = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_FaceButton_Bottom")));
	Globals::Gamepad_FaceButton_Right = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_FaceButton_Right")));
	Globals::Gamepad_FaceButton_Left = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_FaceButton_Left")));
	Globals::Gamepad_FaceButton_Top = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_FaceButton_Top")));

	//return HasInitKeys = true;
}
void Core::InitKeys_4()
{
	Globals::Gamepad_LeftShoulder = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftShoulder")));
	Globals::Gamepad_RightShoulder = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightShoulder")));
	Globals::Gamepad_LeftTrigger = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftTrigger")));
	Globals::Gamepad_RightTrigger = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightTrigger")));
	Globals::Gamepad_DPad_Up = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_DPad_Up")));
	Globals::Gamepad_DPad_Down = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_DPad_Down")));
	Globals::Gamepad_DPad_Right = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_DPad_Right")));
	Globals::Gamepad_DPad_Left = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_DPad_Left")));
	Globals::Gamepad_LeftStick_Up = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftStick_Up")));
	Globals::Gamepad_LeftStick_Down = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftStick_Down")));
	Globals::Gamepad_LeftStick_Right = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftStick_Right")));
	Globals::Gamepad_LeftStick_Left = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_LeftStick_Left")));
	Globals::Gamepad_RightStick_Up = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightStick_Up")));
	Globals::Gamepad_RightStick_Down = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightStick_Down")));
	Globals::Gamepad_RightStick_Right = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightStick_Right")));
	Globals::Gamepad_RightStick_Left = FKey(SDK.Conv_StringToName(xor_w(L"Gamepad_RightStick_Left")));

	//return HasInitKeys = true;
}

void Core::InitBones()
{
	// Assign keys
	Globals::MenuKey = Globals::Insert;
	Globals::TriggerKey = Globals::LeftShift;
	Globals::AimKey = Globals::RightMouseButton;

	Globals::HeadName = SDK.Conv_StringToName(xor_w(L"head"));
	Globals::RootName = SDK.Conv_StringToName(xor_w(L"Root"));
	Globals::NeckName = SDK.Conv_StringToName(xor_w(L"neck_01"));
	Globals::LowerNeckName = SDK.Conv_StringToName(xor_w(L"clavicle_l"));
	Globals::ChestName = SDK.Conv_StringToName(xor_w(L"spine_03"));
	Globals::PelvisName = SDK.Conv_StringToName(xor_w(L"pelvis"));
	Globals::ChestName = SDK.Conv_StringToName(xor_w(L"spine_03"));
	Globals::Upperarm_lName = SDK.Conv_StringToName(xor_w(L"upperarm_l"));
	Globals::Upperarm_rName = SDK.Conv_StringToName(xor_w(L"upperarm_r"));
	Globals::Lowerarm_lName = SDK.Conv_StringToName(xor_w(L"lowerarm_l"));
	Globals::Lowerarm_rName = SDK.Conv_StringToName(xor_w(L"lowerarm_r"));
	Globals::Hand_lName = SDK.Conv_StringToName(xor_w(L"hand_l"));
	Globals::Hand_rName = SDK.Conv_StringToName(xor_w(L"hand_r"));
	Globals::Thigh_lName = SDK.Conv_StringToName(xor_w(L"thigh_l"));
	Globals::Thigh_rName = SDK.Conv_StringToName(xor_w(L"thigh_r"));
	Globals::Calf_lName = SDK.Conv_StringToName(xor_w(L"calf_l"));
	Globals::Calf_rName = SDK.Conv_StringToName(xor_w(L"calf_r"));
	Globals::LowerCalf_lName = SDK.Conv_StringToName(xor_w(L"calf_twist_02_l"));
	Globals::LowerCalf_rName = SDK.Conv_StringToName(xor_w(L"calf_twist_02_r"));
	Globals::Foot_lName = SDK.Conv_StringToName(xor_w(L"ik_foot_l"));
	Globals::Foot_rName = SDK.Conv_StringToName(xor_w(L"ik_foot_r"));
	Globals::Toe_lName = SDK.Conv_StringToName(xor_w(L"ball_l"));
	Globals::Toe_rName = SDK.Conv_StringToName(xor_w(L"ball_r"));

	//return HasInitBones = true;
}

FORCEINLINE BYTE* RelativeVA(BYTE* inst, UINT32 offset) {
	//(addr + Util::ReadMemory<int>(addr + (size - 4)) + size)
	INT relativeOffset = Core.read< INT >((uint64_t)inst + (offset - 4));

	return (inst + relativeOffset + offset);
}

bool Core::InitOffsets()
{

	Globals::base_address = (uint64_t)GetModuleBase_Wrapper(nullptr);

	dbgprint(xor_a("[SWYZZ] base_address: 0x%X\n"), Globals::base_address);
	textBase = getImageSectionByName((uintptr_t)Globals::base_address, xor_a(".text"), &textSize);

	dbgprint(xor_a("[SWYZZ] textBase: 0x%X\n"), textBase);
	auto abc = (uint64_t)Scanner().Scan((HMODULE)Globals::base_address,
		xor_a("\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\xD0\x48\x8B\x00\xE8"),
		xor_a("xxx????xxxxx?x"), 0) - Globals::base_address;

	auto gengine = read<uintptr_t>(Globals::base_address + abc);
	dbgprint(xor_a("[SWYZZ] gengine: 0x%X\n"), gengine);

	auto viewport = read<uintptr_t>(gengine + 0x910);
	dbgprint(xor_a("[SWYZZ] viewport: 0x%X\n"), viewport);

	auto uworld = read<uint64_t>(viewport + 0x78);
	dbgprint(xor_a("[SWYZZ] uworld: 0x%X\n"), uworld);
	return true;
	/*uintptr_t gadget = (uintptr_t)Scanner().Scan((HMODULE)Globals::base_address, xor_a("\xFF\xE3"), xor_a("xx"), 0);
	uintptr_t tramp1 = (uintptr_t)Scanner().Scan((HMODULE)Globals::base_address, xor_a("\x48\x83\xC4\x68\xC3"), xor_a("xxxxx"), 0);

	legitTrampoline = (PVOID)tramp1;
	legitTrampoline2 = (PVOID)gadget;*/

	auto StaticFindFirstObjectPtr = (uint64_t)Scanner().AdvancedScan(
		xor_a("\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\x85"),
		xor_a("xxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx"), 0, 0xC65D40);
	//dbgprint(xor_a("StaticFindFirstObjectPtr: 0x%X\n"), (uintptr_t)StaticFindFirstObjectPtr - (uintptr_t)Globals::base_address);
	if (!StaticFindFirstObjectPtr) {
		StaticFindFirstObjectPtr = (uint64_t)Scanner().Scan((HMODULE)Globals::base_address,
			xor_a("\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\x85"),
			xor_a("xxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx"), 0);
	}
	//dbgprint(xor_a("StaticFindFirstObjectPtr: 0x%X\n"), (uintptr_t)StaticFindFirstObjectPtr - (uintptr_t)Globals::base_address);
	Globals::StaticFindFirstObject_t = reinterpret_cast<decltype(Globals::StaticFindFirstObject_t)>(StaticFindFirstObjectPtr);

	// String ref: ObjectNotFoun
	auto StaticLoadObjectPtr = (uint64_t)Scanner().AdvancedScan(
		xor_a("\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\x85\x00\x00\x00\x00\x33\xFF\x4C\x8B\xB5"),
		xor_a("xxxxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx????xxxxx"), 0, 0xC65D40);
	if (!StaticLoadObjectPtr) {
		StaticLoadObjectPtr = (uint64_t)Scanner().Scan((HMODULE)Globals::base_address,
			xor_a("\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\x85\x00\x00\x00\x00\x33\xFF\x4C\x8B\xB5"),
			xor_a("xxxxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx????xxxxx"), 0);
	}
	Globals::StaticLoadObject_t = reinterpret_cast<decltype(Globals::StaticLoadObject_t)>(StaticLoadObjectPtr);

	// String ref: STAT_Hash_GetObjectsOfClass
	auto GetObjectsOfClassPtr = (uint64_t)Scanner().AdvancedScan(
		xor_a("\x48\x8B\xC4\x48\x89\x58\x00\x48\x89\x70\x00\x48\x89\x78\x00\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x00\x45\x33\xF6\x48\x89\x4D\x00\x44\x38\x35\x00\x00\x00\x00\x48\x8D\x05"),
		xor_a("xxxxxx?xxx?xxx?xxxxxxxxxxxx?xxx????xxx????xxxxxx?xxxxxx?xxx????xxx"), 0, 0x989680);
	if (!GetObjectsOfClassPtr) {
		GetObjectsOfClassPtr = (uint64_t)Scanner().Scan((HMODULE)Globals::base_address,
			xor_a("\x48\x8B\xC4\x48\x89\x58\x00\x48\x89\x70\x00\x48\x89\x78\x00\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x00\x45\x33\xF6\x48\x89\x4D\x00\x44\x38\x35\x00\x00\x00\x00\x48\x8D\x05"),
			xor_a("xxxxxx?xxx?xxx?xxxxxxxxxxxx?xxx????xxx????xxxxxx?xxxxxx?xxx????xxx"), 0);
	}
	Globals::GetObjectsOfClass_t = reinterpret_cast<decltype(Globals::GetObjectsOfClass_t)>(GetObjectsOfClassPtr);

	// String ref: STAT_AFortPlayerPawn_UpdateCharacterCustomization_PostLoad
	auto UpdateCharacterCustomization = (uint64_t)Scanner().AdvancedScan(
		xor_a("\x48\x8B\xC4\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\x00\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\x00\x4C\x8D\x2D\x00\x00\x00\x00\x0F\x29\x78"),
		xor_a("xxxxxxxxxxxxxxxxxx?xxx????xxx?xxx????xxx"), 0, 0x989680);
	if (!UpdateCharacterCustomization) {
		UpdateCharacterCustomization = (uint64_t)Scanner().Scan((HMODULE)Globals::base_address,
			xor_a("\x48\x8B\xC4\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\x00\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\x00\x4C\x8D\x2D\x00\x00\x00\x00\x0F\x29\x78"),
			xor_a("xxxxxxxxxxxxxxxxxx?xxx????xxx?xxx????xxx"), 0);
	}
	Globals::UpdateCharacterCustomization_t = reinterpret_cast<decltype(Globals::UpdateCharacterCustomization_t)>(UpdateCharacterCustomization);

	// Update later, idc abt pickaxe
	//// String ref: STAT_FortWeaponPickaxeAthena_InitWeaponCosmetics
	//auto STAT_FortWeaponPickaxeAthena_InitWeaponCosmetics = (uint64_t)Scanner().Scan((HMODULE)Globals::base_address,
	//	xor_a("\x48\x8B\xC4\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xA8\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\x00\x4C\x8D\x3D"),
	//	xor_a("xxxxxxxxxxxxxxxxxx????xxx????xxx?xxx"), 0);
	//Globals::InitWeaponCosmetics_t = reinterpret_cast<decltype(Globals::InitWeaponCosmetics_t)>(STAT_FortWeaponPickaxeAthena_InitWeaponCosmetics);

	/*Malloc = (MallocFunc)Scanner().AdvancedScan(
		xor_a("\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xEC\x00\x4C\x8B\x25\x00\x00\x00\x00\x33\xED"),
		xor_a("xxxx?xxxxxxxxxxxxxx?xxx????xx"), 0, 0x989680);
	if (!Malloc) {
		Malloc = (MallocFunc)Scanner().Scan(
			xor_a("\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xEC\x00\x4C\x8B\x25\x00\x00\x00\x00\x33\xED"),
			xor_a("xxxx?xxxxxxxxxxxxxx?xxx????xx"));
	}

	Free = (FreeFunc)Scanner().AdvancedScan(
		xor_a("\x48\x85\xC9\x0F\x84\x00\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x74\x24\x00\x48\x8B\xF9\x48\x8B\x35"),
		xor_a("xxxxx????xxxx?xxxx?xxxxxx"), 0, 0x989680);
	if (!Free) {
		Free = (FreeFunc)Scanner().Scan(
			xor_a("\x48\x85\xC9\x0F\x84\x00\x00\x00\x00\x57\x48\x83\xEC\x00\x48\x89\x74\x24\x00\x48\x8B\xF9\x48\x8B\x35"),
			xor_a("xxxxx????xxxx?xxxx?xxxxxx"));
	}*/
	/*Globals::ZeroRotator = Scanner().AdvancedScan(
		xor_a("\x0F\x10\x05\x00\x00\x00\x00\x0F\x11\x82\x00\x00\x00\x00\xF2\x0F\x10\x0D\x00\x00\x00\x00\xF2\x0F\x11\x8A\x00\x00\x00\x00\xC6\x82\x00\x00\x00\x00\x00\x0F\x10\x05"),
		xor_a("xxx????xxx????xxxx????xxxx????xx?????xxx"), 7, 0x895440);*/

	Globals::GWorld = pFindObject(xor_w(L"Frontend"));

	//Globals::GWorld = read<uintptr_t>(Globals::base_address + 0x127a4bd8);
	//UObject::GObjects = reinterpret_cast<TUObjectArray*>(uintptr_t(Globals::base_address + 0x1277ceb0));

	return true;
}

bool Core::InitObjects()
{
	//if (!Globals::TranslucentMaterial)
		//Globals::TranslucentMaterial = pFindObject(xor_w(L"Eyeshadow.Eyeshadow"));
	//Globals::TranslucentMaterial = pFindObject(xor_w(L"M_BaseGlow_Outer.M_BaseGlow_Outer"));

	//if (!Globals::NotoSans)
	//	Globals::NotoSans = pFindObject(xor_w(L"NotoSans.NotoSans"));

	//if (!Globals::Roboto)
	//	Globals::Roboto = pFindObject(xor_w(L"Roboto.Roboto"));

	//// New Fortnite Font
	if (!Globals::HeadingNow)
		Globals::HeadingNow = pFindObject(xor_w(L"HeadingNow.HeadingNow"));

	// Old Fortnite Font
	if (!Globals::Burbank)
		Globals::Burbank = pFindObject(xor_w(L"Burbank.Burbank"));

	if (!Globals::FortPickup)
		Globals::FortPickup = pFindObject(xor_w(L"FortniteGame.FortPickup"));

	if (!Globals::FortAthenaSKVehicle)
		Globals::FortAthenaSKVehicle = pFindObject(xor_w(L"FortniteGame.FortAthenaSKVehicle"));

	if (!Globals::BuildingContainer)
		Globals::BuildingContainer = pFindObject(xor_w(L"FortniteGame.BuildingContainer"));

	if (!Globals::FortAthenaSupplyDrop)
		Globals::FortAthenaSupplyDrop = pFindObject(xor_w(L"FortniteGame.FortAthenaSupplyDrop"));

	//if (!Globals::BuildingActor)
		//Globals::BuildingActor = pFindObject(xor_w(L"FortniteGame.BuildingActor"));

	//if (!Globals::BuildingTrap)
		//Globals::BuildingTrap = pFindObject(xor_w(L"FortniteGame.BuildingTrap"));

	if (!Globals::ScalableFloatUtils)
		Globals::ScalableFloatUtils = pFindObject(xor_w(L"FortniteGame.FortScalableFloatUtils"));

	if (!Globals::AthenaCharacterItemDefinition)
		Globals::AthenaCharacterItemDefinition = pFindObject(xor_w(L"FortniteGame.AthenaCharacterItemDefinition"));

	if (!Globals::AthenaBackpackItemDefinition)
		Globals::AthenaBackpackItemDefinition = pFindObject(xor_w(L"FortniteGame.AthenaBackpackItemDefinition"));

	/*if (!Globals::AthenaPickaxeItemDefinition)
		Globals::AthenaPickaxeItemDefinition = pFindObject(xor_w(L"FortniteGame.AthenaPickaxeItemDefinition"));*/

	//Globals::SkinCIDS = pFindObjectsOfClass(pFindObject(xor_w(L"FortniteGame.AthenaCharacterItemDefinition")));
	//Globals::BackpackCIDS = pFindObjectsOfClass(pFindObject(xor_w(L"FortniteGame.AthenaBackpackItemDefinition")));
	//Globals::PickaxeCIDS = pFindObjectsOfClass(pFindObject(xor_w(L"FortniteGame.AthenaPickaxeItemDefinition")));

	return true;
}

uint64_t Core::pFindObject(const wchar_t* ObjectName)
{
	return (uint64_t)Globals::StaticFindFirstObject_t(0, (WCHAR*)ObjectName, 0, 0, 0);
}

uint64_t Core::pLoadObject(const wchar_t* InName)
{
	return (uint64_t)Globals::StaticLoadObject_t(nullptr, nullptr, (TCHAR*)InName, nullptr, 0, nullptr, true/*false*/, nullptr);
}

void GetObjectsOfClass(uint64_t klass, TArray<uint64_t>* results, bool includederived, int excludeflags, int excludeflagsinternal)
{
	Globals::GetObjectsOfClass_t(klass, results, includederived, excludeflags, excludeflagsinternal);
}

TArray<uint64_t> Core::pFindObjectsOfClass(uint64_t klass, bool includederived)
{
	TArray<uint64_t> out;
	GetObjectsOfClass(klass, &out, includederived, 0, 0);
	return out;
}
