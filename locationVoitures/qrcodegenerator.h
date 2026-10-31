#ifndef QRCODEGENERATOR_H
#define QRCODEGENERATOR_H

#include <QImage>
#include <QString>

// Générateur autonome pour les références de facture courtes (ex. FAC-2026-000010).
// Il produit un QR Code version 1, correction d'erreur M.
QImage creerImageQrFacture(const QString &texte);

#endif // QRCODEGENERATOR_H
