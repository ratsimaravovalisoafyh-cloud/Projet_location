#ifndef VOITURE_H
#define VOITURE_H
#include <QString>
 //creation des voitures

 // disponibilite des voitures
 enum class Statut{
     Disponible = 0,
     Loue = 1,
     Maintenance = 2,
 };

 inline QString texteStatut(Statut s) {
     switch (s) {
     case Statut::Disponible:  return "Disponible";
     case Statut::Loue:        return "Loué";
     case Statut::Maintenance: return "En maintenance";
     }
     return {};
 }
 inline QString cleStatut(Statut s) {  //utiliser par la carte
     switch (s) {
     case Statut::Disponible:  return "disponible";
     case Statut::Loue:        return "loue";
     case Statut::Maintenance: return "maintenance";
     }
     return {};
 }
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
    //constructeur pas defaut
    Voiture() = default;
    //pour qu'il accorde les accolades
    Voiture(Statut p_statut, QString p_nom, QString p_immat, QString p_marque,
            QString p_type, QString p_trans, double p_prix, QString p_photo, int p_id = 0)
        : id(p_id), statut(p_statut), nom(p_nom), immatriculation(p_immat),
        marque(p_marque), type(p_type), transmission(p_trans), prix(p_prix), photo(p_photo) {}
};

#endif // VOITURE_H
