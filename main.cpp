#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFileSystemWatcher>
#include <QStyleHints>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.styleHints()->setColorScheme(Qt::ColorScheme::Light); //pour mettre le theme au clair

    // le style:si "C:/style.qss" existe on l'utilise (pratique pour tester),
    // sinon on prend celui qui est dans le programme
    const QString chemin = "C:/style.qss";

    auto charger = [&a, chemin]() {
        QFile fichier(QFile::exists(chemin) ? chemin : QString(":/style.qss"));
        if (fichier.open(QFile::ReadOnly | QFile::Text))
            a.setStyleSheet(QString::fromUtf8(fichier.readAll()));
    };
    charger();

    // quand on enregistre :/style.qss le style se recharge tout seul sans relancer
    if (QFile::exists(chemin)) {
        auto *veilleur = new QFileSystemWatcher({chemin}, &a);
        QObject::connect(veilleur, &QFileSystemWatcher::fileChanged, &a,[veilleur, chemin, charger]() {
             charger();  // certains personnes remplacent le fichier donc on va le surveiller de nouveau
           if (!veilleur->files().contains(chemin))
            veilleur->addPath(chemin);
         });
    }

    // pour le role genre cote admin et cote employe
    MainWindow w(Role::Admin);
    w.show();
    return QApplication::exec();
}
