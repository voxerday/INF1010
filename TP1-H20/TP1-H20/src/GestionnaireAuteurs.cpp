// TODO: Faire l'entête de fichier
//! Classe GestionaireAuteurs
//! \author Careau, Martin(1978446) et Sitchom Kamdem, Laurelle Audrey(1876331)
//! \date 28 janvier 2020

// TODO: Inclure la définition de la classe appropriée
#include "GestionnaireAuteurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// TODO: Constructeur par défault en utilisant la liste d'initialisation
GestionnaireAuteurs::GestionnaireAuteurs()
    :nbAuteurs_(0) {}


       
// TODO ajouterAuteur(const Auteur& auteur)
// Ajouter un auteur au tableau des auteurs.
// Retourner false si il n'y a plus de place dans le tableau.
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur) {
    //Gérer le cas où le tableau est plein et donc causerait une erreur.
    if(nbAuteurs_ >= NB_AUTEURS_MAX) {
        return false;
    }
    auteurs_[nbAuteurs_] = auteur;
    nbAuteurs_++;
    return true;
}
// TODO chercherAuteur(const std::string& nomAuteur)
// Chercher dans la liste des auteurs si un auteur comporte le nom passé en paramètre.
// Retourner un nullptr si ce n'est pas le cas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur) {
    for (int i = 0; i < nbAuteurs_; i++) {
        if (nomAuteur == auteurs_[i].getNom()) {
            return &auteurs_[i];
        }
    }
    return nullptr;
}
//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        std::string ligne;
        // TODO: envoyer chaque ligne à lireLigneAuteur
        while (getline(fichier, ligne)) {
            if (!lireLigneAuteur(ligne)) {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        auteurs_[i].afficher(stream);
        stream << '\n';
    }
}

// TODO getNbAuteurs() const: Retourner le nombre d'auteurs dans la liste
std::size_t GestionnaireAuteurs::getNbAuteurs() const {
    return nbAuteurs_;
}


//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nom;
    unsigned int age;
    //unsigned int films;
    // TODO
    // Utiliser l'opérateur d'extraction (>>) depuis le stream
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    if (stream.fail()) {
        return false;
    }
    stream >> std::quoted(nom);
    stream >> age;
    if (chercherAuteur(nom) == nullptr) {
        Auteur auteur = Auteur(nom, age);
        ajouterAuteur(auteur);
    }
    return true;
}