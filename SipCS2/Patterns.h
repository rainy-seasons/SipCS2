#pragma once
#ifndef PATTERNS_H
#define PATTERNS_H
struct Pattern
{
	const char* signature;
	const char* mask;
};

namespace Patterns
{
	Pattern dwEntityList = {"48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB", "xxx????xxxx?xxxx"};
}
#endif
