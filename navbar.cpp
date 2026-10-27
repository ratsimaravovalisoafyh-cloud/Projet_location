#include "navbar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QIcon>
#include <QPixmap>

NavBar::NavBar(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("navbar");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedWidth(190);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(14, 20, 14, 20);
    layout->setSpacing(6);

    //logo et titre
    QHBoxLayout *logoLayout = new QHBoxLayout;
    logoLayout->setSpacing(10);

    QLabel *logo = new QLabel;
    logo->setObjectName("navLogo");// changer la couleur du logo
    logo->setPixmap(QPixmap("://images/logo.png")
                        .scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setFixedSize(40, 40);
    logo->setAlignment(Qt::AlignCenter);

    QLabel *titre = new QLabel("Rent a Car");
    titre->setObjectName("navTitre");

    logoLayout->addWidget(logo);
    logoLayout->addWidget(titre);
    logoLayout->addStretch();
    layout->addLayout(logoLayout);
    layout->addSpacing(24);

    //  Boutons
    QButtonGroup *groupe = new QButtonGroup(this);
    groupe->setExclusive(true);

    struct Entree { const char *icone; const char *texte; };
    const Entree entrees[] = {
                               {"icons-analytics-80",  "Dashboard"},
                               {"icons-car-80",    "Véhicules"},
                               {"icons-group-80",    "Clients"},
                               {"icons-schedule-80",  "Locations"},
                               };

    //fonction pour faire correspondre les icones
    int index = 0;
    for (const Entree &e : entrees) {
        QPushButton *b = new QPushButton(QString::fromUtf8(e.texte));
        b->setObjectName("navBouton");
        b->setCheckable(true);
        b->setFixedHeight(40);
        b->setIcon(QIcon(QString("://images/%1.png").arg(e.icone)));
        b->setIconSize(QSize(18, 18));
        b->setCursor(Qt::PointingHandCursor);
        groupe->addButton(b, index);
        layout->addWidget(b);
        ++index;
    }
    groupe->button(1)->setChecked(true);   // "Véhicules" = page actuelle
    connect(groupe, &QButtonGroup::idClicked, this, &NavBar::pageDemandee);

    layout->addStretch();
}