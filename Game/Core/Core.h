#pragma once
#include "../../stdafx.h"

#define rva(addr, size) (reinterpret_cast<unsigned char*>(addr + *reinterpret_cast<int*>(addr + (size - 4)) + size))

class SDK;


class Core {
public:
	bool InitOffsets();
	bool InitObjects();
	uint64_t pFindObject(const wchar_t* ObjectName);
	uint64_t pLoadObject(const wchar_t* InName);
	TArray<uint64_t> pFindObjectsOfClass(uint64_t klass, bool includederived = false);

	//bool HasInitKeys = false;
	//bool HasInitBones = false;
	void InitKeys();
	void InitKeys_1();
	void InitKeys_2();
	void InitKeys_3();
	void InitKeys_4();
	void InitBones();

	template <class T>
	inline bool write(uint64_t address, T value)
	{
		/*if (LI_FN(IsBadWritePtr).safe_cached()((LPVOID)address, sizeof(T))) {
			return false;
		}*/

		*(T*)(address) = value;
		return true;
	}

	template <class T>
	T read(uint64_t address)
	{
		/*if (LI_FN(IsBadReadPtr).safe_cached()((LPCVOID)address, sizeof(T))) {
			return T();
		}*/

		return *(T*)(address);
	}

	/*template<typename T>
	void write(uint64_t Address, T* _)
	{
		custom_MemCpy((void*)Address, _, sizeof(T));
	}*/

	/*template <typename type>
	type read(const uintptr_t ptr) {

		type buffer{ };
		if (ptr > 0x7FFFFFFFFFFF || ptr < 1) return buffer;
		Comms::ReadPhysical(Comms::pid, (PVOID)ptr, &buffer, sizeof(type));

		return buffer;

	}*/
} inline Core;