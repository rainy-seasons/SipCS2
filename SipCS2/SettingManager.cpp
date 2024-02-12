#include "SettingManager.h"
#include "CFGManager.h"
#include <string>

SettingManager::SettingManager()
{
	CFGManager* cfg = new CFGManager("config.ini");
	this->m_ToggleBhop = cfg->ReadKey("KEYBINDS", "Toggle_Bhop");
	this->m_ToggleTrigger = cfg->ReadKey("KEYBINDS", "Toggle_Trigger");
	this->m_ToggleDefuseCheck = cfg->ReadKey("KEYBINDS", "Toggle_DefuseCheck");
	delete cfg;

	this->m_BhopEnabled = false;
	this->m_TriggerEnabled = false;
	this->m_DefuseCheckEnabled = false;
}

void SettingManager::CheckInput()
{
	if (GetAsyncKeyState(m_ToggleBhop))
	{
		this->m_BhopEnabled = !IsBhopEnabled();
		std::string status = IsBhopEnabled() ? "ON" : "OFF";
		std::cout << "||     Bhop   -->  " << status << "      ||" << std::endl;
		Sleep(100);
	}
	if (GetAsyncKeyState(m_ToggleTrigger))
	{
		this->m_TriggerEnabled = !IsTriggerEnabled();
		std::string status = IsTriggerEnabled() ? "ON" : "OFF";
		std::cout << "||    Trigger   -->  " << status << "    ||" << std::endl;
		Sleep(100);
	}
	if (GetAsyncKeyState(m_ToggleDefuseCheck))
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
