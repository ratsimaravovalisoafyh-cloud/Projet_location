#include "headerwidget.h"
#include "ui_headerwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QVBoxLayout>

HeaderWidget::HeaderWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HeaderWidget)
{
    ui->setupUi(this);
    connect(ui->boutonAjouter, &QPushButton::clicked, this, &HeaderWidget::ajouterDemande);
    ui->boutonAjouter->setIcon(QIcon("://images/addcircle.png"));// icone pour ajouter
    ui->boutonAjouter->setIconSize(QSize(14, 14));

    // mettre rent a car
    const auto labels = findChildren<QLabel *>();
    for (QLabel *l : labels)
        if (l->text().compare("rent a car", Qt::CaseInsensitive) == 0)
            l->hide();

    // Cloche de notification
    QPushButton *notif = new QPushButton;
    notif->setObjectName("boutonNotif");
    notif->setFixedSize(36, 36);
    notif->setIcon(QIcon("://images/notif.png"));//icon de notif
    notif->setIconSize(QSize(20, 20));
    notif->setCursor(Qt::PointingHandCursor);
    notif->setToolTip("Notifications");

    // Utilisateur
    QPushButton *utilisateur = new QPushButton;
    utilisateur->setObjectName("boutonUtilisateur");
    utilisateur->setFixedSize(36, 36);
    utilisateur->setIcon(QIcon("://images/profil.png")); // utilisateurs icon
    utilisateur->setIconSize(QSize(20, 20));
    utilisateur->setCursor(Qt::PointingHandCursor);
    utilisateur->setToolTip("Mon compte");

    connect(notif, &QPushButton::clicked, this, &HeaderWidget::notificationsDemandees);
    connect(utilisateur, &QPushButton::clicked, this, &HeaderWidget::profilDemande);

    //co;pleter le vide sideral
    if (auto *h = qobject_cast<QHBoxLayout *>(layout())) {
        // Titre de la page, à gauche
        QLabel *titre = new QLabel("Véhicules");
        titre->setObjectName("headerTitre");
        QLabel *sousTitre = new QLabel("Gérez vos voitures proprement");
        sousTitre->setObjectName("headerSousTitre");

        QVBoxLayout *blocTitre = new QVBoxLayout;
        blocTitre->setSpacing(2);
        blocTitre->setContentsMargins(0, 0, 0, 0);
        blocTitre->addWidget(titre);
        blocTitre->addWidget(sousTitre);
        h->insertLayout(0, blocTitre);

        int pos = h->indexOf(ui->boutonAjouter);
        h->insertWidget(pos, notif);
        h->insertWidget(pos + 1, utilisateur);
        h->setSpacing(12);
    }

}
//pour ajouter le bouton quand c'est admin
void HeaderWidget::setPeutAjouter(bool peut){
    ui->boutonAjouter->setVisible(peut);
}
    HeaderWidget::~HeaderWidget()
{
    delete ui;
}