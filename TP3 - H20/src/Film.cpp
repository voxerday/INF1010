// To do
#include "Film.h"
#include "Auteur.h"
#include "Media.h"
// To do
Film::Film(Auteur* auteur)
// To do
    : Media(auteur, Media::TypeMedia::Film),
    duree_()
{
}

// To do
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree)
    // To do
    :Media(nom, anneeDeSortie, genre, pays,
        estRestreintParAge, auteur, Media::TypeMedia::Film),
    duree_(duree)
{
}

// To do
std::ostream& Film::afficher(std::ostream& os) const
{
    // To do
    os << duree_;
}

// To do
std::istream& Film::lire(std::istream& is)
{
    // To do
    std::string duree;
    is >> std::quoted(duree);
    duree_ = duree;
}

// To do
std::unique_ptr<Media> Film::clone() const
{
    // To do
    return std::make_unique<Media>(this);
}
