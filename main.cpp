#include "mainwindow.h"
#include "dbconnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBConnection::getInstance ().init ();
    MainWindow w;
    w.show();

    return a.exec();
}
