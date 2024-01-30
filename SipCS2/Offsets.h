#pragma once
#ifndef OFFSETS_H
#define OFFSETS_H
#include <Windows.h>

namespace offsets
{
	//extern uintptr_t dwEntityList;
	uintptr_t dwEntityList = 0x17C1950;
	uintptr_t dwLocalPlayerController = 0x1810F48;
	uintptr_t dwLocalPlayerPawn = 0x16C8F58;
	uintptr_t dwGameRules = 0x181E048;  // contains *m_bBombPlanted and *m_bIsDefusing
	uintptr_t m_hPlayerPawn = 0x7EC;
	uintptr_t m_fFlags = 0x3C8;
	uintptr_t m_iIDEntIndex = 0x1544; // crosshair index
	uintptr_t m_iTeamNum = 0x3BF;
	uintptr_t m_iHealth = 0x32C;
	uintptr_t m_bIsScoped = 0x13A8;
	uintptr_t m_bIsDefusing = 0x13B0;
	uintptr_t m_bBombPlanted = 0x9DD;
}
#endif
