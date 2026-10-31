#include "qrcodegenerator.h"

#include <QPainter>
#include <QVector>
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <QByteArray>

namespace {

int valeurAlphanumerique(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    switch (c) {
    case ' ': return 36;
    case '$': return 37;
    case '%': return 38;
    case '*': return 39;
    case '+': return 40;
    case '-': return 41;
    case '.': return 42;
    case '/': return 43;
    case ':': return 44;
    default: return -1;
    }
}

void ajouterBits(QVector<int> &bits, int valeur, int longueur)
{
    for (int i = longueur - 1; i >= 0; --i)
        bits.append((valeur >> i) & 1);
}

std::uint8_t multiplierGf(std::uint8_t x, std::uint8_t y)
{
    int resultat = 0;
    for (int i = 0; i < 8; ++i) {
        if (y & 1)
            resultat ^= x;
        y >>= 1;
        x <<= 1;
        if (x & 0x100)
            x ^= 0x11D;
    }
    return static_cast<std::uint8_t>(resultat);
}

std::array<std::uint8_t, 10> calculerCorrection(
    const std::array<std::uint8_t, 16> &donnees)
{
    constexpr int degre = 10;
    std::array<std::uint8_t, degre> generateur{};
    generateur[degre - 1] = 1;
    std::uint8_t racine = 1;
    for (int i = 0; i < degre; ++i) {
        for (int j = 0; j < degre; ++j) {
            generateur[j] = multiplierGf(generateur[j], racine);
            if (j + 1 < degre)
                generateur[j] ^= generateur[j + 1];
        }
        racine = multiplierGf(racine, 2);
    }

    std::array<std::uint8_t, degre> reste{};
    for (std::uint8_t octet : donnees) {
        const std::uint8_t facteur = octet ^ reste[0];
        for (int j = 0; j < degre - 1; ++j)
            reste[j] = reste[j + 1];
        reste[degre - 1] = 0;
        for (int j = 0; j < degre; ++j)
            reste[j] ^= multiplierGf(generateur[j], facteur);
    }
    return reste;
}

} //namespace

QImage creerImageQrFacture(const QString &texte)
{
    // Version 1-M accepte jusqu'à 20 caractères alphanumériques.
    const QByteArray entree = texte.toUpper().toLatin1();
    if (entree.isEmpty() || entree.size() > 20)
        return {};

    QVector<int> valeurs;
    valeurs.reserve(entree.size());
    for (char c : entree) {
        const int valeur = valeurAlphanumerique(c);
        if (valeur < 0)
            return {};
        valeurs.append(valeur);
    }

    // Encodage QR alphanumérique : mode, longueur, puis groupes de 2 caractères.
    QVector<int> bits;
    ajouterBits(bits, 0x2, 4); // mode alphanumérique
    ajouterBits(bits, valeurs.size(), 9);
    int i = 0;
    for (; i + 1 < valeurs.size(); i += 2)
        ajouterBits(bits, valeurs[i] * 45 + valeurs[i + 1], 11);
    if (i < valeurs.size())
        ajouterBits(bits, valeurs[i], 6);

    const int capaciteBits = 16 * 8;
    for (int n = 0; n < 4 && bits.size() < capaciteBits; ++n)
        bits.append(0); // terminateur
    while (bits.size() % 8 != 0)
        bits.append(0);

    std::array<std::uint8_t, 16> donnees{};
    int octet = 0;
    for (int pos = 0; pos < bits.size(); pos += 8) {
        int valeur = 0;
        for (int b = 0; b < 8; ++b)
            valeur = (valeur << 1) | bits[pos + b];
        donnees[octet++] = static_cast<std::uint8_t>(valeur);
    }
    const std::array<std::uint8_t, 2> remplissage{0xEC, 0x11};
    int numeroRemplissage = 0;
    while (octet < static_cast<int>(donnees.size()))
        donnees[octet++] = remplissage[numeroRemplissage++ % 2];

    const auto correction = calculerCorrection(donnees);
    QVector<int> flux;
    flux.reserve(26 * 8);
    for (std::uint8_t v : donnees) ajouterBits(flux, v, 8);
    for (std::uint8_t v : correction) ajouterBits(flux, v, 8);

    constexpr int taille = 21;
    QVector<QVector<int>> modules(taille, QVector<int>(taille, -1));
    QVector<QVector<bool>> fonction(taille, QVector<bool>(taille, false));
    auto placerFonction = [&](int x, int y, bool noir) {
        if (x >= 0 && x < taille && y >= 0 && y < taille) {
            modules[y][x] = noir ? 1 : 0;
            fonction[y][x] = true;
        }
    };

    // Trois repères de position et leur bordure blanche.
    const std::array<std::array<int, 2>, 3> centres{{{{3, 3}}, {{17, 3}}, {{3, 17}}}};
    for (const auto &centre : centres) {
        for (int dy = -4; dy <= 4; ++dy) {
            for (int dx = -4; dx <= 4; ++dx) {
                const int distance = std::max(std::abs(dx), std::abs(dy));
                const bool noir = distance != 2 && distance != 4;
                placerFonction(centre[0] + dx, centre[1] + dy, noir);
            }
        }
    }

    // Motifs de synchronisation sur la version 1.
    for (int p = 8; p <= 12; ++p) {
        placerFonction(p, 6, p % 2 == 0);
        placerFonction(6, p, p % 2 == 0);
    }

    // Les cases réservées pour les informations de format.
    for (int p = 0; p <= 5; ++p) placerFonction(8, p, false);
    placerFonction(8, 7, false);
    placerFonction(8, 8, false);
    placerFonction(7, 8, false);
    for (int p = 9; p < 15; ++p) placerFonction(14 - p, 8, false);
    for (int p = 0; p < 8; ++p) placerFonction(taille - 1 - p, 8, false);
    for (int p = 8; p < 15; ++p) placerFonction(8, taille - 15 + p, false);
    placerFonction(8, taille - 8, true); // module sombre obligatoire

    // Placement des bits de données, en colonnes alternées de bas en haut.
    int indexBit = 0;
    for (int droite = taille - 1; droite >= 1; droite -= 2) {
        if (droite == 6) --droite;
        const bool versLeHaut = ((droite + 1) & 2) == 0;
        for (int k = 0; k < taille; ++k) {
            const int y = versLeHaut ? taille - 1 - k : k;
            for (int decalage = 0; decalage < 2; ++decalage) {
                const int x = droite - decalage;
                if (!fonction[y][x]) {
                    int bit = indexBit < flux.size() ? flux[indexBit] : 0;
                    ++indexBit;
                    if ((x + y) % 2 == 0) bit ^= 1; // masque QR n° 0
                    modules[y][x] = bit;
                }
            }
        }
    }

    // Informations de format : correction M et masque 0.
    int format = 0; // niveau M = 00, masque 0 = 000
    int reste = format << 10;
    for (int bit = 14; bit >= 10; --bit) {
        if ((reste >> bit) & 1)
            reste ^= 0x537 << (bit - 10);
    }
    const int formatBits = ((format << 10) | reste) ^ 0x5412;
    auto placerFormat = [&](int x, int y, int bit) {
        modules[y][x] = (formatBits >> bit) & 1;
    };
    for (int bit = 0; bit <= 5; ++bit) placerFormat(8, bit, bit);
    placerFormat(8, 7, 6);
    placerFormat(8, 8, 7);
    placerFormat(7, 8, 8);
    for (int bit = 9; bit < 15; ++bit) placerFormat(14 - bit, 8, bit);
    for (int bit = 0; bit < 8; ++bit) placerFormat(taille - 1 - bit, 8, bit);
    for (int bit = 8; bit < 15; ++bit) placerFormat(8, taille - 15 + bit, bit);

    // Une marge blanche de quatre modules est requise pour le scan.
    constexpr int echelle = 5; // 145 px, tient dans le QLabel de 150 px
    constexpr int marge = 4;
    const int pixels = (taille + marge * 2) * echelle;
    QImage image(pixels, pixels, QImage::Format_RGB32);
    image.fill(Qt::white);
    QPainter peintre(&image);
    peintre.setPen(Qt::NoPen);
    peintre.setBrush(Qt::black);
    for (int y = 0; y < taille; ++y) {
        for (int x = 0; x < taille; ++x) {
            if (modules[y][x] == 1)
                peintre.drawRect((x + marge) * echelle,
                                 (y + marge) * echelle,
                                 echelle, echelle);
        }
    }
    return image;
}
