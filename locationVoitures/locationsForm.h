#ifndef LOCATIONSFORM_H
#define LOCATIONSFORM_H

#include <QDialog>

namespace Ui {
class locationsForm;
}

class locationsForm : public QDialog
{
    Q_OBJECT

public:
    explicit locationsForm(QWidget *parent = nullptr,
                             int idLocation = -1);
    ~locationsForm();
    int locationIdEnregistree() const;

private:
    Ui::locationsForm *ui;
    int m_idLocation = -1;
    int m_ancienneVoitureId = -1;
    int m_locationIdEnregistree = -1;


    void Clients(); //recuperer les clients depuis MySql pour le combo client
    void Voitures(); // voitures dispo pour combo voitures
    void calculMontant(); //prix location
    void enregistrerLocation();
    double tarifJournalier(int idVoiture);
    void chargementLocationPourModif(); //pour modifier location
};

#endif // LOCATIONSFORM_H
