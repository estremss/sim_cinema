#include "salle.hpp"

using namespace std;

// Constructeur
Salle::Salle(unsigned int n, unsigned int c, bool i) : numero(n), capacite(c), imax(i) {}

Salle::Salle() : numero(), capacite(), imax() {}

void Salle::print() const
{
    cout << "Salle " << numero << " : " << capacite << " places, ";
    if (imax)
        cout << "IMAX : Oui";
    else
        cout << "IMAX : Non";
}