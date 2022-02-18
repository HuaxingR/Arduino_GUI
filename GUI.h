#pragma once
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/textctrl.h>
using namespace std;
#include <string>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// first step to set wxWidgets app going
class App : public wxApp
{
    string Text_from_Arduino;
public:
    App();
    App(string Text);
    bool OnInit();
    string getText_from_Arduino();
    ~App();

    enum
    {
        TEXT_Main = wxID_HIGHEST + 1
    };
};


DECLARE_APP(App); 