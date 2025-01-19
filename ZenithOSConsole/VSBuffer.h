#pragma once
#include "BasicCircularBuffer.h"

#define VSBufferSize 128

namespace TestOS {

	class VSBuffer : public ZenithOS::BasicBuffer {
		char buffer[128];
	public:
		ZenithOS::uint_z size() override;
		char& operator[](ZenithOS::int_z) override;
		char& at(ZenithOS::int_z) override;
		void copy(char*, ZenithOS::int_z, ZenithOS::int_z) override;
		void loadFromIOStream();
	};
}
