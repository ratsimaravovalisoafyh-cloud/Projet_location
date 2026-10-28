#ifndef VOITUREREPOSITORY_H
#define VOITUREREPOSITORY_H

#include <QList>
#include <QString>
#include "voiture.h"

// la liste des voitures:ajouter,modifier,supprimer et chercher
class VoitureRepository
{
public:
    VoitureRepository();

    QList<Voiture> toutes() const; // toutes les voitures
    int ajouter(Voiture v);
    bool modifier(const Voiture &v);
    bool supprimer(int id);
    bool changerStatut(int id, Statut statut);

    // le boleen indique vrai si une voiture a déjà cette immatriculation

    bool existenceimmatriculation(const QString &immat, int ignorerId = -1) const; // (ignorerId = la voiture qu'on est en train de modifier pour ne pas la comparer à elle-même)

private:
    QList<Voiture> m_liste;
    int m_nextId = 1; // l'id que l'on va donné à la prochaine voiture ajoutée
};

#endif // VOITUREREPOSITORY_H
