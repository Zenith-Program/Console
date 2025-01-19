#pragma once
#define ZenithOS_ProgramListSize 2
#define ZenithOS_DefaultProgramPriority 1
#include "ZenithOSProgramListConfigHeader.h"
ZenithOS_DeclareProgramSlot(0, "Program1", 1)
ZenithOS_DeclareProgramSlotWithPriority(1, "Program2", 1, 2)

/* ZenithOS ProgramListConfig.h----------------
* This file should be modified by the user to choose the program list size and declare it's programs
* 
* The program list size is defined as n by calling #define ZenithOS_ProgramListSize n
* The default program priority can optionally be set here by calling #define ZenithOS_DefaultProgramPriority. It defaults to 1 if not set
* Next "ZenithOSProgramListConfigHeader.h" should be included. It defines the macro that declares each program
* Each program slot must then be declared and given a name with the ZenithOS_DeclareProgramSlot(n, "name") macro
* All program slots must be declared 
* The ZenithOS_DeclareProgramSlotWithPriorit macro can be used to specify a priority different from the default
* Example of a possible 'ZenithOSProgramListConfigHeader.h':
* 
* #pragma once
* #define ZenithOS_ProgramListSize 2
* #include "ZenithOSProgramListConfigHeader.h"
* ZenithOS_DeclareProgramSlot(0, "Program1")
* ZenithOS_DeclareProgramSlotWithPriority(1, "Program2", 2)
*/