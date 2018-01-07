#pragma once

#include <vector>

namespace apryx {

	class ByteStack {
		std::vector<uint8_t> m_Data;
	public:
		void pushInt(int i);
		int popInt();

		bool empty();
		size_t height();

		void pushUByte(uint8_t byte);
		uint8_t popUByte();
	};

}