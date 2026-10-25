#ifndef VOITUREDIALOG_H
#define VOITUREDIALOG_H
#include"voiture.h"
#include <QDialog>

namespace Ui {
class VoitureDialog;
}

class VoitureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoitureDialog(QWidget *parent = nullptr);
    ~VoitureDialog();
    Voiture voiture() const;
    void remplir(const Voiture &v);

private:
    Ui::VoitureDialog *ui;
    int m_id = 0;
protected:
    void accept() override;
};

#endif // VOITUREDIALOG_H
