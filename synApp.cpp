#include "synApp.hpp"
#include "synFrame.hpp"

bool synApp::OnInit() {
	auto frame = new synFrame("title", wxDefaultPosition, wxSize(400, 800));
	frame->Show(true);

	return true;
}

