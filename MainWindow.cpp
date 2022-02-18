#include "MainWindow.h"
#include "ArduinoController.h"
#include "id.h"
#include <wx/artprov.h> //get the bit map
#include <wx/chartype.h> 
#include <cstring>
using namespace std;

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_NEW, MainWindow::onNew)
    EVT_BUTTON(wxID_ANY, MainWindow::OnClick)
    EVT_TIMER(Rec_Timer, MainWindow::OnRecTimer)   //Receive Timer event declaration
    EVT_MENU(wxID_EXIT, MainWindow::onQuit)
END_EVENT_TABLE()

string add_up_string = "";
MainWindow::MainWindow(string Text, wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name) :
    wxFrame(parent, id, title, pos, size, style, name)
{
    char* portName = (char*)"COM3";
    char* char_array;
    char_array = &Text[0];

    //create a menu bar
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();
    //wxWidgets default wxMenuItem example
    fileMenu->Append(wxID_NEW); 

    //create customized wxMenuItem
    wxMenuItem *fileItem = fileMenu->Append(wxID_ANY, _("&Testtt\tCtrl+S"));
    Bind(wxEVT_MENU, &MainWindow::onTest, this, fileItem->GetId());


    //create wxMenuItem example
    wxMenuItem* quitItem = new wxMenuItem(fileMenu, wxID_EXIT);
    quitItem->SetBitmap(wxArtProvider::GetBitmap("wxART_QUIT")); //set the icon

    fileMenu->Append(quitItem);

    menuBar->Append(fileMenu, _("&File"));
    SetMenuBar(menuBar);


    statusBar = CreateStatusBar(1); // two sections in status bar
    statusBar->SetStatusText(_("Ready!"));
    //statusBar->SetStatusText(_("Hello!"), 1);

    // sizer
    //wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    panel = new wxPanel(this);
    mainSizer->Add(panel, 1, wxEXPAND);


    panel->SetSizer(panelMainSizer);
    
    strcpy(char_array, Text.c_str());
    // if your string is UTF-8 encoded, this is the shortest path :
    //wxString mystring = wxString::FromUTF8(char_array);

    wx_read_output = wxString(Text.c_str());

    // add text
    MainEditBox = new wxTextCtrl(this, TEXT_Main,
        wx_read_output, wxDefaultPosition, wxDefaultSize,
        wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);

    mainSizer->Add(MainEditBox, 10, wxEXPAND, 10); 


    // create buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->AddStretchSpacer();
    wxButton* onButton = new wxButton(panel, wxID_ANY, "ON");
    buttonSizer->Add(onButton);

    wxButton* offButton = new wxButton(panel, wxID_ANY, "OFF");
    buttonSizer->Add(offButton);

    wxButton* quitButton = new wxButton(panel, wxID_ANY, "Quit");
    buttonSizer->Add(quitButton);

    panelMainSizer->Add(buttonSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 1);

    SetSizer(mainSizer);
    SetMinSize(wxSize(500, 800));
    recTimer = new wxTimer(this, Rec_Timer);

    recTimer->Start(10);
}


MainWindow::~MainWindow() {

}

//event handler
void MainWindow::onNew(wxCommandEvent& event) {
    wxMessageBox("MainWindow::onNew");
    PushStatusText(_("MainWindow::onNew"));
    wxSleep(5);
    PopStatusText();
}

void MainWindow::OnRecTimer(wxTimerEvent& event) {
    SerialPort* tempSerialPortPtr = arduino;
    string read_output;
    ArduinoController* tempArduinoControllerPtr = AC;
    if (check_power == true && (check_id == -31998)) {
        statusBar->SetStatusText(_("Receiving data from Arduino..."));
        string command = "ON\n";
        add_up_string = "";
        tempArduinoControllerPtr->WriteArduino(tempSerialPortPtr, portName, command);
        check_power = false;
    }
    else if (check_power == false && (check_id == -31998)) {
        read_output = tempArduinoControllerPtr->ReadArduino(tempSerialPortPtr, portName);
        if (read_output != "") {
            //add_up_string += read_output.c_str();
            wx_read_output = wxString(read_output.c_str());

            MainEditBox->AppendText(wx_read_output);

            SetSizer(mainSizer);
            SetMinSize(wxSize(500, 800));
        }
    }
    else if (check_id == -31997) {
            string command = "OFF\n";
            statusBar->SetStatusText(_("Stop receiving data from Arduino..."));
            tempArduinoControllerPtr->WriteArduino(tempSerialPortPtr, portName, command);
            read_output = tempArduinoControllerPtr->ReadArduino(tempSerialPortPtr, portName);
            if (read_output != "") {
                 wx_read_output = wxString(read_output.c_str());

                MainEditBox->AppendText(wx_read_output);
                SetSizer(mainSizer);
                SetMinSize(wxSize(500, 800));
                check_power == true;
            }
           
    }
}

void MainWindow::OnClick(wxCommandEvent& id) {
    

    string read_output;

    SerialPort* tempSerialPortPtr = arduino;
    ArduinoController* tempArduinoControllerPtr = AC;

    check_id = id.GetId();
    // if "ON" is clicked:
    if(check_id == -31998){
        check_power = true;      
    }    

    else if (check_id == -31996) {
        recTimer->Stop();
        this->Destroy();
        
    }
}

void MainWindow::onTest(wxCommandEvent& event) {
    wxMessageBox("MainWindow::onTest");
}

void MainWindow::onQuit(wxCommandEvent& event) {
    wxMessageBox("Quit the window.");
    recTimer->Stop();
    this->Destroy();
    
}



bool MainWindow::get_power() {
    return check_power;
}

