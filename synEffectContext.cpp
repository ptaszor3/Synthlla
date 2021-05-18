#include "synEffectContext.hpp"

#include <algorithm>

template<class SampleType>
void synEffectContext<SampleType>::add_effect(std::string title, SampleType* effect) {
	synEffectRepresentation* buffer = new synEffectRepresentation(this, next_unused_id, title, wxDefaultPosition);
	Bind(SYN_EFFECT_UP, &(this->OnDown), this, next_unused_id);
	Bind(SYN_EFFECT_DOWN, &(this->OnUp), this, next_unused_id);
	Bind(SYN_EFFECT_REMOVE, &(this->OnRemove), this, next_unused_id);

	id_to_position.insert({next_unused_id, effects->size()});
	representations.push_back(buffer);
	effects->push_back(effect);
	repaint();
	next_unused_id++;
}

template<class SampleType>
void synEffectContext<SampleType>::OnRemove(wxCommandEvent& event) {
	for(int i = 0; i < representations.size(); i++) {
		if(representations[i]->GetId() == event.GetId()) {
			auto buffor = representations[i];
			representations.erase(representations.begin() + i);
			Unbind(SYN_EFFECT_UP, &(this->OnDown), this, next_unused_id);
			Unbind(SYN_EFFECT_DOWN, &(this->OnUp), this, next_unused_id);
			Unbind(SYN_EFFECT_REMOVE, &(this->OnRemove), this, next_unused_id);
			//delete buffor;
			//The line above causes segmentation fault, I have no idea why, and at this point I'm more than happy to just leave it as it is.
			buffor->Hide();
			break;
		}
	}

	unsigned int position_of_effect_to_be_removed = id_to_position.at(event.GetId());

	effects->erase(effects->begin() + position_of_effect_to_be_removed);
	id_to_position.erase(event.GetId());
	
	for(auto& x : id_to_position) {
		if(x.second > position_of_effect_to_be_removed)
			x.second--;
	}

	repaint();
	event.Skip();
}

template<class SampleType>
void synEffectContext<SampleType>::OnUp(wxCommandEvent& event) {
	unsigned int current_position = id_to_position.at(event.GetId());

	if(current_position < effects->size() - 1) {
		for(auto& x : id_to_position) {
			if(x.second == current_position + 1) {
				x.second--;
				break;
			}
		}
		id_to_position.at(event.GetId())++;
		std::swap(effects->at(current_position), effects->at(current_position));
	}
	repaint();
	event.Skip();
}

template<class SampleType>
void synEffectContext<SampleType>::OnDown(wxCommandEvent& event) {
	unsigned int current_position = id_to_position.at(event.GetId());

	if(current_position > 0) {
		for(auto& x : id_to_position) {
			if(x.second == current_position - 1) {
				x.second++;
				break;
			}
		}
		id_to_position.at(event.GetId())--;
		std::swap(effects->at(current_position), effects->at(current_position));
	}
	repaint();
	event.Skip();
}

template<class SampleType>
void synEffectContext<SampleType>::repaint() {
	for(auto& representation : representations)
		representation->SetPosition(wxPoint(0, 45 + 115 * id_to_position.at(representation->GetId())));
}

template<class SampleType>
synEffectContext<SampleType>::synEffectContext(wxWindow* parent, wxWindowID id, std::vector<SampleType*>* c_effects, std::string section_title, wxPoint position, wxSize size) 
:wxWindow(parent, id, position, size, wxVSCROLL) {
	title = new wxStaticText(this, wxID_ANY, section_title, wxPoint(15, 15), wxSize(100, -1));
	add_effect_button = new wxButton(this, 9, "Add new...", wxPoint(115, 5));

	effects = c_effects;
	Bind(wxEVT_BUTTON, &(this->OnAdd), this, 9);
}

template<class SampleType>
void synEffectContext<SampleType>::OnAdd(wxCommandEvent& event) {
	event.Skip();
}

template class synEffectContext<SingleSampleEffect>;
template class synEffectContext<WholeSampleEffect>;
