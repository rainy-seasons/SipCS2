#include "Offsets.h"
#include "Patterns.h"
#include "FeatureManager.h"
#include "CFGManager.h"
#include <iostream>
#include <thread>

FeatureManager::FeatureManager()
{
	CFGManager* cfg = new CFGManager("config.ini");
	m_ActivateTrigger = cfg->ReadKey("KEYBINDS", "Triggerbot_Hold");
	delete cfg;

	Mem = new PMemory("cs2.exe");
	clientDLL = Mem->GetModuleAddress("client.dll");
	//scanModule = reinterpret_cast<HMODULE>(clientDLL);
	//GetOffsets();
	InitStaticAddresses();
}

// Initialize some static addresses that don't change over the course of a match
void FeatureManager::InitStaticAddresses()
{
	entityList = Mem->ReadMem<uintptr_t>(clientDLL + offsets::dwEntityList);
	localPlayer = Mem->ReadMem<uintptr_t>(clientDLL + offsets::dwLocalPlayerController);
	localPawn = Mem->ReadMem<uintptr_t>(localPlayer + offsets::m_hPlayerPawn);
	uintptr_t list_entry2 = Mem->ReadMem<uintptr_t>(entityList + 0x8 * ((localPawn & 0x7FFF) >> 9) + 16);
	localPlayer = Mem->ReadMem<uintptr_t>(list_entry2 + 120 * (localPawn & 0x1FF));
	localPlayerPawn = Mem->ReadMem<uintptr_t>(clientDLL + offsets::dwLocalPlayerPawn); // for triggerbot
}

bool FeatureManager::IsBombPlanted()
{
	uintptr_t dwGameRules = Mem->ReadMem<uintptr_t>(clientDLL + offsets::dwGameRules);
	return Mem->ReadMem<bool>(dwGameRules + offsets::m_bBombPlanted);
}

bool FeatureManager::DefuseCheck()
{
	bool defusing = false;
	for (int i = 0; i < 64; i++)
	{
		/********************************************************/
		/* Idk man. This is just how it's all set up in memory. */
		/********************************************************/

		uintptr_t listEntity = Mem->ReadMem<uintptr_t>(entityList + ((8 * (i & 0x7FFF) >> 9) + 16));
		if (!listEntity)
			continue;

		uintptr_t entityController = Mem->ReadMem<uintptr_t>(listEntity + (120) * (i & 0x1FF));
		if (!entityController)
			continue;

		uintptr_t entityControllerPawn = Mem->ReadMem<uintptr_t>(entityController + offsets::m_hPlayerPawn);
		if (!entityControllerPawn)
			continue;

		listEntity = Mem->ReadMem<uintptr_t>(entityList + (0x8 * ((entityControllerPawn & 0x7FFF) >> 9) + 16));
		if (!listEntity)
			continue;

		uintptr_t entityPawn = Mem->ReadMem<uintptr_t>(listEntity + (120) * (entityControllerPawn & 0x1FF));
		if (!entityPawn)
			continue;


		if (Mem->ReadMem<int>(entityPawn + offsets::m_bIsDefusing))
		{
			defusing = true;
			return defusing;
		}
	}
	return defusing;
}

void FeatureManager::DefuseFakeCheck()
{
	bool previousDefusingState = false;
	if (IsBombPlanted()) // If the bomb is planted
	{
		while (true)
		{
			bool currentDefusingState = DefuseCheck(); // Are they defusing?
			if (previousDefusingState && !currentDefusingState) // If the defuse state has changed
			{
				std::cout << '\a'; // Makes the windows ping sound to indicate they've stopped defusing (fake defuse)
			}
			previousDefusingState = currentDefusingState; // Sets new defuse state
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
}

void FeatureManager::StartDefuseThread()
{
	// Start the thread and bind the IsDefuseFake function
	defuseThread = std::thread(&FeatureManager::DefuseFakeCheck, this);
	defuseThreadRunning = true;
}

void FeatureManager::StopDefuseThread()
{
	// Join the thread and wait for it to finish
	if (defuseThread.joinable())
	{
		defuseThread.join();
	}
	defuseThreadRunning = false;
}

bool FeatureManager::IsDefuseThreadRunning()
{
	return defuseThreadRunning;
}

void FeatureManager::Bhop()
{
	if (localPlayer)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			int onGround = Mem->ReadMem<int>(localPlayer + offsets::m_fFlags);

			if ((onGround & 1 << 0)) // Checks the correct flag from the bit field
			{
				// Plus key should be bound to +jump in-game
				// This is due to how the engine handles inputs
				// With jump bound to space, and holding space to bunnyhop, it confuses the engine and 
				//   the jumps will not be timed well enough to maintain speed
				keybd_event(VK_OEM_PLUS, 0, 0, 0); 
				Sleep(15);
				keybd_event(VK_OEM_PLUS, 0, KEYEVENTF_KEYUP, 0);
			}
		}
	}
}

void FeatureManager::Trigger()
{
	if (GetAsyncKeyState(m_ActivateTrigger))
	{
		m_iIDEntIndex = Mem->ReadMem<int32_t>(localPlayerPawn + offsets::m_iIDEntIndex);
		entEntry = Mem->ReadMem<uintptr_t>(entityList + 0x8 * (m_iIDEntIndex >> 9) + 0x10);
		baseEntity = Mem->ReadMem<uintptr_t>(entEntry + 120 * (m_iIDEntIndex & 0x1FF));
		entityTeam = Mem->ReadMem<int>(baseEntity + offsets::m_iTeamNum);
		playerTeam = Mem->ReadMem<int>(localPlayer + offsets::m_iTeamNum);
		if (baseEntity)
		{
			if (playerTeam != entityTeam)
			{
				if (Mem->ReadMem<int>(baseEntity + offsets::m_iHealth) > 0 && m_iIDEntIndex > 64)
				{
					Sleep(15);
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					Sleep(1);
				}
			}
		}
	}
}

//void FeatureManager::GetOffsets()
//{
//	if (clientDLL)
//	{
//		offsets::dwEntityList = FindOffset(Patterns::dwEntityList.signature, Patterns::dwEntityList.mask);
//		if (offsets::dwEntityList != 0)
//		{
//			std::cout << "dwEntityList: 0x" << std::hex << offsets::dwEntityList << std::endl;
//			Sleep(5000);
//		}
//	}
//}

//uintptr_t FeatureManager::FindOffset(const char* pattern, const char* mask) const
//{
//	MODULEINFO moduleInfo;
//	GetModuleInformation(Mem->GetProcessHandle(), scanModule, &moduleInfo, sizeof(MODULEINFO));
//
//	uintptr_t baseAddress = clientDLL;
//	uintptr_t endAddress = baseAddress + moduleInfo.SizeOfImage;
//
//	const size_t patternLength = strlen(mask);
//	const auto patternBytes = pattern;
//
//	for (uintptr_t i = baseAddress; i < endAddress - patternLength; ++i) {
//		bool found = true;
//		for (size_t j = 0; j < patternLength; ++j) {
//			if (i + j >= endAddress) {
//				found = false;
//				break; // Check if we're going beyond the valid memory region
//			}
//
//			if (mask[j] == 'x') {
//				const char* currentBytePtr = reinterpret_cast<const char*>(i + j);
//
//				__try {
//					// Attempt to read from the memory location
//					char value = *currentBytePtr;
//				}
//				__except (EXCEPTION_EXECUTE_HANDLER) {
//					found = false;  // Access violation occurred
//					break;
//				}
//
//				if (patternBytes[j] != *currentBytePtr) {
//					found = false;
//					break;
//				}
//			}
//		}
//
//		if (found) {
//			return i - clientDLL;
//		}
//	}
//
//	return 0;
//}
