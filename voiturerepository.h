#ifndef VOITUREREPOSITORY_H
#define VOITUREREPOSITORY_H

#include <QList>
#include <QString>
#include "voiture.h"

// la liste des voitures : on y ajoute, modifie, supprime et cherche
// (pour l'instant tout est gardé en mémoire, rien n'est enregistré dans un fichier)
class VoitureRepository
{
public:
    VoitureRepository();

    QList<Voiture> toutes() const;                    // toutes les voitures
    int ajouter(Voiture v);                           // ajoute une voiture et renvoie son nouvel id
    bool modifier(const Voiture &v);                  // remplace la voiture qui a le même id
    bool supprimer(int id);                           // supprime la voiture avec cet id
    bool changerStatut(int id, Statut statut);        // change seulement le statut

    // vrai si une voiture a déjà cette immatriculation
    // (ignorerId = la voiture qu'on est en train de modifier, pour ne pas la comparer à elle-même)
    bool existenceimmatriculation(const QString &immat, int ignorerId = -1) const;

private:
    QList<Voiture> m_liste;
    int m_nextId = 1;                                 // l'id donné à la prochaine voiture ajoutée
};

#endif // VOITUREREPOSITORY_H
