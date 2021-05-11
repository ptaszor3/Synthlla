#pragma once

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <exception>

class synEffectInput :public wxChoice {
	std::map<std::string, SingleSampleEffect*> single_sample_effects;
	std::map<std::string, WholeSampleEffect*> whole_sample_effects;
	Instrument* destination;
	union {
		SingleSampleEffect* single_sample_effect;
		WholeSampleEffect* whole_sample_effect;
	} last;
	enum {
		SINGLE_SAMPLE_EFFECT,
		WHOLE_SAMPLE_EFFECT,
		NONE
	} last_choice_type;
public:
	synEffectInput(wxWindow* parent, wxWindowID, Instrument* c_destination, wxPoint position = wxDefaultPosition, wxSize = wxDefaultSize);

	void insert(std::string, SingleSampleEffect*);
	void insert(std::string, WholeSampleEffect*);
	void erase_single_sample_effect(std::string);
	void erase_whole_sample_effect(std::string);
	void OnChoice(wxCommandEvent&);

	class NameHasAlreadyBeenInserted_exception {
	public:
		const char* what() const noexcept {return "The given name has already been used";}
	};
};
