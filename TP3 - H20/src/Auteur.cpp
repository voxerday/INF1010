// To do
#include "Auteur.h"


//! Constructeur de la classe Auteur par defaut
Auteur::Auteur()
    :nom_(),
    anneeDeNaissance_(),
    nbMedias_(0)
{
}

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbMedias_(0)
{
}

//! Méthode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbMedias() const
{
    return nbMedias_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbMedias(unsigned int nbFilms)
{
    nbMedias_ = nbFilms;
}

//! Opérateur qui compare un string avec le nom de l'auteur avec auteur comme opérande de gauche
//! \param nom le nom avec le quel on veut comparé l'auteur
//! \return vrai si les noms sont identique, faux sinon
bool Auteur::operator==(const std::string& nom) const
{
    return (nom_ == nom);
}

//! Operateur qui affiche un auteur
//! \param os Le stream dans lequel afficher
//! \param auteur l'auteur a afficher
std::ostream& operator<<(std::ostream& os, const Auteur& auteur)
{
    os << "Nom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
       << " | Nombre de Film/Serie: " << auteur.nbMedias_;

    return os;
}

//! Operateur qui affecte un auteur
//! \param is Le stream avec les infos (nom et age)
//! \param auteur l'auteur a affecter
std::istream& operator>>(std::istream& is, Auteur& auteur)
{
    // To do
    std::string nomAuteur;
    unsigned int age;
    if (is >> std::quoted(nomAuteur) >> age) {
        auteur.nom_ = nomAuteur;
        auteur.anneeDeNaissance_ = age;
    }
    return is;
}