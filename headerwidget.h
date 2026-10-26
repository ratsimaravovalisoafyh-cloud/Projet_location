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
    ~HeaderWidget();
signals:
    void ajouterDemande();
private:
    Ui::HeaderWidget *ui;
};

#endif // HEADERWIDGET_H
