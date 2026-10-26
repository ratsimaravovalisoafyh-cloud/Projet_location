#include "voiturerepository.h"


VoitureRepository::VoitureRepository() {
    ajouter({0, "Mercedes-Benz", "1234 TAB", "Toyota", "Berline", "Automatique", 150000});
    ajouter({0, "Ford Mustang", "1810 TBH", "Toyota", "Coupé sportif", "Manuelle", 90000});
    ajouter({0, "BMW Série 7", "1106 BRAD", "Hyundai", "Berline", "Manuelle", 400000});
    ajouter({0, "Ferrari", "1204 ANG", "Hyundai", "Hypercar", "Automatique", 600000});
    ajouter({0, "Range Rover", "1510 TSI", "Renault", "Berline", "Manuelle", 100000});
    ajouter({0, "Porsche Cayenne", "1909 MIT", "Renault", "SUV", "Automatique", 300000});
}

//liste voitures
QList<Voiture> VoitureRepository::toutes() const
{
    return m_liste;
}

// fonction ajouter
int VoitureRepository::ajouter(Voiture v)
{
    v.id = m_nextId++;
    m_liste.append(v);
    return v.id;
}

//fonction modifier
bool VoitureRepository:: modifier(const Voiture &v)
{
    for(int i = 0; i < m_liste.size(); ++i){
        if (m_liste[i].id == v.id){
            m_liste[i] = v;
            return true;
        }
    }
    return false;
}

//fonction supprimer
bool VoitureRepository::supprimer(int id){
    for (int i = 0; i < m_liste.size(); ++i){
    if (m_liste[i].id == id){
            m_liste.removeAt(i);
        return true;
      }
    }
    return false;
}

//fonction exister immatriculation
bool VoitureRepository::existenceimmatriculation(const QString &immat, int ignorerId) const{
    for (const Voiture &v : m_liste){
        if (v.id != ignorerId && v.immatriculation.compare(immat.trimmed(), Qt::CaseInsensitive) == 0)
            return true;
    }
    return false;
}





















