//! Classe Pixel
//! \author Careau, Martin(1978446) et Sitchom Kamdem, Laurelle Audrey(1876331)
//! \date 30 mars 2020

#include "Pixel.h"

/**
 * @brief retourne une valeur pixel entre 0 -> 255
 * @param a, l'élément du pixel, a retourner entre 0 -> 255
 * @return la valeur in range entre 0 -> 255
 */
template <typename T> inline T inRange(T a) {
    a = (a > 255) ? 255 : a;
    return (a < 0) ? 0 : a;
}

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(inRange(rouge)), vert_(inRange(vert)), bleu_(inRange(bleu)) {}
/**
 * @brief Copie l'élément pixel
 * @param pixel, le pixel à copier
 */
void Pixel::operator=(const Pixel &pixel) {
    bleu_ = pixel.bleu_;
    vert_ = pixel.vert_;
    rouge_ = pixel.rouge_;
}
/**
 * @brief Set la valeur du paramètre de pixel
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 */
void Pixel::setRouge(int rouge) {
    rouge_ = (uint8_t) inRange(rouge);
}
/**
 * @brief Set la valeur du paramètre de pixel
 * @param vert, l'élément G du pixel, entre 0 -> 255
 */
void Pixel::setVert(int vert) {
    vert_ = (uint8_t) inRange(vert);
}
/**
 * @brief Set la valeur du paramètre de pixel
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
void Pixel::setBleu(int bleu) {
    bleu_ = (uint8_t) inRange(bleu);
}
/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }
/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }
/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }
/**
 * @brief Opérateur permetant d'afficher un pixel en hexadécimal
 * @param os, le stream d'affichage
 * @param pixel, le pixel à afficher
 * @return le stream d'affichage
 */
std::ostream &operator<<(std::ostream &os, Pixel pixel) {
    os << "#"
        << std::hex << std::uppercase << std::setfill('0') 
        << std::setw(2) << unsigned(pixel.getRouge()) << " " 
        << std::setw(2) << unsigned(pixel.getVert()) << " " 
        << std::setw(2) << unsigned(pixel.getBleu());
    return os;
}
/**
 * @brief Opérateur qui affecte un stream à un pixel
 * @param is, le stream avec les données du pixel
 * @param pixel, le pixel à affecter
 * @return le stream
 */
std::istream &operator>>(std::istream &is, Pixel &pixel) {
    int rouge, vert, bleu, cont;
    cont = (is >> rouge >> vert >> bleu) ? 1 : 0;
    while(cont){
        pixel.setRouge(rouge);
        pixel.setVert(vert);
        pixel.setBleu(bleu);
        cont = 0;
    }
    return is;
}