#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

namespace Ui {
class HeaderWidget;
}

// pour le titre du haut avec  titre de la page, notifications, compte et bouton "Ajouter"
class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);
    ~HeaderWidget();

    void setPeutAjouter(bool peut);   // cacher le bouton "Ajouter" (admin seulement)

signals:
    void ajouterDemande();
    void notificationsDemandees();
    void profilDemande();

private:
    Ui::HeaderWidget *ui;
};

#endif // HEADERWIDGET_H