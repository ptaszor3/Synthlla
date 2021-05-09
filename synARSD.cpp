#include "synARSD.hpp"

synARSD::synARSD(wxWindow* c_parent, wxWindowID c_id, envelopes::arsd::Arsd* c_arsd, wxPoint c_position) 
:wxWindow(c_parent, c_id, c_position, wxSize(300, 360), wxBORDER_THEME), arsd{c_arsd} {
	attack = new synSlider(this, wxID_ANY, "Attack", 0, 1000, 100, reinterpret_cast<void*>(arsd), [](void* data, int value){reinterpret_cast<envelopes::arsd::Arsd*>(data)->attack = DoubleSeconds(value / 1000.0);}, wxPoint(0, 0));

	release = new synSlider(this, wxID_ANY, "Release", 0, 1000, 100, reinterpret_cast<void*>(arsd), [](void* data, int value){reinterpret_cast<envelopes::arsd::Arsd*>(data)->release = DoubleSeconds(value / 1000.0);}, wxPoint(0, 90));

	sustain = new synSlider(this, wxID_ANY, "Sustain", 0, 100, 30, reinterpret_cast<void*>(arsd), [](void* data, int value){reinterpret_cast<envelopes::arsd::Arsd*>(data)->sustain = value / 100.0;}, wxPoint(0, 180), synSlider::Styles::FIXED);

	decay = new synSlider(this, wxID_ANY, "Decay", 0, 1000, 100, reinterpret_cast<void*>(arsd), [](void* data, int value){reinterpret_cast<envelopes::arsd::Arsd*>(data)->decay = DoubleSeconds(value / 1000.0);}, wxPoint(0, 270));
}
