#pragma once

#include <string>
#include <memory>

namespace apryx {

	class Expression;

	class Statement {
	protected:
		Statement() {};
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


	class Block : public Statement {
	public:
		virtual std::string toString();
	};

	class Context : public Statement {
	public:
		virtual std::string toString();
		
		//TODO refactor this to a better place?
		virtual void performOperator(class VMWriter &, const std::string &op);			//TODO both types ofc
		virtual void performPrefixOperator(class VMWriter &, const std::string &op);		//TODO the one type ofc
	};

	class Structure : public Statement {
	public:
		virtual std::string toString() = 0;
	};

}