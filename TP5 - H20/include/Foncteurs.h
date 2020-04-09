/// Foncteurs.
/// \author NotMisha
/// \date 2020-04-07

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include "LigneLog.h"

//Foncteur  prédicat  unaire  servant  à  déterminer  si  un  film  est  sorti  entre  deux  années (inclusivement)
class EstDansIntervalleDatesFilm
{
public:

    /// Constructeur de la classe EstDansIntervalleDatesFilm
    /// \param anneeL               Annee la plus vielle de l'intervalle
    /// \param anneeH               Annee la plus jeune de l'intervalle 
    EstDansIntervalleDatesFilm(int anneeL, int anneeH) : anneeL_(anneeL), anneeH_(anneeH) {}

    /// Retourne un bool si le films est sortie dans l'interval d'années donne
    /// \param film			        Le film à vérifier l'année de sortie.
    /// \return						true s'il est dans l'intervalle, sinon false 
    bool operator()(const std::unique_ptr<Film>& film) const
    {
        return (anneeL_ <= film->annee && film->annee <= anneeH_);
    }

private:
    int anneeL_;
    int anneeH_;
};


//Foncteur prédicat binairecomparant les dates des lignes de log pour indiquer si elles sont en ordrechronologique
class ComparateurLog
{
public:

    /// Retourne un bool qui compare la date de deux logs
    /// \param ligneLog1	        Le premier log qui doit etre plus recent.
    /// \param ligneLog2	        Le deuxieme log qui doit etre plus vieux.
    /// \return						true si le premier log est plus recen que le deuxieme, sinon false 
    bool operator()(const LigneLog& ligneLog1, const LigneLog& ligneLog2) const
    {
        return ligneLog1.timestamp < ligneLog2.timestamp;
    }
};


//Template  de  foncteur  prédicat  binaire comparant  les  seconds  éléments  de  paires  pour déterminer  si  elles  sont  en  ordre.On  veut  que  le  foncteur  fonctionne  avec des  paires contenant n’importe quels éléments,et c’est pourquoi on en a fait un template.
template <typename T1, typename T2>
class ComparateurSecondElementPaire
{
public:

    /// Retourne un bool si le second element de la paire vient bien apres le second element de la premiere paire
    /// \param paire1		        La premiere paire qui doit venir avant.
    /// \param paire2		        La deuxieme paire qui doit venir apres.
    /// \return						true si les paires sont en ordre, sinon false 
    bool operator()(const std::pair<T1, T2>& paire1, const std::pair<T1, T2>& paire2) const
    {
        return (paire1.second < paire2.second);
    }
};



#endif // FONCTEURS_H
