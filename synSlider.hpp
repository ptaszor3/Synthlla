#pragma once
#include <wx/wx.h>

class synSlider :public wxWindow {

	void (*set_value)(int);
	wxStaticText* title;
	wxSlider* slider;
	void* response_data;
	void (*response)(void*, int);
public:
	enum class Styles {
		POSITIVE,
		NEGATIVE,
		REAL,
		FIXED
	} style;

	synSlider(wxWindow* parent, wxWindowID id, std::string title, int minimum, int maximum, int value_at_beggining, void* c_response_data, void (*c_response)(void*, int), wxPoint position = wxDefaultPosition, Styles c_style = Styles::POSITIVE);

	void OnScroll(wxScrollEvent& event);
	void OnRelease(wxScrollEvent& event);

	wxDECLARE_EVENT_TABLE();
};
