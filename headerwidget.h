#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

namespace Ui {
class HeaderWidget;
}

// la bande du haut : titre de la page, notifications, compte et bouton "Ajouter"
class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);
    ~HeaderWidget();

    void setPeutAjouter(bool peut);   // montre ou cache le bouton "Ajouter" (admin seulement)

signals:
    void ajouterDemande();            // clic sur "Ajouter une voiture"
    void notificationsDemandees();    // clic sur la cloche
    void profilDemande();             // clic sur le compte utilisateur

private:
    Ui::HeaderWidget *ui;
};

#endif // HEADERWIDGET_H