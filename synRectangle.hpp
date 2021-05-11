#pragma once
#include "synSlider.hpp"
#include "synAllInputsManager.hpp"

#include <wx/wx.h>
#include "../Synthall/Synthall"

extern synAllInputsManager manager;

class synRectangle :public tones::basic::Rect, public wxWindow {
public:
	synRectangle(wxWindow* parent, wxWindowID id = wxID_ANY, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize) 
	:wxWindow(parent, id, position, size){
		new synSlider(this, wxID_ANY, "Infill", 0, 100, 50, reinterpret_cast<void*>(&infill), [](void* data, int value){*reinterpret_cast<double*>(data) = value / 100.0;}, wxDefaultPosition, synSlider::Styles::FIXED);
		manager.insert("Rectangle", this);
	}

	~synRectangle() {
		manager.erase_signal("Rectangle");
	}
};
