#pragma once
#include "synSignalInputsManager.hpp"
#include "synMIDIInput.hpp"
#include "synEffectContext.hpp"

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <map>

extern synSignalInputsManager signal_manager;

class synInstrument :public Instrument, public wxWindow {
	synSignalInput* tone_input;
	synSignalInput* envelope_input;
	synMIDIInput* input_input;
	outputs::ALSAOutputStream* output;
	synEffectContext<SingleSampleEffect>* single_sample_context;
	synEffectContext<WholeSampleEffect>* whole_sample_context;

public:
	synInstrument(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);
	~synInstrument();
};
