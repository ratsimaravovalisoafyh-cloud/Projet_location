#ifndef CARCARD_H
#define CARCARD_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QPixmap>
#include "voiture.h"

class QLabel;
class CarCard : public QWidget
{
    Q_OBJECT
public:
    //constructeurs
    explicit CarCard(Statut statut, const QString &nom, const QString &type, const QString &prix ,const QString &immatriculation, int id, const QString &photo, QWidget *parent = nullptr, bool admin = true);

signals:
    void modifierDemande(int id);
    void supprimerDemande(int id);
    void statutDemande(int id, Statut statut);
private:
    void majImage();
    int m_id = 0;
    QLabel *m_image = nullptr;
    QPixmap m_source;
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CARCARD_H
