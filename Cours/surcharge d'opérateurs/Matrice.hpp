#pragma once


#pragma region "Includes" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <new>

#include <ostream>
#include <cstdio>
#include <vector>
#include <memory>
#include <iomanip>

#include <cppitertools/range.hpp>

using namespace std;
using namespace iter;

#pragma endregion //}


// Déclaration d'un tableau de réels à "deux dimensions", en utilisant un tableau une dimension:
class Matrice
{
public:
	Matrice ( ) = default;

	Matrice ( int hauteur, int largeur, double* valeurs = nullptr )
	: hauteur_(hauteur),
	  largeur_(largeur),
	  valeurs_(hauteur * largeur)
	{
		if ( valeurs != nullptr ) {
			for ( int i = 0; i < valeurs_.size(); i++ )
				valeurs_[i] = valeurs[i];
		}
	}

	Matrice ( int cote, double* valeurs = nullptr ) : Matrice(cote, cote, valeurs) { }

	int getHauteur ( ) const
	{
		return hauteur_;
	}

	int getLargeur ( ) const
	{
		return largeur_;
	}


	bool estValide ( ) const
	{
		return getHauteur() > 0 and getLargeur() > 0 and valeurs_.size() == getHauteur() * getLargeur();
	}

	bool aMemesDimensions ( const Matrice& mat ) const
	{
		return estValide() and mat.estValide() and getHauteur() == mat.getHauteur() and getLargeur() == mat.getLargeur();
	}

	const double& operator () (int ligne, int colonne) const
	{
		return getVal(ligne, colonne);
	}

	double& operator () (int ligne, int colonne)
	{
		return getVal(ligne, colonne);
	}

	/* Versions des opérateurs directement dans la classe.
	Matrice operator - () const
	{
		return opposee();
	}

	Matrice operator + (const Matrice& rhs) const
	{
		return additionner(rhs);
	}

	Matrice operator - (const Matrice& rhs) const
	{
		return *this + -rhs;
	}
	*/

	// Opérateurs définis globalement et amis de la classe.
	friend Matrice operator - ( const Matrice& arg );
	friend Matrice operator + ( const Matrice& lhs, const Matrice& rhs );
	friend Matrice operator - ( const Matrice& lhs, const Matrice& rhs );
	friend Matrice operator * ( const Matrice& lhs, const Matrice& rhs );
	friend ostream& operator << ( ostream& lhs, const Matrice& rhs );

private:
	const double& getVal ( int ligne, int colonne ) const
	{
		 return valeurs_[ligne * largeur_ + colonne];
	}
	
	double& getVal ( int ligne, int colonne )
	{
		 return valeurs_[ligne * largeur_ + colonne];
	}

	Matrice additionner ( const Matrice& rhs ) const
	{
		if ( not aMemesDimensions(rhs) )
			return {};

		Matrice resultat(getHauteur(), getLargeur());
		for ( auto i : range(valeurs_.size()) )
			resultat.valeurs_[i] = valeurs_[i] + rhs.valeurs_[i];

		return resultat;
	}

	Matrice opposee ( ) const
	{
		if ( not estValide() )
			return {};

		Matrice resultat(getHauteur(), getLargeur());
		for ( auto i : range(valeurs_.size()) )
			resultat.valeurs_[i] = -valeurs_[i];

		return resultat;
	}

	void afficher ( ostream& out, int alignement = 0 ) const
	{
		if ( not estValide() ) {
			out << "Matrice invalide" << "\n";
			return;
		}
		
		for ( int ligne = 0; ligne < getHauteur(); ligne++ ) {
			for ( int colonne = 0; colonne < largeur_; colonne++ ) {
				if ( alignement > 0 )
					out << setw(alignement);
				out << getVal(ligne, colonne) << " ";
			}
			out << "\n";
		}
	}

	Matrice multiplier ( const Matrice& rhs ) const
	{
		if ( not (estValide() and rhs.estValide()) or getLargeur() != rhs.getHauteur() )
			return {};
		
		Matrice resultat(getHauteur(), rhs.getLargeur());
		for ( auto i : range(resultat.getHauteur()) ) {
			for ( auto j : range(resultat.getLargeur()) ) {
				for ( auto k : range(getLargeur()) )
					resultat.getVal(i, j) += getVal(i, k) * rhs.getVal(k, j);
			}
		}

		return resultat;
	}

	// Données membres
	int            hauteur_ = -1;
	int            largeur_ = -1;
	vector<double> valeurs_;
};


Matrice operator - ( const Matrice& arg )
{
	return arg.opposee();
}

Matrice operator + ( const Matrice& lhs, const Matrice& rhs )
{
	return lhs.additionner(rhs);
}

Matrice operator - ( const Matrice& lhs, const Matrice& rhs )
{
	return lhs + -rhs;
}

Matrice operator * ( const Matrice& lhs, const Matrice& rhs )
{
	return lhs.multiplier(rhs);
}

ostream& operator << ( ostream& lhs, const Matrice& rhs )
{
	rhs.afficher(lhs, (int)lhs.width());
	return lhs;
}

