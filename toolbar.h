#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QString>

namespace Ui {
class toolbar;
}

// la barre sous le header : la recherche et le choix du tri
class toolbar : public QWidget
{
    Q_OBJECT

public:
    explicit toolbar(QWidget *parent = nullptr);
    ~toolbar();

signals:
    void rechercheChange(const QString &texte);   // le texte de la recherche a changé
    void triChange(int index);                    // le tri a changé (0 recommandé, 1 prix croissant, 2 prix décroissant)

private:
    Ui::toolbar *ui;
};

#endif // TOOLBAR_H
