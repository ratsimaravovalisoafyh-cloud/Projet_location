#ifndef NAVBAR_H
#define NAVBAR_H

#include <QWidget>

class QPushButton;

// la barre de navigation à gauche : logo et boutons Dashboard, Véhicules, Clients, Locations
class NavBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavBar(QWidget *parent = nullptr);

    void setDashboardVisible(bool visible);   // cache le Dashboard pour l'employé

signals:
    void pageDemandee(int index);             // clic sur un bouton (0 Dashboard, 1 Véhicules, 2 Clients, 3 Locations)

private:
    QPushButton *m_boutonDashboard = nullptr;
};

#endif // NAVBAR_H