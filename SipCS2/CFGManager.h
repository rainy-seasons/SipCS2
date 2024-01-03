#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>

class CFGManager
{
public:
	CFGManager(const std::string& filename);
	int ReadKey(const std::string& section, const std::string& key);
private:
	std::string m_filename;
	bool ConfigExists(const std::string& filename);
	void WriteDefault();
};
