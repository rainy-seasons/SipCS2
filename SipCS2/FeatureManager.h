#pragma once
#include <thread>
#include <windows.h>
#include <Psapi.h>
#include "PMemory.h"

class FeatureManager
{
public:
	FeatureManager();
	PMemory* Mem = nullptr;
	void Bhop();
	void Trigger();
	void DefuseFakeCheck();
	void StartDefuseThread();
	void StopDefuseThread();
	bool IsDefuseThreadRunning();

	void GetOffsets(); // Scanner function

private:
	uintptr_t clientDLL;

	void InitStaticAddresses();
	bool IsBombPlanted();
	bool DefuseCheck();

	uintptr_t FindOffset(const char* pattern, const char* mask) const; // another scanner function
	HMODULE scanModule;

	std::thread defuseThread;
	bool defuseThreadRunning = false;

	uintptr_t entityList;
	uintptr_t localPlayer;
	uintptr_t localPawn;
	uintptr_t m_iIDEntIndex;
	uintptr_t entEntry;
	uintptr_t baseEntity;
	uintptr_t entityTeam;
	uintptr_t playerTeam;

	uintptr_t localPlayerPawn; // for triggerbot

};
