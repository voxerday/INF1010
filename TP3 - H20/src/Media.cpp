#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
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

// To do
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia)
// To do
    :nom_(),
    anneeDeSortie_(),
    genre_(),
    pays_(),
    estRestreintParAge_(),
    auteur_(auteur),
    typeMedia_(typeMedia),
    paysRestreints_(std::vector<Pays>(0))
{
}

// To do
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia)
    // To do
    :nom_(nom),
    genre_(genre),
    pays_(pays),
    estRestreintParAge_(estRestreintParAge),
    auteur_(auteur),
    typeMedia_(typeMedia),
    paysRestreints_(std::vector<Pays>(0))
{
}

// To do
Media::Media(const Media& serie)
{
    // To do
    nom_ = serie.nom_;
    anneeDeSortie_ = serie.anneeDeSortie_;
    genre_ = serie.genre_;
    pays_ = serie.pays_;
    estRestreintParAge_ = serie.estRestreintParAge;
    auteur_ = serie.auteur_;
    typeMedia_ = serie.typeMedia_;
    paysRestreints_ = serie.paysRestreints_;
}


// To do
Media::~Media()
{
    // To do
    auteur_->setNbMedias(auteur_->getNbMedias() - 1);
    supprimerPaysRestreints();
}

// To do
void Media::ajouterPaysRestreint(Pays pays)
{
    // To do
    paysRestreints_.push_back(pays);
}

// To do
void Media::supprimerPaysRestreints()
{
    // To do
    paysRestreints_.clear();
}

// To do
bool Media::estRestreintDansPays(Pays pays) const
{
    // To do
    for (auto& p : paysRestreints_) {
        if (p == pays) { return true; }
    }
    return false;
}

// To do
bool Media::estRestreintParAge() const
{
    // To do
    return estRestreintParAge_;
}

// To do
std::ostream& Media::afficher(std::ostream& os) const
{
    // To do
    /*const std::string filmStringAttendu =
        "FilmTestDatedesortie:2019Genre:ActionAuteur:AuteurTestPays:EtatsUnisAucunpaysrestreint."
        "Durée:00:00:00";*/
    /*const std::string serieStringAttendu =
        "SerieTestDatedesortie:2019Genre:ActionAuteur:AuteurTestPays:EtatsUnisAucunpaysrestreint."
        "Saison01:2/20(Encours)"
        "Episode01:Episode:01|Durée:00:00:00"
        "Episode03:Episode:03|Durée:00:00:00"
        "Saison02:0/20(Encours)"
        "SerieTestDatedesortie:2019Genre:ActionAuteur:AuteurTestPays:EtatsUnisAucunpaysrestreint."
        "Saison01:2/20(Encours)"
        "Episode01:Episode:01|Durée:00:00:00"
        "Episode04:Episode:04|Durée:00:00:00"
        "Saison02:1/20(Encours)"
        "Episode05:Episode:05|Durée:00:00:00"
        "SerieTestDatedesortie:2019Genre:ActionAuteur:AuteurTestPays:EtatsUnisAucunpaysrestreint."
        "Saison01:2/20(Encours)"
        "Episode01:Episode:01|Durée:00:00:00"
        "Episode04:Episode:04|Durée:00:00:00";*/

    os << nom_ << 
        "Datedesortie:" << anneeDeSortie_ <<
        "Genre:" << getGenreString(genre_) <<
        "Auteur:" << auteur_ <<
        "Pays:" << getPaysString(pays_) <<
        (paysRestreints_.size() == 0 ? "Aucun pays restreint." : "Pays restreints:");

    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        os << "\n\t\t" << getPaysString(paysRestreints_[i]);
    }
    return os << std::endl;

}

// To do
std::ostream& operator<<(std::ostream& os, const Media& media)
{
    // To do
    if ((media).getTypeMedia() == Media::TypeMedia::Film)
    {
        (Film*)&media.afficher(os);
    }
    else if ((media).getTypeMedia() == Media::TypeMedia::Serie) 
    {
        (Serie*)&media.afficher(os);
    }
}

// To do
Media::Genre Media::getGenre() const
{
    // To do
    return genre_;
}

// To do
const std::string& Media::getNom() const
{
    // To do
    return nom_;
}

// To do
Media::TypeMedia Media::getTypeMedia() const
{
    // To do
    return typeMedia_;
}

// To do
std::istream& Media::lire(std::istream& is)
{
    // To do
    //"\"Film Test\" 2019 0 3 0 \"00:00:00\""
    //"FilmTestDatedesortie:2019Genre:ActionAuteur:AuteurTestPays:EtatsUnisAucunpaysrestreint."
    //"Durée:00:00:00";
    std::string nom;
    unsigned int anneeDeSortie;
    int genreVal;
    int paysVal;
    bool estRestreintParAge;

    if (is >> std::quoted(nom) >> anneeDeSortie >> genreVal >> paysVal >> estRestreintParAge)
    {
        Genre genre = to_enum<Genre>(genreVal);
        Pays pays = to_enum<Pays>(paysVal);
        nom_ = nom;
        anneeDeSortie_ = anneeDeSortie;
        genre_ = genre;
        pays_ = pays;
        estRestreintParAge_ = estRestreintParAge;
        if (*this->getTypeMedia == Media::TypeMedia::Film)
        {
            (Film*)&this->lire(is);
        }
        else if (*this->getTypeMedia == Media::TypeMedia::Serie)
        {
            (Serie*)&this->lire(is);
        }
    }
    
}

// To do
std::istream& operator>>(std::istream& is, Media& media)
{
    // To do
    media.lire(is);
}

// To do
std::unique_ptr<Media> Media::clone() const
{
    // To do
    return std::make_unique<Media>(*this);
}