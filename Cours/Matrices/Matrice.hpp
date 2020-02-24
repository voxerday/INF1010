#pragma once


#pragma region "Includes" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <new>

#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

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

	const double& getVal (int ligne, int colonne) const
	{
		 return valeurs_[ligne * largeur_ + colonne];
	}
	
	double& getVal (int ligne, int colonne)
	{
		 return valeurs_[ligne * largeur_ + colonne];
	}

	void afficher ( ostream& out, int alignement = 0 ) const
	{
		for ( int ligne = 0; ligne < getHauteur(); ligne++ ) {
			for ( int colonne = 0; colonne < largeur_; colonne++ )
				out << setw(alignement) << getVal(ligne, colonne) << " ";
			out << "\n";
		}
	}

private:
	int            hauteur_ = -1;
	int            largeur_ = -1;
	vector<double> valeurs_;
};


