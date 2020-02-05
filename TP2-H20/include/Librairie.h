#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <memory>
#include "Film.h"
#include "GestionnaireAuteurs.h"

class Librairie
{
public:
    Librairie();
    Librairie(const Librairie&);
    Librairie& operator=(const Librairie&);
    ~Librairie();

    //void ajouterFilm(Film* film);
    void operator+=(Film* film);
    //void retirerFilm(const std::string& nomFilm);
    Film* chercherFilm(const std::string& nomFilm);
    bool chargerFilmsDepuisFichier(const std::string& nomFichier,
                                   GestionnaireAuteurs& gestionnaireAuteurs);
    bool chargerRestrictionsDepuisFichiers(const std::string& nomFichier);
    friend std::ostream& operator<<(std::ostream& stream, const Librairie& film);

	const std::vector<std::unique_ptr<Film>>& getFilms() const;
    std::size_t getNbFilms() const;

private:
    void supprimerFilms();
    bool lireLigneRestrictions(const std::string& ligne);
    bool lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs);
    int trouverIndexFilm(const std::string& nomFilm) const;

    // Movies array
    std::vector<std::unique_ptr<Film>> films_;
};

#endif // LIBRAIRIE_H