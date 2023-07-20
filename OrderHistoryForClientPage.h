//
// Created by Andrea Lipperi on 04/05/23.
//

#ifndef INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H
#define INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H

#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include "OrdersList.h"

class OrderHistoryForClientPage : public wxDialog{
public:
    OrderHistoryForClientPage(const wxString& title, int control);

    static const long IdButtonCancel;
    static const long IdButtonView;

    DECLARE_EVENT_TABLE()


private:
    void CancelOrder(wxCommandEvent& event);
    void ViewOrder(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);

    wxButton *Cancel;
    wxButton *View;
    wxTextCtrl *sub;
    wxTextCtrl *cat;
    wxTextCtrl *name;
    wxTextCtrl *cost;
    wxBoxSizer *sizer;
    wxSpinCtrl* spinCtrl;
    wxGrid *grid;
    std::string username;
    wxChoice* choiceOrder;
    std::vector<std::vector<std::string>> mat_order;
    int ctrl;
};


#endif //INGROSSO_ONLINE_ORDERHISTORYFORCLIENTPAGE_H
