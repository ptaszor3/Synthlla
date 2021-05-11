#pragma once
#include "synInput.hpp"

#include <string>
#include <map>
#include <vector>
#include <unordered_set>

template<class InputType>
class synInputsManager {
	std::map<std::string, InputType*> outputs;
	std::unordered_set<synInput<InputType>*> inputs;
public:
	void insert(std::string, InputType*);
	void erase(std::string);
	synInput<InputType>* get_new_input(wxWindow*, wxWindowID, InputType** destination, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	void free(synInput<InputType>*);
};
