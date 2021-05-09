#include <wx/wx.h>

#include "../Synthall/Synthall"

class synFrame :public wxFrame {
	Instrument* instrument;
public:
	synFrame(std::string title, wxPoint position, wxSize size);
};
