#pragma once

#include <wx/wx.h>
#include "../Synthall/Synthall"

class synUnsynchronizedVibrato :public effects::UnsynchronizedVibrato, public wxWindow {
	synSlider* max_time_deviation_slider;
	synSlider* frequency_slider;
	synSignalInput* signal_input;
public:
	synUnsynchronizedVibrato(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize)
	:wxWindow{parent, id, position, size}, UnsynchronizedVibrato{signal_manager.get_default_signal(), 5, 0.000500_ds}
	{
		max_time_deviation_slider = new synSlider(this, wxID_ANY, "Maximal influence", 0, 1000, 500, reinterpret_cast<void*>(&this->max_time_deviation), [](void* data, int value)->void{*reinterpret_cast<DoubleSeconds*>(data) = DoubleSeconds(value / 1000000000.0);});
		frequency_slider = new synSlider(this, wxID_ANY, "Frequency (mHz)", 0, 1000, 500, reinterpret_cast<void*>(&this->frequency), [](void* data, int value)->void{*reinterpret_cast<double*>(data) = value / 1000.0;}, wxPoint(0, 90));
		signal_input = signal_manager.get_new_envelope_input(this, wxID_ANY, &shape, "Shape", wxPoint(0, 180));
		effect_manager.insert("Unsynchronized vibrato", this);
	}
	~synUnsynchronizedVibrato() {
		signal_manager.free_input(signal_input);
		effect_manager.erase_single_sample_effect("Unsynchronized vibrato");
	}
};
