#include "VSBuffer.h"
#include "ConsoleToken.h"
#include "Types.h"
#include <iostream>
using namespace TestOS;
using namespace ZenithOS;
using namespace ZenithOS::Interpreter;
TestOS::VSBuffer buffer;
Token token;

char printBuffer[64];

int main() {
	Token::setTokenBuffer(&buffer);
	while (1) {
		buffer.loadFromIOStream();
		int_z i;
		for (i = 0; buffer[i] != '\n'; i++);
		std::cout << "Location of Newline" << i << std::endl;
		i--;
		while(!token.extract(i)) {
			/*
			std::cout << "Location of end of token" << i << std::endl;
			std::cout << "Character: " << buffer[i+1] << std::endl;
			*/
			if (token.setInterpretation(TokenTypes::FloatData)) {
				std::cout << "found a float" << std::endl;
				std::cout << "Token Value: " << token.getFloatData() << std::endl;
			}
			if (token.setInterpretation(TokenTypes::signedData)) {
				std::cout << "found a signed" << std::endl;
				std::cout << "Token Value: " << token.getSignedData() << std::endl;
			}
			if (token.setInterpretation(TokenTypes::unsignedData)) {
				std::cout << "found an unsigned" << std::endl;
				std::cout << "Token Value: " << token.getUnsignedData() << std::endl;
			}
			if (token.setInterpretation(TokenTypes::StringData)) {
				std::cout << "found a string" << std::endl;
				token.copyStringData(printBuffer, 64);
				std::cout <<"Token Value: " << printBuffer << std::endl;
			}
			if (token.setInterpretation(TokenTypes::WordData)) {
				std::cout << "found a word" << std::endl;
				token.copyStringData(printBuffer, 64);
				std::cout << "Token Value: " << printBuffer << std::endl;
			}
			std::cout << std::endl;
		}
		/*
		std::cout << "Location of end of token" << i << std::endl;
		std::cout << "Character: " << buffer[i+1] << std::endl;
		*/
		if (buffer[i] == '>') std::cout << "Valid" << std::endl;
		else std::cout << "Invalid" << std::endl;
	}
}

