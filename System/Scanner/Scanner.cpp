#include "Scanner.h"

auto Scanner::Sponge(HMODULE Moudle)->PIMAGE_NT_HEADERS {
	return (PIMAGE_NT_HEADERS)((PBYTE)Moudle + PIMAGE_DOS_HEADER(Moudle)->e_lfanew);
}

auto Scanner::Mask(PBYTE start, DWORD size, LPCSTR pattern, LPCSTR mask)->PBYTE {
	auto checkMask = [](PBYTE buffer, LPCSTR pattern, LPCSTR mask) -> BOOL
		{
			for (auto x = buffer; *mask; pattern++, mask++, x++) {
				auto addr = *(BYTE*)(pattern);
				if (addr != *x && *mask != '?')
					return FALSE;
			}

			return TRUE;
		};

	for (auto x = 0; x < size - custom_strlen(mask); x++) {

		auto addr = (PBYTE)start + x;
		if (checkMask(addr, pattern, mask)) {
			return addr;
		}
	}
}

char* Scanner::ScanBasic(char* pattern, char* mask, char* begin, intptr_t size) {
	intptr_t patternLen = custom_strlen(mask);
	for (int i = 0; i < size; i++) {
		bool found = true;
		for (int j = 0; j < patternLen; j++) {
			if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j)) {
				found = false;
				break;
			}
		}
		if (found) {
			return (begin + i);
		}
	}
	return nullptr;
}

auto Scanner::Scan(HMODULE mxdule, LPCSTR pattern, LPCSTR mask, DWORD occurence) -> PBYTE {
	size_t size = Sponge(mxdule)->OptionalHeader.SizeOfImage;

	auto checkMask = [](PBYTE buffer, LPCSTR pattern, LPCSTR mask) -> BOOL
		{
			for (auto x = buffer; *mask; pattern++, mask++, x++) {
				auto addr = *(BYTE*)(pattern);
				if (addr != *x && *mask != '?')
					return FALSE;
			}

			return TRUE;
		};

	if (occurence)
		occurence -= 1;

	for (auto x = 0; x < size - custom_strlen(mask); x++) {

		auto addr = (PBYTE)mxdule + x;

		if (checkMask(addr, pattern, mask)) {

			if (!occurence || loopCount == occurence && addr) {
				loopCount = NULL; // resets the count. (Incase we need to use it again)
				return addr;
			}

			if (loopCount < occurence) {
				addr = Mask((PBYTE)mxdule + x, (PBYTE)size - addr, pattern, mask);
				++loopCount;
				continue;
			}
		}
	}

	return NULL;
}

uintptr_t Scanner::AdvancedScan(char* pattern, char* mask, int RVAOFFSET, size_t scanOffset, char* begin, intptr_t size) {
	char* buffer{ nullptr };
	SIZE_T bytesRead;
	uintptr_t Match = 0;
	PVOID addressToCheck = begin + scanOffset;

	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));
	LI_FN(VirtualQueryEx)((HANDLE)-1, (LPCVOID)begin, &mbi, sizeof(mbi));

	while (addressToCheck < begin + textSize) {
		LI_FN(VirtualQueryEx)((HANDLE)-1, (LPCVOID)addressToCheck, &mbi, sizeof(mbi));

		LI_FN(free)(buffer);
		buffer = (char*)LI_FN(malloc)((size_t)mbi.RegionSize);

		LI_FN(ReadProcessMemory)((HANDLE)-1, (LPCVOID)addressToCheck, buffer, mbi.RegionSize, &bytesRead);

		char* internalAddr = ScanBasic(pattern, mask, buffer, (intptr_t)bytesRead);
		if (internalAddr != nullptr) {
			Match = uintptr_t((char*)addressToCheck + (internalAddr - buffer));
			break;
		}
		addressToCheck = PVOID((uint64_t)addressToCheck + (size_t)mbi.RegionSize);
	}

	LI_FN(free)(buffer);
	if (Match != 0 && RVAOFFSET) {
		Match = reinterpret_cast<decltype(Match)>(rva(Match, RVAOFFSET));
	}

	return Match;
}