/// Gestionnaire de films.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include "GestionnaireFilms.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Foncteurs.h"
#include "RawPointerBackInserter.h"

/// Constructeur par copie.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
GestionnaireFilms::GestionnaireFilms(const GestionnaireFilms& other)
{
    films_.reserve(other.films_.size());
    filtreNomFilms_.reserve(other.filtreNomFilms_.size());
    filtreGenreFilms_.reserve(other.filtreGenreFilms_.size());
    filtrePaysFilms_.reserve(other.filtrePaysFilms_.size());

    for (const auto& film : other.films_)
    {
        ajouterFilm(*film);
    }
}

/// Opérateur d'assignation par copie utilisant le copy-and-swap idiom.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
/// \return         Référence à l'objet actuel.
GestionnaireFilms& GestionnaireFilms::operator=(GestionnaireFilms other)
{
    std::swap(films_, other.films_);
    std::swap(filtreNomFilms_, other.filtreNomFilms_);
    std::swap(filtreGenreFilms_, other.filtreGenreFilms_);
    std::swap(filtrePaysFilms_, other.filtrePaysFilms_);
    return *this;
}

/// Affiche les informations des films gérés par le gestionnaire de films à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des films.
/// \param gestionnaireFilms    Le gestionnaire de films à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireFilms& gestionnaireFilms)
{
    outputStream << "Le gestionnaire de films contient " << gestionnaireFilms.getNombreFilms() << " films.\n"
        << "Affichage par catégories:\n";

    for (std::pair<Film::Genre, std::vector<const Film*>> filtreGenre : gestionnaireFilms.filtreGenreFilms_)
    {
        outputStream << "Genre: " << getGenreString(filtreGenre.first) << " (" << filtreGenre.second.size() << " films):\n";
        for (const Film* film : filtreGenre.second)
        {
            outputStream << '\t' << *film << '\n';
        }
    }
    return outputStream;
}

/// Ajoute les films à partir d'un fichier de description des films.
/// \param nomFichier   Le fichier à partir duquel lire les informations des films.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireFilms::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        films_.clear();
        filtreNomFilms_.clear();
        filtreGenreFilms_.clear();
        filtrePaysFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string nom;
            int genre;
            int pays;
            std::string realisateur;
            int annee;

            if (stream >> std::quoted(nom) >> genre >> pays >> std::quoted(realisateur) >> annee)
            {
                ajouterFilm(Film{nom, static_cast<Film::Genre>(genre), static_cast<Pays>(pays), realisateur, annee});
            }
            else
            {
                std::cerr << "Erreur GestionnaireFilms: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur GestionnaireFilms: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/// Ajoute un film au gestionnaire et met à jour les filtres en conséquence.
/// \param film         Le film a ajouter au gestionnaire.
/// \return             True si le  filma  été  ajouté  avec  succès, false sinon.
bool GestionnaireFilms::ajouterFilm(const Film& film)
{
    if (getFilmParNom(film.nom) == nullptr)
    {
        films_.push_back(std::make_unique<Film>(film));
        const Film* filmPtr = films_.back().get();
        filtreGenreFilms_[film.genre].push_back(filmPtr);
        filtrePaysFilms_[film.pays].push_back(filmPtr);
        return filtreNomFilms_.emplace(film.nom, filmPtr).second;
    }
    return false;
}

/// Supprime un filmdu gestionnaire à partir de son nom.
/// \param nomFilm      Le fichier à partir duquel lire les informations des films.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireFilms::supprimerFilm(const std::string& nomFilm)
{
    const Film* film = getFilmParNom(nomFilm);
    if (film != nullptr)
    {
        filtreGenreFilms_[film->genre].erase(std::remove(filtreGenreFilms_[film->genre].begin(), filtreGenreFilms_[film->genre].end(), film),
            filtreGenreFilms_[film->genre].end());
        filtrePaysFilms_[film->pays].erase(std::remove(filtrePaysFilms_[film->pays].begin(), filtrePaysFilms_[film->pays].end(), film),
            filtrePaysFilms_[film->pays].end());
        films_.erase(std::remove_if(films_.begin(), films_.end(), [nomFilm](std::unique_ptr<Film>& film) {return film->nom == nomFilm; }),
            films_.end());
        return filtreNomFilms_.erase(nomFilm);
    }
    return false;
}

/// Retourne le nombre de films présentement dans le gestionnaire.
/// \return             La grosseur de la map filtreNomFilms_.
std::size_t GestionnaireFilms::getNombreFilms() const
{
    return filtreNomFilms_.size();
}

/// Trouve et retourne un film en le cherchant à partir de son nom.
/// \param nom          Le nom du film a trouver.
/// \return             Un pointeur vers le film trouve, nullptr si non trouve.
const Film* GestionnaireFilms::getFilmParNom(const std::string& nom) const
{
    return filtreNomFilms_.find(nom) != filtreNomFilms_.end() ? (filtreNomFilms_.find(nom)->second) : nullptr;
}

/// Retourne une copie de la liste des films appartenant à un genre donné.
/// \param genre        Le genre des films a retourner.
/// \return             Un vecteur de pointeur vers les film trouve, vecteur vide si aucun film du genre.
std::vector<const Film*> GestionnaireFilms::getFilmsParGenre(Film::Genre genre) const
{
    return filtreGenreFilms_.find(genre) != filtreGenreFilms_.end() ? (filtreGenreFilms_.find(genre)->second) : std::vector<const Film*>();
}

/// Retourne une copie de la liste des films appartenant à un pays donné.
/// \param genre        Le pays des films a retourner.
/// \return             Un vecteur de pointeur vers les film trouve, vecteur vide si aucun film du pays.
std::vector<const Film*> GestionnaireFilms::getFilmsParPays(Pays pays) const
{
    return filtrePaysFilms_.find(pays) != filtrePaysFilms_.end() ? (filtrePaysFilms_.find(pays)->second) : std::vector<const Film*>();
}

/// Retourne une copie de la liste des films appartenant entre deux annees donné.
/// \param anneeDebut   L'annee de la borne inferieure de l'intervalle de recherche.
/// \param anneeFin     L'annee de la borne superieure de l'intervalle de recherche.
/// \return             Un vecteur de pointeur vers les film dans l'intervalle, vecteur vide si aucun film.
std::vector<const Film*> GestionnaireFilms::getFilmsEntreAnnees(int anneeDebut, int anneeFin)
{
    std::vector<const Film*> vecFilms;
    std::for_each(films_.begin(), films_.end(), [&](std::unique_ptr<Film>& film) {if (EstDansIntervalleDatesFilm(anneeDebut, anneeFin).operator()(film)) RawPointerBackInserter<std::vector<const Film*>>(vecFilms).operator=(film); });
    return vecFilms;
}