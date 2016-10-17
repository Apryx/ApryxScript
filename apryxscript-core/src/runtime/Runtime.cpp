#include "Runtime.h"

#include "ast/Statement.h"
#include "ast/Expression.h"
#include "ApryxObject.h"

//TODO not use debugger for real logging, whatever
#include "debug/debug.h"

namespace apryx {

	void Runtime::evaluate(std::shared_ptr<Statement> statement)
	{
		if (auto exp = std::dynamic_pointer_cast<Expression>(statement)) {
			auto obj = evaluate(exp);
			if (obj) {
				LOG(obj->toString());
			}
			else {
				LOG("null");
			}
		}
		else if (auto var = std::dynamic_pointer_cast<Variable>(statement)) {
			if (m_Variables.find(var->m_Name) != m_Variables.end()) {
				LOG("Variable already defined");
				return;
			}

			std::shared_ptr<ApryxObject> value = std::make_shared<ApryxObject>("");

			if (var->m_InitialValue) {
				value = evaluate(var->m_InitialValue);
			}

			m_Variables.insert(std::make_pair(var->m_Name, value));
		}
		else {
			LOG("Unimplemented");
		}
	}


	std::shared_ptr<ApryxObject> Runtime::evaluate(std::shared_ptr<Expression> expression)
	{
		if (auto id = std::dynamic_pointer_cast<IdentiefierExpression>(expression)) {
			auto idVar = m_Variables.find(id->m_Identifier);

			if (idVar == m_Variables.end()) {
				LOG("Undefined variable " << id->m_Identifier);
				return nullptr;
			}

			return idVar->second;
		}
		else if (auto constant = std::dynamic_pointer_cast<ConstantExpression>(expression)) {
			return std::make_shared<ApryxObject>(constant->m_Constant);
		}
		else if (auto op = std::dynamic_pointer_cast<OperatorExpression>(expression)) {
			auto lhValue = evaluate(op->m_Lhs);
			auto rhValue = evaluate(op->m_Rhs);

			if (op->m_Operator == "=") {
				lhValue->assign(*rhValue);
				return rhValue;
			}
			if (op->m_Operator == "+") {
				auto out = std::make_shared<ApryxObject>("");

				float v1 = 0;
				float v2 = 0;

				if (toFloat(lhValue->m_Data, v1) && toFloat(rhValue->m_Data, v2)) {
					out->m_Data = toString(v1 + v2);
				}
				else {
					std::stringstream stream;
					stream << lhValue->m_Data;
					stream << rhValue->m_Data;

					out->m_Data = stream.str();
				}
				return out;
			}
			else {
				LOG("Unimplemented");
				return nullptr;
			}
		}
		else {
			LOG("Unimplemented!");
			return nullptr;
		}

		LOG("Unreachable code");
		assert(false);
		return nullptr;
	}
}
