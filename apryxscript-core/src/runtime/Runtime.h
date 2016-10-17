#pragma once

#include <memory>
#include <map>
#include <string>

namespace apryx {

	class Statement;
	class Expression;
	struct ApryxObject;

	class Runtime {
	private:
		std::map<std::string, std::shared_ptr<ApryxObject>> m_Variables;
	public:
		Runtime() = default;
		~Runtime() = default;

		void evaluate(std::shared_ptr<Statement> statement);
	protected:
		std::shared_ptr<ApryxObject> evaluate(std::shared_ptr<Expression> exp);
	};

}