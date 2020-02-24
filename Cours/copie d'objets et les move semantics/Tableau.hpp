#pragma once


#pragma region "Includes" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <new>

#include <ostream>
#include <iomanip>
#include <cstdio>
#include <utility>

#include <cppitertools/range.hpp>

#include "PtrIntelligent.hpp"

using namespace std;
using namespace iter;

#pragma endregion //}


///
/// \brief Classe impl�mentant un tableau dynamique de double. Comme std::vector<double>, mais un peu plus b�te.
/// 
/// On utilise une classe de pointeur intelligent (PtrIntelligent) pour contenir notre ressource.
/// Cela permet d'�viter des fuites de m�moire surtout dans le cas o� les constructeurs lancent des exceptions (plantent).
/// En effet, �tant donn�e que la ressource est g�r�e par valeurs_ (un ptr intelligent),
/// si le corps du constructeur lance une exception, le destructeur de valeurs_ se fait appeler,
/// lib�rant la resssource sans fuite de m�moire.
///
/// On utilise le principe DRY (Don't Repeat Yourself) le plus possible. En effet, une seule m�thode fait un new dans
/// toute la classe, c-�-d redimensionner().
///
class Tableau
{
public:
	// Tous les chemins m�nent � swap...
	friend void swap ( Tableau&, Tableau& );
	friend ostream& operator << ( ostream&, const Tableau& );

	Tableau ( ) = default;

	Tableau ( const Tableau& autre )
	: Tableau(autre.taille_) // On r�utilise le constructeur par taille pour dimensionner (principe DRY)
	{
		copierValeurs(autre.valeurs_.get(), taille_);
	}

	Tableau ( Tableau&& autre )
	{
		// On swap avec l'objet temporaire, on lui prend donc sa ressource en lui donnant la n�tre.
		// Or, notre ressource est vide, l'objet temporaire se retrouve donc vide et valide.
		swap(*this, autre);
	}

	Tableau ( size_t taille )
	{
		redimensionner(taille);
	}

	~Tableau ( ) = default;

	Tableau& operator = ( const Tableau& autre )
	{
		if ( this == &autre )
			return *this;

		if ( capacite_ < autre.taille_ ) {
			// Si on n'a pas d�j� le tableau suffisant pour contenir les donn�es, on r�utilise notre constructeur par copie (principe DRY).
			// La variable 'tmp' poss�de maintenant exactement ce qu'on veut (une copie profonde de l'objet en param�tre).
			Tableau tmp = autre;
			// En swappant avec un objet local, on n'a pas besoin d'�crire du code de d�sallocation, car la variable tmp poss�de maintenant
			// la ressource qu'on avait, et va s'occuper de la lib�rer � sa destruction, c-�-d � la fin de sa port�e (l'accolade du if).
			swap(*this, tmp);
		}
		else {
			// Si on a de la place, on copie les valeurs.
			copierValeurs(autre.valeurs_.get(), autre.taille_);
			taille_ = autre.taille_;
		}

		return *this;
	}

	Tableau& operator = ( Tableau&& autre )
	{
		if ( this == &autre )
			return *this;

		// M�me concept qu'avec le constructeur par move : l'objet temporaire se retrouve avec notre ancienne ressource et va
		// s'occuper de la lib�rer � sa destruction (pas tr�s longtemps apr�s l'appel courant, si c'est un objet temporaire).
		swap(*this, autre);
		return *this;
	}

	// Des accesseurs utiles.
	size_t getTaille ( ) const { return taille_; }
	size_t getCapacite ( ) const { return capacite_; }
	double& operator [] ( size_t index ) { return valeurs_.get()[index]; }
	const double& operator [] ( size_t index ) const { return valeurs_.get()[index]; }

	void ajouter ( double valeur )
	{
		redimensionner(taille_ + 1);
		(*this)[taille_ - 1] = valeur;
	}

	void redimensionner ( size_t taille )
	{
		if ( taille > capacite_ )
			reserverEspace(taille);

		if ( taille > taille_ ) {
			for ( auto i : range(taille_, taille) )
				valeurs_.get()[i] = {};
		}
		taille_ = taille;
	}

	void reserverEspace ( size_t capacite )
	{
		if ( capacite <= capacite_ )
			return;

		// On transf�re notre ancienne ressource � une variable locale de type PtrIntelligent. De cette fa�on,
		// c'est la variable locale qui est responsable de lib�rer l'ancienne ressource.
		PtrIntelligent ancien = move(valeurs_);
		capacite_ = capacite;
		valeurs_.reset(new double[capacite_]);
		copierValeurs(ancien.get(), taille_);
		// On n'a pas besoin d'�crire de code pour d�sallouer l'ancienne ressource, le destructeur de la variable 'ancien'
		// va s'en occuper � la fin de la m�thode. Il en va de m�me si une exception �tait lanc�e dans la m�thode.
	}


private:
	void copierValeurs ( double* valeurs, size_t taille )
	{
		for ( auto i : range(taille) )
			valeurs_.get()[i] = valeurs[i];
	}

	// Donn�es membres
	size_t         taille_ = 0;
	size_t         capacite_ = 0;
	PtrIntelligent valeurs_;
};


void swap (Tableau& tab1, Tableau& tab2)
{
	swap(tab1.taille_, tab2.taille_);
	swap(tab1.capacite_, tab2.capacite_);
	swap(tab1.valeurs_, tab2.valeurs_);
}


ostream& operator << ( ostream& lhs, const Tableau& rhs )
{
	auto alignement = lhs.width();
	for ( auto i : range(rhs.getTaille()) )
		cout << setw(alignement) << rhs[i] << " ";

	return lhs;
}
