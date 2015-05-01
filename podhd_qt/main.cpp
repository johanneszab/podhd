#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Podhd");
    //a.setApplicationVersion(PODHD_VERSION_DISPLAY);
    a.setOrganizationName("Podhd");
    a.setOrganizationDomain("jzab.de/pod-hd");

    MainWindow w;
    w.show();
    
    return a.exec();
}
