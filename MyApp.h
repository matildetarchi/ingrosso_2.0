//
// Created by dario on 16/11/2022.
//

#include"wx/wx.h"
#ifndef BUTTON_WXWIDGETS_MYAPP_H
#define BUTTON_WXWIDGETS_MYAPP_H

class MyApp: public wxApp // MainApp is the class for our application
{
    // MainApp just acts as a container for the window,
public: // or frame in MainFrame
    virtual bool OnInit();


};

#endif //BUTTON_WXWIDGETS_MYAPP_H