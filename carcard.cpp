#include "carcard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>

CarCard::CarCard(const QString &nom, const QString &type, const QString &prix ,const QString &immatriculation,int id, QWidget *parent)
    : QWidget{parent}
{
    m_id = id;
    //creation de la carte
    QVBoxLayout *Layout = new QVBoxLayout(this);
    Layout->setContentsMargins(16,16,16,16);
    Layout->setSpacing(10);
    QLabel *labelnom = new QLabel(nom);
    QLabel *labeltype = new QLabel(type);
    QLabel *labelprix = new QLabel(prix);
    QLabel *labelimage = new QLabel("image");
    QLabel *labelimmat = new QLabel(immatriculation);
    labelimmat->setStyleSheet("font-size: 12px;");
    setObjectName("carte");
    labelimage->setAlignment(Qt::AlignCenter);
    labelimage->setFixedHeight(120);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("#carte { background: #9db39a; border-radius:16px; }" "QLabel { color:#17201a; background: transparent; }");
    labelimage->setStyleSheet("background: #c5d3c2; border-radius: 12px;");
    setMinimumWidth(260);
    setFixedHeight(300);

    // bouton pour favoris
    QPushButton *boutonfavoris = new QPushButton;
    boutonfavoris->setCheckable(true);

    QIcon iconefavori;
    iconefavori.addFile("://images/favoris.png", QSize(), QIcon::Normal, QIcon::Off);
    iconefavori.addFile("://images/favoris2.png", QSize(), QIcon::Normal, QIcon::On);
    boutonfavoris->setIcon(iconefavori);
    boutonfavoris->setIconSize(QSize(18,18));
    boutonfavoris->setFixedSize(32,32);
    boutonfavoris->setStyleSheet("background: #23282b; border: none; border-radius: 16px");

    QVBoxLayout *texte = new QVBoxLayout;
    texte->setContentsMargins(0,0,0,0);
    texte->setSpacing(2);
    texte->addWidget(labelnom);
    texte->addWidget(labeltype);
    texte->addWidget(labelimmat);

    QHBoxLayout *haut = new QHBoxLayout;
    haut->addLayout(texte);
    haut->addStretch();
    haut->addWidget(boutonfavoris, 0, Qt::AlignTop);
    Layout->addLayout(haut);
    Layout->addWidget(labelimage);
    QPushButton *boutonmodifier = new QPushButton("Modifier");
    QPushButton *boutonsupprimer = new QPushButton("Supprimer");
    QString styleaction = "background: #c5d3c2; border: none; border-radius: 8px; padding: 4px 8px; font-size: 11px; color: #17201a;";
    boutonmodifier->setStyleSheet(styleaction);
    boutonsupprimer->setStyleSheet(styleaction);

    connect(boutonmodifier, &QPushButton::clicked, this, [this]() { emit modifierDemande(m_id); });
    connect(boutonsupprimer, &QPushButton::clicked, this, [this]() { emit supprimerDemande(m_id); });

    QHBoxLayout *bas = new QHBoxLayout;
    bas->addWidget(labelprix);
    bas->addStretch();
    bas->addWidget(boutonmodifier);
    bas->addWidget(boutonsupprimer);
    Layout->addLayout(bas);


}
