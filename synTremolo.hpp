#pragma once
#include "synSynchronization.hpp"
#include "synEffectInputsManager.hpp"

#include <wx/wx.h>
#include "../Synthall/Synthall"

extern synEffectInputsManager effect_manager;

class synTremolo :public effects::Tremolo , public wxWindow {
	synSlider* max_volume_deviation_slider;
	synSlider* frequency_slider;
	synSignalInput* signal_input;
	synSynchronization* synchronization_box;
public:
	synVibrato(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize)
	:wxWindow{parent, id, position, size}, Vibrato{signal_manager.get_default_signal(), 5, effects::SynchronizationType::Synchronized, 0.3} {
		max_volume_deviation_slider = new synSlider(this, wxID_ANY, "Maximal influence", 0, 100, 30, reinterpret_cast<void*>(&this->maximal_volume_deviation), [](void* data, int value)->void{*reinterpret_cast<double*>(data) = value / 100.0);});
		frequency_slider = new synSlider(this, wxID_ANY, "Frequency (mHz)", 0, 1000, 500, reinterpret_cast<void*>(&this->frequency), [](void* data, int value)->void{*reinterpret_cast<double*>(data) = value / 1000.0;}, wxPoint(0, 90));
		signal_input = signal_manager.get_new_signal_input(this, wxID_ANY, &shape, "Shape", wxPoint(0, 180));
		synchronization_box = new synSynchronization(this, wxID_ANY, &synchronization_type, wxPoint(0, 255));
		effect_manager.insert("Tremolo", this);
	}
	~synVibrato() {
		signal_manager.free_input(signal_input);
		effect_manager.erase_single_sample_effect("Tremolo");
	}
	
};
