#include "ConsoleInterpreter.h"

using namespace ZenithOS::Interpreter;
//constructor----------------------------------
ConsoleInterpreter::ConsoleInterpreter() : workingBuffer(nullptr), workingList(nullptr) {}
 //singleton getter----------------------------
ConsoleInterpreter& ConsoleInterpreter::get() {
	static ConsoleInterpreter instance;
	return instance;
}

//implementation-------------------------------
/*Console command protocol---------------------
* a line that begins with a > character is trated as a command. all other transmissions are ignored.
* ex: (first two lines are trated as commands, 3rd is ignored)
* >StartPrgm program1
* > StopPrgm program1
* StartPrgm program2
* 
* parsing process:
* 1) working buffer is searched for a newline character
* 2) moving backward in the buffer, tokens are extracted and their possible interpretations are saved in the token buffer
* 3) when the > or \n character is encountered, token extraction stops. the buffer is traeted as circular
* 4) if > the penultimate token is treated as the command string and the working command list is searched, otherwise the transmission is ignored
* 5) if the command is found, the previous tokens are checked to be interpratable as the types the command requires
* 6) the execute function for the command is called with the token data if it is valid
* if an invalid command is discovered, an eror message is transmitted
* 
* ex:
* >ExampleCommand "a b" 0xFF text 3 2.5
* 
* |tokenization-------------------------------------------------------------------------------------------------------------------------|
* | token:			| '\n'		| '2.5'			| '3'				| 'text'	| '0xFF'	| '"a b"'	| 'ExampleCommand'	| '>'		|
* | interpretations:| endline	| float, word	| int, float, word	| word		| int, word	| string	| word				| command	|
* | pos in buffer:	| 0			| 1				| 2					| 3			| 4			| 5			| 6					| 7			|
* |-------------------------------------------------------------------------------------------------------------------------------------|
* If the command ExampleCommand takes paramaters (string, int, word, int, float) it will be executed, as the tokens can be interpreted as these types
* Alternatively, if ExampleCommand takes (word, float, string, int) execution will fail because the tokens cannot be interpreted as the required types
* 
* Token Types:
* endline - '\n' character. Does not need to be surrounded by whitespace
* command - '>' character. Does not need to be surrounded by whitespace
* int - integer data. numerical characters with '-' sign, hex, or binary (ex. 3, -45, 0xA5, 0b0110)
* float - decimal number data. numbers with decimal point (ex. 3, 3.0, -0.175)
* word - a string of characters with no spaces. (ex. hello)
* string - a string of characters enclosed in ". anyhting enclosed in " can only be interpreted as a string
*/
void ConsoleInterpreter::handleLine() {
	Token::setTokenBuffer(workingBuffer);
	uint32_t lineEnd = 0;
	while (workingBuffer->at(lineEnd) != '\n' && lineEnd < workingBuffer->size()) lineEnd++;
	if (lineEnd == workingBuffer->size() && lineEnd != '\n') {
		//no line
	}
	uint32_t currentToken = 0;
	while()





}
void ConsoleInterpreter::setWorkingBuffer(BasicBuffer* buffer) {
	workingBuffer = buffer;
}
void ConsoleInterpreter::setWorkingCommandList(const CommandList& list) {
	workingList = &list;
}