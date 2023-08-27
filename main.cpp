#include <vector>
#include "wx/wx.h"
#include "MyApp.h"
#include "Engine.h"
#include "SQLiteCpp/Database.h"
using namespace std;

//IMPLEMENT_APP(MyApp)

//TODO riguardare quantity e quantity_available

int main() {

    shared_ptr<User> user= make_shared<User>("C","05550649455", "via.rossi 365", "filippo.nespe@gmail.com", "mare62", "Filippo s.r.l", "Roma" );
    Engine e;
    e.do_registration(user);

    return 0;

}