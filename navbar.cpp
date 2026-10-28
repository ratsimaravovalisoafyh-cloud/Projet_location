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
    setAttribute(Qt::WA_StyledBackground, true);   // pour que le fond du QSS s'affiche
    setFixedWidth(190);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(14, 20, 14, 20);
    layout->setSpacing(6);

    // le logo et le titre en haut
    QHBoxLayout *logoLayout = new QHBoxLayout;
    logoLayout->setSpacing(10);

    QLabel *logo = new QLabel(this);
    logo->setObjectName("navLogo");   // sert à changer la couleur du logo dans le QSS
    logo->setPixmap(QPixmap("://images/logo.png")
                        .scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setFixedSize(40, 40);
    logo->setAlignment(Qt::AlignCenter);

    QLabel *titre = new QLabel("Rent a Car", this);
    titre->setObjectName("navTitre");

    logoLayout->addWidget(logo);
    logoLayout->addWidget(titre);
    logoLayout->addStretch();
    layout->addLayout(logoLayout);
    layout->addSpacing(24);

    // les boutons de navigation : un seul peut être coché à la fois
    QButtonGroup *groupe = new QButtonGroup(this);
    groupe->setExclusive(true);

    // chaque bouton a le nom de son icône et son texte
    struct Entree { const char *icone; const char *texte; };
    const Entree entrees[] = {
                               {"icons-analytics-80", "Dashboard"},
                               {"icons-car-80",       "Véhicules"},
                               {"icons-group-80",     "Clients"},
                               {"icons-schedule-80",  "Locations"},
                               };

    int index = 0;   // l'index sert d'identifiant de page (0 = Dashboard, 1 = Véhicules...)
    for (const Entree &e : entrees) {
        QPushButton *b = new QPushButton(QString::fromUtf8(e.texte), this);
        b->setObjectName("navBouton");
        b->setCheckable(true);
        b->setFixedHeight(40);
        b->setIcon(QIcon(QString("://images/%1.png").arg(e.icone)));
        b->setIconSize(QSize(18, 18));
        b->setCursor(Qt::PointingHandCursor);
        groupe->addButton(b, index);
        layout->addWidget(b);
        if (index == 0)
            m_boutonDashboard = b;   // on le garde pour pouvoir le cacher
        ++index;
    }
    groupe->button(1)->setChecked(true);   // "Véhicules" est la page actuelle
    connect(groupe, &QButtonGroup::idClicked, this, &NavBar::pageDemandee);

    layout->addStretch();   // pousse les boutons vers le haut
}

// le Dashboard est réservé à l'admin : on le cache pour l'employé
void NavBar::setDashboardVisible(bool visible)
{
    m_boutonDashboard->setVisible(visible);
}