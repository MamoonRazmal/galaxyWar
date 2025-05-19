#pragma once
#include <string>
std::string GetResourceDir()
{
#ifdef NDEBUG
	return "assets/";
#else
	return "C:/Users/local/source/repos/LightYears/LightYearsGame/assets/";
#endif
}
