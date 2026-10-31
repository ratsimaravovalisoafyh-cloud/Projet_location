#include "voituredialog.h"
#include "ui_voituredialog.h"
#include <QMessageBox>
VoitureDialog::VoitureDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VoitureDialog)
{
    ui->setupUi(this);
}

//remplissage du formulaire
Voiture VoitureDialog::voiture() const{
    Voiture v;
    v.id = m_id;
    v.nom = ui->lineNom->text().trimmed();
    v.immatriculation = ui->lineImmat->text().trimmed();
    v.marque = ui->comboMarque->currentText().trimmed();
    v.type = ui->comboType->currentText().trimmed();
    v.transmission = ui->comboTransmission->currentText().trimmed();
    v.prix =ui->spinPrix->value();
    return v;
}

void VoitureDialog::accept()
{
    if (ui->lineNom->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Champ manquant", "Le nom est obligatoire.");
        ui->lineNom->setFocus();
        return;
    }
    if (ui->lineImmat->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Champ manquant", "l'immatriculation est obligatoire.");
        ui->lineImmat->setFocus();
        return;
    }
    if (ui->comboMarque->currentText().trimmed().isEmpty()){
        QMessageBox::warning(this, "Champ manquant", "La marque est obligatoire.");
        return;
    }
    if (ui->spinPrix->value() <= 0){
        QMessageBox::warning(this, "Champ manquant", "Le prix journalier doit être supérieur à 0.");
        ui->spinPrix->setFocus();
        return;
    }
    QDialog::accept();
}
void VoitureDialog::remplir(const Voiture &v)
{
    m_id = v.id;
    ui->lineNom->setText(v.nom);
    ui->lineImmat->setText(v.immatriculation);
    ui->comboMarque->setCurrentText(v.marque);
    ui->comboType->setCurrentText(v.type);
    ui->comboTransmission->setCurrentText(v.transmission);
    ui->spinPrix->setValue(v.prix);
    setWindowTitle("Modifier la voiture");
}
VoitureDialog::~VoitureDialog()
{
    delete ui;
}
