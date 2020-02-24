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

#include "Matrice.hpp"

using namespace std;

#pragma endregion //}


class Calcul
{
public:
	Calcul ( ) = default;

	Calcul ( const Matrice* arg ) : arg_(arg) { }

	void executer ( )
	{
		// On prétend qu'on fait des calculs vraiment compliqués qui méritent d'être dans une classe avec un état, genre de la simulation ou de quoi...
		resultat_ = *arg_;
		resultat_.getVal(0, 0) = arg_->getVal(0, 0) + 42;
	}

	void setArg ( const Matrice* arg )
	{
		arg_ = arg;
	}

	const Matrice* getArg ( ) const
	{
		return arg_;
	}

	const Matrice& getResultat ( ) const
	{
		return resultat_;
	}


private:
	const Matrice* arg_ = nullptr; // En agrégation
	Matrice        resultat_; // En composition
};
