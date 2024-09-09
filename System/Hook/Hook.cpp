#include "Hook.h"

auto vmt::GetVtableSize(uint64_t class_member) -> SIZE_T
{
	auto addr = Core.read<uint64_t>(class_member);
	if (!addr) return 0;

	int total_size = 0, current_table = 0;

	while (vpnter(Core.read<uint64_t>(addr + (current_table * sizeof(uint64_t)))))
	{
		total_size += 1;
		current_table++;
	}

	return total_size;
}

auto vmt::ShadowHookObject(uint64_t Object, void* HookFunction, void** HookOrig, DWORD Index) -> bool {
	size_t VtableSize = GetVtableSize(Object);

	uint64_t AllocPage = 0;
	PVOID AllocatedMem = nullptr;

	if (AllocPage == 0)
		AllocPage = (uint64_t)LI_FN(VirtualAlloc).safe_cached()(nullptr, VtableSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	uint64_t NewVTable = (uint64_t)LI_FN(calloc).safe_cached()(VtableSize, sizeof(uint64_t));
	if (NewVTable == 0) {
		LI_FN(VirtualFree).safe_cached()((void*)AllocPage, 0, MEM_RELEASE);
		return false;
	}

	void* OriginalVTable = Core.read<void*>(Object);
	custom_MemCpy((void*)NewVTable, OriginalVTable, VtableSize * sizeof(uint64_t));

	// Setup a hook template for the function redirection
	uint8_t HookTemplate[14] = { 0xFF, 0x25, 0, 0, 0, 0 };
	*(void**)&HookTemplate[6] = HookFunction;
	custom_MemCpy((void*)AllocPage, HookTemplate, sizeof(HookTemplate));

	// Redirect original function to the new hook function
	*(uint64_t*)&HookTemplate[6] = *(uint64_t*)((unsigned char*)NewVTable + (Index * sizeof(PVOID)));
	custom_MemCpy((void*)(AllocPage + sizeof(HookTemplate)), HookTemplate, sizeof(HookTemplate));

	*HookOrig = (void*)(AllocPage + sizeof(HookTemplate));
	*(uint64_t*)((unsigned char*)NewVTable + (Index * sizeof(PVOID))) = AllocPage;

	Core.write<uint64_t>(Object, NewVTable);

	return true;
}