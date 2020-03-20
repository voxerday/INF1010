#include "Pixel.h"

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
    : rouge_(rouge), vert_(vert), bleu_(bleu) {}

void Pixel::operator=(const Pixel &pixel) {
  // TO DO
    bleu_ = pixel.bleu_;
    vert_ = pixel.vert_;
    rouge_ = pixel.rouge_;
}

void Pixel::setRouge(int rouge) {
    rouge_ = rouge;
}

void Pixel::setVert(int vert) {
    vert_ = vert;
}

void Pixel::setBleu(int bleu) {
    bleu_ = bleu;
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

std::ostream &operator<<(std::ostream &os, Pixel pixel) {
    os << pixel.getRouge() << pixel.getVert() << pixel.getBleu() << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Pixel &pixel) {
    uint8_t rouge, vert, bleu;
    if (is >> rouge >> vert >> bleu) {
        pixel.setRouge(rouge);
        pixel.setVert(vert);
        pixel.setBleu(bleu);
    }
    return is;
}