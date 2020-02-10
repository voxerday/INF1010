#include "Film.h"
#include <iostream>
#include "Pays.h"
#include "typesafe_enum.h"
#include <vector>

namespace
{
    constexpr std::size_t CAPACITE_PAYS_INITIALE = 2;

    //! Fonction qui convertit le enum Film::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Film::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Pays>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

//! Constructeur de la classe Film
//! \param nom                  Nom du film
//! \param anneeDeSortie        Année de sortie du film
//! \param genre                Le genre du film
//! \param pays                 Le pays d'origine du film
//! \param estRestreintParAge   Bool qui représente si le film est interdit aux moins de 16 ans
//! \param auteur               Pointeur vers l'auteur du film
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur)
    : nom_(nom)
    , anneeDeSortie_(anneeDeSortie)
    , genre_(genre)
    , pays_(pays)
    , estRestreintParAge_(estRestreintParAge)
    , auteur_(auteur)
    , paysRestreints_(std::vector<Pays>(0))
{
}

Film::~Film()
{
    auteur_->setNbFilms(auteur_->getNbFilms() - 1); 
}

//! Méthode qui ajoute un pays à liste des pays restreints du film
//! \param pays Pays à ajouter à la liste
void Film::ajouterPaysRestreint(Pays pays)
{
    paysRestreints_.push_back(pays);
}

//! Méthode qui supprime les pays restreints
void Film::supprimerPaysRestreints()
{
    paysRestreints_.clear();
}

//! Méthode qui retourne si un pays est dans la liste des pays restreints du film
//! \param pays Le pays à chercher dans la liste des pays restreints
//! \return     Un bool représentant si le pays se trouve dans la liste des pays restreints
bool Film::estRestreintDansPays(Pays pays) const
{
    for (auto& p : paysRestreints_)
    {
        if (p == pays)
        {
            return true;
        }
    }
    return false;
}

//! Méthode qui affiche le film
//! \param stream Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& stream, const Film& film)
{
    // Ne modifiez pas cette fonction
    stream << film.nom_ << "\n\tDate de sortie: " << film.anneeDeSortie_
           << "\n\tGenre: " << getGenreString(film.genre_) << "\n\tAuteur: " << film.auteur_->getNom()
           << "\n\tPays: " << getPaysString(film.pays_)
           << (film.paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < film.paysRestreints_.size(); i++)
    {
        stream << "\n\t\t" << getPaysString(film.paysRestreints_[i]);
    }
    return stream << '\n';
}

// Méthode qui retourne le genre du film
// \return Le genre du film
Film::Genre Film::getGenre() const
{
    return genre_;
}

// Méthode qui retourne si le film est restreint aux moins de 16 ans
// \return Un bool représentant si le film est restreint aux moins de 16 ans
bool Film::estRestreintParAge() const
{
    return estRestreintParAge_;
}

// Méthode qui retourne le nom du film
// \return Le nom du film
const std::string& Film::getNom() const
{
    return nom_;
}

// Méthode qui retourne l'auteur
// \return L'auteur du film
Auteur* Film::getAuteur()
{
    return auteur_;
}
