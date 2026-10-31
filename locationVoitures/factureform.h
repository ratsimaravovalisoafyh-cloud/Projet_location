#ifndef FACTUREFORM_H
#define FACTUREFORM_H

#include <QDialog>

namespace Ui {
class factureForm;
}

class factureForm : public QDialog
{
    Q_OBJECT

public:
    explicit factureForm(QWidget *parent, int idLocation);
    ~factureForm();

private:
    Ui::factureForm *ui;

    int m_idLocation;

    void chargerFacture();
    void telechargerPdf();
};

#endif // FACTUREFORM_H
