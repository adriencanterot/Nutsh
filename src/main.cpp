#include <QtGui/QApplication>
#include "nutshmainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");

    //fen�tre principale
    NutshMainWindow f;
    return a.exec();
}
