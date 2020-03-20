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
 * @brief constructeur par défaut de la classe
 */
template <typename T> inline Matrice<T>::Matrice() {
  // TO DO
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
