#pragma once
#define ZenithOS_ProgramListSize 2
#include "ZenithOSProgramListConfigHeader.h"
ZenithOS_DeclareProgramSlot(0, "Program1")
ZenithOS_DeclareProgramSlot(1, "Program2")

/* ZenithOS ProgramListConfig.h----------------
* This file should be modified by the user to choose the program list size and declare it's programs
* 
* The program list size is defined as n by calling #define ZenithOS_ProgramListSize n
* Next "ZenithOSProgramListConfigHeader.h" should be included. It defines the macro that declares each program
* Each program slot must then be declared and given a name with the ZenithOS_DeclareProgramSlot(n, "name") macro
* All program slots must be declared 
* Example of a possible 'ZenithOSProgramListConfigHeader.h':
* 
* #pragma once
* #define ZenithOS_ProgramListSize 2
* #include "ZenithOSProgramListConfigHeader.h"
* ZenithOS_DeclareProgramSlot(0, "Program1")
* ZenithOS_DeclareProgramSlot(1, "Program2")
*/