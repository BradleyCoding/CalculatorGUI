#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);

private:
	// DECLARATIONS
	
	// output panel:
	wxPanel* outputPanel;
	wxStaticText* mainText;
	wxStaticText* subText;

	// memory panel:

	// control panel:

	//FUNCTIONS

	// create panel functions
	void CreateOutputPanel(wxPanel* panelParent, wxBoxSizer* panelSizer);
	void CreateMemoryPanel(wxPanel* panelParent, wxBoxSizer* panelSizer);
	void CreateControlPanel(wxPanel* panelParent, wxBoxSizer* panelSizer);

	// check for operators
	bool HasOperator(wxString text);
	bool HasEquals(wxString text);
	bool IsNegative(wxString text);

	// remove string text
	wxString removeFirstNum(wxString text);
	wxString removeFirstOccurrence(wxString& str, char ch);

	// EVENTS

	// output panel events

	// memory panel events
	void OnAnyMemoryButtonClicked(wxCommandEvent& evt);

	//control panel events
	void OnAnyCtrlButtonClicked(wxCommandEvent& evt);
	void OnFuncButtonClicked(wxCommandEvent& evt);
	void OnNumButtonClicked(wxCommandEvent& evt);
	void OnOpButtonClicked(wxCommandEvent& evt);
	void OnEqualsButtonClicked(wxCommandEvent& evt);
};