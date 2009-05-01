#include <QtGui/QApplication>
#include "nutshmaj.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NutshMaJ w;
    w.show();
    system("killall nutsh-05");
    return a.exec();
}
