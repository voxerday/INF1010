/*
 * Titre : AgrandirMatrice.h - Travail Pratique #4 - Programmation Orient�e
 * Objet Date : 27 F�vrier 2020 Auteur : Nabil Dabouz
 */

#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

template <class M> class AgrandirMatrice {
public:
  AgrandirMatrice();
  AgrandirMatrice(M *matrice);
  ~AgrandirMatrice() = default;
  Coordonnees trouverLePlusProcheVoisin(const unsigned int &rapport,
                                        size_t posY, size_t posX) const;
  void redimensionnerImage(const unsigned int &rapport);

private:
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> AgrandirMatrice<M>::AgrandirMatrice() {
  // TO DO
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
AgrandirMatrice<M>::AgrandirMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver le point le plus proche du point (posX, posY) dans la matrice
 * originale
 * @param rapport, le rapport du redimensionnement de l'image
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return coordonnées du point le plus proche
 */
template <class M>
Coordonnees
AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int &rapport,
                                              size_t posY, size_t posX) const {
  // TO DO
  return {};
}

#endif
