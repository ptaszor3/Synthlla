#pragma once
#include "synSignalInputsManager.hpp"

#include "../Synthall/Synthall"
#include <wx/wx.h>

extern synSignalInputsManager signal_manager;

class synInstrument :public instrument, public wxWindow {
	synSignalInput* tone_input;
	inputs::MIDIInput* input;
	outputs::ALSAOutputStream* output;
	wxButton* select_midi_device;
public:
	synInstrument(wxWindow* parent, wxWindowID id, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
	~synInstrument();

	wxDECLARE_EVENT_TABLE();
};
