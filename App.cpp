#include "App.h"
#include "mainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() { 
	mainFrame* myFrame = new mainFrame("DreamDwelling Pro"); //Build window
	myFrame->SetClientSize(800, 800); //Set size of window
	myFrame -> Center(); //Display window at center of screen
	myFrame->Show(); //Show window
	return true;
}
