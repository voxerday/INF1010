#include "Librairie.h"
#include "GestionnaireAuteurs.h"

// To do
Librairie::Librairie(const Librairie& librairie)
    :medias_()
{
    // To do
    //std::vector<std::unique_ptr<Media>> medias_
    *this = librairie;
}

// To do
Librairie& Librairie::operator=(const Librairie& librairie)
{
    // To do
    medias_.reserve(librairie.medias_.size());

    for (const auto& e : librairie.medias_)
        medias_.push_back(std::make_unique<Media>(*e));
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

// To do
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    // To do
    for (auto& m : medias_)
    {
        if (m->getNom() == nomFilm)
        {
            return (Film*)&m;
        }
    }
    return nullptr;
}

// To do
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    // To do
    for (auto& s : medias_)
    {
        if (s->getNom() == nomSerie)
        {
            return (Serie*)&s;
        }
    }
    return nullptr;
}

// To do
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    // To do
    Serie* serie = chercherSerie(nomSerie);
    serie->operator+= *saison;
}

// To do
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    // To do
    Serie* serie = chercherSerie(nomSerie);
    serie->operator-= *numSaison;
}

// To do
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
    // To do
    Serie* serie = chercherSerie(nomSerie);
    serie->ajouterEpisode(numSaison, std::move(episode));
}


void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
    // To do
    Serie* serie = chercherSerie(nomSerie);
    serie->retirerEpisode(numSaison, numEpisode);
}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneMedia(ligne, gestionnaireAuteurs))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
        << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

// To do
size_t Librairie::getNbMedias() const
{
    // To do
    return medias_.size();
}

// To do
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    // To do
    for (auto& media : librairie.medias_)
    {
        os << media << std::endl;
    }
}

// To do
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    // To do
    for (size_t i = 0; i < getNbMedias(); i++) 
    {
        if (medias_[i]->getNom() == nomMedia)
        {
            return i;
        }
    }
    return size_t(-1);
}

// To do
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    // To do
    medias_.push_back(media);
}

// To do
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    // To do
    medias_.erase(medias_.begin() + trouverIndexMedia(nomMedia));
}

// To do
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    // To do
    if (typeMedia == Media::TypeMedia::Film)
    {
        return (Media*)chercherFilm(nomMedia);
    }
    else
    {
        return (Media*)chercherSerie(nomMedia);
    }
}

// To do
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    // To do
    std::istringstream stream(ligne);
    int type;
    std::string nomMedia;
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream >> type >> std::quoted(nomMedia))
    {
        
        Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(type));
        if (media == nullptr)
        {
            // Film n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

// To do
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

// To do
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    // To do
    return medias_;
}

// To do
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    // To do
    std::string auteur, nom;
    int annee, genreVal, paysVal;
    bool restriction;
    is >> std::quoted(auteur) >> std::quoted(nom) >> annee >> genreVal >> paysVal >> restriction;
    Auteur* dude = GestionnaireAuteurs::chercherAuteur(auteur);
    Media();
}

// To do
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    // To do
}

// To do
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
}

// To do
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
}

// To do
size_t Librairie::getNbFilms() const
{
    // To do
}

// To do
size_t Librairie::getNbSeries() const
{
    // To do
}

// To do
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
    // To do
}

// To do
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
    // To do
}
