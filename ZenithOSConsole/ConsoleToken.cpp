#include "ConsoleToken.h"

using namespace ZenithOS::Interpreter;
using namespace ZenithOS;

//implementation of static TokenBuffer interface---------------
BasicBuffer* Token::TokenBuffer = nullptr;
void Token::setTokenBuffer(BasicBuffer* buffer) {
	TokenBuffer = buffer;
}

//implementation of command interface--------------------------
bool Token::copyStringData(char* buffer, uint_z size) const {
	uint_z start = data.strData.start, end = data.strData.end;
	if (end - start >= size) {
		//error buffer too small
		return true;
	}
	TokenBuffer->copy(buffer, start, end);
	buffer[end - start] = '\0';
	return false;
}

float_z Token::getFloatData() const {
	return data.floatData;
}

uint_z Token::getUnsignedData() const {
	return data.unsignedData;
}

int_z Token::getSignedData() const {
	return data.signedData;
}

//implementation of console interface--------------------------

bool Token::setInterpretation(TokenTypes type) {
	if (static_cast<uint_z>(type) & interpretations) {
		switch (type) {
		case TokenTypes::unsignedData:
			interpretUnsignedData();
			break;
		case TokenTypes::signedData:
			interpretSignedData();
			break;
		case TokenTypes::FloatData:
			interpretFloatData();
			break;
		case TokenTypes::StringData:
			interpretStringData();
			break;
		case TokenTypes::WordData:
			interpretWordData();
			break;
		}
		return true;
	}
	else
		return false;
}

bool Token::extract(int_z& pos) {
	//clear white space
	for (; isWhiteSpace(TokenBuffer->at(pos)); pos--);
	//save end of token
	int_z end = pos + 1;
	//check for newline (\n) or command start (>)
	if (isStopCharacter(TokenBuffer->at(pos))) return true;
	int_z start;
	interpretations = static_cast<uint_z>(TokenTypes::Empty);
	if (TokenBuffer->at(pos) == '"') { //string token
		end = pos;
		pos--;
		for (; TokenBuffer->at(pos) != '"'; pos--);
		if (end == (pos % TokenBuffer->size() + TokenBuffer->size()) % TokenBuffer->size()) return true;
		start = pos + 1;
		pos--;
		setInterpretationRange(start, end);
		checkStringData();
	}
	else { //non-string token
		//find begining of token
		for (; !isEndCharacter(TokenBuffer->at(pos)); pos--);
		start = pos + 1;
		setInterpretationRange(start, end);
		checkUnsignedData();
		checkSignedData();
		checkFloatData();
		checkWordData();
	}
	return false;
}

//private implementation functions-----------------------------

void Token::setInterpretationRange(uint_z start, uint_z end) {
	data.strData.start = start;
	data.strData.end = end;
}

//interpretations for each type----------------

/* unsigned formats
* Decimal: 12345
* Hex: 0x43F2Ea02
* Binary 0b01001011
*/
void Token::interpretUnsignedData() {
	interpretations = static_cast<uint_z>(TokenTypes::Empty);
	int_z start = data.strData.start;
	int_z end = data.strData.end;
	uint_z value = 0;
	//Decimal Case
	int_z i;
	for (i = start; i < end && isNumeric(TokenBuffer->at(i)); i++)
		value += powerOfTen_u(end - start - 1 - (i -start)) * numberValue_u(TokenBuffer->at(i));
	if (i == end) {
		data.unsignedData = value;
		interpretations |= static_cast<uint_z>(TokenTypes::unsignedData);
		return;
	}
	//Hex case
	value = 0;
	if (end - start > 1 && TokenBuffer->at(start) == '0' && TokenBuffer->at(start + 1) == 'x') {
		for (i = start + 2; i < end && isHex(TokenBuffer->at(i)); i++)
			value += numberValue_u(TokenBuffer->at(i)) << ((end - (start + 2) - 1 - (i - (start + 2))) << 2);
		if (i == end) {
			data.unsignedData = value;
			interpretations |= static_cast<uint_z>(TokenTypes::unsignedData);
			return;
		}
	}
	//Binary
	value = 0;
	if (end - start > 1 && TokenBuffer->at(start) == '0' && TokenBuffer->at(start + 1) == 'b') {
		for (i = start + 2; i < end && isBinary(TokenBuffer->at(i)); i++)
			value += numberValue_u(TokenBuffer->at(i)) << (end - (start+2) - 1 - (i - (start+2)));
		if (i == end) {
			data.unsignedData = value;
			interpretations |= static_cast<uint_z>(TokenTypes::unsignedData);
			return;
		}
	}
}
void Token::interpretSignedData() {
	interpretations = static_cast<uint_z>(TokenTypes::Empty);
	int_z start = data.strData.start;
	int_z end = data.strData.end;
	int_z i;
	int_z value = 0;
	//negative case
	if (TokenBuffer->at(start) == '-') {
		for (i = start + 1; i < end && isNumeric(TokenBuffer->at(i)); i++) {
			value += powerOfTen_s(end - start - 2 - (i - start-1)) * numberValue_s(TokenBuffer->at(i));
		}
		if (i == end) {
			data.signedData = -value;
			interpretations |= static_cast<int_z>(TokenTypes::signedData);
			return;
		}
	}
	else {
		//positive case
		value = 0;
		for (i = start; i < end && isNumeric(TokenBuffer->at(i)); i++)
			value += powerOfTen_s(end - start - 1 - (i - start)) * numberValue_s(TokenBuffer->at(i));
		if (i == end) {
			data.signedData = value;
			interpretations |= static_cast<int_z>(TokenTypes::signedData);
			return;
		}
	}
}
void Token::interpretWordData() {
	interpretations = static_cast<uint_z>(TokenTypes::WordData);
}
void Token::interpretStringData() {
	interpretations = static_cast<uint_z>(TokenTypes::StringData);
}
void Token::interpretFloatData() {
	interpretations = static_cast<uint_z>(TokenTypes::Empty);
	int_z start = data.strData.start;
	int_z end = data.strData.end;
	float_z value = 0;
	bool neg = false;
	if (TokenBuffer->at(start) == '-') {
		neg = true;
		start++;
	}
	int_z i;
	for (i = start; i < end && isNumeric(TokenBuffer->at(i)); i++);
	if (i == end) {//no decimal point case
		for (i = start; i<end; i++)
			value += powerOfTen_f(end - start - 1 - (i - start)) * numberValue_s(TokenBuffer->at(i));
		if (neg) value = -value;
		data.floatData = value;
		interpretations |= static_cast<uint_z>(TokenTypes::FloatData);
		return;
	}
	else if (TokenBuffer->at(i) == '.') {//decimal point case
		uint_z decimalPoint = i;
		//before decimal point
		for(uint_z j = start; j<decimalPoint; j++)
			value += powerOfTen_f(decimalPoint - start - 1 - (j - start)) * numberValue_s(TokenBuffer->at(j));
		//after decimal point
		for (i++; i < end && isNumeric(TokenBuffer->at(i)); i++)
			value += powerOfTen_f(decimalPoint - i) * numberValue_s(TokenBuffer->at(i));
		if (i == end) {
			if (neg) value = -value;
			data.floatData = value;
			interpretations |= static_cast<uint_z>(TokenTypes::FloatData);
			return;
		}
	}
}

//checks for each type-------------------------
void Token::checkUnsignedData() {
	int_z start = data.strData.start;
	int_z end = data.strData.end;
	//decimal case
	int_z i;
	for (i = start; i < end && isNumeric(TokenBuffer->at(i)); i++);
	if (end == i) {
		interpretations |= static_cast<uint_z>(TokenTypes::unsignedData);
		return;
	}
	//hex case
	if (end - start > 1 && TokenBuffer->at(start) == '0' && TokenBuffer->at(start + 1) == 'x') {
		for (i = start + 2; i < end && isHex(TokenBuffer->at(i)); i++);
		if (i == end) {
			interpretations |= static_cast<uint_z>(TokenTypes::unsignedData);
			return;
		}
	}
	//binary case
	if (end - start > 1 && TokenBuffer->at(start) == '0' && TokenBuffer->at(start + 1) == 'b') {
		for (i = start + 2; i < end && isBinary(TokenBuffer->at(i)); i++);
		if (i == end) {
			interpretations |= static_cast<uint_z>(TokenTypes::unsignedData);
			return;
		}
	}
}
void Token::checkSignedData() {
	int_z start = data.strData.start;
	int_z end = data.strData.end;
	int_z i;
	//negative case
	if (TokenBuffer->at(start) == '-') {
		for (i = start + 1; i < end && isNumeric(TokenBuffer->at(i)); i++);
		if (i == end) {
			interpretations |= static_cast<int_z>(TokenTypes::signedData);
			return;
		}
	}
	else {
		//positive case
		for (i = start; i < end && isNumeric(TokenBuffer->at(i)); i++);
		if (i == end) {
			interpretations |= static_cast<int_z>(TokenTypes::signedData);
			return;
		}
	}
}
void Token::checkWordData() {
	interpretations |= static_cast<uint_z>(TokenTypes::WordData);
}
void Token::checkStringData() {
	interpretations |= static_cast<uint_z>(TokenTypes::StringData);
}
void Token::checkFloatData() {
	int_z start = data.strData.start;
	int_z end = data.strData.end;
	bool neg = false;
	if (TokenBuffer->at(start) == '-') {
		neg = true;
		start++;
	}
	int_z i;
	for (i = start; i < end && isNumeric(TokenBuffer->at(i)); i++);
	if (i == end) {
		interpretations |= static_cast<uint_z>(TokenTypes::FloatData);
		return;
	}
	else if (TokenBuffer->at(i) == '.') {
		for (i++; i < end && isNumeric(TokenBuffer->at(i)); i++);
		if (i == end) {
			interpretations |= static_cast<uint_z>(TokenTypes::FloatData);
			return;
		}
	}
}

//statics--------------------------------------
bool Token::isEndCharacter(char c) {
	if (isWhiteSpace(c) || c == '>' || c == '\n' || c == '"') return true;
	return false;
}

bool Token::isStopCharacter(char c) {
	if (c == '\n' || c == '>') return true;
	return false;
}

bool Token::isWhiteSpace(char c) {
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f') return true;
	return false;
}

bool Token::isNumeric(char c) {
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool Token::isHex(char c) {
	if (isNumeric(c) || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F') return true;
	return false;
}

bool Token::isBinary(char c) {
	if (c == '1' || c == '0') return true;
	return false;
}

uint_z Token::powerOfTen_u(uint_z n) {
	uint_z value = 1;
	for (int_z i = 0; i < n; i++)
		value *= 10;
	return value;
}

int_z Token::powerOfTen_s(uint_z n) {
	int_z value = 1;
	for (int_z i = 0; i < n; i++)
		value *= 10;
	return value;
}
float_z Token::powerOfTen_f(int_z n) {
	float_z value = 1;
	if (n < 0) {
		for (int_z i = 0; i < (-1 * n); i++)
			value *= 1.0 / 10;
	}
	else {
		for (int_z i = 0; i < n; i++)
			value *= 10;
	}
	return value;
}

uint_z Token::numberValue_u(char c) {
	uint_z value;
	if (c >= '0' && c <= '9')
		value = c - '0';
	else if (c >= 'a' && c <= 'f')
		value = c - 'a' + 10;
	else
		value = c - 'A' + 10;
	return value;
}

int_z Token::numberValue_s(char c) {
	return c - '0';
}
