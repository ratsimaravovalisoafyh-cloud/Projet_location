#ifndef VOITUREDIALOG_H
#define VOITUREDIALOG_H
#include"voiture.h"
#include <QDialog>
#include <QString>
#include <QComboBox>
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
    QString m_photo;
    class QLabel *m_apercu = nullptr;
    void afficherApercu();
    QComboBox *m_comboStatut = nullptr;
protected:
    void accept() override;
};

#endif // VOITUREDIALOG_H
