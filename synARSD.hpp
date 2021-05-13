#pragma once
#include "synSlider.hpp"
#include "../Synthall/include/envelopes/arsd.hpp"

#include <wx/wx.h>

class synARSD :public wxWindow{
	envelopes::arsd::Arsd* arsd;
	synSlider* attack;
	synSlider* release;
	synSlider* sustain;
	synSlider* decay;
public:
	synARSD(wxWindow* c_parent, wxWindowID c_id, envelopes::arsd::Arsd* c_arsd, wxPoint c_position = wxDefaultPosition);
};
