#include "GUI.h"
#include "id.h"
#include "MainWindow.h"
#include "ArduinoController.h"
#include "MainWindow.h"
#include <wx/artprov.h> //get the bit map
#include <iostream>
#include <wx/string.h>
using namespace std;
#include <string>


using namespace std;

IMPLEMENT_APP(App);

App::App() {
}
App::App(string Text) {
    Text_from_Arduino = Text;
}

bool App::OnInit()
{
    if (!wxApp::OnInit()) {
        return false;
    }

    string Text= "see if it works...";
    //string Text = getText_from_Arduino();
    char* portName = (char*)"COM3";
    ArduinoController AC(Text, portName);
    AC.OpenArduino(portName);
    MainWindow* main = new MainWindow(AC.getText(), nullptr, window::id::MAINWINDOW, _("Main Window"));
    main->Show();
    
    
    return true;
}

string App::getText_from_Arduino() {
    return Text_from_Arduino;
}

App::~App() {

}

