// To do
#include "GestionnaireSaisons.h"


// To do
GestionnaireSaisons::~GestionnaireSaisons()
{
    // To do
    saisons_.clear();
}

// To do
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
    // To do
    unsigned int num = saison->getNumSaison();
    if (trouverIndexSaison(num) != SAISON_INEXSISTANTE) { *this -= num; }
    saisons_.push_back(saison);
    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
}

// To do
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
    // To do
    saisons_.erase(saisons_.begin() + trouverIndexSaison(numSaison));
}

// To do
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    // To do 
    *saisons_[trouverIndexSaison(numSaison)] += std::move(episode);
}

// To do
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    // To do
    *saisons_[trouverIndexSaison(numSaison)] -= numEpisode;
}

/// To do
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    // To do
    for (size_t i; i < getNbSaisons(); i++) {
        if (*saisons_[i] == numSaison) { return i; }
    }
    return SAISON_INEXSISTANTE;
}

// To do
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
    // To do
    return (Saison*)&saisons_[trouverIndexSaison(numSaison)];
}

// To do
size_t GestionnaireSaisons::getNbSaisons() const
{
    // To do
    return saisons_.size();
}
