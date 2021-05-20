#pragma once
#include "synSignalInputsManager.hpp"
#include "synMIDIInput.hpp"

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <map>

extern synSignalInputsManager signal_manager;

class synInstrument :public Instrument, public wxWindow {
	synSignalInput* tone_input;
	synSignalInput* envelope_input;
	synMIDIInput* input_input;
	outputs::ALSAOutputStream* output;

public:
	synInstrument(wxWindow* parent, wxWindowID id, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
};
