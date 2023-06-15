//
// Created by Andrea Lipperi on 04/05/23.
//

#ifndef INGROSSO_ONLINE_SINGLEORDERDATAFORCLIENT_H
#define INGROSSO_ONLINE_SINGLEORDERDATAFORCLIENT_H



#include "wx/wx.h"
#include "wx/wxhtml.h"
#include "wx/grid.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class SingleOrderDataForClient: public wxDialog {
public:
    SingleOrderDataForClient(const wxString& title, const std::string &code_order, const std::string &us_prov);

    static const long IdButtonBack;

DECLARE_EVENT_TABLE()


private:
    void ComeBack(wxCommandEvent& event);

    wxButton *Back;
    wxBoxSizer *sizer;
    wxGrid *grid;
    std::string order;
    std::string username;
    std::string prov;
    std::vector<std::vector<std::string>> mat_order;
};
#endif //INGROSSO_ONLINE_SINGLEORDERDATAFORCLIENT_H
