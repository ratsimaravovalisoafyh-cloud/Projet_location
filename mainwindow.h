#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "role.h"
#include <QMainWindow>
#include <QList>
#include<QString>
#include <QStringList>
#include <QButtonGroup>
#include "voiture.h"
#include "voiturerepository.h"

class QScrollArea;
class CarCard;
class QGridLayout;
class QEvent;
class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;

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
    explicit MainWindow(Role role = Role::Admin, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Role m_role = Role::Admin;
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
    int m_statut = -1; // ici le -1 designe tous
    QStringList m_marques;
    //prix
    int m_prixmin = 0;
    int m_prixmax = 500000;
    QString m_recherche;
    int m_tri = 0; // 0 recommande 1 prix croissant 2 prix decroissant
    VoitureRepository m_repo;
    QWidget *m_catalogue = nullptr;// mettre de nouvelles cartes
    void mettreCartes();
    //pour les marques a ajouter au formulaire
    QVBoxLayout *m_marqueslayout = nullptr;
    QButtonGroup *m_marquegroupe = nullptr;
    QCheckBox *m_totalmarque = nullptr;
    void rafraichirMarques();
    int m_page = 0;
    int m_parPage = 6;
    QWidget *m_pagination = nullptr;
    QHBoxLayout *m_paginationLayout = nullptr;
    void majPagination(int pages);
    void allerPage(int page);

protected:
    bool eventFilter(QObject *obj, QEvent * event) override;
};
#endif // MAINWINDOW_H
