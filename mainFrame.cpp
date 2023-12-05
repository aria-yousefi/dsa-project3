#include "mainFrame.h"
#include <wx/wx.h>
#include <string>
#include <iostream>
#include <fstream> 
#include "HomeRank.h"
using namespace std;


mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold()); //Font for the title
	wxFont mainFont(wxFontInfo(wxSize(0, 15))); //Font for main text
	
	wxPanel* panel = new wxPanel(this); //The main frame
	

	wxStaticText* mainTitle = new wxStaticText(panel, wxID_ANY, "DreamDwelling Pro", wxPoint(0, 0), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); //Create title of UI interface
	mainTitle->SetFont(headlineFont); //Set font of title to title font

	wxStaticText* Q1 = new wxStaticText(panel, wxID_ANY, "How much are you looking to spend on a home? (Enter an integer)", wxPoint(0, 90), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); //Question for price
	Q1->SetFont(mainFont); //Set font of question
	wxTextCtrl* text1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 115), wxSize(200, -1), wxALIGN_CENTER_HORIZONTAL); //Textbox for user input of price
	text1->Bind(wxEVT_TEXT, &mainFrame::dollars, this); //Bind the user input to the dollars function
	maxDollars = 0; //Default value of price
	maxDollarsWeight = 1;

	wxStaticText* Q3 = new wxStaticText(panel, wxID_ANY, "How many bedrooms would you like your home to have?", wxPoint(0, 150), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); //Question for number of beds
	Q3->SetFont(mainFont);
	wxSlider* slider2 = new wxSlider(panel, wxID_ANY, 1, 1, 10, wxPoint(300, 170), wxSize(200, -1), wxSL_VALUE_LABEL); //Slider for user input of number of beds, goes from 1 - 10
	slider2->Bind(wxEVT_SLIDER, &mainFrame::bedrooms, this); //Bind the slider to an event function
	numBedrooms = 1; //Default value of number of bedrooms

	wxStaticText* Q4 = new wxStaticText(panel, wxID_ANY, "On a scale from 1 to 5, how significant is this factor when purchasing a home?", wxPoint(0, 210), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);//Question for how much number of beds matters
	Q4->SetFont(mainFont);
	wxSlider* slider3 = new wxSlider(panel, wxID_ANY, 1, 1, 5, wxPoint(300, 230), wxSize(200, -1), wxSL_VALUE_LABEL);
	slider3->Bind(wxEVT_SLIDER, &mainFrame::bedroomsWeight, this);
	numBedroomsWeight = 1; //Default value for weight of number of bedrooms

	wxStaticText* Q5 = new wxStaticText(panel, wxID_ANY, "How many bathrooms would you like your home to have?", wxPoint(0, 270), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); //Question for how many bathrooms to have
	Q5->SetFont(mainFont);
	wxSlider* slider4 = new wxSlider(panel, wxID_ANY, 1, 1, 10, wxPoint(300, 290), wxSize(200, -1), wxSL_VALUE_LABEL);
	slider4->Bind(wxEVT_SLIDER, &mainFrame::bathrooms, this);
	numBathrooms = 1; //Default value for number of bathrooms

	wxStaticText* Q6 = new wxStaticText(panel, wxID_ANY, "On a scale from 1 to 5, how significant is this factor when purchasing a home?", wxPoint(0, 330), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); //Question for how much number of bathrooms matters
	Q6->SetFont(mainFont);
	wxSlider* slider5 = new wxSlider(panel, wxID_ANY, 1, 1, 5, wxPoint(300, 350), wxSize(200, -1), wxSL_VALUE_LABEL);
	slider5->Bind(wxEVT_SLIDER, &mainFrame::bathroomsWeight, this);
	numBathroomsWeight = 1; //Default value for how much number of bathrooms matters

	wxStaticText* Q7 = new wxStaticText(panel, wxID_ANY, "What would be the ideal square footage for your home? (Enter an integer)", wxPoint(0, 390), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); //Question for ideal square footage of home
	Q7->SetFont(mainFont);
	wxTextCtrl* text2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 415), wxSize(200, -1), wxALIGN_CENTER_HORIZONTAL);
	text2->Bind(wxEVT_TEXT, &mainFrame::sqfoot, this);
	numSqFoot = 0; //Default value for number of square feet

	wxStaticText* Q8 = new wxStaticText(panel, wxID_ANY, "On a scale from 1 to 5, how significant is this factor when purchasing a home?", wxPoint(0, 450), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);//Question for how much ideal square footage matters
	Q8->SetFont(mainFont);
	wxSlider* slider6 = new wxSlider(panel, wxID_ANY, 1, 1, 5, wxPoint(300, 470), wxSize(200, -1), wxSL_VALUE_LABEL);
	slider6->Bind(wxEVT_SLIDER, &mainFrame::sqfootWeight, this);
	numSqFootWeight = 1; //Default value for number of square feet weight

	wxStaticText* Q9 = new wxStaticText(panel, wxID_ANY, "What is the earliest year you'd be comfortable with your home being built in? (Enter an integer)", wxPoint(0, 510), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);//Question for earliest year of construction user is comfortable with
	Q9->SetFont(mainFont);
	wxTextCtrl* text3 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 535), wxSize(200, -1), wxALIGN_CENTER_HORIZONTAL);
	text3->Bind(wxEVT_TEXT, &mainFrame::year, this);
	numYears = 0; //Default value for number of years
	numYearsWeight = 1; //Default value for how much number of years matters (we ended up not using this value and it is only for debug purposes)

	wxButton* button = new wxButton(panel, wxID_ANY, "Find me the perfect house!", wxPoint(310, 640), wxSize(180, 25), wxBU_EXACTFIT); //Button to actually create the homerank object and call the sorting functions
	button->Bind(wxEVT_BUTTON, &mainFrame::OnButtonClicked, this);
	
	tb1 = new wxStaticText(panel, wxID_ANY, "Top 5 Houses:", wxPoint(0, 670), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); 
	tb1->SetFont(mainFont);
	tb1->SetBackgroundColour(*wxWHITE);

	tb2 = new wxStaticText(panel, wxID_ANY, "1. Scores Not Yet Calculated", wxPoint(0, 690), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); // Field where we will put top scoring house
	tb2->SetFont(mainFont);
	tb2->SetBackgroundColour(*wxWHITE);

	tb3 = new wxStaticText(panel, wxID_ANY, "2. Scores Not Yet Calculated", wxPoint(0, 710), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); // Field where we will put second best scoring house
	tb3->SetFont(mainFont);
	tb3->SetBackgroundColour(*wxWHITE);

	tb4 = new wxStaticText(panel, wxID_ANY, "3. Scores Not Yet Calculated", wxPoint(0, 730), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); // Field where we will put third best scoring house
	tb4->SetFont(mainFont);
	tb4->SetBackgroundColour(*wxWHITE);

	tb5 = new wxStaticText(panel, wxID_ANY, "4. Scores Not Yet Calculated", wxPoint(0, 750), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); // Field where we will put fourth best scoring house
	tb5->SetFont(mainFont);
	tb5->SetBackgroundColour(*wxWHITE);

	tb6 = new wxStaticText(panel, wxID_ANY, "5. Scores Not Yet Calculated", wxPoint(0, 770), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL); // Field where we will put fifth best scoring house
	tb6->SetFont(mainFont);
	tb6->SetBackgroundColour(*wxWHITE);

	tb7 = new wxStaticText(panel, wxID_ANY, "Quick Sort Time: Algorithm Not Yet Called", wxPoint(5, 645), wxSize(300, -1), wxALIGN_CENTER_HORIZONTAL); //Field where we will put the quick sort time
	tb7->SetFont(mainFont);
	tb7->SetBackgroundColour(*wxWHITE);

	tb8 = new wxStaticText(panel, wxID_ANY, "Merge Sort Time: Algorithm Not Yet Called", wxPoint(495, 645), wxSize(300, -1), wxALIGN_CENTER_HORIZONTAL); //Field where we will put the merge sort time
	tb8->SetFont(mainFont);
	tb8->SetBackgroundColour(*wxWHITE);

	CreateStatusBar();
}

void mainFrame::OnButtonClicked(wxCommandEvent& evt) { //Function to actually call the sort algorithms and create our home rank object
	HomeRank h("housingdata.csv"); //Create homeRank object and read in the csv
	float temp = 0;

	temp = (float)maxDollars; //Use maxDollars variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfile(temp);
	temp = (float)maxDollarsWeight; //Use maxDollars weight variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfileWeights(temp);

	temp = (float)numBedrooms; //Use numBedrooms variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfile(temp);
	temp = (float)numBedroomsWeight; //Use numBedrooms weight variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfileWeights(temp);

	temp = (float)numBathrooms; //Use numBathrooms variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfile(temp);
	temp = (float)numBathroomsWeight; //Use numBathrooms weight variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfileWeights(temp);

	temp = (float)numSqFoot; //Use numSqFoot variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfile(temp);
	temp = (float)numSqFootWeight; //Use numSqFoot weight variable of mainframe to create userprofile vector in homerank
	h.addToUserProfileWeights(temp);

	temp = (float)numYears; //Use numYears variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfile(temp);
	temp = (float)numYearsWeight; //Use numYears weight variable of mainframe to ceate userprofile vector in homerank
	h.addToUserProfileWeights(temp);

	h.calculateScores(); //Calculate scores using our score algorithm 

	int mergeSortRunTime = h.helperMergeSort(); //Call the Merge sort function and sort our scores
	int quickSortRunTime = h.helperQuickSort(); //Call the quick sort function and sort our scores


	tb2->SetLabelText("1. " + h.stringOutput(0)); //Set output field to top scoring house
	tb3->SetLabelText("2. " + h.stringOutput(1)); //Set output field to second top scoring house
	tb4->SetLabelText("3. " + h.stringOutput(2)); //Set output field to third top scoring house
	tb5->SetLabelText("4. " + h.stringOutput(3)); //Set output field to fourth top scoring house
	tb6->SetLabelText("5. " + h.stringOutput(4)); //Set output field to fifth top scoring house

	tb7->SetLabelText("Quick Sort Time: " + to_string(quickSortRunTime) + " Microseconds"); //Give quick sort time
	tb8->SetLabelText("Merge Sort Time: " + to_string(mergeSortRunTime) + " Microseconds"); //Give merge sort time

	wxLogStatus("Button Clicked"); //Debug message
}

void mainFrame::dollarsWeight(wxCommandEvent& evt) { //Event function to get weight of price (ended up only using this for debug purposes)
	maxDollarsWeight = evt.GetInt();
	wxString str = wxString::Format("Dollars Weight: %d", evt.GetInt());
	wxLogStatus(str);
}

void mainFrame::dollars(wxCommandEvent& evt) { //Event function to get approximate price of house to use from the input text field
	
	if (evt.GetString().ToStdString() == "") {
		maxDollars = 0;
	}
	else {
		maxDollars = stoi(evt.GetString().ToStdString());
	}

	wxString mystring(to_string(maxDollars));
	wxLogStatus("Dollars: " + mystring);
}

void mainFrame::bedrooms(wxCommandEvent& evt) { //Event function to get how many bedrooms ideal house should have from input slider field
	numBedrooms = evt.GetInt();
	wxString str = wxString::Format("Bedrooms: %d", evt.GetInt());
	wxLogStatus(str);
}

void mainFrame::bedroomsWeight(wxCommandEvent& evt) { //Event function to get how much the number of bedrooms matters from the input slider field
	numBedroomsWeight = evt.GetInt();
	wxString str = wxString::Format("Bedrooms Weight: %d", evt.GetInt());
	wxLogStatus(str);
}

void mainFrame::bathrooms(wxCommandEvent& evt) { //Event function to get how many bathrooms house should have from the input slider field
	numBathrooms = evt.GetInt();
	wxString str = wxString::Format("Bathrooms: %d", evt.GetInt());
	wxLogStatus(str);
}

void mainFrame::bathroomsWeight(wxCommandEvent& evt) { //Event function to get how much the number of bathrooms matters from the input slider field
	numBathroomsWeight = evt.GetInt();
	wxString str = wxString::Format("Num Bathrooms Weight: %d", evt.GetInt());
	wxLogStatus(str);
}

void mainFrame::sqfoot(wxCommandEvent& evt) { //Event function to get the amount of sq foot from the input text field
	if (evt.GetString().ToStdString() == "") {
		numSqFoot = 0;
	}
	else {
		numSqFoot = stoi(evt.GetString().ToStdString());
	}
	
	wxString mystring(to_string(numSqFoot));
	wxLogStatus("sqfoot: " + mystring);
}

void mainFrame::sqfootWeight(wxCommandEvent& evt) { //Event function to get how much the sq foot matters from the input slider field
	numSqFootWeight = evt.GetInt();
	wxString str = wxString::Format("sqFoot Weight: %d", evt.GetInt());
	wxLogStatus(str);
}

void mainFrame::year(wxCommandEvent& evt) { //Event function to get what is the earliest year user would be comfortable with 
	if (evt.GetString().ToStdString() == "") {
		numYears = 0;
	}
	else {
		numYears = stoi(evt.GetString().ToStdString());
	}

	wxString mystring(to_string(numYears));
	wxLogStatus("year: " + mystring);
}

void mainFrame::yearWeight(wxCommandEvent& evt) { //Event function to get how much the max age of the house matters (only used for debugging the program)
	numYearsWeight = evt.GetInt();
	wxString str = wxString::Format("yearWeight: %d", evt.GetInt());
	wxLogStatus(str);
}