#include "toolbar.h"
#include "ui_toolbar.h"
#include <QLineEdit>
#include <QComboBox>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QColor>

toolbar::toolbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::toolbar)
{
    ui->setupUi(this);

    // l'icône de la loupe fait  en bleu clair pour qu'elle suive le thème
    QPixmap pm("://images/search.png");
    if (!pm.isNull()) {
        QPainter p(&pm);
        p.setCompositionMode(QPainter::CompositionMode_SourceIn); // la couleur ne remplace que les pixels visibles
        p.fillRect(pm.rect(), QColor("#6d8fb5"));
        p.end();
    }
    ui->lineEdit->addAction(QIcon(pm), QLineEdit::LeadingPosition); // place la loupe à gauche dans la recherche

    // on prévient la fenêtre quand on tape ou quand on change le tri
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &toolbar::rechercheChange);
    connect(ui->combotri, &QComboBox::currentIndexChanged, this, &toolbar::triChange);
}

toolbar::~toolbar()
{
    delete ui;
}