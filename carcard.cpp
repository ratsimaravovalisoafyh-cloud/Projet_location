#include "carcard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QPainterPath>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QMenu>
#include <QAction>
// enlève les marges blanches ou transparentes autour de la voiture
/*static QPixmap rogner(const QPixmap &src)
{
    if (src.isNull())
        return src;

    QImage img = src.toImage().convertToFormat(QImage::Format_ARGB32);
    int minX = img.width(), minY = img.height(), maxX = -1, maxY = -1;

    for (int y = 0; y < img.height(); ++y) {
        const QRgb *ligne = reinterpret_cast<const QRgb *>(img.constScanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            QRgb c = ligne[x];
            bool vide = qAlpha(c) < 20
                        || (qRed(c) > 245 && qGreen(c) > 245 && qBlue(c) > 245);
            if (!vide) {
                minX = qMin(minX, x);
                maxX = qMax(maxX, x);
                minY = qMin(minY, y);
                maxY = qMax(maxY, y);
            }
        }
    }
    if (maxX < 0)
        return src; //l'image est blanc

    QRect zone(minX, minY, maxX - minX + 1, maxY - minY + 1);
    const int marge = qMax(6, zone.width() / 50);
    zone.adjust(-marge, -marge, marge, marge);
    zone = zone.intersected(img.rect());
    return src.copy(zone);
}*/
// enlève les marges blanches ou transparentes autour de la voiture
static QPixmap rogner(const QPixmap &src)
{
    if (src.isNull())
        return src;

    // l'analyse se fait sur une petite copie (300 px de large) : beaucoup plus rapide
    QImage img = src.toImage();
    const qreal echelle = img.width() > 300 ? 300.0 / img.width() : 1.0;
    if (echelle < 1.0)
        img = img.scaledToWidth(300, Qt::FastTransformation);
    img = img.convertToFormat(QImage::Format_ARGB32);

    int minX = img.width(), minY = img.height(), maxX = -1, maxY = -1;
    for (int y = 0; y < img.height(); ++y) {
        const QRgb *ligne = reinterpret_cast<const QRgb *>(img.constScanLine(y));
        for (int x = 0; x < img.width(); ++x) {
            QRgb c = ligne[x];
            bool vide = qAlpha(c) < 20
                        || (qRed(c) > 245 && qGreen(c) > 245 && qBlue(c) > 245);
            if (!vide) {
                minX = qMin(minX, x);
                maxX = qMax(maxX, x);
                minY = qMin(minY, y);
                maxY = qMax(maxY, y);
            }
        }
    }
    if (maxX < 0)
        return src;                       // image entièrement blanche

    QRect zone(minX, minY, maxX - minX + 1, maxY - minY + 1);
    const int marge = qMax(2, zone.width() / 50);
    zone.adjust(-marge, -marge, marge, marge);
    zone = zone.intersected(img.rect());

    // on remet la zone à l'échelle de l'image d'origine
    if (echelle < 1.0)
        zone = QRect(qFloor(zone.x() / echelle), qFloor(zone.y() / echelle),
                     qCeil(zone.width() / echelle), qCeil(zone.height() / echelle));
    zone = zone.intersected(src.rect());
    return src.copy(zone);
}

// charge une photo une seule fois : les cartes suivantes reprennent le résultat en mémoire
static QPixmap chargerPhoto(const QString &chemin)
{
    static QHash<QString, QPixmap> cache;
    auto it = cache.constFind(chemin);
    if (it != cache.constEnd())
        return it.value();

    QPixmap pm = rogner(QPixmap(chemin));
    if (pm.width() > 600)                 // 600 px suffisent pour une carte de 260 px, même en haute densité
        pm = pm.scaledToWidth(600, Qt::SmoothTransformation);
    cache.insert(chemin, pm);
    return pm;
}
CarCard::CarCard(Statut statut, const QString &nom, const QString &type, const QString &prix ,const QString &immatriculation,int id, const QString &photo, QWidget *parent, bool admin)
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
    labelprix->setToolTip("Prix par jour");
    QLabel *labelimage = new QLabel("image");
    QLabel *labelimmat = new QLabel(immatriculation);

    // badge de statut cliquable
    QPushButton *boutonstatut = new QPushButton(texteStatut(statut));
    boutonstatut->setObjectName("labelStatut");              // même nom : le QSS actuel continue de fonctionner
    boutonstatut->setProperty("statut", cleStatut(statut));
    boutonstatut->setCursor(Qt::PointingHandCursor);
    boutonstatut->setToolTip("Cliquer pour changer le statut");

    connect(boutonstatut, &QPushButton::clicked, this, [this, boutonstatut, statut]() {
        QMenu menu(this);
        for (Statut s : {Statut::Disponible, Statut::Loue, Statut::Maintenance}) {
            QAction *action = menu.addAction(texteStatut(s));
            action->setCheckable(true);
            action->setChecked(s == statut);               // coche le statut actuel
            connect(action, &QAction::triggered, this, [this, s, statut]() {
                if (s != statut)
                    emit statutDemande(m_id, s);
            });
        }
        menu.exec(boutonstatut->mapToGlobal(QPoint(0, boutonstatut->height())));
    });

    //style des cartes
    labelnom->setObjectName("carteNom");
    labeltype->setObjectName("carteType");
    labelimmat->setObjectName("carteImmat");
    labelprix->setObjectName("cartePrix");
    labelimage->setObjectName("carteImage");
    m_image = labelimage;
   // m_source = rogner(QPixmap(photo));
    m_source = chargerPhoto(photo);      // vide si pas de photo    // vide si pas de photo
    setObjectName("carte");
    labelimage->setAlignment(Qt::AlignCenter);
    labelimage->setFixedHeight(120);
    setAttribute(Qt::WA_StyledBackground, true);
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
    boutonfavoris->setObjectName("boutonFavori");
    //l'immatriculation et le badge sont sur la même ligne
    QHBoxLayout *ligneimmat = new QHBoxLayout;
    ligneimmat->setContentsMargins(0,0,0,0);
    ligneimmat->setSpacing(8);
    ligneimmat->addWidget(labelimmat);
    ligneimmat->addWidget(boutonstatut);
    ligneimmat->addStretch();

    QVBoxLayout *texte = new QVBoxLayout;
    texte->setContentsMargins(0,0,0,0);
    texte->setSpacing(2);
    texte->addWidget(labelnom);
    texte->addWidget(labeltype);
    texte->addLayout(ligneimmat);

    QHBoxLayout *haut = new QHBoxLayout;
    haut->addLayout(texte);
    haut->addStretch();
    haut->addWidget(boutonfavoris, 0, Qt::AlignTop);
    Layout->addLayout(haut);
    Layout->addWidget(labelimage);
    QPushButton *boutonmodifier = new QPushButton("Modifier");
    QPushButton *boutonsupprimer = new QPushButton("Supprimer");
    boutonmodifier->setVisible(admin);
    boutonsupprimer->setVisible(admin);

    //supprimer au'une voiiture disponible
    if (statut != Statut::Disponible) {
        boutonsupprimer->setEnabled(false);
        boutonsupprimer->setToolTip("Impossible de supprimer une voiture louée ou en maintenance");
    }

    connect(boutonmodifier, &QPushButton::clicked, this, [this]() { emit modifierDemande(m_id); });
    connect(boutonsupprimer, &QPushButton::clicked, this, [this]() { emit supprimerDemande(m_id); });
    boutonmodifier->setObjectName("boutonModifier");
    boutonsupprimer->setObjectName("boutonSupprimer");
    QHBoxLayout *bas = new QHBoxLayout;
    bas->addWidget(labelprix);
    bas->addStretch();
    bas->addWidget(boutonmodifier);
    bas->addWidget(boutonsupprimer);
    Layout->addLayout(bas);

    majImage();




}
void CarCard::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    majImage();
}

void CarCard::majImage()
{
    if (!m_image || m_source.isNull())
        return;                         // on garde le mot "image"

    const qreal dpr = devicePixelRatioF();
    const int w = qMax(10, width() - 32);
    const int h = m_image->height();

    QPixmap mise = m_source.scaled(QSize(qRound(w * dpr), qRound(h * dpr)),
                                   Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mise.setDevicePixelRatio(dpr);
    m_image->setPixmap(mise);           // le label centre l'image
}