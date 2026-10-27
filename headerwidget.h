#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

namespace Ui {
class HeaderWidget;
}

class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);
    void setPeutAjouter(bool peut);
    ~HeaderWidget();
signals:
    void ajouterDemande();
    void notificationsDemandees();
    void profilDemande();
private:
    Ui::HeaderWidget *ui;
};

#endif // HEADERWIDGET_H
