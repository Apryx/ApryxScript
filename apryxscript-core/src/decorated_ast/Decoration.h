#pragma once

#include "Type.h"
#include "ApryxNamespace.h"

namespace apryx {
	struct Decoration {
		Type m_Type;				//The type

		ApryxNamespace *m_Scope;	//Scope it belongs to
		bool m_Static;				//For example in class scopes, this would be false
	};
}