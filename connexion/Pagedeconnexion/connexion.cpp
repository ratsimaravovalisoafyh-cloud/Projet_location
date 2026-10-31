#include "connexion.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFont>
#include <QFrame>
#include <QPainter>
#include <QPixmap>
#include <QPolygon>
#include <QColor>

// ==================================
// CREATION DU LOGO DE VOITURE
// ==================================

static QPixmap creerLogo()
{
    QPixmap pixmap(120, 120);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Cercle bleu clair
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#E7F0FF"));
    painter.drawEllipse(5, 5, 110, 110);

    // Carrosserie bleue
    painter.setBrush(QColor("#1877F2"));
    painter.drawRoundedRect(22, 55, 76, 25, 8, 8);

    // Toit de la voiture
    QPolygon toit;
    toit << QPoint(35, 55)
         << QPoint(45, 35)
         << QPoint(75, 35)
         << QPoint(88, 55);

    painter.drawPolygon(toit);

    // Vitres blanches
    painter.setBrush(QColor("#FFFFFF"));

    QPolygon vitreGauche;
    vitreGauche << QPoint(43, 52)
                << QPoint(49, 40)
                << QPoint(59, 40)
                << QPoint(59, 52);

    painter.drawPolygon(vitreGauche);

    QPolygon vitreDroite;
    vitreDroite << QPoint(63, 40)
                << QPoint(73, 40)
                << QPoint(81, 52)
                << QPoint(63, 52);

    painter.drawPolygon(vitreDroite);

    // Roues bleu foncé
    painter.setBrush(QColor("#174A8B"));
    painter.drawEllipse(32, 72, 18, 18);
    painter.drawEllipse(72, 72, 18, 18);

    // Centres des roues blancs
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawEllipse(37, 77, 8, 8);
    painter.drawEllipse(77, 77, 8, 8);

    return pixmap;

}

// ==================================
// CONSTRUCTEUR DE LA FENETRE
// ==================================

Connexion::Connexion(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Rent a Car - Connexion");
    setMinimumSize(850, 520);
    resize(950, 580);

    setStyleSheet(
        "Connexion {"
        " background-color: #F0F2F5;"
        "}"
        );

    QHBoxLayout *layoutPrincipal = new QHBoxLayout(this);
    layoutPrincipal->setContentsMargins(55, 35, 55, 35);
    layoutPrincipal->setSpacing(45);

    // ==================================
    // PARTIE GAUCHE
    // ==================================

    QWidget *gauche = new QWidget(this);

    QVBoxLayout *layoutGauche = new QVBoxLayout(gauche);
    layoutGauche->setAlignment(Qt::AlignCenter);
    layoutGauche->setSpacing(12);

    // Logo
    QLabel *logo = new QLabel(gauche);
    logo->setPixmap(creerLogo());
    logo->setAlignment(Qt::AlignCenter);
    logo->setFixedSize(130, 130);

    // Nom de l'application
    QLabel *nomApplication = new QLabel("Rent a Car", gauche);
    nomApplication->setFont(QFont("Arial", 32, QFont::Bold));
    nomApplication->setAlignment(Qt::AlignCenter);
    nomApplication->setStyleSheet(
        "color: #1877F2;"
        "background: transparent;"
        );

    // Description
    QLabel *description = new QLabel(
        "La simplicité de louer,\n"
        "le plaisir de conduire.",
        gauche
        );

    description->setFont(QFont("Arial", 14));
    description->setAlignment(Qt::AlignCenter);
    description->setStyleSheet(
        "color: #333333;"
        "background: transparent;"
        );

    layoutGauche->addWidget(logo, 0, Qt::AlignCenter);
    layoutGauche->addWidget(nomApplication);
    layoutGauche->addWidget(description);

    // ==================================
    // CARTE DE CONNEXION
    // ==================================

    QFrame *carteConnexion = new QFrame(this);
    carteConnexion->setObjectName("carteConnexion");
    carteConnexion->setFixedWidth(350);

    carteConnexion->setStyleSheet(
        "QFrame#carteConnexion {"
        " background-color: #FFFFFF;"
        " border: 1px solid #E0E0E0;"
        " border-radius: 15px;"
        "}"
        );

    QVBoxLayout *layoutConnexion = new QVBoxLayout(carteConnexion);
    layoutConnexion->setContentsMargins(25, 25, 25, 25);
    layoutConnexion->setSpacing(13);

    // Titre
    QLabel *titreConnexion = new QLabel("Bienvenue !", carteConnexion);
    titreConnexion->setFont(QFont("Arial", 22, QFont::Bold));
    titreConnexion->setAlignment(Qt::AlignCenter);
    titreConnexion->setStyleSheet(
        "color: #1877F2;"
        "background: transparent;"
        );

    QLabel *sousTitre = new QLabel(
        "Connectez-vous à votre compte",
        carteConnexion
        );

    sousTitre->setAlignment(Qt::AlignCenter);
    sousTitre->setStyleSheet(
        "color: #777777;"
        "font-size: 12px;"
        "background: transparent;"
        );

    // Nom d'utilisateur
    QLabel *labelUtilisateur = new QLabel(
        "Nom d'utilisateur",
        carteConnexion
        );

    labelUtilisateur->setStyleSheet(
        "color: #333333;"
        "font-weight: bold;"
        "background: transparent;"
        );

    nomUtilisateurEdit = new QLineEdit(carteConnexion);
    nomUtilisateurEdit->setPlaceholderText("Entrez votre nom d'utilisateur");
    nomUtilisateurEdit->setMinimumHeight(42);

    // Mot de passe
    QLabel *labelPassword = new QLabel("Mot de passe", carteConnexion);
    labelPassword->setStyleSheet(
        "color: #333333;"
        "font-weight: bold;"
        "background: transparent;"
        );

    passwordEdit = new QLineEdit(carteConnexion);
    passwordEdit->setPlaceholderText("Entrez votre mot de passe");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(42);

    // Type de compte
    QLabel *labelTypeCompte = new QLabel("Type de compte", carteConnexion);
    labelTypeCompte->setStyleSheet(
        "color: #333333;"
        "font-weight: bold;"
        "background: transparent;"
        );

    typeCompteCombo = new QComboBox(carteConnexion);
    typeCompteCombo->addItem("Employé", "employe");
    typeCompteCombo->addItem("Administrateur", "admin");
    typeCompteCombo->setMinimumHeight(42);

    // Style des champs
    QString styleChamps =
        "QLineEdit, QComboBox {"
        " border: 1px solid #CCCCCC;"
        " border-radius: 7px;"
        " padding: 8px;"
        " font-size: 13px;"
        " background-color: #FFFFFF;"
        " color: #333333;"
        "}"
        "QLineEdit:focus, QComboBox:focus {"
        " border: 1px solid #1877F2;"
        "}";

    nomUtilisateurEdit->setStyleSheet(styleChamps);
    passwordEdit->setStyleSheet(styleChamps);
    typeCompteCombo->setStyleSheet(styleChamps);

    // Bouton de connexion
    loginButton = new QPushButton("Se connecter", carteConnexion);
    loginButton->setMinimumHeight(45);

    loginButton->setStyleSheet(
        "QPushButton {"
        " background-color: #1877F2;"
        " color: #FFFFFF;"
        " border: none;"
        " border-radius: 7px;"
        " font-size: 15px;"
        " font-weight: bold;"
        "}"
        "QPushButton:hover {"
        " background-color: #166FE5;"
        "}"
        "QPushButton:pressed {"
        " background-color: #1258B8;"
        "}"
        );

    // Texte inférieur
    QLabel *texteBas = new QLabel(
        "Rent a Car - Votre mobilité, notre priorité.",
        carteConnexion
        );

    texteBas->setAlignment(Qt::AlignCenter);
    texteBas->setWordWrap(true);
    texteBas->setStyleSheet(
        "color: #888888;"
        "font-size: 10px;"
        "background: transparent;"
        );

    // Organisation de la carte
    layoutConnexion->addWidget(titreConnexion);
    layoutConnexion->addWidget(sousTitre);
    layoutConnexion->addSpacing(8);

    layoutConnexion->addWidget(labelUtilisateur);
    layoutConnexion->addWidget(nomUtilisateurEdit);

    layoutConnexion->addWidget(labelPassword);
    layoutConnexion->addWidget(passwordEdit);

    layoutConnexion->addWidget(labelTypeCompte);
    layoutConnexion->addWidget(typeCompteCombo);

    layoutConnexion->addSpacing(5);
    layoutConnexion->addWidget(loginButton);
    layoutConnexion->addSpacing(5);
    layoutConnexion->addWidget(texteBas);

    // Assemblage de la fenêtre
    layoutPrincipal->addWidget(gauche, 1);
    layoutPrincipal->addWidget(carteConnexion);

    connect(
        loginButton,
        &QPushButton::clicked,
        this,
        &Connexion::seConnecter
        );

}

// ==================================
// FONCTION DE CONNEXION
// ==================================

void Connexion::seConnecter()
{
    QString nomUtilisateur = nomUtilisateurEdit->text().trimmed();
    QString motDePasse = passwordEdit->text();
    QString typeCompte = typeCompteCombo->currentData().toString();

    if (nomUtilisateur.isEmpty() || motDePasse.isEmpty()) {
        QMessageBox::warning(
            this,
            "Champs manquants",
            "Veuillez remplir le nom d'utilisateur et le mot de passe."
            );
        return;
    }

    // Vérification temporaire : MySQL n'est pas encore connecté.
    QString roleAffiche;

    if (typeCompte == "employe") {
        roleAffiche = "Employé";
    } else {
        roleAffiche = "Administrateur";
    }

    QMessageBox::information(
        this,
        "Rent a Car",
        "Nom d'utilisateur : " + nomUtilisateur +
            "\nType de compte : " + roleAffiche +
            "\n\nLa connexion à MySQL reste à configurer."
        );

}