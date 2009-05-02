#include <QtGui/QApplication>
#include "nutshupdater.h"
#include "nutshmainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");
    NutshMainWindow f;
    f.show();
    NutshUpdater update(&f);
    if(update.isUpdate()) {
        update.exec();
    }
    return a.exec();
}
