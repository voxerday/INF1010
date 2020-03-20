// To do
#include "Episode.h"

//! Constructeur de la classe Episode par defaut
Episode::Episode()
    :nom_(),
    duree_(),
    numEpisode_(0)
{
}

//! Constructeur de la classe Episode
//! \param numEpisode        Num�ro de l'episode
//! \param nom               Nom de l'episode
//! \param duree             Duree de l'episode
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree)

    :nom_(nom),
    duree_(duree),
    numEpisode_(numEpisode)
{
}

//! Methode qui compare deux numero d'episode
//! \param numEpisode        Num�ro de l'episode
//! \return vrai si le numero d'episode est identique, faux sinon
bool Episode::operator==(unsigned int numEpisode)
{
    return (numEpisode_ == numEpisode);
}

//! Operateur qui affiche un episode
//! \param os Le stream dans lequel afficher
//! \param episode l'episode a afficher
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
    os << "Episode" << std::setfill('0') << std::setw(2) 
        << episode.numEpisode_ << ": " 
        << episode.nom_ 
        << " | Durée: " << episode.duree_;
    return os;
}

//! Operateur qui affecte un Episode
//! \param is Le stream avec les infos (numero d'episode, nom et duree)
//! \param episode l'episode a affecter
std::istream& operator>>(std::istream& is, Episode& episode)
{
    is >> episode.numEpisode_ >> std::quoted(episode.nom_) >> std::quoted(episode.duree_);
    return is;
}

//! Methode qui retourne le numero d'episode
//! \return numEpisode_
unsigned int Episode::getNumEpisode() const
{
    return numEpisode_;
}