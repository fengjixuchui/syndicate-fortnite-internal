#include "mincrt.h"

// This gives Object Error in Main
extern "C" int _fltused = 0;
#pragma data_seg()
#pragma comment(linker, "/merge:.CRT=.rdata")

#pragma intrinsic(memset) // weird fix to compile bug in release
extern void* __cdecl memset(void*, int, size_t);
#pragma function(memset)
void* memset(void* dest, int c, size_t count) {
	unsigned char* p = (unsigned char*)dest;
	for (size_t i = 0; i < count; i++) {
		p[i] = (unsigned char)c;
	}
	return dest;
}

#pragma intrinsic(memcpy) // weird fix to compile bug in release
extern void* __cdecl memcpy(void*, void const*, size_t);
#pragma function(memcpy)
void* memcpy(void* dest, const void* src, size_t count) {

	char* pDest = static_cast<char*>(dest);
	const char* pSrc = static_cast<const char*>(src);

	for (size_t i = 0; i < count; ++i) {
		pDest[i] = pSrc[i];
	}

	return dest;
}

float Pow(float b, float p)
{
	float Result = 1.0f;
	for (int i = 0; i < p; ++i)
	{
		Result *= b;
	}
	return Result;
}

size_t custom_wcstombs(char* dest, const wchar_t* src, size_t n) {
	size_t i = 0;
	while (src[i] != L'\0' && i < n) {
		dest[i] = static_cast<char>(src[i]);
		++i;
	}
	if (i < n) {
		dest[i] = '\0';
	}
	return i;
}

int custom_strlen(const char* string)
{
	int cnt = 0;
	if (string)
	{
		for (; *string != 0; ++string) ++cnt;
	}
	return cnt;
}

void* custom_MemCpy(void* dest, void* src, size_t n)
{
	char* csrc = (char*)src;
	char* cdest = (char*)dest;

	for (size_t i = 0; i < n; i++)
		cdest[i] = csrc[i];

	return dest;
}
//void* Memcpy(void* dst, void* src, int n)
//{
//	auto Src = static_cast<unsigned char*>(src);
//	auto Dest = static_cast<unsigned char*>(dst);
//
//	int i = n;
//	while (i--)
//	{
//		*Dest++ = *Src++;
//	}
//
//	return static_cast<void*>(Dest);
//}
errno_t custom_memcpy_s(void* dest, size_t destSize, void* src, size_t count) {
	if (dest == nullptr || src == nullptr || destSize < count) {
		return EINVAL;
	}
	custom_MemCpy(dest, src, count);
	return 0;
}
int custom_strcmp(const char* str1, const char* str2) {
	int i = 0;
	while (str1[i] && (str1[i] == str2[i])) {
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
int strcmpcustom(const char* src, const char* dst)
{
	int ret = 0;
	unsigned char* p1 = (unsigned char*)src;
	unsigned char* p2 = (unsigned char*)dst;
	while (*p2 && *p1 && !(ret = *p1 - *p2))
		++p1, ++p2;
	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;
	return (ret);
}

double CustomSqrt(double number)
{
	if (number < 0) return -1; // Return -1 for negative inputs, or handle as needed
	if (number == 0) return 0;

	double x = number;
	double y = 1.0;
	const double epsilon = 0.000001; // Error tolerance

	while (x - y > epsilon) {
		x = (x + y) / 2;
		y = number / x;
	}

	return x;
}
int My_wcslen(const wchar_t* string)
{
	int cnt = 0;
	if (string)
	{
		for (; *string != 0; ++string) ++cnt;
	}
	return cnt;
}
int _wcsicmp(const wchar_t* s1, const wchar_t* s2) {
	while (*s1 && *s2) {
		wchar_t c1 = *s1;
		wchar_t c2 = *s2;
		if (c1 >= 'A' && c1 <= 'Z') {
			c1 += 'a' - 'A';
		}
		if (c2 >= 'A' && c2 <= 'Z') {
			c2 += 'a' - 'A';
		}
		if (c1 != c2) {
			return c1 - c2;
		}
		++s1;
		++s2;
	}
	return *s1 - *s2;
}
double custom_fabs(double value) {
	return (value < 0) ? -value : value;
}
char tolower_custom(char c) {
	if (c >= 'A' && c <= 'Z') {
		return c + ('a' - 'A');
	}
	else {
		return c;
	}
}
#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)

template <typename StrType, typename StrType2>
bool StrCmp(StrType Str, StrType2 InStr, bool Two) {
	if (!Str || !InStr) return false;
	wchar_t c1, c2; do {
		c1 = *Str++; c2 = *InStr++;
		c1 = ToLower(c1); c2 = ToLower(c2);
		if (!c1 && (Two ? !c2 : 1)) return true;
	} while (c1 == c2); return false;
}

__declspec(noinline) PBYTE GetModuleBase_Wrapper(const char* ModuleName) {

	PPEB_LDR_DATA Ldr = ((PTEB)__readgsqword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr;

	for (PLIST_ENTRY CurEnt = Ldr->InMemoryOrderModuleList.Flink; CurEnt != &Ldr->InMemoryOrderModuleList; CurEnt = CurEnt->Flink) {

		LDR_DATA_TABLE_ENTRY* pEntry = CONTAINING_RECORD(CurEnt, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
		PUNICODE_STRING BaseDllName = (PUNICODE_STRING)&pEntry->Reserved4[0];

		if (!ModuleName || StrCmp(ModuleName, BaseDllName->Buffer, false)) {
			return (PBYTE)pEntry->DllBase;
		}
	}

	return nullptr;
}

__declspec(noinline) PVOID GetExportAddress(PBYTE hDll, const char* Name)
{

	PIMAGE_NT_HEADERS NT_Head = (PIMAGE_NT_HEADERS)(hDll + ((PIMAGE_DOS_HEADER)hDll)->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)(hDll + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);

	//process list
	for (DWORD i = 0; i < ExportDir->NumberOfNames; i++)
	{
		//get ordinal & name

		USHORT Ordinal = ((USHORT*)(hDll + ExportDir->AddressOfNameOrdinals))[i];
		const char* ExpName = (const char*)hDll + ((DWORD*)(hDll + ExportDir->AddressOfNames))[i];

		if (StrCmp(Name, ExpName, true))
			return (PVOID)(hDll + ((DWORD*)(hDll + ExportDir->AddressOfFunctions))[Ordinal]);
	}

	return nullptr;
}

uintptr_t getImageSectionByName(const std::uintptr_t imageBase, const char* sectionName, std::size_t* sizeOut) {
	if (reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase)->e_magic != 0x5A4D)
		return {};
	const auto ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS64>(
		imageBase + reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase)->e_lfanew);
	const auto sectionCount = ntHeader->FileHeader.NumberOfSections;
	auto sectionHeader = IMAGE_FIRST_SECTION(ntHeader);

	for (std::size_t i{}; i < sectionCount; ++i, ++sectionHeader) {
		if (!strcmpcustom(sectionName, reinterpret_cast<const char*>(sectionHeader->Name))) {
			if (sizeOut)
				*sizeOut = sectionHeader->Misc.VirtualSize;
			return imageBase + sectionHeader->VirtualAddress;
		}
	}
	return {};
}