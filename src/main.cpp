#include <QtGui/QApplication>

#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "nutshstyle.h"

#include "nutshmainwindow.h"

QString getFileContent(const QString& path) {
    QFile f(path);
    f.open(QIODevice::ReadOnly);

    QString styleSheetContent = QLatin1String(f.readAll());
    f.close();

    return styleSheetContent;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Nutsh!");
    QTranslator translator;
    QString locale = QLocale::system().name().section('_', 0, 0);
    translator.load(":/translations/nutsh_"+locale);
    a.installTranslator(&translator);
    a.setStyle(new NutshStyle);
    a.setStyleSheet(getFileContent(":/css/style.css"));

    //fenêtre principale
    NutshMainWindow f;
    return a.exec();
}
