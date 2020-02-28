// To do
#include "Serie.h"

// To do              Pointeur vers l'auteur du serie
Serie::Serie(Auteur* auteur)
    // To do
    : Media(auteur, Media::TypeMedia::Serie)
{
}

// To do
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur)
    // To do
    : Media(nom, anneeDeSortie, genre, pays,
        estRestreintParAge, auteur, Media::TypeMedia::Serie)
{
}

// To do
Serie::Serie(const Serie& serie)
    // To do
    : Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_,
        serie.estRestreintParAge_, serie.auteur_, Media::TypeMedia::Serie)
{
    saisons_.reserve(serie.saisons_.size());

        for (const auto& e : serie.saisons_)
            saisons_.push_back(std::make_unique<Saison>(*e));
}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
    // To do
    for (auto& s : saisons_)
    {
        os << s;
    }
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    // To do//Type Serie if doesn't work *this
    return std::make_unique<Media>(this);
}