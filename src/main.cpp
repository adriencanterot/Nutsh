#include <QtGui/QApplication>

#include <QApplication>
#include <QTextEdit>
#include <QFile>
#include <QString>
#include <QTextStream>

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

    a.setStyle(new style);
    a.setStyleSheet(getFileContent(":/css/style.css"));

    //fen�tre principale
    NutshMainWindow f;
    return a.exec();
}
