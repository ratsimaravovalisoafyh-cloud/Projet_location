/********************************************************************************
** Form generated from reading UI file 'headerwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEADERWIDGET_H
#define UI_HEADERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HeaderWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labellogo;
    QLabel *labelNomApp;
    QSpacerItem *horizontalSpacer;
    QPushButton *boutonAjouter;

    void setupUi(QWidget *HeaderWidget)
    {
        if (HeaderWidget->objectName().isEmpty())
            HeaderWidget->setObjectName("HeaderWidget");
        HeaderWidget->resize(398, 307);
        horizontalLayout = new QHBoxLayout(HeaderWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(28, 14, 28, 14);
        labellogo = new QLabel(HeaderWidget);
        labellogo->setObjectName("labellogo");

        horizontalLayout->addWidget(labellogo);

        labelNomApp = new QLabel(HeaderWidget);
        labelNomApp->setObjectName("labelNomApp");

        horizontalLayout->addWidget(labelNomApp);

        horizontalSpacer = new QSpacerItem(46, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        boutonAjouter = new QPushButton(HeaderWidget);
        boutonAjouter->setObjectName("boutonAjouter");

        horizontalLayout->addWidget(boutonAjouter);


        retranslateUi(HeaderWidget);

        QMetaObject::connectSlotsByName(HeaderWidget);
    } // setupUi

    void retranslateUi(QWidget *HeaderWidget)
    {
        HeaderWidget->setWindowTitle(QCoreApplication::translate("HeaderWidget", "Form", nullptr));
        labellogo->setText(QString());
        labelNomApp->setText(QCoreApplication::translate("HeaderWidget", "rent a car", nullptr));
        boutonAjouter->setText(QCoreApplication::translate("HeaderWidget", "Ajouter une voiture ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HeaderWidget: public Ui_HeaderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEADERWIDGET_H
