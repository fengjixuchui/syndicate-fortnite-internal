#pragma once
#if 0
namespace Comms {
	enum Request {
		CONNECTION = 0
	};

	typedef struct Communication {
		Request Request; // Request Type
		GUID Code; // Secret Code
	}*pCommunication;

	static const GUID SECRET_GUID = { 0xA4F156B2, 0x9B7F, 0x4F08, {0x83, 0xEF, 0x2C, 0x10, 0x88, 0x4C, 0xA9, 0x72} };
	NTSTATUS(*PointerComm)(PVOID, PVOID) = nullptr;
	BOOL Setup() {
		auto win32 = GetModuleBase_Wrapper(xor_a("win32u.dll"));

		if (!win32) {
			return FALSE;
		}

		auto addr = GetExportAddress(win32, xor_a("NtMITPostWindowEventMessage"));
		if (!addr) {
			return FALSE;
		}

		*(PVOID*)&PointerComm = addr;

		return TRUE;
	}

	BOOL CompareGuids(const GUID* guid1, const GUID* guid2) {
		return (guid1->Data1 == guid2->Data1 &&
			guid1->Data2 == guid2->Data2 &&
			guid1->Data3 == guid2->Data3 &&
			guid1->Data4[0] == guid2->Data4[0] &&
			guid1->Data4[1] == guid2->Data4[1] &&
			guid1->Data4[2] == guid2->Data4[2] &&
			guid1->Data4[3] == guid2->Data4[3] &&
			guid1->Data4[4] == guid2->Data4[4] &&
			guid1->Data4[5] == guid2->Data4[5] &&
			guid1->Data4[6] == guid2->Data4[6] &&
			guid1->Data4[7] == guid2->Data4[7]);
	}

	BOOL VerifyConnection() {
		Communication request = {};
		SecureZeroMemoryCustom(&request, sizeof(request));

		request.Request = Request::CONNECTION;

		PointerComm(&request, NULL);

		if (CompareGuids(&request.Code, &SECRET_GUID)) {
			return TRUE;
		}
		return FALSE;
	}
}
#endif