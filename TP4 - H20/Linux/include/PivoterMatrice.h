/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M> class PivoterMatrice {
public:
  // Constructeurs
  PivoterMatrice();
  PivoterMatrice(M *matrice);
  // Destructeur
  ~PivoterMatrice() = default;
  void pivoterMatrice(Direction direction);

private:
  Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
  Coordonnees recupererCoordonnees(Coordonnees coords) const;
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice() {
  // TO DO
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
  // TO DO
  return {};
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
  // TO DO
  return {};
}

#endif
