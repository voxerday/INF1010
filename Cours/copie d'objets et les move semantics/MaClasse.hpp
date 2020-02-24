#pragma once


#pragma region "Includes" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <new>

#include <iostream>

using namespace std;

#pragma endregion //}


///
/// \brief Classe qui ne fait rien d'autre que d'afficher l'appel de ses constructeurs, opérateurs d'affectation et son destructeur
///
class MaClasse
{
public:
	MaClasse ( ) { cout << "MaClasse()" << endl; }
	MaClasse ( const MaClasse& ) { cout << "MaClasse(const MaClasse&)" << endl; }
	MaClasse ( MaClasse&& ) { cout << "MaClasse(MaClasse&&)" << endl; }
	MaClasse ( int ) { cout << "MaClasse(int)" << endl; }

	~MaClasse ( ) { cout << "~MaClasse()" << endl; }

	MaClasse& operator = ( const MaClasse& ) { cout << "operator=(const MaClasse&)" << endl; return *this; }
	MaClasse& operator = ( MaClasse&& ) { cout << "operator=(MaClasse&&)" << endl; return *this; }
};

