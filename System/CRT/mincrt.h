#pragma once
#include <Windows.h>
#include <winternl.h>
#include <TlHelp32.h>

#include "..\importer\lazy_importer.h"
#include "../spoofer/Spoof.h"

float Pow(float b, float p);
int My_wcslen(const wchar_t* string);
//void custom_MemCpy(void* dest, void* src, size_t n);
void* custom_MemCpy(void* dest, void* src, size_t n);
//void* Memcpy(void* dst, void* src, int n);
int custom_strlen(const char* string);
PBYTE GetModuleBase_Wrapper(const char* ModuleName);
PVOID GetExportAddress(PBYTE hDll, const char* Name);
uintptr_t getImageSectionByName(const std::uintptr_t imageBase, const char* sectionName, std::size_t* sizeOut);
template <typename FuncType>
size_t custom_wcstombs(char* dest, const wchar_t* src, size_t n);
errno_t custom_memcpy_s(void* dest, size_t destSize, void* src, size_t count);
int custom_strcmp(const char* str1, const char* str2);
double CustomSqrt(double number);
double custom_fabs(double value);
