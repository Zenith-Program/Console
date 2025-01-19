#include "ZenithOSCommandList.h"
#include "ZenithOSProgramErrorCodes.h"
#include <cstring>
#include <iostream>

#define RunBit (1 << 0)

//program data initialization
template <ZenithOS::int_z size> constexpr ZenithOS::ProgramList::ProgramList<size>::ProgramList() : programs(initProgramData(std::make_index_sequence<size>())), currentThread(-1) {}

template <ZenithOS::int_z size> template<std::size_t... I> constexpr std::array<ZenithOS::ProgramList::ProgramData, size> ZenithOS::ProgramList::ProgramList<size>::initProgramData(std::index_sequence<I...> a) {
	return { ProgramData{ProgramName<I>, &ProgramStartup<I>, &ProgramLoop<I>, &ProgramShutdown<I>, ProgramCommandList<I>, ProgramPriority<I>, 0 }... };
}

//program execution

template <ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::ProgramList<size>::startProgram(ZenithOS::int_z programIndex) {
	if (programIndex < 0 || programIndex >= size) return ZenithOS_ProgramError_DoesNotExist;
	if (isRunning(programIndex)) return ZenithOS_ProgramError_AlreadyRunning;
	ZenithOS::int_z previousThread = currentThread;
	currentThread = programIndex;
	ZenithOS::int_z errorCode = programs[programIndex].Startup();
	currentThread = previousThread;
	programs[programIndex].status |= RunBit;
	return errorCode;
}
template <ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::ProgramList<size>::stopProgram(ZenithOS::int_z programIndex) {
	if (programIndex < 0 || programIndex >= size) return ZenithOS_ProgramError_DoesNotExist;
	if (!isRunning(programIndex)) return ZenithOS_ProgramError_NotRunning;
	programs[programIndex].status &= ~RunBit;
	ZenithOS::int_z previousThread = currentThread;
	currentThread = programIndex;
	ZenithOS::int_z errorCode = programs[programIndex].Shutdown();
	currentThread = previousThread;
	return errorCode;
}

template <ZenithOS::int_z size> void ZenithOS::ProgramList::ProgramList<size>::runActiveLoops() {
	for (int_z index = 0; index < size; index++) {
		if (isRunning(index)) {
			ZenithOS::int_z previousThread = currentThread;
			currentThread = index;
			programs[index].Loop();
			currentThread = previousThread;
		}
	}
}

template <ZenithOS::int_z size> bool ZenithOS::ProgramList::ProgramList<size>::isRunning(ZenithOS::int_z programIndex) const {
	if (programIndex < 0 || programIndex >= size) return false;
	return programs[programIndex].status & RunBit;
}



//program information
template <ZenithOS::int_z size> const ZenithOS::ProgramList::CommandList* ZenithOS::ProgramList::ProgramList<size>::getProgramCommandList(ZenithOS::int_z programIndex) const {
	if (programIndex < 0 || programIndex >= size) return nullptr;
	return programs[programIndex].commandList;
}
template <ZenithOS::int_z size> ZenithOS::uint_z ZenithOS::ProgramList::ProgramList<size>::getProgramPriority(ZenithOS::int_z programIndex) const {
	if (programIndex < 0 || programIndex >= size) return -1;
	return programs[programIndex].priority;
}
template <ZenithOS::int_z size> const char* ZenithOS::ProgramList::ProgramList<size>::getProgramName(ZenithOS::int_z programIndex) const {
	if (programIndex < 0 || programIndex >= size) return nullptr;
	return programs[programIndex].name;
}
template <ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::ProgramList<size>::getProgramIndex(const char* name) const {
	ZenithOS::int_z index = 0;
	for (index = 0; index < size && std::strcmp(name, programs[index].name); index++);
	if (index == size) return -1;
	return index;
}



//thread information
template <ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::ProgramList<size>::getCurrentThread() const {
	return currentThread;
}
template <ZenithOS::int_z size> ZenithOS::int_z ZenithOS::ProgramList::ProgramList<size>::setCurrentThread(ZenithOS::int_z thread) {
	if (thread >= 0 || thread < size) {
		currentThread = thread;
		return ZenithOS_ProgramError_NoError;
	}
	return ZenithOS_ProgramError_DoesNotExist;
}
template <ZenithOS::int_z size> ZenithOS::uint_z ZenithOS::ProgramList::ProgramList<size>::getCurrentThreadPriority() const {
	return programs[currentThread].priority;
}

ZenithOS::ProgramList::ProgramLedger& ZenithOS::ProgramList::getProgramList() {
	static ZenithOS::ProgramList::ProgramLedger instance;
	return instance;
}

#undef RunBit