#include "VSBuffer.h"
#include <iostream>

using namespace ZenithOS;
using namespace TestOS;

//implementation of interface------------------

uint_z VSBuffer::size() {
	return VSBufferSize;
}
char& VSBuffer::operator[](int_z n) {
	int_z m = (n % size() + size()) % size();
	return buffer[m];
}
char& VSBuffer::at(int_z n) {
	int_z m = (n % size() + size()) % size();
	return buffer[m];
}
void VSBuffer::copy(char* newBuffer, int_z n, int_z m) {
	for (int_z i = n; i < m; i++)
		newBuffer[i - n] = at(i);
}

void VSBuffer::loadFromIOStream() {
	std::cin.getline(buffer, VSBufferSize);
	int_z i;
	for (i = 0; i < size() && buffer[i] != '\0'; i++);
	if (i == size()) buffer[0] = '\n';
	else buffer[i] = '\n';
}