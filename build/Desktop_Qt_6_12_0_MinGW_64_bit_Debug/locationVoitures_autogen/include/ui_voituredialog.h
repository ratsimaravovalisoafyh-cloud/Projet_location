/********************************************************************************
** Form generated from reading UI file 'voituredialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOITUREDIALOG_H
#define UI_VOITUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VoitureDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineNom;
    QLabel *label_2;
    QLineEdit *lineImmat;
    QLabel *label_3;
    QComboBox *comboMarque;
    QLabel *label_4;
    QComboBox *comboType;
    QComboBox *comboTransmission;
    QSpinBox *spinPrix;
    QLabel *label_6;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VoitureDialog)
    {
        if (VoitureDialog->objectName().isEmpty())
            VoitureDialog->setObjectName("VoitureDialog");
        VoitureDialog->resize(470, 501);
        verticalLayout = new QVBoxLayout(VoitureDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(VoitureDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lineNom = new QLineEdit(VoitureDialog);
        lineNom->setObjectName("lineNom");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineNom);

        label_2 = new QLabel(VoitureDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::ItemRole::SpanningRole, label_2);

        lineImmat = new QLineEdit(VoitureDialog);
        lineImmat->setObjectName("lineImmat");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, lineImmat);

        label_3 = new QLabel(VoitureDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_3);

        comboMarque = new QComboBox(VoitureDialog);
        comboMarque->addItem(QString());
        comboMarque->addItem(QString());
        comboMarque->addItem(QString());
        comboMarque->setObjectName("comboMarque");
        comboMarque->setEditable(true);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, comboMarque);

        label_4 = new QLabel(VoitureDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, label_4);

        comboType = new QComboBox(VoitureDialog);
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->setObjectName("comboType");
        comboType->setEditable(true);

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, comboType);

        comboTransmission = new QComboBox(VoitureDialog);
        comboTransmission->addItem(QString());
        comboTransmission->addItem(QString());
        comboTransmission->setObjectName("comboTransmission");

        formLayout->setWidget(13, QFormLayout::ItemRole::FieldRole, comboTransmission);

        spinPrix = new QSpinBox(VoitureDialog);
        spinPrix->setObjectName("spinPrix");
        spinPrix->setMaximum(500000);
        spinPrix->setSingleStep(1000);

        formLayout->setWidget(17, QFormLayout::ItemRole::FieldRole, spinPrix);

        label_6 = new QLabel(VoitureDialog);
        label_6->setObjectName("label_6");

        formLayout->setWidget(15, QFormLayout::ItemRole::SpanningRole, label_6);

        label_5 = new QLabel(VoitureDialog);
        label_5->setObjectName("label_5");

        formLayout->setWidget(12, QFormLayout::ItemRole::FieldRole, label_5);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(VoitureDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(VoitureDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, VoitureDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, VoitureDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(VoitureDialog);
    } // setupUi

    void retranslateUi(QDialog *VoitureDialog)
    {
        VoitureDialog->setWindowTitle(QCoreApplication::translate("VoitureDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("VoitureDialog", "Nom :", nullptr));
        lineNom->setPlaceholderText(QCoreApplication::translate("VoitureDialog", "Nom", nullptr));
        label_2->setText(QCoreApplication::translate("VoitureDialog", "Immatriculation :", nullptr));
        lineImmat->setText(QString());
        lineImmat->setPlaceholderText(QCoreApplication::translate("VoitureDialog", "immatriculation", nullptr));
        label_3->setText(QCoreApplication::translate("VoitureDialog", "Marque :", nullptr));
        comboMarque->setItemText(0, QCoreApplication::translate("VoitureDialog", "Toyota", nullptr));
        comboMarque->setItemText(1, QCoreApplication::translate("VoitureDialog", "Hyundai", nullptr));
        comboMarque->setItemText(2, QCoreApplication::translate("VoitureDialog", "Renault", nullptr));

        comboMarque->setCurrentText(QCoreApplication::translate("VoitureDialog", "Toyota", nullptr));
        label_4->setText(QCoreApplication::translate("VoitureDialog", "Type :", nullptr));
        comboType->setItemText(0, QCoreApplication::translate("VoitureDialog", "Berline", nullptr));
        comboType->setItemText(1, QCoreApplication::translate("VoitureDialog", "SUV", nullptr));
        comboType->setItemText(2, QCoreApplication::translate("VoitureDialog", "Citadine", nullptr));
        comboType->setItemText(3, QCoreApplication::translate("VoitureDialog", "Pick-up", nullptr));
        comboType->setItemText(4, QCoreApplication::translate("VoitureDialog", "Coup\303\251", nullptr));
        comboType->setItemText(5, QCoreApplication::translate("VoitureDialog", "Hypercar", nullptr));

        comboType->setCurrentText(QCoreApplication::translate("VoitureDialog", "Berline", nullptr));
        comboType->setPlaceholderText(QString());
        comboTransmission->setItemText(0, QCoreApplication::translate("VoitureDialog", "Automatique", nullptr));
        comboTransmission->setItemText(1, QCoreApplication::translate("VoitureDialog", "Manuelle", nullptr));

        comboTransmission->setCurrentText(QCoreApplication::translate("VoitureDialog", "Automatique", nullptr));
        label_6->setText(QCoreApplication::translate("VoitureDialog", "Prix Journalier :", nullptr));
        label_5->setText(QCoreApplication::translate("VoitureDialog", "Transmission :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VoitureDialog: public Ui_VoitureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOITUREDIALOG_H
