#pragma once
#include <Windows.h>
#include "PMemory.h"

class PatternScanner
{
public:
	PatternScanner(PMemory Mem);
	~PatternScanner();
	void GetOffsets();
	uintptr_t FindOffsets(const char* pattern, const char* mask) const;

private:
	uintptr_t clientDLL;
	HMODULE scanModule;
	PMemory* Mem;
};
