//
// Created by dario on 16/11/2022.
//

#ifndef BUTTON_WXWIDGETS_MYAPP_H
#define BUTTON_WXWIDGETS_MYAPP_H
#include "wx/wx.h"
#include "InitialPage.h"
#include "SelectionSubcategoryPage.h"
#include "LogInPage.h"
#include "RegistrationPage.h"

class MyApp: public wxApp // MainApp is the class for our application
{
    // MainApp just acts as a container for the window,
public: // or frame in MainFrame
    virtual bool OnInit();


};

#endif //BUTTON_WXWIDGETS_MYAPP_H