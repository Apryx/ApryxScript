#include "Decorator.h"

#include "ast/Statement.h"
#include "ast/Expression.h"

namespace apryx {

	std::shared_ptr<ApryxNamespace> Decorator::decorate(std::shared_ptr<CompilationUnit> unit)
	{
		// There should be a root namespace
		auto nms = std::make_shared<ApryxNamespace>();

		// TODO add the builtin types (other module)

		for (auto statement : unit->m_Statements) {
			if (auto stStatement = std::dynamic_pointer_cast<StructureStatement>(statement)) {

				auto type = std::make_shared<ApryxType>();

				// Double name yay
				// TODO extract the name and other properties from the name
				type->m_Name = stStatement->m_Name->m_Name;

				nms->m_Types.push_back(type);
			}
		}
		
		// Functions second
		for (auto statement : unit->m_Statements) {
			if (auto fnStatement = std::dynamic_pointer_cast<FunctionStatement>(statement)) {
				
				auto fn = std::make_shared<ApryxFunction>();

				fn->m_Name = fnStatement->m_Name;

				nms->m_Functions.push_back(fn);
			}
		}
	}

}
