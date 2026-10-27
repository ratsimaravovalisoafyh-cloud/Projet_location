#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QStyleHints>
#include <QFileSystemWatcher>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.styleHints()->setColorScheme(Qt::ColorScheme::Light);
    const QString chemin = "C:/style.qss";

    auto charger = [&a, chemin]() {
        QFile fichier(QFile::exists(chemin) ? chemin : QString(":/style.qss"));
        if (fichier.open(QFile::ReadOnly | QFile::Text))
            a.setStyleSheet(QString::fromUtf8(fichier.readAll()));
    };
    charger();

    auto *veilleur = new QFileSystemWatcher({chemin}, &a);
    QObject::connect(veilleur, &QFileSystemWatcher::fileChanged, &a,
                     [veilleur, chemin, charger]() {
                         charger();
                         if (!veilleur->files().contains(chemin))
                             veilleur->addPath(chemin);
                     });
    MainWindow w(Role::Admin);
    w.show();
    return QApplication::exec();
}
