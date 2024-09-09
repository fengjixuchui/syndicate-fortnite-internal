#pragma once
#include "../../stdafx.h"

class Scanner
{
private:
	DWORD loopCount;
	char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
	auto Sponge(HMODULE Module) -> PIMAGE_NT_HEADERS;
	auto Mask(PBYTE Start, DWORD Size, LPCSTR Pattern, LPCSTR Mask) -> PBYTE;
public:
	auto Scan(HMODULE mxdule, LPCSTR pattern, LPCSTR mask, DWORD occurence) -> PBYTE;
	uintptr_t AdvancedScan(char* pattern, char* mask, int RVAOFFSET, size_t scanOffset, char* begin = reinterpret_cast<char*>(textBase), intptr_t size = textSize);
};

