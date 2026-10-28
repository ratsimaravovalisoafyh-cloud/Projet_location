#ifndef VOITURE_H
#define VOITURE_H

#include <QString>

// l'état de la voiture
enum class Statut {
    Disponible  = 0,
    Loue        = 1,
    Maintenance = 2,
};

// badge, filtre, liste du dialogue afficher a l'ecran
inline QString texteStatut(Statut s)
{
    switch (s) {
    case Statut::Disponible:  return "Disponible";
    case Statut::Loue:        return "Loué";
    case Statut::Maintenance: return "En maintenance";
    }
    return {};
}

// le mot utilisé par le QSS pour colorer le badge (propriété "statut" de la carte)
inline QString cleStatut(Statut s)
{
    switch (s) {
    case Statut::Disponible:  return "disponible";
    case Statut::Loue:        return "loue";
    case Statut::Maintenance: return "maintenance";
    }
    return {};
}

// informations de la  voiture
struct Voiture {
    int id = 0;
    Statut statut = Statut::Disponible;
    QString nom;
    QString immatriculation;
    QString marque;
    QString type;
    QString transmission;
    double prix = 0.0;
    QString photo;

    Voiture() = default;

    // pour faire ne sorte que les accolades soit trouve quand on met une nouvelle voiture  {Statut::Loue, "Ford", ...}
    Voiture(Statut p_statut, const QString &p_nom, const QString &p_immat, const QString &p_marque,
            const QString &p_type, const QString &p_trans, double p_prix, const QString &p_photo,
            int p_id = 0)
        : id(p_id), statut(p_statut), nom(p_nom), immatriculation(p_immat),
        marque(p_marque), type(p_type), transmission(p_trans), prix(p_prix), photo(p_photo) {}
};

#endif // VOITURE_H