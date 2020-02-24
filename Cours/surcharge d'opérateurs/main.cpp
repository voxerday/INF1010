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


int main ( )
{
	double vals1[] = {11, 12, 13,
	                  21, 22, 23};
	double vals2[] = {1, 2, 3,
	                  4, 5, 6};
	double vals3[] = { 7,  8,
	                   9, 10,
	                  11, 12};

	Matrice mat1(2, 3, vals2);
	Matrice mat2(3, 2, vals3);

	cout << setw(3) << (mat1 * mat2) << "\n"
	     << setw(3) << -Matrice(2, 3, vals1) << "\n"
	     << setw(3) << (Matrice(2, 3) - mat1) << "\n"
	     << setw(3) << (mat1 + mat2) << "\n"; // Matrices incompatibles, devrait afficher "Matrice invalide".
}
