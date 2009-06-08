#include <QtGui/QApplication>
#include "nutshmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");

    //fenêtre principale
    NutshMainWindow f;
    return a.exec();
}
