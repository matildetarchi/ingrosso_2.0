//
// Created by dario on 16/11/2022.
//

#include "MyApp.h"


bool MyApp::OnInit()
{

    auto* e = new Engine();
    auto *MainWin = new InitialPage(e,_T("YOUR MARKET RIGHT HERE"), wxPoint(50, 20), wxSize(500, 300));
    MainWin->Show(TRUE);
    SetTopWindow(MainWin);

    return TRUE;
}