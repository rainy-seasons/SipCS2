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

private:
	uintptr_t clientDLL;

	void InitStaticAddresses();
	bool IsBombPlanted();
	bool DefuseCheck();

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

	int m_ActivateTrigger;
};
