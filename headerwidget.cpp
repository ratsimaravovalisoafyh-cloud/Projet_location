#include "headerwidget.h"
#include "ui_headerwidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>

HeaderWidget::HeaderWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HeaderWidget)
{
    ui->setupUi(this);

    // le bouton ajouter
    connect(ui->boutonAjouter, &QPushButton::clicked, this, &HeaderWidget::ajouterDemande);
    ui->boutonAjouter->setIcon(QIcon("://images/addcircle.png"));
    ui->boutonAjouter->setIconSize(QSize(14, 14));

    // je cache le label "Rent a Car" qui vient du .ui sinon il apparait 2 fois
    const auto labels = findChildren<QLabel *>();
    for (QLabel *l : labels)
        if (l->text().compare("rent a car", Qt::CaseInsensitive) == 0)
            l->hide();

    //  notifications
    QPushButton *notif = new QPushButton(this);
    notif->setObjectName("boutonNotif");
    notif->setFixedSize(36, 36);
    notif->setIcon(QIcon("://images/notif.png"));
    notif->setIconSize(QSize(20, 20));
    notif->setCursor(Qt::PointingHandCursor);
    notif->setToolTip("Notifications");

    // le bouton du compte utilisateur
    QPushButton *utilisateur = new QPushButton(this);
    utilisateur->setObjectName("boutonUtilisateur");
    utilisateur->setFixedSize(36, 36);
    utilisateur->setIcon(QIcon("://images/profil.png"));
    utilisateur->setIconSize(QSize(20, 20));
    utilisateur->setCursor(Qt::PointingHandCursor);
    utilisateur->setToolTip("Mon compte");

    connect(notif, &QPushButton::clicked, this, &HeaderWidget::notificationsDemandees);
    connect(utilisateur, &QPushButton::clicked, this, &HeaderWidget::profilDemande);

    // positionnement des differents objets
    if (auto *h = qobject_cast<QHBoxLayout *>(layout())) {
        QLabel *titre = new QLabel("Véhicules", this);
        titre->setObjectName("headerTitre");
        QLabel *sousTitre = new QLabel("Gérez vos voitures proprement", this);
        sousTitre->setObjectName("headerSousTitre");

        QVBoxLayout *blocTitre = new QVBoxLayout;
        blocTitre->setSpacing(2);
        blocTitre->setContentsMargins(0, 0, 0, 0);
        blocTitre->addWidget(titre);
        blocTitre->addWidget(sousTitre);
        h->insertLayout(0, blocTitre); // le titre tout à gauche

        int pos = h->indexOf(ui->boutonAjouter);
        h->insertWidget(pos, notif); // cloche juste avant "Ajouter"
        h->insertWidget(pos + 1, utilisateur);
        h->setSpacing(12);
    }
}

// le bouton Ajouter n'est visible que pour l'admin
void HeaderWidget::setPeutAjouter(bool peut)
{
    ui->boutonAjouter->setVisible(peut);
}

HeaderWidget::~HeaderWidget()
{
    delete ui;
}