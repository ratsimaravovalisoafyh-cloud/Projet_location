#ifndef VOITUREREPOSITORY_H
#include <QList>
#include "voiture.h"
#define VOITUREREPOSITORY_H

class VoitureRepository
{
public:
    VoitureRepository();

    QList<Voiture> toutes() const;
    int ajouter(Voiture v);//envoiye id que possede lq voiture
    bool modifier(const Voiture &v);//retrouve lq voiture pqr son id
    bool supprimer(int id);
    bool existenceimmatriculation(const QString &immat, int ignorerId = -1)const;
    bool changerStatut(int id, Statut statut);
private:
    QList<Voiture> m_liste;
    int m_nextId =  1;
};


#endif // VOITUREREPOSITORY_H
