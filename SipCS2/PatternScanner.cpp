#include "PatternScanner.h"
#include "Patterns.h"
#include "Offsets.h"
#include <iostream>
#include <thread>
#include <Psapi.h>

PatternScanner::PatternScanner(PMemory PMem)
{
	this->Mem = &PMem;
}

PatternScanner::~PatternScanner()
{
	delete this->Mem;
}

void PatternScanner::GetOffsets()
{
	if (clientDLL)
	{
		offsets::dwEntityList = FindOffsets(Patterns::dwEntityList.signature, Patterns::dwEntityList.mask);
		if (offsets::dwEntityList != 0)
		{
			std::cout << "dwEntityList: 0x" << std::hex << offsets::dwEntityList << std::endl;
			Sleep(5000);
		}
	}
}

// TODO:
// Currently not in use - This class needs more work to make it functional
uintptr_t PatternScanner::FindOffsets(const char* pattern, const char* mask) const
{
	MODULEINFO moduleInfo;
	GetModuleInformation(Mem->GetProcessHandle(), scanModule, &moduleInfo, sizeof(MODULEINFO));
	uintptr_t baseAddr = clientDLL;
	uintptr_t endAddr = baseAddr + moduleInfo.SizeOfImage;

	const size_t patternLen = strlen(mask);
	const auto patternBytes = pattern;

	for (uintptr_t i = baseAddr; i < endAddr - patternLen; ++i)
	{
		bool found = true;
		for (size_t j = 0; j < patternLen; ++j)
		{
			if (i + j >= endAddr)
			{
				found = false;
				break; // Check if we're going beyond the valid memory region
			}

			if (mask[j] == 'x')
			{
				const char* currentBytePtr = reinterpret_cast<const char*>(i + j);

				__try
				{
					// Attempt to read from the memory location
					char value = *currentBytePtr;
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
					found = false; // Access violation occurred
					break;
				}

				if (patternBytes[j] != *currentBytePtr)
				{
					found = false;
					break;
				}
			}
		}

		if (found)
		{
			return i = clientDLL;
		}
	}
	return 0;
}