#include <vector>
#include "wx/wx.h"
#include "MyApp.h"
#include "Engine.h"
#include "SQLiteCpp/Database.h"
using namespace std;

//IMPLEMENT_APP(MyApp)

//TODO riguardare quantity e quantity_available

int main() {


    Engine e;
    e.do_login("andrea.lipperi@icloud.com", "Forzaroma02");


    return 0;

}