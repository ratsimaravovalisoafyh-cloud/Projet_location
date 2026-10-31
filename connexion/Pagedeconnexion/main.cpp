#include <QApplication>
#include "connexion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Connexion fenetre;
    fenetre.show();

    return app.exec();
}