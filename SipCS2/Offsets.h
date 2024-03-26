#pragma once
#ifndef OFFSETS_H
#define OFFSETS_H
#include <Windows.h>

namespace offsets
{
	uintptr_t dwEntityList = 0x18C2D58;
	uintptr_t dwLocalPlayerController = 0x1912578;
	uintptr_t dwLocalPlayerPawn = 0x17371A8;
	uintptr_t dwGameRules = 0x191FCA0;  // contains *m_bBombPlanted and *m_bIsDefusing
	uintptr_t m_hPlayerPawn = 0x7E4;
	//uintptr_t m_fFlags = 0x3C8; // maybe??????
	uintptr_t m_fFlags = 0x3D4;
	uintptr_t m_iIDEntIndex = 0x15A4; // crosshair index
	uintptr_t m_iTeamNum = 0x3CB;
	uintptr_t m_iHealth = 0x334;
	//uintptr_t m_bIsScoped = 0x1400;
	uintptr_t m_bIsDefusing = 0x1408;
	uintptr_t m_bBombPlanted = 0x1ACB; // IDK
	//uintptr_t m_bBombPlanted = 0x9DD;
}
#endif
