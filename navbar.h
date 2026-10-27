#ifndef NAVBAR_H
#define NAVBAR_H

#include <QWidget>

class NavBar : public QWidget
{
    Q_OBJECT
public:
    explicit NavBar(QWidget *parent = nullptr);
signals:
    void pageDemandee(int index);

};

#endif // NAVBAR_H
