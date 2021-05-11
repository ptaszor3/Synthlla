#pragma once
#include "synInput.hpp"

#include <wx/wx.h>
#include "../Synthall/Synthall"
#include <unordered_set>

class synEffectInputsManager {
	unordered_set<SingleSampleEffect*> single_sample_effects;
	unordered_set<WholeSampleEffect*> whole_sample_effects;
public:
	void insert(std::string, SingleSampleEffect*);
	void insert(std::string, WholeSampleEffect*);
	template<class InputType>
	void erase(std::string);
	synInput<>
}
