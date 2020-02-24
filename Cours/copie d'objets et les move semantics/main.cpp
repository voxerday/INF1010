#pragma region "Includes" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <new>

#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>

#include "MaClasse.hpp"
#include "Tableau.hpp"

using namespace std;

#pragma endregion //}


/// Fonction bidon qui retourne un 'MaClasse' construit par défaut. Le compilateur peut faire beaucoup d'optimisation.
MaClasse allerAuToast ( ) { return {}; }

Tableau faireFrette ( )
{
	Tableau res;
	res.ajouter(-273.15);
	return res; // Par élision de constructeur, il n'y aura pas de constructeur par copie appelé pour retourner 'res'.
}

int main ( )
{
	// Démonstration des appels de constructeurs et d'opérateurs d'affectation.
	cout << "-------------------------------" << "\n";
	{
		MaClasse foo; // Ctor par défaut.
		MaClasse bar = 42; // Ctor par param.
		MaClasse qux = foo; // Ctor par copie (lvalue).
		MaClasse spam = allerAuToast(); // Ctor par défaut (élision de constructeur par le compilateur).
		foo = move(bar); // Affectation par move. Ici, 'bar' est échangé avec 'foo' et va contenir la ressource de 'foo' (donc rien). 'bar' se fait détruire à la fin du scope.
		foo = allerAuToast(); // Operateur d'affectation par move (MaClasse&&), swap avec objet temporaire puis destruction de l'objet temporaire.
		cout << "- - - - - - - - - - - - - - - -" << "\n";
	}
	cout << "-------------------------------" << "\n\n";

	// Utilisation des tableaux dynamiques.
	{
		Tableau foo;
		for ( auto i : range(1, 5) )
			foo.ajouter(1.0 + i / 10.0);
		cout << "foo: " << foo << "\n";
		Tableau bar(foo); // Ctor par copie.
		cout << "bar: " << bar << "\n";
		Tableau qux(move(bar)); // Ctor par move. 'bar' se retrouve vide.
		cout << "qux: " << qux << "\n";
		cout << "bar: " << bar << "\n";
		bar = faireFrette(); // Affectation par move.
		cout << "bar: " << bar << "\n";
	}
}
