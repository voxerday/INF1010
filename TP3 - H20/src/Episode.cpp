// To do
#include "Episode.h"
// To do
Episode::Episode()
// To 
    :nom_(),
    duree_(),
    numEpisode_()
{
}

// To do
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree)
// To do
    :nom_(nom),
    duree_(duree),
    numEpisode_(numEpisode)
{
}

// To do
bool Episode::operator==(unsigned int numEpisode)
{
    // To do
    return (numEpisode_ == numEpisode);
}

// To do
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
    // To do
    //Episode01:Episode:01|Durée:00:00:00
    os << episode.nom_ << ":Episode:" << episode.numEpisode_ << "|Durée:" << episode.duree_ << std::endl;
    return os;
}

// To do
std::istream& operator>>(std::istream& is, Episode& episode)
{
    // To do
    std::string nom;
    std::string duree;
    unsigned int num;
    //"1\"Episode:01\"\"00:00:00\""
    if (is >> num >> std::quoted(nom) >> duree) 
    {
        episode.nom_ = nom;
        episode.duree_ = duree;
        episode.numEpisode_ = num;
    }
    return is;
}

// To do
unsigned int Episode::getNumEpisode() const
{
    // To do
    return this->numEpisode_;
}