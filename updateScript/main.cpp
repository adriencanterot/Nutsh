#include <QtCore/QCoreApplication>
#include "nutshupdater.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NutshUpdate update;
    return a.exec();
}
