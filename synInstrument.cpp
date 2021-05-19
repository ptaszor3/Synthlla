#include "synInstrument.hpp"

synInstrument::synInstrument(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size)
:wxWindow(parent, id, position, size) {
	tone_input = new synSignalInput(this, wxID_ANY, &tone);
	envelope_input = new synSignalInput();
	input = new MIDIInput
}
