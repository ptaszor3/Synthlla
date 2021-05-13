#pragma once

#include "synEffectInput.hpp"
#include "synEffectInputsManager.hpp"

#include <wx/wx.h>
#include "../Synthall/Synthall"

extern synEffectInputsManager effect_manager;

class synEffectsControl :public wxWindow {
	Instrument* instrument;
public:
	synEffectsControl(wxWindow* parent, wxWindowID id, Instrument* c_instrument, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
}
