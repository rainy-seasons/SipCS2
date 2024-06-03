#pragma once
#ifndef OFFSETS_H
#define OFFSETS_H
#include <Windows.h>

namespace offsets
{
	uintptr_t dwEntityList = 0x18C7F98;			   // Entity list contains pointers to every registered entity
	uintptr_t dwLocalPlayerController = 0x19176A8; // Needed to resolve localplayer
	uintptr_t dwLocalPlayerPawn = 0x173B568;       // Needed to resolve localplayer
	uintptr_t dwGameRules = 0x1924EF0;             // contains *m_bBombPlanted and *m_bIsDefusing
	uintptr_t m_hPlayerPawn = 0x7E4;               // Needed to resolve localplayer
	uintptr_t m_fFlags = 0x3D4;                    // contains onGround flag
	uintptr_t m_iIDEntIndex = 0x13B0;              // crosshair index
	uintptr_t m_iTeamNum = 0x3CB;                  // Offset that gives a team index of the entity
	uintptr_t m_iHealth = 0x334;                   // Gives health value for the entity
	uintptr_t m_bIsDefusing = 0x1408;              // Checks if the entity is defusing
	uintptr_t m_bBombPlanted = 0x9DD;              // Checks if bomb is planted
}
#endif
