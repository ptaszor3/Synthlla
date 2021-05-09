#include "synSlider.hpp"

synSlider::synSlider(wxWindow* parent, wxWindowID id, std::string c_title, int minimum, int maximum, int value_at_beggining, void* c_response_data, void (*c_response)(void*, int), wxPoint position, Styles c_style) 
	:wxWindow(parent, id, position, wxSize(300, 90)), response_data{c_response_data}, response{c_response}, style{c_style} {

	title = new wxStaticText(this, wxID_ANY, c_title, wxPoint(15, 5), wxSize(285, 20));
	slider = new wxSlider(this, wxID_ANY, value_at_beggining, minimum, maximum, wxPoint(5, 25), wxSize(290, -1), wxSL_HORIZONTAL | wxSL_LABELS);
}

void synSlider::OnScroll(wxScrollEvent& event) {
	response(response_data, event.GetPosition());
	event.Skip();
}

void synSlider::OnRelease(wxScrollEvent& event) {
	switch(style) {
		case Styles::POSITIVE:
			slider->SetMax(2 * event.GetPosition());
		break;
		case Styles::NEGATIVE:
			slider->SetMin(2 * event.GetPosition());
		break;
		case Styles::REAL:
			slider->SetMax(2 * event.GetPosition() * ((event.GetPosition() < 0) ? -1 : 1));
			slider->SetMin(2 * event.GetPosition() * ((event.GetPosition() > 0) ? -1 : 1));
		break;
		case Styles::FIXED:
		break;
	}
}

wxBEGIN_EVENT_TABLE(synSlider, wxWindow)
	EVT_SCROLL(synSlider::OnScroll)
	EVT_SCROLL_THUMBRELEASE(synSlider::OnRelease)
wxEND_EVENT_TABLE()
