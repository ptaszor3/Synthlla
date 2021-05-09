#include <wx/wx.h>
#include <map>
#include <utility>
#include <string>
#include "../Synthall/Synthall"

template<class InputType>
class synSignalInput :public wxChoice {
	std::map<std::string, InputType*> signals;
	InputType** destination;
public:
	synSignalInput(wxWindow* parent, wxWindowID, InputType** destination, wxPoint position = wxDefaultPosition, wxSize = wxDefaultSize);

	void add_signal(std::string, InputType*);
	void remove_signal(std::string);
	void OnChoice(wxCommandEvent&);

	//wxDECLARE_EVENT_TABLE();
};
