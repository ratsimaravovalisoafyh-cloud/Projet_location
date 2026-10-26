/********************************************************************************
** Form generated from reading UI file 'toolbar.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBAR_H
#define UI_TOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_toolbar
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QComboBox *combotri;

    void setupUi(QWidget *toolbar)
    {
        if (toolbar->objectName().isEmpty())
            toolbar->setObjectName("toolbar");
        toolbar->resize(400, 300);
        horizontalLayout = new QHBoxLayout(toolbar);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(28, 20, 28, 20);
        lineEdit = new QLineEdit(toolbar);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        combotri = new QComboBox(toolbar);
        combotri->addItem(QString());
        combotri->addItem(QString());
        combotri->addItem(QString());
        combotri->setObjectName("combotri");

        horizontalLayout->addWidget(combotri);

        QWidget::setTabOrder(lineEdit, combotri);

        retranslateUi(toolbar);

        QMetaObject::connectSlotsByName(toolbar);
    } // setupUi

    void retranslateUi(QWidget *toolbar)
    {
        toolbar->setWindowTitle(QCoreApplication::translate("toolbar", "Form", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("toolbar", "Rechercher une voiture ", nullptr));
        combotri->setItemText(0, QCoreApplication::translate("toolbar", "Recommand\303\251", nullptr));
        combotri->setItemText(1, QCoreApplication::translate("toolbar", "Prix Croissant", nullptr));
        combotri->setItemText(2, QCoreApplication::translate("toolbar", "Prix decroissant", nullptr));

        combotri->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class toolbar: public Ui_toolbar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBAR_H
