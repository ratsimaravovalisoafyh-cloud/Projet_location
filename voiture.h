#ifndef VOITURE_H
#define VOITURE_H
#include <QString>
 //creation des voitures

struct Voiture {
    int id;
    QString nom;
    QString immatriculation;
    QString marque;
    QString type;
    QString transmission;
    int prix;

};

#endif // VOITURE_H
