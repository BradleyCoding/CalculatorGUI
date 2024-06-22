#include "MainFrame.h"
#include "CalculatorLogic.h"
#include <wx/wx.h>
#include <vector>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	// Create a main panel
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

	// Create a box sizer
	wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

	// create and add sub panels to box sizer
	CreateOutputPanel(mainPanel, panelSizer);
	CreateMemoryPanel(mainPanel, panelSizer);
	CreateControlPanel(mainPanel, panelSizer);

	// set size of the sizer and min/max size
	mainPanel->SetSizer(panelSizer);
	panelSizer->SetSizeHints(this);
}

void MainFrame::CreateOutputPanel(wxPanel* panelParent, wxBoxSizer* sizerParent) {

	// output panel //

	// set up the panel

	outputPanel = new wxPanel(panelParent, wxID_ANY);

	wxSizerFlags outputPanelFlags = wxSizerFlags().Proportion(4).Expand().Border(wxALL, 5);

	outputPanel->SetBackgroundColour(wxColour(70, 70, 70));
	sizerParent->Add(outputPanel, outputPanelFlags);

	// output pad //

	wxGridSizer* outputPadBoxSizer = new wxGridSizer(2, 1, wxSize(0, 0));

	// sub text
	subText = new wxStaticText(outputPanel, wxID_ANY, "");
	subText->SetForegroundColour(wxColour(190, 190, 190));
	subText->SetMinSize(wxSize(-1, -1));

	wxFont subTextFont = subTextFont.GetBaseFont().Bold().Scale(2);
	subText->SetFont(subTextFont);

	wxSizerFlags subTextFlags = wxSizerFlags().Top().Right().Border(wxALL, 2);
	outputPadBoxSizer->Add(subText, subTextFlags);

	// main text
	mainText = new wxStaticText(outputPanel, wxID_ANY, "");
	mainText->SetForegroundColour(wxColour(255, 255, 255));
	mainText->SetMinSize(wxSize(-1, -1));
	
	wxFont mainTextFont = mainTextFont.GetBaseFont().Bold().Scale(3); 
	mainText->SetFont(mainTextFont);

	wxSizerFlags mainTextFlags = wxSizerFlags().Bottom().Right().Border(wxALL, 5);
	outputPadBoxSizer->Add(mainText, mainTextFlags);

	

	outputPanel->SetSizer(outputPadBoxSizer);
	
}

void MainFrame::CreateMemoryPanel(wxPanel* panelParent, wxBoxSizer* sizerParent) {

	// memory panel //

	// set up the panel

	wxPanel* memoryPanel = new wxPanel(panelParent, wxID_ANY);

	wxSizerFlags memoryPanelFlags = wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5);

	memoryPanel->SetBackgroundColour(wxColour(38, 38, 38));
	sizerParent->Add(memoryPanel, memoryPanelFlags);

	// memory pad //

	// create a vector to store the layout of the memory pad

	std::vector<wxString> memoryPadButtonLbl = {
		"MC", "MR", "MS", "M+", "M-"
	};
	
	wxGridSizer* memoryPadBoxSizer = new wxGridSizer(1, 5, wxSize(0, 0));
	wxSizerFlags memoryPadFlags = wxSizerFlags().Expand().Border(wxALL, 2);

	for (wxString label : memoryPadButtonLbl) {
		wxButton* memoryPadButton = new wxButton(memoryPanel, wxID_ANY, label);
		memoryPadButton->SetBackgroundColour(wxColour(116, 255, 118));
		memoryPadButton->Bind(wxEVT_BUTTON, &MainFrame::OnAnyMemoryButtonClicked, this);

		memoryPadBoxSizer->Add(memoryPadButton, memoryPadFlags);
	}

	memoryPanel->SetSizer(memoryPadBoxSizer);
}

void MainFrame::CreateControlPanel(wxPanel* panelParent, wxBoxSizer* sizerParent) {

	// control panel //

	// set up the panel

	wxPanel* ctrlPanel = new wxPanel(panelParent, wxID_ANY);

	wxSizerFlags ctrlPanelFlags = wxSizerFlags().Proportion(8).Expand().Border(wxALL, 5);

	ctrlPanel->Bind(wxEVT_BUTTON, &MainFrame::OnAnyCtrlButtonClicked, this); //bind all buttons to event handler

	ctrlPanel->SetBackgroundColour(wxColour(38, 38, 38));
	sizerParent->Add(ctrlPanel, ctrlPanelFlags);

	// control pad //

	// create a vector to store the layout of the control pad

	std::vector<wxString> ctrlPadButtonLbl = {
		"DEL", "CE", "AC", "±",
		"7", "8", "9", "÷",
		"4", "5", "6", "×",
		"1", "2", "3", "-",
		"0", ".", "=", "+"
	};

	wxGridSizer* controlPadGridSizer = new wxGridSizer(5, 4, wxSize(0, 0));  // (num rows, num columns, size)
	wxSizerFlags ctrlPadFlags = wxSizerFlags().Expand().Border(wxALL, 2); //flags for the control pad

	//CreateStatusBar();

	// iterate through each button in the vector
	for (wxString label : ctrlPadButtonLbl) { 

		//create the button
		wxButton* ctrlPadButton = new wxButton(ctrlPanel, wxID_ANY, label);

		//set the colour and bind them

		//function buttons
		if (label == ctrlPadButtonLbl[0] || label == ctrlPadButtonLbl[1] || label == ctrlPadButtonLbl[2] || label == ctrlPadButtonLbl[3]) {
			ctrlPadButton->SetBackgroundColour(wxColour(52, 231, 255));

			ctrlPadButton->Bind(wxEVT_BUTTON, &MainFrame::OnFuncButtonClicked, this);
		}

		//0-9 buttons
		else if (label == ctrlPadButtonLbl[4] || label == ctrlPadButtonLbl[5] || label == ctrlPadButtonLbl[6]
			|| label == ctrlPadButtonLbl[8] || label == ctrlPadButtonLbl[9] || label == ctrlPadButtonLbl[10]
			|| label == ctrlPadButtonLbl[12] || label == ctrlPadButtonLbl[13] || label == ctrlPadButtonLbl[14]
			|| label == ctrlPadButtonLbl[16] || label == ctrlPadButtonLbl[17]) {

			ctrlPadButton->SetBackgroundColour(wxColour(215, 215, 215));

			ctrlPadButton->Bind(wxEVT_BUTTON, &MainFrame::OnNumButtonClicked, this);
		}
		//operator buttons
		else if (label == ctrlPadButtonLbl[7] || label == ctrlPadButtonLbl[11] || label == ctrlPadButtonLbl[15] || label == ctrlPadButtonLbl[19]) {
			ctrlPadButton->SetBackgroundColour(wxColour(255, 141, 0));

			ctrlPadButton->Bind(wxEVT_BUTTON, &MainFrame::OnOpButtonClicked, this);
		}
		//equals button
		else if (label == ctrlPadButtonLbl[18]) {
			ctrlPadButton->SetBackgroundColour(wxColour(205, 41, 41)); 

			ctrlPadButton->Bind(wxEVT_BUTTON, &MainFrame::OnEqualsButtonClicked, this);
		}
		controlPadGridSizer->Add(ctrlPadButton, ctrlPadFlags);
	}

	ctrlPanel->SetSizer(controlPadGridSizer);
	
}

// EVENT HANDLING //
  
// MEMORY PANEL
void MainFrame::OnAnyMemoryButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Memory Button Clicked");

	// get the button that was clicked
	wxButton* clickedButton = dynamic_cast<wxButton*>(evt.GetEventObject());

	// get the label of the clicked button
	wxString clickedLabel = clickedButton->GetLabel();
}
 
// CTRL PANEL
void MainFrame::OnAnyCtrlButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button Clicked");
}

void MainFrame::OnFuncButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Func Button Clicked");

	// get the button that was clicked
	wxButton* clickedButton = dynamic_cast<wxButton*>(evt.GetEventObject());

	// get the label of the clicked button
	wxString clickedLabel = clickedButton->GetLabel();

	// get the current label
	wxString currentLabel = mainText->GetLabel();

	// handling the DEL button
	if (clickedLabel == "DEL") {
		// remove the last character in the string
		currentLabel.RemoveLast();

		// update the text
		mainText->SetLabel(currentLabel);
	}

	// handling the CE button
	else if (clickedLabel == "CE") {
		//clear entry
		mainText->SetLabel("");
		subText->SetLabel("");
	}

	// handling the AC button ////////////////////////////////////////////////////////// COME BACK TO THIS AND MAKE IT CLEAR EVERYTHING INCLUDING MEMORY ENTRIES ///////////////////////////////////////////////////////////////
	else if (clickedLabel == "AC") {
		//clear entry
		mainText->SetLabel("");
		subText->SetLabel("");

		//clear memory
	}

	// handling the ± button
	else if (clickedLabel == "±") {
		// clear the sub text
		subText->SetLabel("");

		// check if the number is positive or negative

		if (IsNegative(currentLabel)) {
			currentLabel = removeFirstOccurrence(currentLabel, '-');
			mainText->SetLabel(currentLabel);
		}
		else {
			mainText->SetLabel('-' + currentLabel);
		}
	}

	// adjust the text position
	outputPanel->Layout();
}

void MainFrame::OnNumButtonClicked(wxCommandEvent& evt) {

	// get the button that was clicked
	wxButton* clickedButton = dynamic_cast<wxButton*>(evt.GetEventObject());

	// get the label of the clicked button
	wxString clickedLabel = clickedButton->GetLabel();

	// get the current label
	wxString currentLabel = mainText->GetLabel();

	// add the clicked label to the current label
	mainText->SetLabel(currentLabel + clickedLabel);

	// adjust the text position
	mainText->SetMinSize(wxSize(-1, -1));
	outputPanel->Layout();

	wxLogStatus(currentLabel);
}

void MainFrame::OnOpButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Op Button Clicked");
	// get the button that was clicked
	wxButton* clickedButton = dynamic_cast<wxButton*>(evt.GetEventObject());

	// get the label of the clicked button
	wxString clickedLabel = clickedButton->GetLabel();

	// get the current label of the main text
	wxString currentLabel = mainText->GetLabel();

	// check if the sub text already has a expression - if it does, it will calculate the expression, then set the sub text to the result + new operator and clear the main text
	wxString subTextLabel = subText->GetLabel();
	if (HasOperator(subTextLabel)) {
		wxLogStatus("Op Found");

		// check if the expression has already been calculated (has equals)

		if (HasEquals(subTextLabel)) {
			// clear the main text
			mainText->SetLabel("");
			
			// set the main text result to the sub text
			subText->SetLabel(currentLabel + " " + clickedLabel);
		}
		else {
			wxString expression = subTextLabel + currentLabel;

			wxString result = CalculatorLogic::calculateExpression(expression);

			subText->SetLabel(result + " " + clickedLabel);
			mainText->SetLabel("");
		}
	}

	// move main text to sub text and clear main text
	else {
		subText->SetLabel(currentLabel + " " + clickedLabel);
		mainText->SetLabel("");
	}
	// adjust the text position
	outputPanel->Layout();
}

void MainFrame::OnEqualsButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Equals Button Clicked");

	wxString clickedLabel = '='; // it will always be this

	// get the current label of the main text
	wxString currentLabel = mainText->GetLabel();

	// get the sub text label
	wxString subTextLabel = subText->GetLabel();

	// check if the expression already has equals
	if (HasEquals(subTextLabel)) {

		// remove the first number from the sub text then replace it with the main text
		wxString existingText = removeFirstNum(subTextLabel);

		subText->SetLabel(currentLabel + " " + existingText);

		// clear the main text
		mainText->SetLabel("");

		// get the new label
		wxString expression = subText->GetLabel();

		// calculate result and place it in main text
		mainText->SetLabel(CalculatorLogic::calculateExpression(expression));
	}

	// is not already calculated
	else {
		// set the sub text to be full expression
		subText->SetLabel(subTextLabel + " " + currentLabel + " " + clickedLabel);

		// clear main text
		mainText->SetLabel("");

		// calculte the answer and display it in main text
		wxString expression = subText->GetLabel();
		mainText->SetLabel(CalculatorLogic::calculateExpression(expression));
	}

	// adjust the text position
	outputPanel->Layout();

}

//FUNCTIONS
bool MainFrame::HasOperator(wxString text) {
	for (char op : text) {
		if (op == '+' || op == '-' || op == '×' || op == '÷') {
			return true;
		}
	}
	return false;
}

bool MainFrame::HasEquals(wxString text) {
	for (char op : text) {
		if (op == '=') {
			return true;
		}
	}
	return false;
}

bool MainFrame::IsNegative(wxString text) {
	// only use if you know the negative symbol will always be before the number
	for (char op : text) {
		if (op == '-') {
			return true;
		}
	}
	return false;
}

wxString MainFrame::removeFirstNum(wxString text) {
	size_t pos = text.find(' ');

	if (pos != wxString::npos) {
		// extract substring starting from the character right after the first space
		wxString newText = text.substr(pos + 1);
		return newText;
	}
	else {
		return text;
	}
}

wxString MainFrame::removeFirstOccurrence(wxString& str, char ch) {
	size_t found = str.find(ch);
	if (found != wxString::npos) {
		str.erase(found, 1);
		return str;
	}
	else {
		return str;
	}
}