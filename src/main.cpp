#include <QtGui/QApplication>

#include "nutshmainwindow.h"
#include "nutshindexer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");
    NutshMainWindow f;
    f.show();
    return a.exec();
}
