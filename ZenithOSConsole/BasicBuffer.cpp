#include "BasicBuffer.h"

using namespace ZenithOS;

//itterator implementation---------------------
BasicBuffer::Itterator::Itterator(BasicBuffer* buffer, int_z n) : buffer(buffer) {
	pos = (n % buffer->size() + buffer->size()) % buffer->size();
}

char& BasicBuffer::Itterator::operator*() {
	return buffer->at(pos);
}

BasicBuffer::Itterator& BasicBuffer::Itterator::operator++() {
	pos = (pos+1) % buffer->size();
}

BasicBuffer::Itterator& BasicBuffer::Itterator::operator--() {
	pos = ((pos-1) % buffer->size() + buffer->size()) % buffer->size();
}

BasicBuffer::Itterator& BasicBuffer::Itterator::operator+=(int_z n) {
	pos = ((pos + n) % buffer->size() + buffer->size()) % buffer->size();
}

BasicBuffer::Itterator& BasicBuffer::Itterator::operator-=(int_z n) {
	pos = ((pos - n) % buffer->size() + buffer->size()) % buffer->size();
}

bool BasicBuffer::Itterator::operator==(const BasicBuffer::Itterator& other) const {
	return this->buffer == other.buffer && this->pos == other.pos;
}

bool BasicBuffer::Itterator::operator!=(const BasicBuffer::Itterator& other) const {
	return this->buffer != other.buffer || this->pos != other.pos;
}

//Basic buffer itterator functions-------------
BasicBuffer::Itterator BasicBuffer::itterator(int_z n) {
	return Itterator(this, (n % size() + size()) % size());
}