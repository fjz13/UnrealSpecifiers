#include "PrivateAccess.h"
#include "Windows/AllowWindowsPlatformTypes.h"

bool FHotPatch::HookHelper(uint64* FromAddress, uint64* ToAddress)
{
	uint8 Patch[] =
	{
		0x49, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov r10 addr
		0x41, 0xFF, 0xE2                                            //jmp r10
	};

	FMemory::Memcpy(&Patch[2], &ToAddress, sizeof(ToAddress));

	DWORD BaseProtection;
	const DWORD NewProtection = PAGE_EXECUTE_READWRITE;
	if (!VirtualProtect(FromAddress, sizeof(Patch), NewProtection, &BaseProtection))
	{
		return false;
	}

	FMemory::Memcpy(FromAddress, Patch, sizeof(Patch));
	VirtualProtect(FromAddress, sizeof(Patch), BaseProtection, &BaseProtection);
	FlushInstructionCache(GetCurrentProcess(), nullptr, 0);

	return true;
}

#include "Windows/HideWindowsPlatformTypes.h"
