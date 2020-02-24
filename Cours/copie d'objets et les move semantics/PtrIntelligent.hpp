#pragma once


#pragma region "Includes" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <new>

#include <iostream>
#include <cstdio>
#include <utility>

#include <cppitertools/range.hpp>

using namespace std;
using namespace iter;

#pragma endregion //}

///
/// \brief Un pointeur intelligent de tableau de double, comme std::unique_ptr<double[]>
///
/// Comme pour std::unique_ptr, le constructeur par copie est effacé et le constructeur par move utilise
/// un swap qui échange sa ressource avec le paramètre.
///
class PtrIntelligent
{
public:
	friend void swap ( PtrIntelligent&, PtrIntelligent& );

	PtrIntelligent ( ) = default;

	PtrIntelligent ( const PtrIntelligent& ) = delete;

	PtrIntelligent ( PtrIntelligent&& autre )
	{
		swap(*this, autre);
	}

	PtrIntelligent ( double* ressource )
	: ressource_(ressource)
	{ }

	~PtrIntelligent ( )
	{
		reset(nullptr);
	}

	double* get ( ) const { return ressource_; };

	void reset ( double* ressource )
	{
		delete[] ressource_;
		ressource_ = ressource;
	}

private:
	// Données membres
	double* ressource_ = nullptr;
};


void swap (PtrIntelligent& ptr1, PtrIntelligent& ptr2)
{
	double* tmp = ptr1.ressource_;
	ptr1.ressource_ = ptr2.ressource_;
	ptr2.ressource_ = tmp;
}
