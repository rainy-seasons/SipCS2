#pragma once
#pragma once
#include <windows.h>
#include <iostream>


class SettingManager
{
public:
	SettingManager();
	void CheckInput();

	bool IsBhopEnabled();
	bool IsTriggerEnabled();
	bool IsDefuseCheckEnabled();

private:
	bool m_BhopEnabled;
	bool m_TriggerEnabled;
	bool m_DefuseCheckEnabled;
};

