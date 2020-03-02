// To do
#include "GestionnaireSaisons.h"


//! Destructeur de la classe GestionnaireSaisons
GestionnaireSaisons::~GestionnaireSaisons()
{
    saisons_.clear();
}

//! Operateur qui ajoute une saison.
//! \param saison               La saison a ajouter
//! \return                     Le GestionnaireSaisons
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
    if (trouverIndexSaison(saison->getNumSaison()) == SAISON_INEXSISTANTE)
    {
        saisons_.push_back(std::move(saison));
    }
    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
    return *this;
}

//! Operateur qui retire une saison.
//! \param numSaison            Le numero de la saison a retirer
//! \return                     Le GestionnaireSaisons
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
    size_t indexSaison = trouverIndexSaison(numSaison);

    if (indexSaison != SAISON_INEXSISTANTE) {
        saisons_.erase(saisons_.begin() + indexSaison);
    }

    return *this;
}

//! Methode qui ajoute un episode.
//! \param numSaison            Le numero de la saison de l'episode a ajouter
//! \param episode              L'episode a ajouter
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    if (trouverIndexSaison(numSaison) != SAISON_INEXSISTANTE)
    {
        *(saisons_[trouverIndexSaison(numSaison)]) += std::move(episode);
    }
}

//! Methode qui retire un episode.
//! \param numSaison            Le numero de la saison de l'episode a retirer
//! \param numEpisode           Le numero de l'episode a retirer
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    if (trouverIndexSaison(numSaison) != SAISON_INEXSISTANTE)
    {
        *(saisons_[trouverIndexSaison(numSaison)]) -= numEpisode;
    }
}

//! Methode qui cherche l'index de la saison.
//! \param numSaison        Le numero de la saison a chercher
//! \return                 L'index de la saison
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    for (size_t i = 0; i < saisons_.size(); i++)
    {
        if (saisons_[i]->getNumSaison() == numSaison)
            return i;
    }
    return SAISON_INEXSISTANTE;
}

//! Methode qui cherche une saison.
//! \param numSaison        Le numero de la saison a chercher
//! \return                 Le pointeur vers la saison (nullptr si non trouve)
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
    size_t i = trouverIndexSaison(numSaison);
    if (i != SAISON_INEXSISTANTE)
    {
        return saisons_[i].get();
    }
    return nullptr;
}

//! Methode qui retourne le nombre de saisons.
//! \return                 La grosseur du vecteur saisons_
size_t GestionnaireSaisons::getNbSaisons() const
{
    return saisons_.size();
}
