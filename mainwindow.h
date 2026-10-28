#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QStringList>
#include "role.h"
#include "voiture.h"
#include "voiturerepository.h"

class QScrollArea;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;
class QButtonGroup;
class QEvent;
class CarCard;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// la fenêtre principale : la page des véhicules (filtres, cartes, pagination)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Role role = Role::Admin, QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;   // pour replacer les cartes quand la taille change

private:
    // la fenêtre et son rôle
    Ui::MainWindow *ui;
    Role m_role = Role::Admin;

    // les données
    VoitureRepository m_repo;      // la liste des voitures
    QList<Voiture> m_voitures;     // copie de la liste affichée
    QList<CarCard *> m_cartes;     // une carte par voiture, dans le même ordre

    // la grille des cartes
    QWidget *m_catalogue = nullptr;
    QGridLayout *m_cataloglayout = nullptr;
    QScrollArea *m_scroll = nullptr;
    int m_colonnes = 0;            // nombre de colonnes actuel (0 = à recalculer)
    void mettreCartes();           // recrée toutes les cartes
    void placerCartes();           // range les cartes dans la grille
    void filtrer();                // cache les cartes qui ne passent pas les filtres

    // les filtres et le tri
    QString m_transmission;        // vide = toutes
    int m_statut = -1;             // -1 = tous les statuts
    QStringList m_marques;         // vide = toutes les marques
    int m_prixmin = 0;
    int m_prixmax = 500000;
    QString m_recherche;
    int m_tri = 0;                 // 0 = recommandé, 1 = prix croissant, 2 = prix décroissant

    // les marques dans la colonne des filtres
    QVBoxLayout *m_marqueslayout = nullptr;
    QButtonGroup *m_marquegroupe = nullptr;
    QCheckBox *m_totalmarque = nullptr;
    void rafraichirMarques();

    // la pagination
    int m_page = 0;                // page actuelle (0 = première)
    int m_parPage = 6;             // nombre de voitures par page
    QWidget *m_pagination = nullptr;
    QHBoxLayout *m_paginationLayout = nullptr;
    void majPagination(int pages);
    void allerPage(int page);
};

#endif // MAINWINDOW_H