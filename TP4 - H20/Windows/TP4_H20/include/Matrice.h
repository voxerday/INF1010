/*
 * Titre : Matrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "Pixel.h"

template <typename T> class Matrice {

public:
  Matrice();
  // Destructeur
  ~Matrice() = default;
  T operator()(const size_t &posY, const size_t &posX) const;
  // Lecture du fichier
  bool chargerDepuisFichier(const std::string &nomFichier);
  bool lireElement(const std::string &elementFichier, const size_t &posY,
                   const size_t &posX);
  // Remplir un matrice
  bool ajouterElement(T element, const size_t &posY, const size_t &posX);
  // Faire une copie
  std::unique_ptr<Matrice<T>> clone() const;
  // Setters
  void setHeight(size_t height);
  void setWidth(size_t width);
  // Getters
  size_t getHeight() const;
  size_t getWidth() const;

private:
  std::vector<std::vector<T>> elements_;
  size_t height_;
  size_t width_;
};

namespace {
static constexpr int CAPACITE_MATRICE = 100;
}
/**
 * @brief Retourne l’élément se trouvant à la ligne posY et la colonne posX du tableau elements_.
 * @param posY, la colonne du point dans la nouvelle image
 * @param posX, la ligne du point dans la nouvelle image
 * @return l'élément demandé, si non trouvé, retourne T()
 */
template <typename T> T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const {
    if (posX > getWidth() || posY > getHeight()) { return T(); }
    return elements_[posX][posY];
}
/**
 * @brief Lit les éléments d'une matrice depuis un fichier et les ajoutes
 * @param nomFichier, le fichier contenant la matrice
 * @return un bool; true si l'opération a réussi, sinon false si échec
 */
template <typename T> inline bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        size_t y = 0;
        size_t x = 0;
        std::string ligne;
        while (getline(fichier, ligne)) {
            if (ligne == "L") {
                if (x != 0)y += 1;
                if (height_ <= y)setHeight(y+1);
                x = 0;
                continue;
            }
            else if (width_ <= x)setWidth(x + 1);
            if (!lireElement(ligne, y, x)) {
                return false;
            }
            x += 1;
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
        << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}
/**
 * @brief Lit l'élément à ajouter au point (posX, posY)
 * @param elementFichier, l'élément à lire puis à ajouter dans la matrice
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return un bool; true si l'opération a réussi, sinon false si échec
 */
template <typename T> inline bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY,
    const size_t& posX) {
    T element;
    std::stringstream stream(elementFichier);
    stream >> element;
    return ajouterElement(element, posY, posX);
}
/**
 * @brief Ajoute un élément à la matrice au point (posX, posY)
 * @param element, l'élément à ajouter dans la matrice
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return un bool; true si l'opération a réussi, sinon false si échec
 */
template <typename T> bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX) {
    //check if posing problem if not in range...
    if (posY > height_ || posX > width_) return false;
    elements_[posX][posY] = element;
    return true;
    
}
/**
 * @brief Copie une matrice et retourne une pointeur vers cette dernière
 * @return un pointeur vers la matrice copiée
 */
template <typename T> std::unique_ptr<Matrice<T>> Matrice<T>::clone() const {
    std::unique_ptr<Matrice<T>> matrice = std::make_unique<Matrice>(*this);
    return std::move(matrice);
}
// Setters
/**
 * @brief Set la valeur height_ et fait un resize de la matrice
 * @param height, la valeur à setter height_
 */
template <typename T> void Matrice<T>::setHeight(size_t height) {
    height_ = (height > CAPACITE_MATRICE) ? CAPACITE_MATRICE : height;
    for (auto& row : elements_) {
        row.resize(height_);
    }
}
/**
 * @brief Set la valeur width_ et fait un resize de la matrice
 * @param width, la valeur à setter width_
 */
template <typename T> void Matrice<T>::setWidth(size_t width) {
    width_ = (width > CAPACITE_MATRICE) ? CAPACITE_MATRICE : width;
    elements_.resize(width_);
    setHeight(height_);
}
/**
 * @brief constructeur par défaut de la classe
 */
template <typename T> inline Matrice<T>::Matrice() {
    elements_ = {};
    height_ = 0;
    width_ = 0;
}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getHeight() const {
  return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getWidth() const {
  return width_;
}

#endif
