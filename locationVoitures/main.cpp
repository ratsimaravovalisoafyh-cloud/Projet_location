#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile fichierStyle(":/style.qss");
    if (fichierStyle.open(QFile::ReadOnly | QFile::Text)) {
        a.setStyleSheet(QString::fromUtf8(fichierStyle.readAll()));
    } else {
        qWarning() << "Impossible de charger style.qss :"
                   << fichierStyle.errorString();
    }
    MainWindow w;
    w.show();

    return a.exec();
}