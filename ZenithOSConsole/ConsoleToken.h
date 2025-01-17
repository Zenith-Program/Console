#pragma once
#include "types.h"
#include "BasicBuffer.h"
namespace ZenithOS {
	// Testing purposes ignore comment
	// Added 1 more comment for testing
	namespace Interpreter {
		struct StrPos {
			int_z start;
			int_z end;
		};
		union TokenData {
			uint_z unsignedData;
			int_z signedData;
			float_z floatData;
			StrPos strData;
		};
		enum class TokenTypes : uint_z {
			Empty = 0, unsignedData = 1, signedData = (1 << 1), FloatData = (1 << 2), StringData = (1 << 3), WordData = (1 << 4)
		};
		
		
		class Token {
			TokenData data;
			uint_z interpretations;
			static BasicBuffer* TokenBuffer;
		public:
			//usage in a command---------------
			bool copyStringData(char*, uint_z) const;
			uint_z getUnsignedData() const;
			int_z getSignedData() const;
			float_z getFloatData() const;
			//usage in console interpreter-----
			bool extract(int_z&);
			bool setInterpretation(TokenTypes);
		public:
			static void setTokenBuffer(BasicBuffer*);
		private:
			static bool isEndCharacter(char);
			static bool isStopCharacter(char);
			static bool isWhiteSpace(char);
			static bool isNumeric(char);
			static bool isHex(char);
			static bool isBinary(char);
			static uint_z powerOfTen_u(uint_z);
			static int_z powerOfTen_s(uint_z);
			static float_z powerOfTen_f(int_z);
			static uint_z numberValue_u(char);
			static int_z numberValue_s(char);

			void setInterpretationRange(uint_z, uint_z);

			void interpretUnsignedData();
			void interpretSignedData();
			void interpretWordData();
			void interpretStringData();
			void interpretFloatData();

			void checkUnsignedData();
			void checkSignedData();
			void checkWordData();
			void checkStringData();
			void checkFloatData();

		};
	}
}
