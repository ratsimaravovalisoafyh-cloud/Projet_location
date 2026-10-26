//return QApplication::exec();
#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QGuiApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);

    QFont defaultFont = QApplication::font();
    defaultFont.setStyleStrategy(QFont::NoSubpixelAntialias);
    QApplication::setFont(defaultFont);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "AutoRentManager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
//Fond
    a.setStyleSheet(R"(
    QMainWindow {
        background-color: #151A19;
    }
    QLabel {
        color: #F1F3EF;
    }
    QPushButton {
        background-color: #C3E6B5;
        color: #151A19;
        border: none;
        border-radius: 6px;
        padding: 8px 16px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #A3B99A;
    }
)");

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("AutoRentDSN");
    db.setUserName("root");
    db.setPassword("Vals3922?");

    if (!db.open()) {
        qDebug() << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur de connexion", db.lastError().text());
        return -1;
    }

    QSqlQuery query(db);

    if (query.exec("USE autorentmanager")) {
        qDebug() << "Base autorentmanager sélectionnée.";

        if (query.exec("SELECT DATABASE()") && query.next()) {
            qDebug() << "Base active :"
                     << query.value(0).toString();
        } else {
            qDebug() << "Erreur SQL :" << query.lastError().text();
        }
    } else {
        qDebug() << "Impossible de sélectionner la base :"
                 << query.lastError().text();
    }
    MainWindow w;
    w.show();
    return a.exec();
}