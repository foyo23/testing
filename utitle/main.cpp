
#include <QApplication>
#include "calculatorform.h"
using namespace std;

int main(int argc,char *argv[])
{
    QApplication app(argc, argv);
    Cal call;
    call.show();
   // cout << "Hello World!" << endl;
    return app.exec();
}

