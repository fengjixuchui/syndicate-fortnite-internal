#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {

	if (reason == DLL_PROCESS_ATTACH) {
		dbgprint("[SWYZZ] base1: 0x%X\n", Globals::base_address);
		if (!Core.InitOffsets()) return FALSE;
		dbgprint("[SWYZZ] base2: 0x%X\n", Globals::base_address);
		if (!Core.InitObjects()) return FALSE;
		dbgprint("[SWYZZ] base3: 0x%X\n", Globals::base_address);

		// Retrieve all offsets
		Offsets.fetch_offsets();

		auto OwningGameInstance = SDK.GetGameInstance();
		dbgprint("[SWYZZ] base4: 0x%X\n", Globals::base_address);
		//uint64_t LocalPlayer = Core.read<TArray<uint64_t>>(OwningGameInstance + Offsets.LocalPlayers)[0];
		//auto ViewportClient = Core.read<uint64_t>(LocalPlayer + Offsets.ViewportClient);
		auto UEngine = SDK.GetOuterObject(OwningGameInstance);

		// print base address
		dbgprint("[SWYZZ] UEngine: 0x%X\n", UEngine);
		dbgprint("[SWYZZ] UEngine-base: 0x%X\n", UEngine - (uintptr_t)GetModuleHandleA(0));

		//vmt().ShadowHookObject(ViewportClient, DrawTransistion, (void**)&Globals::DrawTransition, 114);
	}
	
	return TRUE;
}