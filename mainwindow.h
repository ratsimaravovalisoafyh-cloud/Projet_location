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

// la page des véhicules (filtres, cartes, pagination)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Role role = Role::Admin, QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    // pour replace les cartes quand la taille change
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    // la fenêtre avec le rôle
    Ui::MainWindow *ui;
    Role m_role = Role::Admin;

    // les données avec la liste des voitures
    VoitureRepository m_repo;
    QList<Voiture> m_voitures; // copie de la liste affichée
    QList<CarCard *> m_cartes; // fais en sorte qu'il y ait une carte par voiture, dans le même ordre

    // la grille pour les cartes
    QWidget *m_catalogue = nullptr;
    QGridLayout *m_cataloglayout = nullptr;
    QScrollArea *m_scroll = nullptr;
    int m_colonnes = 0;
    void mettreCartes();
    void placerCartes();
    void filtrer();

    // les filtres et le tri
    QString m_transmission;
    int m_statut = -1; //pour tous les status
    QStringList m_marques;
    int m_prixmin = 0;
    int m_prixmax = 500000;
    QString m_recherche;
    int m_tri = 0; // 0 pour recommandé, 1 pour prix croissant, 2 pour prix décroissant

    // les marques dans la partie des filtres
    QVBoxLayout *m_marqueslayout = nullptr;
    QButtonGroup *m_marquegroupe = nullptr;
    QCheckBox *m_totalmarque = nullptr;
    void rafraichirMarques();

    // la pagination
    int m_page = 0; // page actuelle (0 = première)
    int m_parPage = 6;
    QWidget *m_pagination = nullptr;
    QHBoxLayout *m_paginationLayout = nullptr;
    void majPagination(int pages);
    void allerPage(int page);
};

#endif // MAINWINDOW_H