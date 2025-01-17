#pragma once
#include "Types.h"

namespace ZenithOS {
	class BasicBuffer {
	public:
		virtual uint_z size() = 0;
		virtual char& operator[](int_z) = 0;
		virtual char& at(int_z) = 0;
		virtual void copy(char*, int_z, int_z) = 0;
	};
}