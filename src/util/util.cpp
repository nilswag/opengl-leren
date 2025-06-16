#include <iostream>
#include <fstream>
#include <sstream>

#include "util.h"

std::string util::readFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file)
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}