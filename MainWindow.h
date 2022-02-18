#pragma once
#include <wx/wxprec.h>
#include <wx/textctrl.h>
#include <string>
#include "SerialPort.h"
#include "ArduinoController.h"
using namespace std;

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MainWindow: public wxFrame
{
    bool check_power = false;
    int check_id = 0;
public:
    char* portName = (char*)"\\\\.\\COM3";
    SerialPort* arduino = new SerialPort(portName);
    ArduinoController* AC = new ArduinoController();

    wxString wx_read_output;

    wxPanel* panel;
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* panelMainSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* MainEditBox;
    wxStatusBar* statusBar;

    //create a timer
    wxTimer* recTimer;

	MainWindow(string Text, wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxASCII_STR(wxFrameNameStr));
	~MainWindow();
    void onNew(wxCommandEvent& event);
    void OnRecTimer(wxTimerEvent& event);
    void OnClick(wxCommandEvent & id);
    void onTest(wxCommandEvent& event);
    void onQuit(wxCommandEvent& event);
    bool get_power();
    //void onClose(wxCloseEvent& event);

    enum
    {
        TEXT_Main = wxID_HIGHEST + 1,
        Rec_Timer = wxID_HIGHEST
    };

    DECLARE_EVENT_TABLE();
};

