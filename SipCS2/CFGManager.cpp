#include "CFGManager.h"

CFGManager::CFGManager(const std::string& filename)
{
	this->m_filename = filename;
	if (!ConfigExists(filename))
	{
		WriteDefault();
	}
}

bool CFGManager::ConfigExists(const std::string& filename)
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	
	std::string localPath(buffer);
	size_t lastSlash = localPath.find_last_of("\\/");
	std::string directory = localPath.substr(0, lastSlash + 1);

	// Append the filename to the directory
	std::string fullPath = directory + filename;

	// Check if file exists
	std::ifstream file(fullPath.c_str());
	return file.good();

}

void CFGManager::WriteDefault()
{
	std::ofstream file(m_filename);
	if (file.is_open())
	{
		file << "# Virtual Key Codes can be found here: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes" << "\n";
		file << "[KEYBINDS]\n";
		file << "Toggle_Bhop=0x26" << "\n";
		file << "Toggle_Trigger=0x28" << "\n";
		file << "Toggle_DefuseCheck=0x27" << "\n";
		file << "Triggerbot_Hold=0xA4" << "\n";
		file.close();
	}
	else
	{
		std::cerr << "ERROR: Could not create default .ini file" << std::endl;
	}
}

int CFGManager::ReadKey(const std::string& section, const std::string& key)
{
	std::ifstream file(m_filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Error opening ini file.");
	}
	std::string line;
	std::string currentSection;
	
	while (std::getline(file, line))
	{
		// Skip comments and empty lines
		if (line.empty() || line[0] == ';' || line[0] == '#')
		{
			continue;
		}

		// Check if the line contains a section
		if (line[0] == '[' && line[line.length() - 1] == ']')
		{
			currentSection = line.substr(1, line.length() - 2);
			continue;
		}

		// Check if the line contains the given key in the given section
		if (currentSection == section)
		{
			size_t delimiterPos = line.find('=');
			if (delimiterPos != std::string::npos)
			{
				std::string keyInFile = line.substr(0, delimiterPos);
				if (keyInFile == key)
				{
					std::string valueStr = line.substr(delimiterPos + 1);
					std::istringstream converter(valueStr);
					int value;
					converter >> std::hex >> value;
					return value;
				}
			}
		}
	}
}