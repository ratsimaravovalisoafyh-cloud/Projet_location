#include "toolbar.h"
#include "ui_toolbar.h"
#include <QComboBox>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
toolbar::toolbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::toolbar)
{
    ui->setupUi(this);
    QPixmap pm("://images/search.png");//changer couleur icon
    QPainter p(&pm);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(pm.rect(), QColor("#6d8fb5"));
    p.end();
    ui->lineEdit->addAction(QIcon(pm), QLineEdit::LeadingPosition);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &toolbar::rechercheChange);
    connect(ui->combotri, &QComboBox::currentIndexChanged, this, &toolbar::triChange);
}

toolbar::~toolbar()
{
    delete ui;
}
