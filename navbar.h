#ifndef NAVBAR_H
#define NAVBAR_H

#include <QWidget>

class QPushButton;

//  logo et boutons Dashboard, Véhicules, Clients, Locations
class NavBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavBar(QWidget *parent = nullptr);
 // cache le Dashboard pour l'employé
    void setDashboardVisible(bool visible);

signals:
    // 0 Dashboard, 1 Véhicules, 2 Clients, 3 Locations pour changer de page
    void pageDemandee(int index);

private:
    QPushButton *m_boutonDashboard = nullptr;
};

#endif // NAVBAR_H