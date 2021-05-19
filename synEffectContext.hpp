#pragma once

#include "synEffectRepresentation.hpp"
#include "synEffectInputsManager.hpp"

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <vector>
#include <map>

extern synEffectInputsManager effect_manager;

template <class SampleType>
class synEffectContext :public wxWindow {
	wxButton* add_effect_button;
	wxStaticText* title;

	std::vector<SampleType*>* effects;
	std::map<wxWindowID, unsigned int> id_to_position;
	std::vector<synEffectRepresentation*> representations;

	unsigned int next_unused_id{10};

	void OnRemove(wxCommandEvent&);
	void OnUp(wxCommandEvent&);
	void OnDown(wxCommandEvent&);

	void OnAdd(wxCommandEvent&);

	void repaint();
public:
	void add_effect(std::string title, SampleType* effect);
	synEffectContext(wxWindow* parent, wxWindowID id, std::vector<SampleType*>*, std::string, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
};

//extern template class synEffectContext<SingleSampleEffect>;
//extern template class synEffectContext<WholeSampleEffect>;
