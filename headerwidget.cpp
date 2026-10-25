#include "headerwidget.h"
#include "ui_headerwidget.h"
#include<QPushButton>
HeaderWidget::HeaderWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HeaderWidget)
{
    ui->setupUi(this);
    connect(ui->boutonAjouter, &QPushButton::clicked, this, &HeaderWidget::ajouterDemande);
}

HeaderWidget::~HeaderWidget()
{
    delete ui;
}
