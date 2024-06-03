#define WIN32_LEAN_AND_MEAN
#include "FeatureManager.h"
#include "SettingManager.h"

void WindowSetup();
void MenuScreen();

int main()
{
	WindowSetup();
	MenuScreen();

	auto Settings = SettingManager();
	auto Feature = FeatureManager();
	
	// Main loop
	while (true)
	{
		Settings.CheckInput();
		if (Settings.IsBhopEnabled())
		{
			Feature.Bhop();
		}
		if (Settings.IsTriggerEnabled())
		{
			Feature.Trigger();
		}
		if (Settings.IsDefuseCheckEnabled())
		{
			if (!Feature.IsDefuseThreadRunning())
			{
				Feature.StartDefuseThread();
			}
		}
	}
}

// Sets up the console window with desired layout
void WindowSetup()
{
	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top, 265, 500, TRUE);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	GetConsoleScreenBufferInfo(handle, &bufInfo);
	COORD new_size =
	{
		bufInfo.srWindow.Right - bufInfo.srWindow.Left + 1,
		bufInfo.srWindow.Bottom - bufInfo.srWindow.Top + 1
	};

	SetConsoleScreenBufferSize(handle, new_size);
}

void MenuScreen()
{
	system("cls");
	system("color D");
	std::cout << R"(      _)        )"  << std::endl;
	std::cout << R"(  __|  |  __ \ )" << std::endl;
	std::cout << R"(\__ \  |  | | )" << std::endl;
	std::cout << R"(____/ _|  .__/  )" << std::endl;
	std::cout << R"(         _|     )" << std::endl;

	std::cout << "-----------------------------" << std::endl;
	std::cout << "|| [ UP ]     Bhop         ||" << std::endl;
	std::cout << "|| [ DWN ]    Trigger      ||" << std::endl;
	std::cout << "|| [ RGHT ]   DefuseCheck  ||" << std::endl;
	std::cout << "-----------------------------" << std::endl;
}