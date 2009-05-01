#include <QtGui/QApplication>
#include "nutshupdater.h"
#include "nutshmainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");
    NutshUpdater update;
    NutshMainWindow f;
    f.show();
    update.show();
    return a.exec();
}
