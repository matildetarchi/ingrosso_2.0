//
// Created by dario on 12/11/2022.
//

#include "wx/wxhtml.h"
#include "wx/wx.h"
#ifndef BUTTON_WXWIDGETS_FRAME_H
#define BUTTON_WXWIDGETS_FRAME_H
class SelectionSubcategoryPage: public wxFrame {
public:
    SelectionSubcategoryPage(const wxString &title);

    static const long IdButtonInsert;
    static const long IdButtonComeBack;


DECLARE_EVENT_TABLE()
private:
    void ComeBack(wxCommandEvent& event);
    void InsertProduct(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);
    wxButton *Insert;
    wxButton *Back;
    wxTextCtrl *tcCategory;
    wxChoice* choiceC;
    wxChoice* choiceSubC;
    wxChoice* choiceDisp;
};
#endif //BUTTON_WXWIDGETS_FRAME_H