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

//! Constructeur de la classe Media
//! \param auteur              Pointeur vers l'auteur
//! \param typeMedia           Le type du media
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia)
    : auteur_(auteur)
    , typeMedia_(typeMedia)
    , paysRestreints_({})
{
}

//! Constructeur de la classe Media
//! \param nom                 Nom du Media
//! \param anneeDeSortie       Annee de sortie
//! \param genre               Genre
//! \param pays                Pays
//! \param estRestreintParAge  Si le Media est restreint par age
//! \param auteur              Pointeur vers l'auteur
//! \param typeMedia           Le type du media
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia)
    :nom_(nom),
    anneeDeSortie_(anneeDeSortie),
    genre_(genre),
    pays_(pays),
    estRestreintParAge_(estRestreintParAge),
    auteur_(auteur),
    typeMedia_(typeMedia),
    paysRestreints_({})
{
}

//! Constructeur par copie de la classe Media
//! \param serie                 media a copier
Media::Media(const Media& serie)
    : nom_(serie.nom_),
    anneeDeSortie_(serie.anneeDeSortie_),
    genre_(serie.genre_),
    pays_(serie.pays_),
    estRestreintParAge_(serie.estRestreintParAge_),
    auteur_(serie.auteur_),
    typeMedia_(serie.typeMedia_)
{
    supprimerPaysRestreints();

    for (unsigned int i = 0; i < serie.paysRestreints_.size(); i++) {
        ajouterPaysRestreint(serie.paysRestreints_[i]);
    }
}


//! Destructeur de la classe Media
Media::~Media()
{
    paysRestreints_.clear();
}

//! Methode qui ajoute un pays  a la liste des pays restreint
//! \param pays Le pays restreint
void Media::ajouterPaysRestreint(Pays pays)
{
    // To do
    paysRestreints_.push_back(pays);
}

//! Methode qui vide le vecteur de peays restreint
void Media::supprimerPaysRestreints()
{
    paysRestreints_.clear();
}

//! Methode qui retourne un bool si le film est restreint dans le pays
//! \param pays Le pays a verifier
//! \return     un bool si le film est restreint dans le pays
bool Media::estRestreintDansPays(Pays pays) const
{
    // To do
    for (auto& p : paysRestreints_) {
        if (p == pays) { return true; }
    }
    return false;
}

//! Methode qui retourne un bool si le film est restreint par l'age
//! \return un bool si le film est restreint par l'age
bool Media::estRestreintParAge() const
{
    return estRestreintParAge_;
}

//! Methode qui affiche un media.
//! \param os                   Le stream dans lequel afficher
//! \return                     Le stream dans lequel afficher
std::ostream& Media::afficher(std::ostream& os) const
{
    return os << *this;
}

//! Operateur qui affiche un media.
//! \param os                   Le stream dans lequel afficher
//! \param media                Le media a afficher
//! \return                     Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& os, const Media& media)
{

    os << media.nom_ << "\n\tDate de sortie: " << media.anneeDeSortie_
        << "\n\tGenre: " << getGenreString(media.genre_) << "\n\tAuteur: " << media.auteur_->getNom()
        << "\n\tPays: " << getPaysString(media.pays_)
        << (media.paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < media.paysRestreints_.size(); i++)
    {
        os << "\n\t\t" << getPaysString(media.paysRestreints_[i]);
    }
    os << '\n';
    media.afficher(os);
    return os;
}

//! Methode qui retourne l'auteur
//! \return auteur_
Auteur* Media::getAuteur() const
{
    return auteur_;
}

//! Methode qui retourne le genre
//! \return genre_
Media::Genre Media::getGenre() const
{
    return genre_;
}

//! Methode qui retourne le nom
//! \return nom_
const std::string& Media::getNom() const
{
    return nom_;
}

//! Methode qui retourne le type de media
//! \return typeMedia_
Media::TypeMedia Media::getTypeMedia() const
{
    return typeMedia_;
}

//! Methode qui affecte un media depuis un stream
//! \param is   le stream avec les infos du media
//! \return     le stream
std::istream& Media::lire(std::istream& is)
{
    return is;
}

//! Operateur qui affecte un media depuis un stream
//! \param is       le stream avec les infos du media
//! \param media    le media a affecter
//! \return         le stream
std::istream& operator>>(std::istream& is, Media& media)
{
    std::string nom;
    unsigned int anneeDeSortie;
    int genre, pays;
    bool estRestreintParAge;
    if (is >> std::quoted(nom) >> anneeDeSortie >> genre >> pays >> estRestreintParAge)
    {
        media.nom_ = nom;
        media.anneeDeSortie_ = anneeDeSortie;
        media.genre_ = to_enum<Media::Genre>(genre);
        media.pays_ = to_enum<Pays>(pays);
        media.estRestreintParAge_ = estRestreintParAge;
    }
    media.lire(is);
    return is;
}

//! Methode qui copie un pointeur Media
//! \return Le pointeur de media
std::unique_ptr<Media> Media::clone() const
{
    return std::make_unique<Media>(*this);
}