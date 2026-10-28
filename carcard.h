#ifndef CARCARD_H
#define CARCARD_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QSize>
#include "voiture.h"

class QLabel;
class QResizeEvent;

// une carte qui affiche une voiture (photo, nom, prix, statut, boutons)
class CarCard : public QWidget
{
    Q_OBJECT
public:
    explicit CarCard(Statut statut, const QString &nom, const QString &type, const QString &prix,
                     const QString &immatriculation, int id, const QString &photo,
                     QWidget *parent = nullptr, bool admin = true);

signals:
    void modifierDemande(int id);                 // clic sur "Modifier"
    void supprimerDemande(int id);                // clic sur "Supprimer"
    void statutDemande(int id, Statut statut);    // on a choisi un nouveau statut dans le badge

protected:
    void resizeEvent(QResizeEvent *event) override;   // on redimensionne la photo avec la carte

private:
    void majImage();

    int m_id = 0;                  // l'id de la voiture
    QLabel *m_image = nullptr;     // le label qui montre la photo
    QPixmap m_source;              // la photo d'origine, gardée pour la redimensionner
    QSize m_derniereTaille;        // dernière taille de photo, pour ne pas refaire le travail pour rien
};

#endif // CARCARD_H
