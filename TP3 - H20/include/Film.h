#ifndef FILM_H
#define FILM_H

// To do
#include "Media.h"
#include "Auteur.h"


class Film : public Media
{
public:
    Film(Auteur* auteur);
    Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
         bool estRestreintParAge, Auteur* auteur, const std::string& duree);

    std::ostream& afficher(std::ostream& os) const override;
    std::istream& lire(std::istream& is) override;
    std::unique_ptr<Media> clone() const override;

private:
    // Attributes
    std::string duree_;
};
#endif // FILM_H
