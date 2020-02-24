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
#include "Calcul.hpp"

using namespace std;

#pragma endregion //}


int main ( )
{
	int vals[] = {11, 12, 13,
	              21, 22, 23};
	Matrice mat(2, 3, vals);

	Calcul calc(&mat);
	calc.executer();
	calc.getResultat().afficher(cout, 3);
	cout << "\n";
	mat.getVal(0, 0) = 9000;
	calc.executer();
	calc.getResultat().afficher(cout , 4);
}
