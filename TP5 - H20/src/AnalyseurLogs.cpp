/// Analyseur de statistiques grâce aux logs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include "AnalyseurLogs.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Foncteurs.h"

/// Ajoute les lignes de log en ordre chronologique à partir d'un fichier de logs.
/// \param nomFichier               Le fichier à partir duquel lire les logs.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout le chargement s'est effectué avec succès, false sinon.
bool AnalyseurLogs::chargerDepuisFichier(const std::string& nomFichier,
                                         GestionnaireUtilisateurs& gestionnaireUtilisateurs,
                                         GestionnaireFilms& gestionnaireFilms)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        logs_.clear();
        vuesFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string timestamp;
            std::string idUtilisateur;
            std::string nomFilm;

            if (stream >> timestamp >> idUtilisateur >> std::quoted(nomFilm))
            {
                creerLigneLog(timestamp, idUtilisateur, nomFilm, gestionnaireUtilisateurs, gestionnaireFilms);
            }
            else
            {
                std::cerr << "Erreur AnalyseurLogs: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur AnalyseurLogs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/// Cree une ligne de log depuis les parametres puis l'ajoute au log.
/// \param timestamp            Le temps de l'evenement de log.
/// \param idUtilisateur        L'id d'utilisateur qui a fait l'action.
/// \param nomFilm              Le nom du film qui a ete visione.
/// \param gUtilisateurs        Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gFilms               Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                     true si le film et l’utilisateur existaient et le log a été ajouté avec succès, false sinon.
bool AnalyseurLogs::creerLigneLog(const std::string& timestamp, const std::string& idUtilisateur, const std::string& nomFilm,
    GestionnaireUtilisateurs& gUtilisateurs, GestionnaireFilms& gFilms)
{
    if (const Film* film = gFilms.getFilmParNom(nomFilm))
    {
        if (const Utilisateur * user = gUtilisateurs.getUtilisateurParId(idUtilisateur))
        {
            ajouterLigneLog(LigneLog{ timestamp, user, film });
            return true;
        }
    }
    return false;
}

/// Ajoute  une  ligne  de  log  en  ordre  chronologique  dans  le vecteur  de  logs  tout  en mettant à jour le nombre de vues.
/// \param ligneLog               La ligne de log du film vue a ajouter.
void AnalyseurLogs::ajouterLigneLog(const LigneLog& ligneLog)
{
    ComparateurLog compLog;
    auto pos = std::upper_bound(logs_.begin(), logs_.end(), ligneLog, compLog);
    logs_.insert(pos, ligneLog);
    vuesFilms_[ligneLog.film]++;
}

/// Retourne le nombre de vues pour un film donne en parametre.
/// \param film                 Un pointeur vers le film a extraire le nombre de vue.
/// \return                     Un int avec le nombre d'entree avec le film dans le logs_.
int AnalyseurLogs::getNombreVuesFilm(const Film* film) const
{
    return std::count_if(logs_.begin(), logs_.end(), [film](LigneLog ligne) {return ligne.film == film; });
}

/// Retourne le film le plus visionne depuis vuesFilms_.
/// \return                    Le pointeur de film associe au film avecvle plus de vues.
const Film* AnalyseurLogs::getFilmPlusPopulaire() const
{   
    std::pair<const Film*, int> film = { nullptr, 0 };
    ComparateurSecondElementPaire<const Film*, int> comp;
    std::for_each(vuesFilms_.begin(), vuesFilms_.end(), [&film, comp](std::pair<const Film*, int> vue) {if (comp(film, vue)) film = vue; });
    return film.first;
}

/// Retourne  une  liste  des  films  les  plus  regardés  et  leur  nombre  de  vues  parmi  lesdonnées chargées dans l'analyseur de logs.
/// \param nombre               Le nombre de films a retourner.
/// \return                     Un vecteur de paire (pointeur vers le film, nombre de vues) des N films plus populaires.
std::vector<std::pair<const Film*, int>> AnalyseurLogs::getNFilmsPlusPopulaires(std::size_t nombre) const
{
    //Initialisation du comparateur pour la lisibilite
    ComparateurSecondElementPaire<const Film*, int> comp;
    std::vector<std::pair<const Film*, int>> filmsPop(vuesFilms_.begin(), vuesFilms_.end());
    std::sort(filmsPop.begin(), filmsPop.end(), [&](auto& left, auto& right) {return comp(right, left); });
    filmsPop.resize(std::min(nombre, filmsPop.size()));
    return filmsPop;

    /* En 4 lignes, mais illisible.
    std::vector<std::pair<const Film*, int>> filmsPop(vuesFilms_.begin(), vuesFilms_.end());
    std::sort(filmsPop.begin(), filmsPop.end(), [](auto& left, auto& right) {ComparateurSecondElementPaire<const Film*, int> comp;  return comp(right, left); });
    filmsPop.resize(std::min(nombre, filmsPop.size()));
    return filmsPop;*/
}

/// Retourne le nombre de films vues par un utilisateur.
/// \param utilisateur          L'utilisateur a extraire le nombre de films visionne.
/// \return                     Un int representant le nombre de films vus par un utilisateur .
int AnalyseurLogs::getNombreVuesPourUtilisateur(const Utilisateur* utilisateur) const
{
    return std::count_if(logs_.begin(), logs_.end(), [utilisateur](LigneLog ligne) {return ligne.utilisateur == utilisateur; });
}

/// Retourne un vecteur des films vu par un utilisateur.
/// \param utilisateur          L'utilisateur a extraire les films visionne.
/// \return                     Un vecteur des films vus par un utilisateur 
std::vector<const Film*> AnalyseurLogs::getFilmsVusParUtilisateur(const Utilisateur* utilisateur) const
{
    std::vector<const Film*> films;
    std::for_each(logs_.begin(), logs_.end(), [utilisateur, &films](LigneLog ligne) {if ((ligne.utilisateur == utilisateur) && !(std::count(films.begin(), films.end(), ligne.film))) films.push_back(ligne.film); });
    return films;
}