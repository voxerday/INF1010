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
/// \brief Classe implémentant un tableau dynamique de double. Comme std::vector<double>, mais un peu plus bête.
/// 
/// On utilise une classe de pointeur intelligent (PtrIntelligent) pour contenir notre ressource.
/// Cela permet d'éviter des fuites de mémoire surtout dans le cas où les constructeurs lancent des exceptions (plantent).
/// En effet, étant donnée que la ressource est gérée par valeurs_ (un ptr intelligent),
/// si le corps du constructeur lance une exception, le destructeur de valeurs_ se fait appeler,
/// libérant la resssource sans fuite de mémoire.
///
/// On utilise le principe DRY (Don't Repeat Yourself) le plus possible. En effet, une seule méthode fait un new dans
/// toute la classe, c-à-d redimensionner().
///
class Tableau
{
public:
	// Tous les chemins mènent à swap...
	friend void swap ( Tableau&, Tableau& );
	friend ostream& operator << ( ostream&, const Tableau& );

	Tableau ( ) = default;

	Tableau ( const Tableau& autre )
	: Tableau(autre.taille_) // On réutilise le constructeur par taille pour dimensionner (principe DRY)
	{
		copierValeurs(autre.valeurs_.get(), taille_);
	}

	Tableau ( Tableau&& autre )
	{
		// On swap avec l'objet temporaire, on lui prend donc sa ressource en lui donnant la nôtre.
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
			// Si on n'a pas déjà le tableau suffisant pour contenir les données, on réutilise notre constructeur par copie (principe DRY).
			// La variable 'tmp' possède maintenant exactement ce qu'on veut (une copie profonde de l'objet en paramètre).
			Tableau tmp = autre;
			// En swappant avec un objet local, on n'a pas besoin d'écrire du code de désallocation, car la variable tmp possède maintenant
			// la ressource qu'on avait, et va s'occuper de la libérer à sa destruction, c-à-d à la fin de sa portée (l'accolade du if).
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

		// Même concept qu'avec le constructeur par move : l'objet temporaire se retrouve avec notre ancienne ressource et va
		// s'occuper de la libérer à sa destruction (pas très longtemps après l'appel courant, si c'est un objet temporaire).
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

		// On transfère notre ancienne ressource à une variable locale de type PtrIntelligent. De cette façon,
		// c'est la variable locale qui est responsable de libérer l'ancienne ressource.
		PtrIntelligent ancien = move(valeurs_);
		capacite_ = capacite;
		valeurs_.reset(new double[capacite_]);
		copierValeurs(ancien.get(), taille_);
		// On n'a pas besoin d'écrire de code pour désallouer l'ancienne ressource, le destructeur de la variable 'ancien'
		// va s'en occuper à la fin de la méthode. Il en va de même si une exception était lancée dans la méthode.
	}


private:
	void copierValeurs ( double* valeurs, size_t taille )
	{
		for ( auto i : range(taille) )
			valeurs_.get()[i] = valeurs[i];
	}

	// Données membres
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
