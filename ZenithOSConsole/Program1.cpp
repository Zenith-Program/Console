#define ZenithOS_UseProgramSlot 0
#define ZenithOS_CommandListSize 1
#include "ZenithOSProgramEntryPoint.hpp"
#include "ZenithOSProgramSetCommandList.hpp"

//ZenithOS_ProgramCommandList = {NextCommand{"Command1", "f", nullptr}};
//ZenithOS_RegisterProgramCommandList


#include <iostream>

Startup() {
	std::cout << "adress: " << &ProgramCommandList_0 << std::endl;
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