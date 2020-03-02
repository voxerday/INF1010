// To do
#include "Saison.h"

//! Constructeur par defaut de la classe Saison
Saison::Saison()
    :numSaison_(0),
    nbEpisodesmax_(0)
{
}

//! Constructeur de la classe Saison
//! \param numSaison           Numero de la saison
//! \param anneeDeSortie       Le nombre d'episodes de la saison
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax)
    :numSaison_(numSaison),
    nbEpisodesmax_(nbEpisodemax)
{
}

//! Constructeur par copie de la classe Saison
//! \param saison               Saison a copier
Saison::Saison(const Saison& saison)
{
    episodes_.clear();
    numSaison_ = saison.numSaison_;
    nbEpisodesmax_ = saison.nbEpisodesmax_;
    for (unsigned int i = 0; i < saison.getNbEpisodes(); i++)
    {
        episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));
    }
}

//! Destructeur de la classe Saison
Saison::~Saison()
{
    episodes_.clear();
}

//! Operateur qui ajoute un episode a une saison
//! \param episode      L'episode a ajouter
//! \return             La saison
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
    size_t i = trouverIndexEpisode(episode->getNumEpisode());
    if (i != EPISODE_INEXSISTANTE)
    {
        episodes_[i] = std::move(episodes_[episodes_.size() - 1]);
        episodes_.pop_back();
    }
    episodes_.push_back(std::move(episode));
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
    return *this;
}

//! Operateur qui ajoute un episode a une saison
//! \param numEpisode   Le numero d'episode a retirer
//! \return             La saison
Saison& Saison::operator-=(unsigned int numEpisode)
{
    size_t i = trouverIndexEpisode(numEpisode);
    if (i != EPISODE_INEXSISTANTE)
    {
        episodes_[i] = std::move(episodes_[episodes_.size() - 1]);
        episodes_.pop_back();
    }
    return *this;
}

//! Operateur qui compare le numero d'une saison
//! \param numSaison    Le numero de la saison a tester
//! \return             un bool si c'est pareil ou non
bool Saison::operator==(unsigned int numSaison)
{
    return (numSaison_ == numSaison);
}

//! Operateur qui affiche une saison
//! \param os       Le stream dans lequel afficher
//! \param saison   la saison a afficher
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
    os << "Saison" << std::setfill('0') << std::setw(2) << saison.numSaison_ << ": "
        << saison.episodes_.size() << "/" << saison.nbEpisodesmax_
        << (saison.episodes_.size() == saison.nbEpisodesmax_ ? "(Terminée)" : "(En cours)") << std::endl;
    for (auto& ep:saison.episodes_)
    {
        os << "\t\t" << *(ep) << std::endl;
    }
    return os;
}

//! Operateur qui affecte une saison
//! \param is       Le stream avec les infos (numero de saison et nombre d'episodes dans la saison)
//! \param saison   La saison a affecter
std::istream& operator>>(std::istream& is, Saison& saison)
{
    is >> saison.numSaison_ >> saison.nbEpisodesmax_;
    return is;
}

//! Methode qui retourne le numero de la saison
//! \return numSaison_
unsigned int Saison::getNumSaison() const
{
    return numSaison_;
}

//! Methode qui retourne le nombre d'episodes dans la saison
//! \return la grosseur du vecteur episodes_
size_t Saison::getNbEpisodes() const
{
    return episodes_.size();
}

//! Methode qui retourne l'indexe d'un episode
//! \param numEpisode   Le numero d'episode recherche
//! \return             L'index de l'episode(EPISODE_INEXSISTANTE si non trouve)
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
    for (unsigned int i = 0; i < episodes_.size(); i++)
    {
        if (episodes_[i]->getNumEpisode() == numEpisode) { return i; }
    }
    return EPISODE_INEXSISTANTE;
}