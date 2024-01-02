#include "SettingManager.h"
#include <string>

SettingManager::SettingManager()
{
	this->m_BhopEnabled = false;
	this->m_TriggerEnabled = false;
	this->m_DefuseCheckEnabled = false;
}

void SettingManager::CheckInput()
{
	if (GetAsyncKeyState(VK_UP))
	{
		this->m_BhopEnabled = !IsBhopEnabled();
		std::string status = IsBhopEnabled() ? "ON" : "OFF";
		std::cout << "||     Bhop   -->  " << status << "      ||" << std::endl;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		this->m_TriggerEnabled = !IsTriggerEnabled();
		std::string status = IsTriggerEnabled() ? "ON" : "OFF";
		std::cout << "||    Trigger   -->  " << status << "    ||" << std::endl;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		this->m_DefuseCheckEnabled = !IsDefuseCheckEnabled();
		std::string status = IsDefuseCheckEnabled() ? "ON" : "OFF";
		std::cout << "||   DefuseCheck  -->  " << status << " ||" << std::endl;
		Sleep(100);
	}
}

bool SettingManager::IsBhopEnabled()
{
	return this->m_BhopEnabled;
}

bool SettingManager::IsTriggerEnabled()
{
	return this->m_TriggerEnabled;
}

bool SettingManager::IsDefuseCheckEnabled()
{
	return this->m_DefuseCheckEnabled;
}
