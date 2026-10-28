#include "voiturerepository.h"

// au démarrage on met quelques voitures de test
VoitureRepository::VoitureRepository()
{
    ajouter({Statut::Disponible,  "Mercedes-Benz",  "1234 TAB",  "Toyota",  "Berline",       "Automatique", 180000, ":/images/mercedes benz berline.jpg"});
    ajouter({Statut::Loue,        "Ford Mustang",   "1810 TBH",  "Toyota",  "Coupé sportif", "Manuelle",    250000, ":/images/ford mustang.png"});
    ajouter({Statut::Maintenance, "BMW Série 7",    "1106 BRAD", "Hyundai", "Berline",       "Manuelle",    450000, ":/images/BMW serie 7 black.jpg"});
    ajouter({Statut::Disponible,  "Ferrari",        "1204 ANG",  "Hyundai", "Hypercar",      "Automatique", 600000, ":/images/ferrari.jpg"});
    ajouter({Statut::Disponible,  "Range Rover",    "1510 TSI",  "Renault", "Berline",       "Manuelle",    300000, ":/images/range rover.jpg"});
    ajouter({Statut::Loue,        "Porsche Cayenne","1909 MIT",  "Renault", "SUV",           "Automatique", 350000, ":/images/porsche Cayenne.jpg"});
    ajouter({Statut::Disponible,  "Toyota Corolla", "2045 TAA",  "Toyota",  "Berline",       "Manuelle",     60000, ":/images/toyotacorolla.png"});
    ajouter({Statut::Disponible,  "Hyundai Tucson", "3321 TBC",  "Hyundai", "SUV",           "Automatique",  90000, ":/images/hyundaitucson .png"});
    ajouter({Statut::Disponible,  "Renault Clio",   "4410 TDD",  "Renault", "Citadine",      "Manuelle",     45000, ":/images/renaultclio.png"});
    ajouter({Statut::Maintenance, "Toyota Hilux",   "5120 TEE",  "Toyota",  "Pick-up",       "Manuelle",    120000, ":/images/toyotahilux.png"});
    ajouter({Statut::Disponible,  "Hyundai i10",    "6032 TFF",  "Hyundai", "Citadine",      "Automatique",  50000, ":/images/Hyundai i10 .png"});
    ajouter({Statut::Disponible,  "Renault Duster", "7714 TGG",  "Renault", "SUV",           "Manuelle",     80000, ":/images/renaultduster.png"});
}

// toute la liste des voitures
QList<Voiture> VoitureRepository::toutes() const
{
    return m_liste;
}

// on ajoute une voiture et on lui donne un nouvel id (on le renvoie)
int VoitureRepository::ajouter(Voiture v)
{
    v.id = m_nextId++;
    m_liste.append(v);
    return v.id;
}

// on remplace la voiture qui a le même id (false si elle n'existe pas)
bool VoitureRepository::modifier(const Voiture &v)
{
    for (int i = 0; i < m_liste.size(); ++i) {
        if (m_liste[i].id == v.id) {
            m_liste[i] = v;
            return true;
        }
    }
    return false;
}

// on supprime la voiture avec cet id (false si elle n'existe pas)
bool VoitureRepository::supprimer(int id)
{
    for (int i = 0; i < m_liste.size(); ++i) {
        if (m_liste[i].id == id) {
            m_liste.removeAt(i);
            return true;
        }
    }
    return false;
}

// est-ce qu'une voiture a déjà cette immatriculation ?
// "ignorerId" sert à la modification : la voiture ne doit pas se comparer à elle-même
bool VoitureRepository::existenceimmatriculation(const QString &immat, int ignorerId) const
{
    for (const Voiture &v : m_liste) {
        if (v.id != ignorerId && v.immatriculation.compare(immat.trimmed(), Qt::CaseInsensitive) == 0)
            return true;
    }
    return false;
}

// on change seulement le statut d'une voiture (false si elle n'existe pas)
bool VoitureRepository::changerStatut(int id, Statut statut)
{
    for (int i = 0; i < m_liste.size(); ++i) {
        if (m_liste[i].id == id) {
            m_liste[i].statut = statut;
            return true;
        }
    }
    return false;
}



















