//
// Created by Andrea Lipperi on 04/05/23.
//

#include "ChooseStatusPage.h"

using namespace std;


const long ChooseStatusPage::IdButtonInsert =::wxNewId();
const long ChooseStatusPage::IdButtonComeBack =::wxNewId();

BEGIN_EVENT_TABLE (ChooseStatusPage, wxFrame)
                EVT_BUTTON(IdButtonInsert, ChooseStatusPage::InsertProduct)
                EVT_BUTTON(IdButtonComeBack, ChooseStatusPage::ComeBack)
END_EVENT_TABLE()

ChooseStatusPage::ChooseStatusPage(Engine* e, const wxString &title) :engine(e),
        wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 350)){

    user= e->get_user();
    type=user->get_type();

    wxStaticText *txt = new wxStaticText(this, -1, wxT("CHOOSE STATUS OF THE ORDERS YOU WANT TO SEE"));

    Insert=new wxButton (this,IdButtonInsert,_T ("Insert"),wxDefaultPosition,wxDefaultSize,0);
    Back=new wxButton(this,IdButtonComeBack,_T ("Back"),wxDefaultPosition,wxDefaultSize,0);

    choice=new wxChoice(this, wxID_ANY,wxDefaultPosition, wxDefaultSize);
    wxString myChoice[]={"Only Pending", "All"};
    choice->Append("Select");
    choice->Append(2,myChoice);

    sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(txt, 0);
    sizer->Add(choice, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Insert, 1, wxEXPAND | wxALL, 5);
    sizer->Add(Back, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);


    Centre();

}
void ChooseStatusPage::InsertProduct(wxCommandEvent &event) {
    if (choice->GetSelection() == wxNOT_FOUND)
    {
        wxMessageBox("Choose an option", "Error", wxICON_ERROR);
    } else {
        int Id_choice = choice->GetSelection()-1;
        if (type=="F") {
            ManageRequestPage *req = new ManageRequestPage(engine, _T("YOUR REQUESTS"), Id_choice);
            // Passa la stringa alla classe wxFrame di destinazione.
            req->Show(TRUE);
        } else {
            OrderHistoryForClientPage *ord = new OrderHistoryForClientPage(engine,_T("YOUR ORDERS"), Id_choice);
            // Passa la stringa alla classe wxFrame di destinazione.
            ord->Show(TRUE);
        }

    }
}

void ChooseStatusPage::ComeBack(wxCommandEvent &event) {

    Close();

}
