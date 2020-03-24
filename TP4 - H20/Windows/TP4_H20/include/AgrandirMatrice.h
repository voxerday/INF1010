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
 * @brief Agrandit une matrice selon un rapport donné
 * @param rapport, un multiplicateur pour redimmentionner la matrice
 */
template <class M> void AgrandirMatrice<M>::redimensionnerImage(const unsigned int& rapport) {
    std::unique_ptr<M> matrice = matrice_->clone();
    matrice_->setHeight(rapport * matrice_->getHeight());
    matrice_->setWidth(rapport * matrice_->getWidth());

    for (size_t i = 0; i < matrice_->getWidth(); i++) {
        for (size_t j = 0; j < matrice_->getHeight(); j++) {
            Coordonnees pos = trouverLePlusProcheVoisin(rapport, j, i);
            matrice_->ajouterElement(matrice->operator()(pos.y, pos.x), j, i);
        }
    }
}
/**
 * @brief constructeur par défaut de la classe
 */
template <class M> AgrandirMatrice<M>::AgrandirMatrice() {
    matrice_->M();
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
    Coordonnees pos;
    pos.x = posX / rapport;
    pos.y = posY / rapport;
    return { pos };
}

#endif
