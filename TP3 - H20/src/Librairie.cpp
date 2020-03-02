#include "Librairie.h"

//! Constructeur par copie de la classe Librairie
//! \param librairie        librairie a copier
Librairie::Librairie(const Librairie& librairie)
    :medias_()
{
    *this = librairie;
}

//! Operateur qui copie une librairie.
//! \param librairie            Librairie a copier.
//! \return                     La copie de la librairie.
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (&librairie != this)
    {
        medias_.clear();
        for (auto& media:librairie.medias_) {
            medias_.push_back(media->clone());
        }
    }
    return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

//! Méthode qui cherche un film.
//! \param nomFilm             nom du film a trouver.
//! \return                     un pointeur vers le film(nullptr si non trouvee).
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    if (chercherMedia(nomFilm, Media::TypeMedia::Film) == nullptr) { return nullptr; }
    return dynamic_cast<Film*>(chercherMedia(nomFilm, Media::TypeMedia::Film));
}

//! Méthode qui cherche une serie.
//! \param nomSerie             nom de la serie a trouver.
//! \return                     un pointeur vers la serie(nullptr si non trouvee).
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    if (chercherMedia(nomSerie, Media::TypeMedia::Serie) == nullptr) { return nullptr; }
    return dynamic_cast<Serie*>(chercherMedia(nomSerie, Media::TypeMedia::Serie));
}

//! Méthode qui retire une saison.
//! \param nomSerie             Serie de la saison.
//! \param saison               Pointeur vers la saison.
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    int i = trouverIndexMedia(nomSerie);
    if (i != MEDIA_INEXSISTANT)
    {
        if (medias_[i]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[i]).get())->GestionnaireSaisons::operator+=(std::move(saison));
        }
    }
}

//! Méthode qui retire une saison.
//! \param nomSerie             Serie de la saison.
//! \param numSaison            Numero de la saison.
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    int i = trouverIndexMedia(nomSerie);
    if (i != MEDIA_INEXSISTANT)
    {
        if (medias_[i]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[i]).get())->GestionnaireSaisons::operator-=(numSaison);
        }
    }
}

//! Méthode qui ajoute un episode.
//! \param nomSerie             Serie de l'episode.
//! \param numSaison            Saison de l'episode.
//! \param episode              Pointeur vers l'episode.
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
    int i = trouverIndexMedia(nomSerie);
    if (i != MEDIA_INEXSISTANT)
    {
        if (medias_[i]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[i]).get())->GestionnaireSaisons::ajouterEpisode(numSaison, std::move(episode));
        }
    }
}

//! Méthode qui retire un episode.
//! \param nomSerie             Serie de l'episode.
//! \param numSaison            Saison de l'episode.
//! \param numEpisode           Numero de l'episode.
void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
    int i = trouverIndexMedia(nomSerie);
    if (i != MEDIA_INEXSISTANT)
    {
        if (medias_[i]->Media::getTypeMedia() == Media::TypeMedia::Serie)
        {
            dynamic_cast<Serie*>((medias_[i]).get())->GestionnaireSaisons::retirerEpisode(numSaison, numEpisode);
        }
    }
}

//! Methode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
        {
            Auteur* ok = medias_[i]->getAuteur();
            ok->setNbMedias(ok->getNbMedias() - 1);
        }

        medias_.clear();

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

//! Methode qui charge les restrictions des series à partir d'un fichier.
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

//! Methode qui retourne le nombre de medias.
//! \return                     la grosseur du vecteur medias_.
size_t Librairie::getNbMedias() const
{
    return medias_.size();
}

//! Operateur qui affiche la librairie.
//! \param os                   Le stream dans lequel afficher
//! \param librairie            La librairie a afficher
//! \return                     Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    for (auto& media:librairie.medias_) 
    {
        if (media->getTypeMedia() == Media::TypeMedia::Film) { os << *(media) << std::endl; }
    }
    for (auto& media : librairie.medias_)
    {
        if (media->getTypeMedia() == Media::TypeMedia::Serie) { os << *(media) << std::endl; }
    }
    return os;
}

//! Methode qui cherche l'index du media.
//! \param nomMedia         Le nom du media a chercher
//! \return                 L'index du media
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    for (size_t i = 0; i < getNbMedias(); i++) 
    {
        if (medias_[i]->getNom() == nomMedia) { return i; }
    }
    return MEDIA_INEXSISTANT;
}

//! Operateur qui ajoute un media.
//! \param media                Le media a ajouter
//! \return                     La librairie
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    if (media != nullptr)
    {
        medias_.push_back(std::move(media));
    }
    return *this;
}

//! Operateur qui retire un media.
//! \param nomMedia             Le nom du media a retirer
//! \return                     La librairie
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    int indexMedia = trouverIndexMedia(nomMedia);
    if (indexMedia == MEDIA_INEXSISTANT)
    {
        return *this;
    }

    medias_[indexMedia] = std::move(medias_[medias_.size() - 1]);
    medias_.pop_back();
    return *this;
}

//! Methode qui cherche un media selon son type.
//! \param nomMedia         Le nom du media a chercher
//! \param typeMedia        le type du media a chercher
//! \return                 Le pointeur vers le media (nullptr si non trouve)
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    int i = trouverIndexMedia(nomMedia);
    if ((i == MEDIA_INEXSISTANT) || (medias_[i]->getTypeMedia() != typeMedia))
    {
        return nullptr;
    }
    return medias_[i].get();
}

//! Methode qui lit les pays restreint d'un media.
//! \param ligne         Un stream avec les infos sur le media
//! \return              Un bool selon le succes de l'operation
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomMedia;
    int mediaValeurEnum;
    stream >> mediaValeurEnum;
    if (stream >> std::quoted(nomMedia))
    {
        Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(mediaValeurEnum));

        if (media == nullptr)
        {
            // Media n'existe pas
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

//! Methode qui lit les pays restreint d'un media.
//! \param ligne                  Un stream avec les infos sur le media
//! \param gestionnaireAuteurs    Les auteurs
//! \return                       Un bool selon le succes de l'operation
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

//! Methode qui retourne les medias de la librairie.
//! \return                 medias_
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    return medias_;
}

//! Methode qui lit les infos d'un film.
//! \param is                     Un stream avec les infos sur le media
//! \param gestionnaireAuteurs    Les auteurs
//! \return                       Un bool selon le succes de l'operation
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;
    if (is >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        Film film = Film(auteur);

        if (is >> film)
        {

            *this += std::make_unique<Film>(film);
            auteur->setNbMedias((auteur->getNbMedias()) + 1);
            return true;
        }
        return false;
    }
    return false;
    
}

//! Methode qui lit les infos d'une serie.
//! \param is                     Un stream avec les infos sur le media
//! \param gestionnaireAuteurs    Les auteurs
//! \return                       Un bool selon le succes de l'operation
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;
    if (is >> std::quoted(nomAuteur))
    {
        Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
        if (auteur == nullptr)
        {
            // Auteur non existant
            return false;
        }
        Serie serie = Serie(auteur);
        if (is >> serie)
        {
            auteur->setNbMedias(auteur->getNbMedias() + 1);
            *this += std::make_unique<Serie>(serie);
            return true;
        }
        return false;
    }
    return false;
}

//! Methode qui lit les infos d'une saison.
//! \param is                     Un stream avec les infos sur le media
//! \param gestionnaireAuteurs    Les auteurs
//! \return                       Un bool selon le succes de l'operation
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    std::string nom;
    int numero, nbEp;
    if (is >> numero >> nbEp >> std::quoted(nom))
    {
        Saison saison(numero, nbEp);
        Serie* serie = chercherSerie(nom);
        if (serie)
        {
            serie->operator+= (std::make_unique<Saison>(saison));
            return true;
        }
    }
    return false;

}

//! Methode qui lit les infos d'un episode.
//! \param is                     Un stream avec les infos sur le media
//! \param gestionnaireAuteurs    Les auteurs
//! \return                       Un bool selon le succes de l'operation
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    std::string nom, duree, nomSerie;
    int num, numSaison;
    if (is >> num >> std::quoted(nom) >> std::quoted(duree) >> std::quoted(nomSerie) >> numSaison)
    {
        Episode ep(num, nom, duree);
        Serie* serie = chercherSerie(nomSerie);
        if (serie)
        {
            serie->ajouterEpisode(numSaison, std::make_unique<Episode>(ep));
            return true;
        }
    }
    return false;
}

//! Methode qui retourne le nombre de films de la librairie.
//! \return                       le nombre de films de la librairie
size_t Librairie::getNbFilms() const
{
    size_t nbFilms = 0;
    for (auto&  media:medias_) {
        if (media->getTypeMedia() == Media::TypeMedia::Film) { nbFilms++; }
    }
    return nbFilms;
}

//! Methode qui retourne le nombre de series de la librairie.
//! \return                       le nombre de series de la librairie
size_t Librairie::getNbSeries() const
{
    size_t nbSeries = 0;
    for (auto& media : medias_) {
        if (media->getTypeMedia() == Media::TypeMedia::Serie) { nbSeries++; }
    }

    return nbSeries;
}

//! Methode qui retourne le nombre de saisons d'une serie de la librairie.
//! \param nomSerie               La serie qu'on veut l'info
//! \return                       le nombre de saisons de la librairie
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
    size_t i = trouverIndexMedia(nomSerie);
    if (i != MEDIA_INEXSISTANT)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
        {
            return dynamic_cast<Serie*>(medias_[i].get())->getNbSaisons();
        }

    }
    return 0;
}

//! Methode qui retourne le nombre de d'episodes d'une serie de la librairie.
//! \param nomSerie               La serie qu'on veut l'info
//! \return                       le nombre de d'episodes de la librairie
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
    size_t i = trouverIndexMedia(nomSerie);
    if (i != MEDIA_INEXSISTANT)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
        {
            return   dynamic_cast<Serie*>(medias_[i].get())->getSaison(numSaison)->getNbEpisodes();
        }
    }
    return 0;
}
