#pragma once
#include "synSlider.hpp"
#include "synSignalInputsManager.hpp"
#include "synEffectInputsManager.hpp"

#include <wx/wx.h>
#include "../Synthall/Synthall"

extern synSignalInputsManager signal_manager;
extern synEffectInputsManager effect_manager;

class synSynchronizedVibrato :public wxWindow, public effects::SynchronizedVibrato {
	synSlider* max_time_deviation_slider;
	synSlider* frequency_slider;
	synSignalInput* signal_input;
public:
	synSynchronizedVibrato(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize)
	:wxWindow{parent, id, position, size}, SynchronizedVibrato{signal_manager.get_default_signal(), 5, 0.000500_ds}
	{
		max_time_deviation_slider = new synSlider(this, wxID_ANY, "Maximal influence", 0, 1000, 500, reinterpret_cast<void*>(&this->max_time_deviation), [](void* data, int value)->void{*reinterpret_cast<DoubleSeconds*>(data) = DoubleSeconds(value / 1000000000.0);});
		frequency_slider = new synSlider(this, wxID_ANY, "Frequency (mHz)", 0, 1000, 500, reinterpret_cast<void*>(&this->frequency), [](void* data, int value)->void{*reinterpret_cast<double*>(data) = value / 1000.0;}, wxPoint(0, 90));
		signal_input = signal_manager.get_new_input(this, wxID_ANY, &shape, wxPoint(0, 180));
		effect_manager.insert("SynchronizedVibrato", this);
	}
	~synSynchronizedVibrato() {
		signal_manager.free_input(signal_input);
		effect_manager.erase_single_sample_effect("SynchronizedVibrato");
	}
};
