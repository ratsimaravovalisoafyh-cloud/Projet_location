#ifndef VOITUREDIALOG_H
#define VOITUREDIALOG_H

#include <QDialog>
#include <QString>
#include "voiture.h"

class QLabel;
class QComboBox;

namespace Ui {
class VoitureDialog;
}

// la fenêtre pour ajouter une voiture ou modifier une voiture existante
class VoitureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoitureDialog(QWidget *parent = nullptr);
    ~VoitureDialog();

    Voiture voiture() const;               // lit le formulaire et renvoie la voiture
    void remplir(const Voiture &v);        // remplit le formulaire (pour modifier)

protected:
    void accept() override;                // vérifie les champs obligatoires avant de fermer

private:
    void afficherApercu();                 // montre la photo choisie en petit

    Ui::VoitureDialog *ui;
    int m_id = 0;                          // 0 pour une nouvelle voiture
    QString m_photo;                       // chemin de la photo choisie
    QLabel *m_apercu = nullptr;            // l'aperçu de la photo
    QComboBox *m_comboStatut = nullptr;    // le choix du statut
};

#endif // VOITUREDIALOG_H
