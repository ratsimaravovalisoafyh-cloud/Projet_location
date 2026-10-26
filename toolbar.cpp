#include "toolbar.h"
#include "ui_toolbar.h"
#include <QComboBox>
toolbar::toolbar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::toolbar)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &toolbar::rechercheChange);
    connect(ui->combotri, &QComboBox::currentIndexChanged, this, &toolbar::triChange);
}

toolbar::~toolbar()
{
    delete ui;
}
