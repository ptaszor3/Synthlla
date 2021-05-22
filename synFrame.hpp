#include <wx/wx.h>
#include <wx/aui/aui.h>

#include "../Synthall/Synthall"

class synFrame :public wxFrame {
	//Instrument* instrument;
	wxAuiNotebook* notebook;
public:
	synFrame(std::string title, wxPoint position, wxSize size);
	void OnVolumeControl(wxCommandEvent& event);
	//void OnSynchronizedVibrato(wxCommandEvent& event);
	//void OnUnsynchronizedVibrato(wxCommandEvent& event);
	//void OnSynchronizedTremolo(wxCommandEvent& event);
	//void OnUnsynchronizedTremolo(wxCommandEvent& event);
	void OnVibrato(wxCommandEvent& event);
	void OnTremolo(wxCommandEvent& event);

	void OnRectangle(wxCommandEvent& event);
	void OnAdditiveSynthesizer(wxCommandEvent& event);

	void OnQuadraticARSD(wxCommandEvent& event);
	void OnLinearARSD(wxCommandEvent& event);

	void OnInstrument(wxCommandEvent&);
	
	wxDECLARE_EVENT_TABLE();
};
