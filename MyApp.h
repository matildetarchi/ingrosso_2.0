//
// Created by dario on 16/11/2022.
//

#ifndef BUTTON_WXWIDGETS_MYAPP_H
#define BUTTON_WXWIDGETS_MYAPP_H

#include "Engine.h"
#include"wx/wx.h"
#include "InitialPage.h"


class MyApp: public wxApp // MainApp is the class for our application
{

public:
    virtual bool OnInit();

};

#endif //BUTTON_WXWIDGETS_MYAPP_H
