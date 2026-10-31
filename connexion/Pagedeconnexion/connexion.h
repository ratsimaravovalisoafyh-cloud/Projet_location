#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QComboBox;

class Connexion : public QWidget
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);

private slots:
    void seConnecter();

private:
    QLineEdit *nomUtilisateurEdit;
    QLineEdit *passwordEdit;
    QComboBox *typeCompteCombo;
    QPushButton *loginButton;
};

#endif // CONNEXION_H