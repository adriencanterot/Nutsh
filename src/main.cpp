#include <QtGui/QApplication>

#include <QApplication>
#include <QTextEdit>
#include <QString>
#include <QTextStream>
#include "nutshstyle.h"

#include "nutshmainwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");
    QTranslator translator;
    QString locale = QLocale::system().name().section('_', 0, 0);
    translator.load(":/translations/nutsh_"+locale);
    a.installTranslator(&translator);
    a.setStyle(new NutshStyle);
    QFile file(":/css/style.css");
    file.open(QIODevice::ReadOnly);
    QString styleSheetContent = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(styleSheetContent);

    //fen�tre principale
    NutshMainWindow f;
    return a.exec();
}
