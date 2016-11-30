#pragma once

#include "AccessModifier.h"
#include "Type.h"

namespace apryx {

	struct ApryxVariable {
		std::string m_Name;
		Type m_Type;

		AccessModifier m_Access;
		bool m_Static;
	};

}