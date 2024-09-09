#pragma once
//#define _HAS_EXCEPTIONS 0
#include <Windows.h>
#include <iostream>
#include <ntstatus.h>
#include <stdio.h>
#include <cstdint>
#include <wchar.h>
#include <vector>

#include "System/xor/xor.h"
#include "System/xor/xor_data.h"
#include "System/xor/xor_value.h"
#include "System/CRT/mincrt.h"

static void SecureZeroMemoryCustom(void* pDest, size_t nSize)
{
	unsigned char* p = (unsigned char*)pDest;
	for (size_t i = 0; i < nSize; i++)
	{
		p[i] = 0;
	}
}

static void dbgprint(const char* string, ...)
{
	char buf[512];
	va_list arg_list;

	SecureZeroMemoryCustom(buf, sizeof(buf));

	va_start(arg_list, string);
	LI_FN(vsnprintf).get()(buf, sizeof(buf), string, arg_list);
	va_end(arg_list);

	LI_FN(OutputDebugStringA).get()(buf);

	return;
}

static void dbgprint(const wchar_t* string, ...)
{
	wchar_t buf[512];
	va_list arg_list;

	SecureZeroMemoryCustom(buf, sizeof(buf));

	va_start(arg_list, string);
	vswprintf(buf, sizeof(buf), string, arg_list);
	va_end(arg_list);

	LI_FN(OutputDebugStringW).get()(buf);
}

//inline void* Malloc;
//inline void* Free;

inline size_t textSize;
inline uintptr_t textBase;

#include "System/Scanner/Scanner.h"
#include "Settings/Settings.h"
#include "Settings/Config.h"
#include "Game/SDK/Structs/structs.h"
#include "Globals/Globals.hpp"
#include "Game/Core/Core.h"
#include "Game/SDK/SDK.h"
#include "System/OffsetFinder/OffsetFinder.h"
#include "Game/Functions/Functions.h"
#include "Game/DrawTransistion/GUI/GUI.h"
#include "System/Hook/Hook.h"
#include "Game/DrawTransistion/DrawTransistion.h"