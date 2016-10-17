#pragma once

#include <string>
#include <memory>

namespace apryx {

	class Expression;

	class Statement {
	protected:
		Statement() {}; //TODO delete this
		virtual ~Statement()  = default;
	public:
		virtual std::string toString() = 0;
	};

	class Function : public Statement {
	public:
		virtual std::string toString() = 0;
	};

	class Variable : public Statement {
	public:
		std::string m_Name;
		std::string m_Type;
		std::shared_ptr<Expression> m_InitialValue;

		virtual std::string toString();
		bool isValid() { return m_Type.size() > 0 || m_InitialValue != nullptr; }
	};

	class Structure : public Statement {
	public:
		virtual std::string toString() = 0;
	};

	class Context : public Statement{
	public:
		virtual std::string toString() = 0;
	};
}