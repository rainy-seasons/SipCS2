#ifndef PMEMORY_H
#define PMEMORY_H
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>


class PMemory
{
private:
	DWORD m_PID = 0;
	HANDLE m_pHandle = nullptr;

public:
	PMemory(const char* procName);
	PMemory();
	~PMemory();

	DWORD GetPID();
	HANDLE GetProcessHandle();

	uintptr_t GetModuleAddress(const char* ModuleName);

	template<class T>
	T ReadPtr(LPVOID addr)
	{
		return *((T*)addr);
	}

	template<class T>
	void WritePtr(LPVOID addr, T val)
	{
		*((T*)addr) = val;
	}

	template<typename T>
	T ReadMem(uintptr_t addr)
	{
		T val;
		ReadProcessMemory(m_pHandle, (LPCVOID)addr, &val, sizeof(T), NULL);
		return val;
	}

	template<typename T>
	bool WriteMem(uintptr_t addr, T val)
	{
		return WriteProcessMemory(m_pHandle, (LPVOID)addr, &val, sizeof(T), NULL);
	}

	template<class T>
	DWORD ProtectMemory(LPVOID addr, DWORD prot)
	{
		DWORD oldProt;
		VirtualProtectEx(m_pHandle, addr, sizeof(T), prot, &oldProt);
		return oldProt;
	}
};
#endif
