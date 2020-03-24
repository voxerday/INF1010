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
    matrice_ = nullptr;
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}

template <class M>
inline void PivoterMatrice<M>::pivoterMatrice(Direction direction) {
    Coordonnees pos;
    int x, y;
    std::unique_ptr<M> matrice = matrice_->clone();
    for (int i = 0; i < matrice_->getWidth(); i++) {
        for (int j = 0; j < matrice_->getHeight(); j++) {
            pos = changerCoordonneesCentreMatrice({ i,j });
            if (direction == Direction::Right) {
                x = -pos.y;
                y = pos.x;
            }
            else {
                x = pos.y;
                y = -pos.x;
            }
            pos = recupererCoordonnees({ x,y });
            matrice_->ajouterElement(matrice->operator()(i,j), pos.y, pos.x);
        }
    }
    matrice_;
}


/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
    coords.x = coords.x - matrice_->getWidth() / 2;
    coords.y = coords.y - matrice_->getHeight() / 2;
    return { coords };
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
    coords.x = coords.x + matrice_->getWidth() / 2;
    coords.y = coords.y + matrice_->getHeight() / 2;
    return { coords };
}

#endif
