#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QWidget> //F Widget central
#include <QMessageBox>

#include <QVBoxLayout>
#include <QHBoxLayout> //F layout pple
#include <QButtonGroup>
//ito 2
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>
//ito3
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QPainter>
//icons
#include <QPixmap>
#include <QSizePolicy>
//finition 4
#include <QDate>
//le pilote MySQL
#include <QSqlDatabase>
#include <QDebug>

#include <QStackedWidget>

#include <QIcon>
#include <QSize>
#include <QStringList>
#include <QColor>

#include <QFrame>
//4.fonction qui construit une carte
QFrame *createStatCard(const QString &iconPath,
                       const QString &title,
                       const QString &value,
                       const QString &caption,
                       const QColor &accentColor)
{
    // 1. Carte principale
    QFrame *card = new QFrame;
    card->setObjectName("statCard");

    card->setStyleSheet(QString(
                            "QFrame#statCard {"
                            " background-color: #FFFFFF;"
                            " border: 1px solid #D8E2EF;"
                            " border-top: 4px solid %1;"
                            " border-radius: 12px;"
                            "}"
                            ).arg(accentColor.name()));

    // Hauteur suffisante pour tous les éléments
    card->setMinimumHeight(155);
    card->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Preferred
        );

    // 2. Organisation verticale
    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(18, 14, 18, 14);
    layout->setSpacing(5);

    // 3. Icône
    QLabel *iconLabel = new QLabel;
    iconLabel->setFixedSize(40, 40);
    iconLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap(iconPath);

    if (!pixmap.isNull()) {
        iconLabel->setPixmap(
            pixmap.scaled(
                24, 24,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                )
            );
    }

    iconLabel->setStyleSheet(QString(
                                 "background-color: %1;"
                                 "border-radius: 20px;"
                                 ).arg(accentColor.name()));

    // 4. Titre : peut passer sur deux lignes
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setWordWrap(true);
    titleLabel->setMinimumHeight(30);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLabel->setStyleSheet(
        "color: #526579;"
        "font-size: 12px;"
        "font-weight: bold;"
        "background: transparent;"
        );

    // 5. Valeur : taille adaptée, sans couper le texte
    QLabel *valueLabel = new QLabel(value);
    valueLabel->setWordWrap(true);
    valueLabel->setMinimumHeight(30);
    valueLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    valueLabel->setStyleSheet(
        "color: #183B5B;"
        "font-size: 22px;"
        "font-weight: bold;"
        "background: transparent;"
        );

    // 6. Texte secondaire
    QLabel *captionLabel = new QLabel(caption);
    captionLabel->setWordWrap(true);
    captionLabel->setStyleSheet(
        "color: #526579;"
        "font-size: 11px;"
        "background: transparent;"
        );

    // 7. Ajout dans le bon ordre
    layout->addWidget(iconLabel, 0, Qt::AlignLeft);
    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    layout->addWidget(captionLabel);

    return card;
}


 //eto tab location
QFrame *createLocationsTable()
{
    QFrame *card = new QFrame;
    card->setObjectName("statCard");
    card->setStyleSheet("#statCard { background-color: #FFFFFF; "
                        " border: 1px solid #D9E2EC;"
                        "border-radius: 10px; }");

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 16, 16, 16);

    QLabel *title = new QLabel("🚗  Dernières locations");
    title->setStyleSheet("color: #24364B; font-size: 15px; font-weight: bold; background: transparent;");
    layout->addWidget(title);

    QTableWidget *table = new QTableWidget(5, 5);
    table->setHorizontalHeaderLabels({"N° Location", "Véhicule", "Client", "Date début", "Statut"});
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    //table->horizontalHeader()->setStretchLastSection(true);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    table->setWordWrap(false);

    QHeaderView *header = table->horizontalHeader();

    // Largeur adaptée au numéro de location
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    // Les colonnes Véhicule et Client se partagent l'espace
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);

    // La date garde une largeur adaptée à son contenu
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    // Statut : largeur fixe plus petite
    header->setSectionResizeMode(4, QHeaderView::Fixed);
    table->setColumnWidth(4, 110);

    table->verticalHeader()->setDefaultSectionSize(38);
    table->setMinimumHeight(260);
    table->setMinimumWidth(0);

    header->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    table->setShowGrid(false);
    table->setStyleSheet(
        "QTableWidget { background-color: #FFFFFF; color: #24364B; border: none; gridline-color: #E1E8F0;}"
        "QHeaderView::section { background-color: #FFFFFF; color: #183B5B;"
        " border: none; padding: 6px; font-weight: bold; }"
        );

    struct Row { QString id, vehicule, client, date, statut; };
    QList<Row> data = {
                        {"LOC-2026-001", "Toyota RAV4", "Jess", "25/10/2026", "En cours"},
                        {"LOC-2026-002", "Hyundai i20", "Anja", "24/10/2026", "En cours"},
                        {"LOC-2026-003", "Mitsubishi Lancer", "Rakotomalala J.", "22/10/2026", "En cours"},
                        {"LOC-2026-004", "Suzuki Swift", "Vals", "20/10/2026", "Terminée"},
                        {"LOC-2026-005", "Toyota Hiace", "Ticia.", "18/10/2026", "Terminée"},
                        };

    for (int row = 0; row < data.size(); ++row) {
        const Row &r = data[row];
        table->setItem(row, 0, new QTableWidgetItem(r.id));
        table->setItem(row, 1, new QTableWidgetItem(r.vehicule));
        table->setItem(row, 2, new QTableWidgetItem(r.client));
        table->setItem(row, 3, new QTableWidgetItem(r.date));
//not sure
        table->item(row, 0)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        table->item(row, 1)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        table->item(row, 2)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        table->item(row, 3)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        QLabel *badge = new QLabel(r.statut);
        bool enCours = (r.statut == "En cours");
        badge->setAlignment(Qt::AlignCenter);
        badge->setStyleSheet(QString(
                                 "QLabel {"
                                 " background-color: %1;"
                                 " color: %2;"
                                 " border-radius: 8px;"
                                 " padding: 5px 8px;"
                                 " font-weight: bold;"
                                 " font-size: 11px;"
                                 "}"
                                 ).arg(
                                     enCours ? "#D8EAFE" : "#E7EDF5",
                                     enCours ? "#245A87" : "#526579"
                                     ));
        badge->setMinimumWidth(0);
        badge->setMaximumWidth(95);
        badge->setSizePolicy(
            QSizePolicy::Fixed,
            QSizePolicy::Preferred
        );

        QWidget *statusContainer = new QWidget;
        QHBoxLayout *statusLayout = new QHBoxLayout(statusContainer);

        statusLayout->setContentsMargins(0, 0, 0, 0);
        statusLayout->setAlignment(Qt::AlignCenter);

        badge->setFixedWidth(95);
        statusLayout->addWidget(badge);

        table->setCellWidget(row, 4, statusContainer);
    }

    layout->addWidget(table);
    return card;
}
//eto micreer le donut si table prochain retours
QFrame *createDonutChart()
{
    QFrame *card = new QFrame;
    card->setObjectName("statCard");
    card->setStyleSheet(
        "#statCard { background-color: #FFFFFF; border: 1px solid #D9E2EC; border-radius: 10px; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 12, 16, 12);
    layout->setSpacing(6);

    QLabel *title = new QLabel("Répartition des locations");
    title->setStyleSheet(
        "color: #24364B; font-size: 15px; font-weight: bold;"
        "background: transparent;"
        );
    layout->addWidget(title);

    QPieSeries *series = new QPieSeries();
    series->append("Citadines", 8)->setColor(QColor("#6F9FCB"));
    series->append("SUV", 5)->setColor(QColor("#E4B66A"));
    series->append("Utilitaires", 3)->setColor(QColor("#A9C7B5"));
    series->append("Autres", 4)->setColor(QColor("#355C7D"));

    series->setHoleSize(0.55);
    series->setPieSize(0.95);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setBackgroundBrush(QColor("#FFFFFF"));
    chart->setBackgroundRoundness(0);
    chart->setMargins(QMargins(4, 4, 4, 4));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor("#526579"));
    chart->legend()->setFont(QFont("Arial", 9));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(200);
    chartView->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
        );
    chartView->setStyleSheet("background: transparent; border: none;");

    layout->addWidget(chartView, 1);

    return card;
}

QFrame *createUpcomingReturnsPanel()
{
    QFrame *card = new QFrame;
    card->setObjectName("statCard");
    card->setStyleSheet("#statCard { background-color: #FFFFFF; border: 1px solid #D9E2EC; border-radius: 10px; }");

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(16, 12, 16, 12);
    layout->setSpacing(4);

    card->setMinimumHeight(170);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *title = new QLabel("📅  Prochains retours");
    title->setStyleSheet("color: #24364B; font-size: 15px; font-weight: bold; background: transparent;");
    layout->addWidget(title);

    struct Retour { QString vehicule, immat, date; };
    QList<Retour> retours = {
                              {"Toyota RAV4", "T1234AB", "27 oct. 2026 · 10:00"},
                              {"Hyundai i20", "T5678CD", "27 oct. 2026 · 14:30"},
                              {"Mitsubishi Lancer", "K9012EF", "25 oct. 2026 · 09:00"},
                              };

    for (const Retour &r : retours) {
        QLabel *nom = new QLabel(r.vehicule + " — " + r.immat);
        nom->setWordWrap(true);
        nom->setStyleSheet(
            "color:  #24364B;"
            "font-weight: bold;"
            "background: transparent;"
            );

        QLabel *date = new QLabel(r.date);
        date->setWordWrap(true);
        date->setStyleSheet(
            "color: #172B4D;"
            "font-size: 12px;"
            "background: transparent;"
            );

        layout->addWidget(nom);
        layout->addWidget(date);
    }
    layout->addStretch();
    return card;
}

QWidget *createAccueilPage()
{
    // Zone de contenu (provisoire, remplit aux prochains exo)
    QWidget *content = new QWidget;
    content->setStyleSheet("background-color:  #EFF6FF;"); //F couleur ny contenu
    QVBoxLayout *contentLayout = new QVBoxLayout(content);

    contentLayout->setContentsMargins(24, 24, 24, 24);
    contentLayout->setSpacing(14);

    //ajout an'ito Finition ako acceuil
    //1.titre contenu
    QHBoxLayout *headerRow = new QHBoxLayout();

    QVBoxLayout *greetingCol = new QVBoxLayout();
    greetingCol->setSpacing(2);
    QLabel *greeting = new QLabel("Bonjour, Admin !"); //F titre contenu
    greeting->setStyleSheet("color: #24364B; font-size: 24px; font-weight: bold;");

    //2.Sous titre
    QLabel *subGreeting = new QLabel("Voici un aperçu de votre agence de location.");
    subGreeting->setStyleSheet("color: #526579; font-size: 13px;");
    greetingCol->addWidget(greeting);
    greetingCol->addWidget(subGreeting);

    //3.date à droite
    QLabel *dateLabel = new QLabel(
        QDate::currentDate().toString("dd MMMM yyyy")
        );
    dateLabel->setStyleSheet(
        "color: #526579; font-size: 13px;"
        "background: transparent;"
        );


    // Illustration du paysage et de la voiture
    QLabel *bannerLabel = new QLabel;
    QPixmap banner(":/icons/icons/deco.png");

    if (!banner.isNull()) {
        bannerLabel->setPixmap(
            banner.scaled(
                280, 45,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
                )
            );
    } else {
        qDebug() << "Erreur : image deco.png introuvable !";
    }

    bannerLabel->setFixedHeight(45);
    bannerLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    bannerLabel->setStyleSheet("background: transparent;");

    // Colonne de droite : date et image rapprochées
    QVBoxLayout *dateBannerLayout = new QVBoxLayout;
    dateBannerLayout->setSpacing(0);
    dateBannerLayout->setContentsMargins(0, 0, 0, 0);

    dateBannerLayout->addWidget(dateLabel, 0, Qt::AlignRight);
    dateBannerLayout->addWidget(bannerLabel, 0, Qt::AlignRight);

    // Organisation de l'en-tête
    headerRow->addLayout(greetingCol);
    headerRow->addStretch();
    headerRow->addLayout(dateBannerLayout);

    contentLayout->addLayout(headerRow);
    //contentLayout->setSpacing(6);

    //5.Appel fonction createStatCard

    QHBoxLayout *statsRow = new QHBoxLayout();
    statsRow->setSpacing(16);

    // 1. Véhicules : bleu moyen
    statsRow->addWidget(createStatCard(
        ":/icons/icons/icons8-car-80.png",
        "VÉHICULES DISPONIBLES",
        "12",
        "sur 20 au total",
        QColor("#6F9FCB")
        ));

    // 2. Locations : doré doux
    statsRow->addWidget(createStatCard(
        ":/icons/icons/icons8-schedule-80.png",
        "LOCATIONS EN COURS",
        "5",
        "aujourd'hui",
        QColor("#E4B66A")
        ));

    // 3. Clients : vert sauge
    statsRow->addWidget(createStatCard(
        ":/icons/icons/icons8-profile-80.png",
        "CLIENTS ENREGISTRÉS",
        "32",
        "dont 8 nouveaux ce mois",
        QColor("#A9C7B5")
        ));

    // 4. Revenus : bleu ardoise
    statsRow->addWidget(createStatCard(
        ":/icons/icons/icons8-get-revenue-80.png",
        "REVENUS DU MOIS",
        "3 240 000 Ar",
        "+12% ce mois-ci",
        QColor("#355C7D")
        ));


    contentLayout->addLayout(statsRow);
    //contentLayout->addStretch();    //eto eeh
    //contentLayout->addWidget(createLocationsTable(), 1);
    //teto 5

    QHBoxLayout *bottomRow = new QHBoxLayout();
    bottomRow->setSpacing(16);

    // Dernières locations : prend davantage de largeur
    QFrame *locationsCard = createLocationsTable();
    locationsCard->setMinimumWidth(0);
    bottomRow->addWidget(locationsCard, 2);

    // Colonne de droite
    QVBoxLayout *rightColumn = new QVBoxLayout();
    rightColumn->setSpacing(12);

    QFrame *donutCard = createDonutChart();
    donutCard->setMinimumWidth(0);
    rightColumn->addWidget(donutCard, 4);

    QFrame *returnsCard = createUpcomingReturnsPanel();
    returnsCard->setMinimumWidth(0);
    rightColumn->addWidget(returnsCard, 3);

    bottomRow->addLayout(rightColumn, 1);

    // La ligne du bas prend l'espace disponible
    contentLayout->addLayout(bottomRow, 1);


    //ajout an'ito finition ako
    QFrame *tipBanner = new QFrame;
    tipBanner->setStyleSheet(
        "background-color: #D8EAFE; border-radius: 8px; border-left: 4px solid #6F9FCB;"
        );
    QHBoxLayout *tipLayout = new QHBoxLayout(tipBanner);
    tipLayout->setContentsMargins(16, 12, 16, 12);

    QLabel *tipIcon = new QLabel("💡");
    QLabel *tipText = new QLabel(
        "Pensez à vérifier la disponibilité des véhicules avant de confirmer une nouvelle location."
        );
    tipText->setStyleSheet("color: #183B5B;");

    QPushButton *closeBtn = new QPushButton("✕");
    closeBtn->setStyleSheet("background: transparent; color: #A3B99A; border: none; font-weight: bold;");
    closeBtn->setFixedWidth(24);
    QObject::connect(closeBtn, &QPushButton::clicked, tipBanner, &QWidget::hide);

    tipLayout->addWidget(tipIcon);
    tipLayout->addWidget(tipText, 1);
    tipLayout->addWidget(closeBtn);

    contentLayout->addWidget(tipBanner, 0);

    contentLayout->setContentsMargins(24, 12, 24, 12);
    contentLayout->setSpacing(10);
    return content;
    //placeholder->setStyleSheet("color: #F1F3EF; font-size: 18px;");
}

QWidget *createVehiculesPage()
{
    QWidget *page = new QWidget;
    page->setStyleSheet("background-color: #EFF6FF;");

    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(24, 24, 24, 24);

    QLabel *title = new QLabel("Gestion des véhicules");
    title->setStyleSheet("color: #F1F3EF; font-size: 22px; font-weight: bold; background: transparent;");
    layout->addWidget(title);
    layout->addStretch();

    return page;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

//les pilotes disponibles
        qDebug() << "Pilotes SQL disponibles :" << QSqlDatabase::drivers();

//F titre et Taille
        setWindowTitle("Rent a Car");
        resize(1600, 900);

//tapany ambony
        QWidget *central = new QWidget(this);
        setCentralWidget(central);

        // Layout principal vertical : barre supérieure + contenu
        QVBoxLayout *rootLayout = new QVBoxLayout(central);
        rootLayout->setContentsMargins(0, 0, 0, 0);
        rootLayout->setSpacing(0);


        // BARRE SUPÉRIEURE
        QWidget *topBar = new QWidget(central);
        topBar->setObjectName("topBar");
        topBar->setFixedHeight(62);

        topBar->setStyleSheet(
            "#topBar {"
            " background-color: #D8EAFE;"
            " border-bottom: 1px solid #C5D9EF;"
            " border-radius: 10px;"
            "}"
            );

        QHBoxLayout *topBarLayout = new QHBoxLayout(topBar);
        topBarLayout->setContentsMargins(24, 0, 24, 0);
        topBarLayout->setSpacing(12);

        // Logo et nom de l'application
        QWidget *brandWidget = new QWidget(topBar);
        brandWidget->setStyleSheet("background: transparent;");

        QHBoxLayout *brandLayout = new QHBoxLayout(brandWidget);
        brandLayout->setContentsMargins(0, 0, 0, 0);
        brandLayout->setSpacing(8);

        // Image du logo
        QLabel *logoLabel = new QLabel(brandWidget);
        logoLabel->setFixedSize(36, 36);
        logoLabel->setAlignment(Qt::AlignCenter);

        QPixmap logo(":/icons/icons/logo-remove-background.png");

        if (!logo.isNull()) {
            logoLabel->setPixmap(
                logo.scaled(
                    36, 36,
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                    )
                );
        } else {
            qDebug() << "Erreur : logo introuvable !";
        }

        // Nom de l'agence
        QLabel *appLogo = new QLabel("Rent a Car", brandWidget);
        appLogo->setStyleSheet(
            "color: #173F68;"
            "font-size: 20px;"
            "font-weight: bold;"
            "background: transparent;"
            );

        brandLayout->addWidget(logoLabel);
        brandLayout->addWidget(appLogo);


        // Titre de l'application
        QLabel *appTitle = new QLabel(
            "GESTION DE LOCATION DE VOITURES"
            );
        appTitle->setAlignment(Qt::AlignCenter);
        appTitle->setStyleSheet(
            "color: #173F68;"
            "font-size: 15px;"
            "font-weight: bold;"
            "background: transparent;"
            );


        // Bouton Notifications
        QPushButton *notificationBtn = new QPushButton(topBar);
        notificationBtn->setIcon(
            QIcon(":/icons/icons/icons-notification-80.png")
            );
        notificationBtn->setIconSize(QSize(22, 22));
        notificationBtn->setFixedSize(38, 38);
        notificationBtn->setCursor(Qt::PointingHandCursor);
        notificationBtn->setToolTip("Notifications");

        // Bouton Profil utilisateur
        QPushButton *userBtn = new QPushButton(topBar);
        userBtn->setIcon(
            QIcon(":/icons/icons/icons-user-80.png")
            );
        userBtn->setIconSize(QSize(22, 22));
        userBtn->setFixedSize(38, 38);
        userBtn->setCursor(Qt::PointingHandCursor);
        userBtn->setToolTip("Profil utilisateur");

        // Style commun
        QString iconButtonStyle =
            "QPushButton {"
            " background-color: #C3DDF8;"
            " border: none;"
            " border-radius: 19px;"
            "}"
            "QPushButton:hover {"
            " background-color: #B2D1F2;"
            "}"
            "QPushButton:pressed {"
            " background-color: #A0C4EB;"
            "}";

        notificationBtn->setStyleSheet(iconButtonStyle);
        userBtn->setStyleSheet(iconButtonStyle);


        // Répartition horizontale
        topBarLayout->addWidget(brandWidget);
        topBarLayout->addStretch(1);
        topBarLayout->addWidget(appTitle);
        topBarLayout->addStretch(1);
        topBarLayout->addWidget(notificationBtn);
        topBarLayout->addWidget(userBtn);


        rootLayout->addWidget(topBar);


        //ZONE SOUS LA BARRE
        QWidget *body = new QWidget(central);

        QHBoxLayout *mainLayout = new QHBoxLayout(body);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        rootLayout->addWidget(body, 1);

//F stacked
        QStackedWidget *pages = new QStackedWidget(body);
        pages->addWidget(createAccueilPage());
        pages->addWidget(createVehiculesPage());

//F Sidebar vertical @ sisiny coté Gauche
        QWidget *sidebar = new QWidget(body);
        sidebar->setObjectName("sidebar"); //F nom unique
        sidebar->setFixedWidth(200); //largeur fixe
        sidebar->setStyleSheet("#sidebar { background-color: #163A5F; border-top-right-radius: 16px; border-bottom-right-radius: 16px; }");

        mainLayout->addWidget(sidebar);

        QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setContentsMargins(16, 24, 16, 24);
        sidebarLayout->setSpacing(6);

        //QLabel *logo = new QLabel("Rent a Car");
        //logo->setStyleSheet("font-size: 16px; font-weight: bold; color: #F1F3EF;");
        //sidebarLayout->addWidget(logo);
        //sidebarLayout->addSpacing(20);
//6.boutons sidebar
        QStringList navItems = {"Dashboard",
                                "Véhicules",
                                "Clients",
                                "Locations",
                                "Paramètres"};

        QStringList iconPaths = {
            ":/icons/icons/icons-analytics-80.png",
            ":/icons/icons/icons-car-80.png",
            ":/icons/icons/icons-group-80.png",
            ":/icons/icons/icons-schedule-80.png",
            ":/icons/icons/icons-engineering-80.png"
        };

        QButtonGroup *navGroup = new QButtonGroup(this);

        for (int i = 0; i < navItems.size(); ++i) {

            // 1. Créer le bouton avec son texte
            QPushButton *btn = new QPushButton(navItems[i]);

            // 2. Ajouter l'icône correspondante
            btn->setIcon(QIcon(iconPaths[i]));
            btn->setIconSize(QSize(20, 20));
            btn->setMinimumHeight(44);

            // 3. Style du bouton
            btn->setStyleSheet(
                "QPushButton {"
                "text-align: left;"
                " padding: 10px 12px;"
                " border: none;"
                " border-radius: 8px;"
                " color: #FFFFFF;"
                " background-color: transparent;"
                " font-size: 13px;"
                " font-weight: 500;"
                "}"
                "QPushButton:hover {"
                " background-color: #285783;"
                "}"
                "QPushButton:checked {"
                " background-color: #D8EAFE;"
                " color: #173F68;"
                " font-weight: bold;"
                "}"
                );

            // 4. Ajouter le bouton au groupe
            btn->setCheckable(true);
            navGroup->addButton(btn);

            // 5. Relier le bouton à la page correspondante
            int index = i;

            connect(btn, &QPushButton::clicked, this,
                    [pages, index]() {
                        if (index < pages->count()) {
                            pages->setCurrentIndex(index);
                        }
                    });

            // 6. Ajouter le bouton à la barre latérale
            sidebarLayout->addWidget(btn);

            // 7. Sélectionner Dashboard au démarrage
            if (i == 0) {
                btn->setChecked(true);
            }
        }

        sidebarLayout->addStretch(); //ts misy blem
        mainLayout->addWidget(pages, 1); // le 1 = prend tout l'espace restant
    }

MainWindow::~MainWindow()
    {
        delete ui;
    }


//#include "mainwindow.h" récupère la déclaration de notre fenêtre.
//#include "ui_mainwindow.h" récupère l'interface générée depuis mainwindow.ui.
//MainWindow::MainWindow(...) construit la fenêtre.
//ui->setupUi(this) charge l'interface.
//setWindowTitle(...) donne son nom à la fenêtre.
//MainWindow::~MainWindow() libère la mémoire utilisée par l'interface.
