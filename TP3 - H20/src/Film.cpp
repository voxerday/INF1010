// To do
#include "Film.h"

//! Constructeur de la classe Film
//! \param auteur              Pointeur vers l'auteur
Film::Film(Auteur* auteur)
    : Media(auteur, Media::TypeMedia::Film),
    duree_("00:00:00")
{
}

//! Constructeur de la classe Film
//! \param nom                 Nom du film
//! \param anneeDeSortie       Annee de sortie
//! \param genre               Genre
//! \param pays                Pays
//! \param estRestreintParAge  Si le film est restreint par age
//! \param auteur              Pointeur vers l'auteur
//! \param duree               Duree du film
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree)
    :Media(nom, anneeDeSortie, genre, pays,
        estRestreintParAge, auteur, Media::TypeMedia::Film),
    duree_(duree)
{
}

//! Methode qui affiche un film
//! \param os Le stream dans lequel afficher
//! \return   Le stream dans lequel afficher
std::ostream& Film::afficher(std::ostream& os) const
{
    os << "Durée:" << duree_;
    return os;
}

//! Methode qui affecte un film
//! \param is Le stream avec les infos (duree)
//! \return   Le stream avec les infos
std::istream& Film::lire(std::istream& is)
{
    // To do
    std::string duree;
    is >> std::quoted(duree);
    duree_ = duree;
    return is;
}

//! Methode qui copie un pointeur Film
//! \return Le pointeur de film
std::unique_ptr<Media> Film::clone() const
{
    return std::make_unique<Film>(*this);
}
