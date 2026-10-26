#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include<QString>
#include <QStringList>
#include "voiture.h"
#include "voiturerepository.h"

class QScrollArea;
class CarCard;
class QGridLayout;
class QEvent;

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QList<Voiture> m_voitures;
    QList<CarCard*> m_cartes;
    QGridLayout *m_cataloglayout;
    QScrollArea *m_scroll;
    //fonction pour replacer les cartes
    int m_colonnes = 0;
    void placerCartes();
    //transmissions
    void filtrer();
    QString m_transmission;
    QStringList m_marques;
    //prix
    int m_prixmin = 0;
    int m_prixmax = 500000;
    QString m_recherche;
    int m_tri = 0; // 0 recommande 1 prix croissant 2 prix decroissant
    VoitureRepository m_repo;
    QWidget *m_catalogue = nullptr;// mettre de nouvelles cartes
    void mettreCartes();

protected:
    bool eventFilter(QObject *obj, QEvent * event) override;
};
#endif // MAINWINDOW_H
