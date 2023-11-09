#include "Component.h"
#include <string>
#include <vector>
#pragma once
class CompLoader {
protected:
	static std::vector<std::string> splitSaveLine(std::string& line, const char delimiter);
};

