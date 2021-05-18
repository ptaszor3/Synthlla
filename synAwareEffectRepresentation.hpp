#pragma once

#include "synEffectRepresentation.hpp"

struct synAwareEffectRepresentation {
	unsigned int position;
	synEffectRepresentation* representation;
	wxWindowID id;
}
