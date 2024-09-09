#ifdef FALSE
#include "DriverUtil.h"

namespace Comms {
	BOOL Setup() {
		auto win32 = GetModuleBase_Wrapper(xor_a("win32u.dll"));

		//If one or the other is not loaded, just return false
		if (!win32) {
			dbgprint("Couldn't find win32\n");
			return FALSE;
		}

		//Find the pointer addr	
		auto addr = GetExportAddress(win32, xor_a("NtMITPostWindowEventMessage"));
		// If cannot find return false
		if (!addr) {
			dbgprint("Couldn't find NtMITPostWindowEventMessage\n");
			return FALSE;
		}

		//Else set it to the pointer comm, and return true.
		*(PVOID*)&PointerComm = addr;

		return TRUE;
	}

	PVOID GetBaseAddress(DWORD processID) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::GETBASE;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;
		request.Outbase = 0;
		PointerComm(&request, 0);

		return request.Outbase;
	}

	NTSTATUS Read(DWORD processID, PVOID DestinationToRead, PVOID Buffer, DWORD size) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::READPROCESSMEMORY;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;

		request.Dest = DestinationToRead;
		request.Src = Buffer;
		request.Size = size;

		PointerComm(&request, 0);

		return 0;
	}

	NTSTATUS ReadPhysical(DWORD processID, PVOID DestinationToRead2, PVOID buffer, DWORD size) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::READPHYSICALMEMORY;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;

		request.Dest = DestinationToRead2;
		request.Src = buffer;
		request.Size = size;

		PointerComm(&request, 0);

		return 0;
	}

	NTSTATUS Write(DWORD processID, PVOID DestinationToWrite, PVOID Buffer, DWORD size) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::WRITEPROCESSMEMORY;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;

		request.Dest = DestinationToWrite;
		request.Src = Buffer;
		request.Size = size;

		PointerComm(&request, 0);

		return 0;
	}

	PVOID ZWAlloc(DWORD processID, PVOID* baseaddr, PSIZE_T first, ULONG AllocType, DWORD protects) {

		PVOID outAddress = 0;

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::ZWALLOC;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;
		request.InAddress = baseaddr;
		request.OutAddress = &outAddress;
		request.RegionSize = first;
		request.Protect = protects;
		request.AllocationType = AllocType;

		PointerComm(&request, 0);

		return outAddress;
	}

	NTSTATUS Prot(DWORD processID, PVOID Address, DWORD size, DWORD protect, PDWORD outprotect) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::PROTECTVIRTUALMEMORY;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;
		request.Address = Address;
		request.Size = size;
		request.Protect = protect;
		request.InOutProtect = outprotect;

		PointerComm(&request, 0);

		return 0;
	}


	PVOID PML4Injection(DWORD GamePID, DWORD BackingProcessID, ULONG64 RemoteImageBase, int PML4INDEX) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::INJECTION;
		request.Reason = 0xDEADBEEF;
		request.TargetProcessId = GamePID;
		request.RemoteProcessId = BackingProcessID;
		request.RemotePayloadImageBase = RemoteImageBase,
			request.PML4Index = PML4INDEX;

		PointerComm(&request, 0);

		return 0;
	}


	NTSTATUS Free(DWORD processID, SIZE_T size, PVOID address, DWORD protect) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::FREEPROCESSMEMORY;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;
		request.Address = address;
		request.Size = size;
		request.Protect = protect;

		PointerComm(&request, 0);

		return 0;
	}

	NTSTATUS VadHide(DWORD processID, PVOID address) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::HIDEVAD;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;
		request.Address = address;

		PointerComm(&request, 0);

		return 0;
	}

	PVOID MouseMove(long x, long y, unsigned short buttonflags) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::MOVEMOUSE;
		request.Reason = 0xDEADBEEF;
		request.button_flags = buttonflags;
		request.x = x;
		request.y = y;

		PointerComm(&request, 0);

		return 0;
	}

	PVOID VirtQuery(DWORD processID, PVOID address, PVOID* mbistate, PVOID* mbiprotect, SIZE_T size) {

		PVOID outAddress = 0;

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::QVIRT;
		request.processID = processID;
		request.Reason = 0xDEADBEEF;
		request.Address = address;
		request.Size = size;
		request.mbistate = mbistate;
		request.mbiprotect = mbiprotect;
		request.OutAddress = &outAddress;

		PointerComm(&request, 0);

		return outAddress;

	}

	int FindValidPML4Index(DWORD processID) {

		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::PFNPML4CHECK;
		request.processID = processID;
		request.Reason = 0xDEADBEEF;
		request.PML4Index = 221;

		PointerComm(&request, 0);

		return request.PML4Index;
	}
}
#endif