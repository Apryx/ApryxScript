#pragma once

#include "Type.h"
#include "Scope.h"

namespace apryx {
	struct Decoration {
		Type m_Type;
		Scope *m_Scope;
	};
}