#ifndef CARCARD_H
#define CARCARD_H

#include <QObject>
#include <QWidget>
#include <QString>
class CarCard : public QWidget
{
    Q_OBJECT
public:
    //constructeurs
    explicit CarCard(const QString &nom, const QString &type, const QString &prix ,const QString &immatriculation, int id, QWidget *parent = nullptr);

signals:
    void modifierDemande(int id);
    void supprimerDemande(int id);

private:
    int m_id = 0;
};

#endif // CARCARD_H
