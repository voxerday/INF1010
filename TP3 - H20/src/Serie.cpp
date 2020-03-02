// To do
#include "Serie.h"

//! Constructeur de la classe Serie
//! \param auteur              Pointeur vers l'auteur
Serie::Serie(Auteur* auteur)
    // To do
    : Media(auteur, Media::TypeMedia::Serie)
{
}

//! Constructeur de la classe Serie
//! \param nom                 Nom de la serie
//! \param anneeDeSortie       Annee de sortie
//! \param genre               Genre
//! \param pays                Pays
//! \param estRestreintParAge  Si le film est restreint par age
//! \param auteur              Pointeur vers l'auteur
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur)
    : Media(nom, anneeDeSortie, genre, pays,
        estRestreintParAge, auteur, Media::TypeMedia::Serie)
{
}

//! Constructeur par copie de la classe Serie
//! \param serie                 serie a copier
Serie::Serie(const Serie& serie)
    : Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_,
        serie.estRestreintParAge_, serie.auteur_, Media::TypeMedia::Serie)
{
    saisons_.reserve(serie.saisons_.size());

        for (const auto& e : serie.saisons_)
            saisons_.push_back(std::make_unique<Saison>(*e));
}

//! Operateur qui affiche la serie.
//! \param os                   Le stream dans lequel afficher
//! \return                     Le stream dans lequel afficher
std::ostream& Serie::afficher(std::ostream& os) const
{
    for (auto&& s : saisons_)
    {
        os << *s;
    }
    return os;
}

//! Methode qui copie un pointeur serie
//! \return Le pointeur de serie
std::unique_ptr<Media> Serie::clone() const
{
    // To do//Type Serie if doesn't work *this
    return std::make_unique<Serie>(*this); //return std::make_unique<Media>(this);
}