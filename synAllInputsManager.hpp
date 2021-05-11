#pragma once 
#include "synInputsManager.hpp"

#include <unordered_set>

class synAllInputsManager {
	synInputsManager<Signal> signals;
	synInputsManager<SingleSampleEffect> single_sample_effects;
	synInputsManager<WholeSampleEffect> whole_sample_effects;

	template<class InputType>
	synInputsManager<InputType>* get_set_of_type() {}

public:
	template<class InputType>
	void insert(std::string name, InputType* output);

	template<class InputType>
	void erase(std::string name);

	template<class InputType>
	synInput<InputType>* get_new_input(wxWindow*, wxWindowID, InputType**, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);

	template<class InputType>
	void free_input(synInput<InputType>*);
};
