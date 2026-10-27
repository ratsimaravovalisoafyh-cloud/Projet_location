#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include "carcard.h"
#include "voiture.h"
#include <QList>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QEvent>
#include <QLineEdit>
#include <algorithm>
#include <QMessageBox>
#include <QComboBox>
#include <utility>
#include "toolbar.h"
#include "headerwidget.h"
#include "voituredialog.h"
#include "navbar.h"

MainWindow::MainWindow(Role role, QWidget *parent)// ajout du role
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_role = role;
    ui->setupUi(this);
    // fenetre
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    central->setObjectName("centrale");

    //barre de navigation
    QHBoxLayout *racine = new QHBoxLayout(central);
    racine->setContentsMargins(0, 0, 0, 0);
    racine->setSpacing(0);

    NavBar *nav = new NavBar;
    racine->addWidget(nav);

    QWidget *contenu = new QWidget;
    racine->addWidget(contenu, 1);

    QVBoxLayout *layout = new QVBoxLayout(contenu);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    //header
    HeaderWidget *header = new HeaderWidget;
    header->setAttribute(Qt::WA_StyledBackground, true);
    header->setObjectName("header");
    header->setPeutAjouter(m_role == Role::Admin);
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
    barre->setObjectName("barre");
    layout->addWidget(barre);
    //connection de la barre de recherche
    connect(barre, &toolbar::rechercheChange, this, [this](const QString &texte){
        m_recherche = texte.trimmed();
        filtrer();
    });
    //connect de la recherche toolbar

    connect(barre, &toolbar::triChange, this, [this](int index){
        m_tri = index;
        m_page = 0;//page
        m_colonnes = 0;
        placerCartes();

    });

    // corps
    QHBoxLayout *body = new QHBoxLayout;
    body->setContentsMargins(28,24,28,24);

    //les filtres
    QWidget *sidebar = new QWidget;
    QVBoxLayout *sidebarlayout = new QVBoxLayout(sidebar);
    sidebar->setFixedWidth(290);
    //couleurs
    sidebar->setAttribute(Qt::WA_StyledBackground, true);
    sidebar->setObjectName("sidebar");
    sidebarlayout->setContentsMargins(16,20,16,20);
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
    Filtres->setObjectName("titreFiltres");
    QPushButton *Reinitialiser = new QPushButton("Reinitialiser");
    Reinitialiser->setObjectName("boutonReinit");
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
    typelayout->setStretch(0, 2);//toutes
    typelayout->setStretch(1, 3);//automatique
    typelayout->setStretch(2, 3);// manuelle
    sidebarlayout->addLayout(typelayout);

    // statut
    QLabel *labelstatut = new QLabel("Statut");
    sidebarlayout->addWidget(labelstatut);
    QComboBox *combostatut = new QComboBox;
    combostatut->addItem("Tous", -1);
    combostatut->addItem(texteStatut(Statut::Disponible),  static_cast<int>(Statut::Disponible));
    combostatut->addItem(texteStatut(Statut::Loue),        static_cast<int>(Statut::Loue));
    combostatut->addItem(texteStatut(Statut::Maintenance), static_cast<int>(Statut::Maintenance));
    sidebarlayout->addWidget(combostatut);
    connect(combostatut, &QComboBox::currentIndexChanged, this, [this, combostatut](int) {
        m_statut = combostatut->currentData().toInt();
        filtrer();
    });


    //style des boutons

    boutontoutes->setObjectName("pastille");
    boutonautomatique->setObjectName("pastille");
    boutonmanuelle->setObjectName("pastille");
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
    m_totalmarque = new QCheckBox("Total des marques");
    m_totalmarque->setChecked(true);
    m_marquegroupe = new QButtonGroup(this);
    m_marquegroupe->addButton(m_totalmarque);
    m_marqueslayout = new QVBoxLayout;//contient les cases des marques
    m_marqueslayout->setSpacing(14);//garder le meme ecart  que le reste de la colonne

    sidebarlayout->addWidget(m_totalmarque);
    sidebarlayout->addLayout(m_marqueslayout);

    connect(m_totalmarque, &QCheckBox::clicked, this, [this](){
        m_marques.clear();
        filtrer();
    });

    //prix minimum et maximum

    QLabel *prix = new QLabel("Prix Journalier");
    sidebarlayout->addWidget(prix);
    QSpinBox *prixmin = new QSpinBox;
    QSpinBox *prixmax = new QSpinBox;
    prixmin->setRange(0,500000);
    prixmin->setValue(0);
    prixmax->setRange(0,500000);
    prixmax->setValue(500000);
    prixmin->setSingleStep(5000);
    prixmax->setSingleStep(5000);
    prixmin->setAccelerated(true);
    prixmax->setAccelerated(true);
    prixmin->setGroupSeparatorShown(true);
    prixmax->setGroupSeparatorShown(true);

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
    boutonvalider->setObjectName("boutonValider");
    sidebarlayout->addWidget(boutonvalider);
    connect(boutonvalider, &QPushButton::clicked, this, majprix);
    connect(prixmin->findChild<QLineEdit *>(), &QLineEdit::returnPressed, boutonvalider, &QPushButton::click);
    connect(prixmax->findChild<QLineEdit *>(), &QLineEdit::returnPressed, boutonvalider, &QPushButton::click);


    //bouton reinitialiser
    connect(Reinitialiser, &QPushButton::clicked, this, [this, boutontoutes, prixmin, prixmax, combostatut]() {
        boutontoutes->setChecked(true);
        m_totalmarque->setChecked(true);
        prixmin->setValue(0);
        prixmax->setValue(500000);
        combostatut->setCurrentIndex(0);
        m_transmission = "";
        m_statut = -1;
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
    //  pagination
    m_pagination = new QWidget;
    m_pagination->setObjectName("pagination");
    m_pagination->setAttribute(Qt::WA_StyledBackground, true);
    m_paginationLayout = new QHBoxLayout(m_pagination);
    m_paginationLayout->setContentsMargins(0, 0, 0, 0);
    m_paginationLayout->setSpacing(8);

    QVBoxLayout *droite = new QVBoxLayout;
    droite->setSpacing(12);
    droite->addWidget(m_scroll, 1);
    droite->addWidget(m_pagination);
    body->addLayout(droite, 1);

    mettreCartes();

}

//fonction filtrer

void MainWindow::filtrer()
{
    for ( int i = 0; i < m_voitures.size(); ++i){
        bool garder = true;
        if (!m_transmission.isEmpty()&& m_voitures[i].transmission != m_transmission)
            garder = false;
        if (m_statut >= 0 && static_cast<int>(m_voitures[i].statut) != m_statut)
            garder = false;
        if(!m_marques.isEmpty() && !m_marques.contains(m_voitures[i].marque, Qt::CaseInsensitive))
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
    }
    m_colonnes = 0;
    placerCartes();

}

// fonction placer cartes
void MainWindow::placerCartes()
{
    int largeur = m_scroll->viewport()->width();
    int colonnes = qMax(1, (largeur + 20) / (260 + 20));

    if (colonnes == m_colonnes)
        return;
    m_colonnes = colonnes;

    for (int c = 0; c < 10; ++c)
        m_cataloglayout->setColumnStretch(c, c < colonnes ? 1 : 0);
    for (CarCard *carte : m_cartes)
        m_cataloglayout->removeWidget(carte);

    QList<int> ordre;
    for (int i = 0; i < m_cartes.size(); ++i)
        ordre.append(i);
    if (m_tri == 1)
        std::stable_sort(ordre.begin(), ordre.end(), [this](int a, int b){
            return m_voitures[a].prix < m_voitures[b].prix;
        });
    else if (m_tri == 2)
        std::stable_sort(ordre.begin(), ordre.end(), [this](int a, int b){
            return m_voitures[a].prix > m_voitures[b].prix;
        });

    // cartes qui passent les filtres, dans l'ordre du tri
    QList<CarCard *> visibles;
    for (int idx : ordre) {
        CarCard *carte = m_cartes[idx];
        if (carte->property("masquee").toBool())
            carte->hide();
        else
            visibles.append(carte);
    }

    int pages = qMax(1, (int(visibles.size()) + m_parPage - 1) / m_parPage);
    m_page = qBound(0, m_page, pages - 1);
    int debut = m_page * m_parPage;

    for (int i = 0; i < visibles.size(); ++i) {
        CarCard *carte = visibles[i];
        if (i < debut || i >= debut + m_parPage) {
            carte->hide(); // autre page
            continue;
        }
        int n = i - debut;
        m_cataloglayout->addWidget(carte, n / colonnes, n % colonnes);
        carte->show();
    }
    majPagination(pages);
}

//fonction mettrre les cartes
void MainWindow::mettreCartes(){
    m_scroll->setUpdatesEnabled(false); //geler l'affichage
    for (CarCard *carte : std::as_const(m_cartes){
        m_cataloglayout->removeWidget(carte);
        carte->hide();
        carte->deleteLater();
    }
    m_cartes.clear();

    m_voitures = m_repo.toutes();
    for (const Voiture &v : std::as_const(m_voitures){
        const QString prixTexte = QLocale(QLocale::English).toString(qlonglong(v.prix)).replace(',', ' ') + " Ar";
        CarCard *carte = new CarCard(v.statut, v.nom, v.type, prixTexte, v.immatriculation, v.id, v.photo, m_catalogue, m_role == Role::Admin);
        m_cartes.append(carte);

        connect(carte, &CarCard::supprimerDemande, this, [this](int id){
            if (m_role != Role::Admin) return;
            auto reponse = QMessageBox::question(this, "Supprimer la voiture", "Voulez-vous vraiment supprimer la voiture ?");
            if (reponse == QMessageBox::Yes) {
                m_repo.supprimer(id);
                mettreCartes();
            }

        });

        connect(carte, &CarCard::statutDemande, this, [this](int id, Statut nouveau) {
            if (m_role != Role::Admin) return;
            m_repo.changerStatut(id, nouveau);
            mettreCartes();
        });

        connect(carte, &CarCard::modifierDemande, this, [this](int id) {
            Voiture courante;
            bool trouve = false;
            for (const Voiture &candidate : std::as_const(m_voitures) {
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
    int pageAvant = m_page;
    rafraichirMarques();
    filtrer();
    if (pageAvant > 0) {
        m_page = pageAvant;//ramener a la derniere page si besoin
        m_colonnes = 0;
        placerCartes();
    }
    m_scroll->setUpdatesEnabled(true); //reafficher d'un coup
}

// evenement de filtrer
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_scroll->viewport() && event->type() == QEvent::Resize)
        placerCartes();
    return QMainWindow::eventFilter(obj, event);
}

// fonction de rafraichissement des marques de voitures
void MainWindow::rafraichirMarques(){
    QString selection = m_marques.isEmpty() ? QString() : m_marques.first();

    for(QAbstractButton *b : m_marquegroupe->buttons()){
        if (b == m_totalmarque)
            continue;
        m_marquegroupe->removeButton(b);
        m_marqueslayout->removeWidget(b);
        b->deleteLater();
    }

    QStringList marques;
    for (const Voiture &v : m_voitures){
        if(!marques.contains(v.marque, Qt::CaseInsensitive))
            marques << v.marque;
    }
    marques.sort(Qt::CaseInsensitive);//pour eviter la casse des mots

    bool retrouvee = false;
    for (const QString &m : marques){
        QCheckBox *c = new QCheckBox(m);
        m_marquegroupe->addButton(c);
        m_marqueslayout->addWidget(c);
        if (m == selection){
            c->setChecked(true);
            retrouvee = true;
        }
        connect(c, &QCheckBox::clicked, this, [this,m](){
            m_marques.clear();
            m_marques << m;
            filtrer();
        });
    }
    if (!retrouvee){
        m_totalmarque->setChecked(true);
        m_marques.clear();
    }
}
void MainWindow::allerPage(int page)
{
    m_page = page;
    m_colonnes = 0;
    placerCartes();
    m_scroll->verticalScrollBar()->setValue(0);
}

void MainWindow::majPagination(int pages)
{
    if (!m_paginationLayout)
        return;

    // vider la barre
    while (QLayoutItem *item = m_paginationLayout->takeAt(0)) {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }
    m_pagination->setVisible(pages > 1);
    if (pages <= 1)
        return;

    auto bouton = [this](const QString &texte, int page, bool actif, bool fleche) {
        QPushButton *b = new QPushButton(texte);
        b->setObjectName(fleche ? "pageFleche" : "pageBouton");
        b->setFixedSize(32, 32);
        b->setCursor(Qt::PointingHandCursor);
        if (!fleche) {
            b->setCheckable(true);
            b->setChecked(actif);
        }
        b->setEnabled(page >= 0 && page < 1000000 && (fleche ? page >= 0 : true));
        connect(b, &QPushButton::clicked, this, [this, page]() { allerPage(page); });
        m_paginationLayout->addWidget(b);
        return b;
    };

    m_paginationLayout->addStretch();

    // flèche précédente
    QPushButton *prec = bouton("‹", qMax(0, m_page - 1), false, true);
    prec->setEnabled(m_page > 0);

    // numéros : première, dernière, page courante et ses voisines
    QList<int> liste;
    for (int p = 0; p < pages; ++p)
        if (p == 0 || p == pages - 1 || qAbs(p - m_page) <= 1)
            liste << p;

    int precedent = -1;
    for (int p : liste) {
        if (precedent != -1 && p - precedent > 1) {
            QLabel *points = new QLabel("…");
            m_paginationLayout->addWidget(points);
        }
        bouton(QString::number(p + 1), p, p == m_page, false);
        precedent = p;
    }

    // flèche suivante
    QPushButton *suiv = bouton("›", qMin(pages - 1, m_page + 1), false, true);
    suiv->setEnabled(m_page < pages - 1);

    m_paginationLayout->addStretch();
}
MainWindow::~MainWindow()
{
    delete ui;
}
