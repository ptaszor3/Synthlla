#pragma once
#include "synEffectInput.hpp"

#include <wx/wx.h>
#include "../Synthall/Synthall"
#include <unordered_set>
#include <exception>

class synEffectInputsManager {
	std::map<std::string, SingleSampleEffect*> single_sample_effects;
	std::map<std::string, WholeSampleEffect*> whole_sample_effects;
	std::unordered_set<synEffectInput<SingleSampleEffect>*> single_sample_inputs;
	std::unordered_set<synEffectInput<WholeSampleEffect>*> whole_sample_inputs;
public:
	void insert(std::string, SingleSampleEffect*);
	void insert(std::string, WholeSampleEffect*);
	void erase_single_sample_effect(std::string);
	void erase_whole_sample_effect(std::string);
	synEffectInput<SingleSampleEffect>* get_new_single_sample_input(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
	synEffectInput<WholeSampleEffect>* get_new_whole_sample_input(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
	void free_input(synEffectInput<SingleSampleEffect>* to_be_freed);
	void free_input(synEffectInput<WholeSampleEffect>* to_be_freed);

	class NameHasAlreadyBeenUsed_exception {
	public:
		const char* what() const noexcept {return "The given name has already been used";}
	};
};
