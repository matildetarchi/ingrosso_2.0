#include <vector>
#include "wx/wx.h"
#include "MyApp.h"
#include "Engine.h"
#include "SQLiteCpp/Database.h"
using namespace std;

//IMPLEMENT_APP(MyApp)

int main() {




    Engine e;
    e.doLogin("andrea.lipperi@icloud.com", "Forzaroma02");
    //cout<< "ciao"<<endl;

    return 0;

}
