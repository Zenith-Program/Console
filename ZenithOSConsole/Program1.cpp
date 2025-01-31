#define ZenithOS_ProgramID ProgramA
#include "ZenithOSProgramEntryPoint.hpp"
#include "ZenithOSProgramSetCommandList.hpp"

ZenithOS_ProgramCommandList = { {"aa", "bb", nullptr}, {"ab", "ff", nullptr} };



#include <iostream>

Startup() {
	std::cout << "Start of program 0" << std::endl;
	return 0;
}

Loop() {
	std::cout << "This is the loop of program 0" << std::endl;
}

Shutdown() {
	std::cout << "End of program 0" << std::endl;
	return 0;
}