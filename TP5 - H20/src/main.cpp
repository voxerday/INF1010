/// Fonction main.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include <iostream>
#include <algorithm>
#include "AnalyseurLogs.h"
#include "GestionnaireFilms.h"
#include "GestionnaireUtilisateurs.h"
#include "Tests.h"
#include "WindowsUnicodeConsole.h"
#include "Foncteurs.h"

int main()
{
    // Change le code page de la console Windows en UTF-8 si l'OS est Windows
    initializeConsole();

    Tests::testAll();

    // Écrivez le code pour le bonus ici
    
    //Nom des fichiers des gestionnaires avec l'info à extraire
    std::string userTxt = "utilisateurs.txt";
    std::string filmsTxt = "films.txt";
    std::string logTxt = "logs.txt";

    //Initialiosation des gestionnaires
    GestionnaireUtilisateurs gestionnaireUtilisateurs;
    GestionnaireFilms gestionnaireFilms;
    AnalyseurLogs analyseurLogs;


    //Affichage UTILISATEURS
    gestionnaireUtilisateurs.chargerDepuisFichier(userTxt);

    std::cout << std::endl << gestionnaireUtilisateurs << std::endl;

    //Affichage FILMS
    gestionnaireFilms.chargerDepuisFichier(filmsTxt);

    std::cout << "Films d'aventure:" << std::endl;
    for (const Film* film : gestionnaireFilms.getFilmsParGenre(Film::Genre(1)))
    {
        std::cout << '\t' << *film << '\n';
    }

    std::cout << std::endl << "Films produits de 1960 à 1961:" << std::endl;
    for (const Film* film : gestionnaireFilms.getFilmsEntreAnnees(1960, 1961))
    {
        std::cout << '\t' << *film << '\n';
    }

    //Affichage LOGS
    analyseurLogs.chargerDepuisFichier(logTxt, gestionnaireUtilisateurs, gestionnaireFilms);

    const Film* filmPop = analyseurLogs.getFilmPlusPopulaire();
    int filmPopScore = analyseurLogs.getNombreVuesFilm(filmPop);
    std::cout << std::endl << "Films le plus populaire (" << filmPopScore << " vues): " << *filmPop << std::endl;

    std::cout << std::endl << "5 films les plus polpulaires:" << std::endl;
    for (std::pair<const Film*, int> film : analyseurLogs.getNFilmsPlusPopulaires(5))
    {
        std::cout << '\t' << *film.first << '\n';
    }

    std::string id = "karasik@msn.com";
    const Utilisateur* user = gestionnaireUtilisateurs.getUtilisateurParId(id);
    std::cout << std::endl << "Nombre de films vus par l'utilisateur " << id << ":" << analyseurLogs.getNombreVuesPourUtilisateur(user) << std::endl;
}