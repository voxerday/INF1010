// To do
#include "Saison.h"

// To do
Saison::Saison()
    // To do
    :episodes_(),
    numSaison_(),
    nbEpisodesmax_()
{
}

// To do
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax)
    // To do
    :episodes_(),
    numSaison_(numSaison),
    nbEpisodesmax_(nbEpisodemax)
{
}

// To do
Saison::Saison(const Saison& saison)
{
    // To do
    episodes_ = saison.episodes_;
    numSaison_ = saison.numSaison_;
    nbEpisodesmax_ = saison.nbEpisodesmax_;
}

// To do
Saison::~Saison()
{
    // To do
    episodes_.clear();
}

// To do
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
    // To do
    unsigned int epNum = *episode->getNumEpisode;
    if (trouverIndexEpisode(epNum)) { *this -= epNum; }
    episodes_.push_back(episode);
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
}

// To do
Saison& Saison::operator-=(unsigned int numEpisode)
{
    // To do
    episodes_.erase(episodes_.begin() + trouverIndexEpisode(numEpisode));
}

// To do
bool Saison::operator==(unsigned int numSaison)
{
    // To do
    return (numSaison_ == numSaison);
}

// To do
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
    // To do
    //"Saison01:3/20(Encours)"
    //    "Episode01:Episode:01|Durée:00:00:00"
    //    "Episode02:Episode:02|Durée:00:00:00"
    //    "Episode03:Episode:03|Durée:00:00:00"
    //    "Saison01:2/20(Encours)"
    //    "Episode01:Episode:01|Durée:00:00:00"
    //    "Episode03:Episode:03|Durée:00:00:00"
    os << "Saison" << saison.numSaison_ << ":" << saison.getNbEpisodes() << "/" << saison.nbEpisodesmax_;
    if (saison.getNbEpisodes() != saison.nbEpisodesmax_) { os << "(Encours)"; }
    os << std::endl;
    for (auto&& ep : saison.episodes_) {
        os << ep;
    }

}

// To do
std::istream& operator>>(std::istream& is, Saison& saison)
{
    // To do
    unsigned int num;
    unsigned int max;
    //"1 20"
    if (is >> num >> max)
    {
        saison.numSaison_ = num;
        saison.nbEpisodesmax_ = max;
    }
}

// To do
unsigned int Saison::getNumSaison() const
{
    // To do
    return numSaison_;
}

// To do
size_t Saison::getNbEpisodes() const
{
   // To do
    return episodes_.size();
}

// To do
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
    // To do
    for (size_t i; i < getNbEpisodes(); i++) {
        if (*episodes_[i] == numEpisode) { return i; }
    }
    return Saison::EPISODE_INEXSISTANTE;
}