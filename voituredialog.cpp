#include "voituredialog.h"
#include "ui_voituredialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>
#include <QUuid>
#include <QPixmap>
#include <QComboBox>

VoitureDialog::VoitureDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VoitureDialog)
{
    ui->setupUi(this);
    setObjectName("dialogVoiture");
    setAttribute(Qt::WA_StyledBackground, true);

 // apropos des photos
    m_apercu = new QLabel("Aucune");
    m_apercu->setFixedSize(96, 60);
    m_apercu->setAlignment(Qt::AlignCenter);
    QPushButton *choisir = new QPushButton("Choisir une photo...");
    choisir->setAutoDefault(false);
    //champ du status
    m_comboStatut = new QComboBox;
    for (Statut s : {Statut::Disponible, Statut::Loue, Statut::Maintenance})
        m_comboStatut->addItem(texteStatut(s), static_cast<int>(s));
    ui->formLayout->addRow("Statut :", m_comboStatut);

//ajout photo
    QHBoxLayout *ligne = new QHBoxLayout;
    ligne->addWidget(choisir);
    ligne->addWidget(m_apercu);
    ligne->addStretch();
    ui->formLayout->addRow("Photo :", ligne);


    connect(choisir, &QPushButton::clicked, this, [this]() {
        QString source = QFileDialog::getOpenFileName(
            this, "Choisir une photo", QString(),
            "Images (*.png *.jpg *.jpeg *.webp)");
        if (source.isEmpty())
            return;


        QString dossier = QCoreApplication::applicationDirPath() + "/photos";
        QDir().mkpath(dossier);
        QString dest = dossier + "/"
                       + QUuid::createUuid().toString(QUuid::WithoutBraces)
                       + "." + QFileInfo(source).suffix().toLower();
        if (!QFile::copy(source, dest)) {
            QMessageBox::warning(this, "Photo", "Impossible de copier l'image.");
            return;
        }
        m_photo = dest;
        afficherApercu();
    });
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
    v.photo = m_photo;
    v.statut = static_cast<Statut>(m_comboStatut->currentData().toInt());
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
    m_photo = v.photo;
    afficherApercu();
    m_comboStatut->setCurrentIndex(m_comboStatut->findData(static_cast<int>(v.statut)));
    setWindowTitle("Modifier la voiture");
}

// afficher un apercu
void VoitureDialog::afficherApercu()
{
    QPixmap pm(m_photo);
    if (m_photo.isEmpty() || pm.isNull()) {
        m_apercu->setPixmap(QPixmap());
        m_apercu->setText("Aucune");
        return;
    }
    m_apercu->setPixmap(pm.scaled(m_apercu->size(), Qt::KeepAspectRatio,
                                  Qt::SmoothTransformation));
}

VoitureDialog::~VoitureDialog()
{
    delete ui;
}
