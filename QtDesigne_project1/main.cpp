#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "QtEvents.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Service service;
   
    GUI ui(service);

    ui.show();


    return a.exec();
}
