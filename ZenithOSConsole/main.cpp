#include "VSBuffer.h"
#include "ConsoleToken.h"
#include "ZenithOSTypes.h"
#include "ZenithOSProgramList.h"
#include "ZenithOSCommandList.h"
#include <iostream>
using namespace TestOS;
using namespace ZenithOS;
using namespace ZenithOS::Interpreter;
TestOS::VSBuffer buffer;
Token token;

char printBuffer[64];

int main() {
	constexpr ZenithOS::ProgramList::StaticCommandList<2> list = { ZenithOS::ProgramList::Command({"Command1", "if", nullptr}), ZenithOS::ProgramList::Command({"Command2", "wi", nullptr}) };
	ZenithOS::ProgramList::ProgramLedger ledger = ZenithOS::ProgramList::getProgramList();

	std::cout << list.getCommandIndex("Command1") << ' ' << list.getCommandIndex("Focus") << std::endl;
	std::cout << list.getArgumentsList(0) << ' ' << list.getArgumentsList(1) << std::endl;
	//ledger.initProgramData();
	std::cout << ledger.getProgramName(0) << std::endl;
	std::cout << ledger.getProgramName(1) << std::endl;
	ledger.startProgram(0);
	std::cout << ledger.isRunning(0) << ' ' << ledger.isRunning(1) << std::endl;
	ledger.runActiveLoops();
	std::cout << ledger.stopProgram(1) << std::endl;
	ledger.startProgram(1);
	ledger.runActiveLoops();
	ledger.stopProgram(1);
	ledger.stopProgram(0);
	std::cout << ledger.getProgramIndex("Program2") << ' ' << ledger.getProgramIndex("Data Logger") << std::endl;
	std::cout << ledger.getProgramPriority(1) << ' ' << ledger.getProgramPriority(0) << std::endl;
	std::cout << ledger.getCurrentThread() << std::endl;
	return 0;
}

