#pragma once
#include <wx/wx.h>


class mainFrame : public wxFrame
{

public:
	mainFrame(const wxString& title);

private:
	wxStaticText* tb1; //Private variables are textboxes where we would like to change their text in order to display output
	wxStaticText* tb2;
	wxStaticText* tb3;
	wxStaticText* tb4;
	wxStaticText* tb5;
	wxStaticText* tb6;

	wxStaticText* tb7;
	wxStaticText* tb8;

	void OnButtonClicked(wxCommandEvent& evt); //Function to actually call the sort algorithms and create our home rank object

	void dollarsWeight(wxCommandEvent& evt); //Event function to get weight of price (ended up only using this for debug purposes)
	void dollars(wxCommandEvent& evt); //Event function to get approximate price of house to use from the input text field
	int maxDollars;
	int maxDollarsWeight;

	void bedrooms(wxCommandEvent& evt); //Event function to get how many bedrooms ideal house should have from input slider field
	void bedroomsWeight(wxCommandEvent& evt); //Event function to get how much the number of bedrooms matters from the input slider field
	int numBedrooms;
	int numBedroomsWeight;

	void bathrooms(wxCommandEvent& evt); //Event function to get how many bathrooms house should have from the input slider field
	void bathroomsWeight(wxCommandEvent& evt); //Event function to get how much the number of bathrooms matters from the input slider field
	int numBathrooms;
	int numBathroomsWeight;

	void sqfoot(wxCommandEvent& evt); //Event function to get the amount of sq foot from the input text field
	void sqfootWeight(wxCommandEvent& evt);  //Event function to get how much the sq foot matters from the input slider field
	int numSqFoot;
	int numSqFootWeight;

	void year(wxCommandEvent& evt); //Event function to get what is the earliest year user would be comfortable with
	void yearWeight(wxCommandEvent& evt); //Event function to get how much the max age of the house matters (only used for debugging the program)
	int numYears;
	int numYearsWeight;

};

