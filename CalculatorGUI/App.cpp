#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Calculator");
	mainFrame->SetClientSize(320, 475);
	mainFrame->SetBackgroundColour(wxColour(38, 38, 38));
	mainFrame->Show();
	return true;
}