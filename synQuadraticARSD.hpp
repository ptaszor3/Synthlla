#pragma once
#include "synARSD.hpp"
#include "synSignalInputsManager.hpp"

#include "../Synthall/Synthall"

extern synSignalInputsManager signal_manager;

class synQuadraticARSD :public synARSD, public envelopes::arsd::Quadratic {
public:
	synQuadraticARSD(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize)
	:synARSD(parent, id, &(Quadratic::arsd), position) {
		signal_manager.insert("ARSD", this);
	}

	~synQuadraticARSD() {
		signal_manager.erase_signal("ARSD");
	}
};
