#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFileSystemWatcher>
#include <QStyleHints>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.styleHints()->setColorScheme(Qt::ColorScheme::Light);   // toujours le thème clair

    // le style : si "C:/style.qss" existe on l'utilise (pratique pour tester),
    // sinon on prend celui qui est dans le programme
    const QString chemin = "C:/style.qss";

    auto charger = [&a, chemin]() {
        QFile fichier(QFile::exists(chemin) ? chemin : QString(":/style.qss"));
        if (fichier.open(QFile::ReadOnly | QFile::Text))
            a.setStyleSheet(QString::fromUtf8(fichier.readAll()));
    };
    charger();

    // quand on enregistre "C:/style.qss", le style se recharge tout seul, sans relancer
    if (QFile::exists(chemin)) {
        auto *veilleur = new QFileSystemWatcher({chemin}, &a);
        QObject::connect(veilleur, &QFileSystemWatcher::fileChanged, &a,
                         [veilleur, chemin, charger]() {
                             charger();
                             // certains éditeurs remplacent le fichier : on le surveille de nouveau
                             if (!veilleur->files().contains(chemin))
                                 veilleur->addPath(chemin);
                         });
    }

    // pour tester l'employé, remplace Role::Admin par Role::Employe
    MainWindow w(Role::Admin);
    w.show();
    return QApplication::exec();
}
