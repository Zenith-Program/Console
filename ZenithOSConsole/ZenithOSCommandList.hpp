#include "ZenithOSCommandList.h"
#include <cstring>

//template<ZenithOS::int_z size> template<typename... T, typename> constexpr ZenithOS::ProgramList::StaticCommandList<size>::StaticCommandList(T... values) : commands{ values... } {}
template<ZenithOS::int_z size> constexpr ZenithOS::ProgramList::StaticCommandList<size>::StaticCommandList<size>(std::initializer_list<ZenithOS::ProgramList::Command> list) {
	if (list.size() <= size) {
		static_assert(false, "Command list size cannot be greater than the maximum command list size");
	}
	actualSize = list.size();
	for (int i = 0; i < actualSize; i++)
		commands[i] = list[i];
}


//interface implementation
template<ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::StaticCommandList<size>::getCommandIndex(const char* name) const {
	int_z index;
	for (index = 0; index < actualSize && std::strcmp(name, commands[index].name); index++);
	if (index == actualSize) return -1;
	return index;
}
template<ZenithOS::int_z size> const char* ZenithOS::ProgramList::StaticCommandList<size>::getArgumentsList(ZenithOS::int_z commandIndex) const {
	if (commandIndex < 0 || commandIndex >= actualSize) return nullptr;
	return commands[commandIndex].args;
}
template<ZenithOS::int_z size> const char* (*ZenithOS::ProgramList::StaticCommandList<size>::getFunction(ZenithOS::int_z commandIndex) const)(ZenithOS::Interpreter::Token*) {
	if (commandIndex < 0 || commandIndex >= actualSize) return nullptr;
	return commands[commandIndex].function;
}