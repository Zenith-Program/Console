#include "ZenithOSCommandList.h"
#include <cstring>

template<ZenithOS::int_z size> template<typename... T, typename> constexpr ZenithOS::ProgramList::StaticCommandList<size>::StaticCommandList(T... values) : commands{ values... } {}

//interface implementation
template<ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::StaticCommandList<size>::getCommandIndex(const char* name) const {
	int_z index;
	for (index = 0; index < size && std::strcmp(name, commands[index].name); index++);
	if (index == size) return -1;
	return index;
}
template<ZenithOS::int_z size> const char* ZenithOS::ProgramList::StaticCommandList<size>::getArgumentsList(ZenithOS::int_z commandIndex) const {
	if (commandIndex < 0 || commandIndex >= size) return nullptr;
	return commands[commandIndex].args;
}
template<ZenithOS::int_z size> const char* (*ZenithOS::ProgramList::StaticCommandList<size>::getFunction(ZenithOS::int_z commandIndex) const)(ZenithOS::Interpreter::Token*) {
	if (commandIndex < 0 || commandIndex >= size) return nullptr;
	return commands[commandIndex].function;
}