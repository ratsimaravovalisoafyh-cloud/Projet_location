#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QSpinBox>
#include<QGridLayout>
#include "carcard.h"
#include "voiture.h"
#include <QList>
#include <QScrollArea>
#include <QTimer>
#include <QEvent>
#include <QLineEdit>
#include <algorithm>
#include <QMessageBox>
#include "toolbar.h"
#include "headerwidget.h"
#include "voituredialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // fenetre
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    central->setStyleSheet("background : #1c2023; color: #dfe8dc;");

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    //header
    HeaderWidget *header = new HeaderWidget;
    header->setAttribute(Qt::WA_StyledBackground, true);
    header->setStyleSheet("background: #14171a; color: #dfe8dc;");
    layout->addWidget(header);

    // faire marcher le bouton ajouter voitures
    connect(header, &HeaderWidget::ajouterDemande, this, [this](){
        VoitureDialog dlg(this);
        while (dlg.exec() == QDialog::Accepted){
            Voiture v = dlg.voiture();
            if (m_repo.existenceimmatriculation(v.immatriculation)) {
                QMessageBox::warning(this, "Immatriculation déjà utilisée",
                                     "Une voiture porte deja cette immatriculation.");
                continue;
            }

        m_repo.ajouter(v);
        mettreCartes();
        break;
        }

    });
    //barre d'outils

    toolbar *barre = new toolbar;
    barre->setAttribute(Qt::WA_StyledBackground, true);
    barre->setStyleSheet("background: #23282b; color: #dfe8dc;");
    layout->addWidget(barre);
    //connection de la barre de recherche
    connect(barre, &toolbar::rechercheChange, this, [this](const QString &texte){
        m_recherche = texte.trimmed();
        filtrer();
    });
    //connect de la recherche toolbar

    connect(barre, &toolbar::triChange, this, [this](int index){
        m_tri = index;
        m_colonnes = 0;
        placerCartes();

    });

    // corps
    QHBoxLayout *body = new QHBoxLayout;
    body->setContentsMargins(28,24,28,24);

    //les filtres
    QWidget *sidebar = new QWidget;
    QVBoxLayout *sidebarlayout = new QVBoxLayout(sidebar);
    sidebar->setFixedWidth(240);
    //couleurs
    sidebar->setStyleSheet("background: #23282b; color: #dfe8dc; border-radius: 20px;");
    sidebarlayout->setContentsMargins(20,20,20,20);
    sidebarlayout->setSpacing(14);

    // catalogue carte pour voiture et voitures grille
    QWidget *catalogue = new QWidget;
    m_catalogue = catalogue;
    m_cataloglayout = new QGridLayout(catalogue);
    m_cataloglayout->setContentsMargins(0,0,0,0);
    m_cataloglayout->setSpacing(20);
    m_cataloglayout->setAlignment(Qt::AlignTop);


    //positionnement
    body->addWidget(sidebar);
    body->setSpacing(24);
    layout->addLayout(body,1);

    QHBoxLayout *titrelayout = new QHBoxLayout;
    QLabel *Filtres = new QLabel("Filtres");
    QPushButton *Reinitialiser = new QPushButton("Reinitialiser");
    Reinitialiser->setStyleSheet("background: transparent; border: none; color: #b9cab6; font-size: 13px;");
    //changer le curseur
    Reinitialiser->setCursor(Qt::PointingHandCursor);
    titrelayout->addWidget(Filtres);
    titrelayout->addStretch();
    titrelayout->addWidget(Reinitialiser);
    sidebarlayout->addLayout(titrelayout);

    //type de voitures
    QLabel *labeltype = new QLabel("Type de voiture");
    sidebarlayout->addWidget(labeltype);


    //bouton manuelle et automatique
    QPushButton *boutonautomatique = new QPushButton("Automatique");
    QPushButton *boutonmanuelle = new QPushButton("Manuelle");
    QPushButton *boutontoutes = new QPushButton("Toutes");
    boutontoutes->setCheckable(true);
    boutonautomatique->setCheckable(true);
    boutonmanuelle->setCheckable(true);
    boutontoutes->setChecked(true);

    //ajout boutons aux groupes
    QButtonGroup *typegroupe = new QButtonGroup(this);
    typegroupe->addButton(boutontoutes);
    typegroupe->addButton(boutonautomatique);
    typegroupe->addButton(boutonmanuelle);

    //placement des boutons
    QHBoxLayout *typelayout = new QHBoxLayout;
    typelayout->addWidget(boutontoutes);
    typelayout->addWidget(boutonautomatique);
    typelayout->addWidget(boutonmanuelle);
    typelayout->setSpacing(6);
    sidebarlayout->addLayout(typelayout);

    //style des boutons
    QString styleBouton = "QPushButton { border: 1px solid #9db39a; border-radius: 10px; padding: 8px 4px; font-size: 12px;}"
                          "QPushButton:checked { background: #9db39a; color: #17201a; }";
    boutontoutes->setStyleSheet(styleBouton);
    boutonautomatique->setStyleSheet(styleBouton);
    boutonmanuelle->setStyleSheet(styleBouton);

    //interaction des boutons
    connect(boutontoutes, &QPushButton::clicked, this, [this](){
        m_transmission = "";
        filtrer();

    });
    connect(boutonautomatique, &QPushButton::clicked, this, [this](){
        m_transmission = "Automatique";
        filtrer();

    });

    connect(boutonmanuelle, &QPushButton::clicked, this, [this](){
        m_transmission = "Manuelle";
        filtrer();

    });


    // marque
    QLabel *labelmarque = new QLabel("Marque");
    sidebarlayout->addWidget(labelmarque);
    // les voitures
    QCheckBox *totalmarque = new QCheckBox("Total des marques");
    QCheckBox *Toyota = new QCheckBox("Toyota");
    QCheckBox *hyundai = new QCheckBox("Hyundai");
    QCheckBox *renault = new QCheckBox("Renault");
    totalmarque->setChecked(true);
    sidebarlayout->addWidget(totalmarque);
    sidebarlayout->addWidget(Toyota);
    sidebarlayout->addWidget(hyundai);
    sidebarlayout->addWidget(renault);
    QButtonGroup *marquegroupe = new QButtonGroup(this);
    marquegroupe->addButton(totalmarque);
    marquegroupe->addButton(Toyota);
    marquegroupe->addButton(hyundai);
    marquegroupe->addButton(renault);

    // filtre de marque
    auto majmarques = [this, totalmarque, Toyota, hyundai, renault](){
        m_marques.clear();
        if(Toyota->isChecked()) m_marques << "Toyota";
        if(hyundai->isChecked()) m_marques << "Hyundai";
        if(renault->isChecked()) m_marques << "Renault";
        filtrer();
    };
    // connecter
    connect(totalmarque, &QCheckBox::clicked, this, majmarques);
    connect(Toyota, &QCheckBox::clicked, this, majmarques);
    connect(hyundai, &QCheckBox::clicked, this, majmarques);
    connect(renault, &QCheckBox::clicked, this, majmarques);


    QLabel *prix = new QLabel("Prix Journalier");
    sidebarlayout->addWidget(prix);
    QSpinBox *prixmin = new QSpinBox;
    QSpinBox *prixmax = new QSpinBox;
    prixmin->setRange(0,500000);
    prixmin->setValue(0);
    prixmax->setRange(0,500000);
    prixmax->setValue(500000);

    sidebarlayout->addWidget(new QLabel("Minimum"));
    sidebarlayout->addWidget(prixmin);
    sidebarlayout->addWidget(new QLabel("Maximum"));
    sidebarlayout->addWidget(prixmax);

    auto majprix = [this, prixmin, prixmax]() {
        prixmin->interpretText();
        prixmax->interpretText();
        m_prixmin = prixmin->value();
        m_prixmax = prixmax-> value();
        filtrer();
    };
    prixmin->setKeyboardTracking(false);
    prixmax->setKeyboardTracking(false);

    //bouton valider
    QPushButton *boutonvalider = new QPushButton("Valider");
    boutonvalider->setStyleSheet("background: #9db39a; color: #17201a; border: none; border-radius: 10px; padding: 8px;");
    sidebarlayout->addWidget(boutonvalider);
    connect(boutonvalider, &QPushButton::clicked, this, majprix);
    connect(prixmin->findChild<QLineEdit *>(), &QLineEdit::returnPressed, boutonvalider, &QPushButton::click);
    connect(prixmax->findChild<QLineEdit *>(), &QLineEdit::returnPressed, boutonvalider, &QPushButton::click);


    //bouton reinitialiser
    connect(Reinitialiser, &QPushButton::clicked, this, [this, boutontoutes, totalmarque, prixmin, prixmax]() {
        boutontoutes->setChecked(true);
        totalmarque->setChecked(true);
        prixmin->setValue(0);
        prixmax->setValue(500000);

        m_transmission = "";
        m_marques.clear();
        m_prixmin = 0;
        m_prixmax = 500000;

        filtrer();
    });
    sidebarlayout->addStretch();

    //scroll
    m_scroll = new QScrollArea;
    m_scroll->viewport()->installEventFilter(this);
    m_scroll->setWidget(catalogue);
    m_scroll->setWidgetResizable(true);
    m_scroll->setFrameShape(QFrame::NoFrame);
    m_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    body->addWidget(m_scroll, 1);
    mettreCartes();

}

//fonction filtrer

void MainWindow::filtrer()
{
    for ( int i = 0; i < m_voitures.size(); ++i){
        bool garder = true;
        if (!m_transmission.isEmpty()&& m_voitures[i].transmission != m_transmission)
            garder = false;
        if(!m_marques.isEmpty() && !m_marques.contains(m_voitures[i].marque))
            garder = false;

        if(m_voitures[i].prix < m_prixmin || m_voitures[i].prix > m_prixmax)
            garder = false;
        if (!m_recherche.isEmpty()) {
            const Voiture &v = m_voitures[i];
            bool trouve = v.nom.contains(m_recherche, Qt::CaseInsensitive)
                          || v.marque.contains(m_recherche, Qt::CaseInsensitive)
                          || v.type.contains(m_recherche, Qt::CaseInsensitive)
                          || v.immatriculation.contains(m_recherche, Qt::CaseInsensitive);
            if (!trouve)
                garder = false;
        }
        m_cartes[i]->setProperty("masquee", !garder);
        m_cartes[i]->setVisible(garder);
    }
    m_colonnes = 0;
    placerCartes();

}


// fonction placercarte
void MainWindow::placerCartes()
{
    int largeur = m_scroll->viewport()->width();

    int colonnes = qMax(1, (largeur + 20) / (260 + 20));

    if (colonnes == m_colonnes)
        return;
    m_colonnes = colonnes;



    for(int c = 0; c <10; ++c)
        m_cataloglayout->setColumnStretch(c, c < colonnes ? 1 : 0);
    for (CarCard *carte : m_cartes)
        m_cataloglayout->removeWidget(carte);

    QList<int> ordre;
    for (int i = 0; i < m_cartes.size(); ++i)
        ordre.append(i);
    if (m_tri == 1)
        std::stable_sort(ordre.begin(), ordre.end(),[this](int a, int b){
            return m_voitures[a].prix < m_voitures[b].prix;
        });
    else if (m_tri == 2)
        std::stable_sort(ordre.begin(), ordre.end(),[this](int a, int b){
            return m_voitures[a].prix > m_voitures[b].prix;
        });
    int n = 0;
    for (int idx : ordre) {
        CarCard *carte = m_cartes[idx];
        if (carte->property("masquee").toBool())
            continue;
        m_cataloglayout->addWidget(carte, n / colonnes, n % colonnes);
        ++n;
    }
}

void MainWindow::mettreCartes(){
    for (CarCard *carte : m_cartes){
        m_cataloglayout->removeWidget(carte);
        carte->deleteLater();
    }
    m_cartes.clear();

    m_voitures = m_repo.toutes();
    for (const Voiture &v : m_voitures){
        CarCard *carte = new CarCard(v.nom, v.type, QString::number(v.prix), v.immatriculation,v.id, m_catalogue);
        m_cartes.append(carte);
        connect(carte, &CarCard::supprimerDemande, this, [this](int id){
            auto reponse = QMessageBox::question(this, "Supprimer la voiture", "Voulez-vous vraiment supprimer la voiture ?");
            if (reponse == QMessageBox::Yes) {
                m_repo.supprimer(id);
                mettreCartes();
            }

        });
        connect(carte, &CarCard::modifierDemande, this, [this](int id) {
            Voiture courante;
            bool trouve = false;
            for (const Voiture &candidate : m_voitures) {
                if (candidate.id == id) {
                    courante = candidate;
                    trouve = true;
                    break;
                }
            }
            if (!trouve)
                return;

            VoitureDialog dlg(this);
            dlg.remplir(courante);
            while (dlg.exec() == QDialog::Accepted) {
                Voiture modifiee = dlg.voiture();
                if (m_repo.existenceimmatriculation(modifiee.immatriculation, modifiee.id)) {
                    QMessageBox::warning(this, "Immatriculation déjà utilisée",
                                         "Une autre voiture porte déjà cette immatriculation.");
                    continue;
                }
                m_repo.modifier(modifiee);
                mettreCartes();
                break;
            }
        });

    }
    filtrer();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_scroll->viewport() && event->type() == QEvent::Resize)
        placerCartes();
    return QMainWindow::eventFilter(obj, event);
}
MainWindow::~MainWindow()
{
    delete ui;
}
