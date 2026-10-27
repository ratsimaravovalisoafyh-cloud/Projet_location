#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class toolbar;
}

class toolbar : public QWidget
{
    Q_OBJECT

public:
    explicit toolbar(QWidget *parent = nullptr);
    ~toolbar();
signals:
    void rechercheChange(const QString &texte);
    void triChange(int index);
private:
    Ui::toolbar *ui;
};

#endif // TOOLBAR_H
