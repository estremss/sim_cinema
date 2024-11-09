#ifndef SALLE_HPP
#define SALLE_HPP

#include <iostream>

class Salle
{
private:
    // Attributs
    unsigned int numero;
    unsigned int capacite;
    bool imax;

public:
    Salle();
    Salle(unsigned int, unsigned int, bool);
    void print() const;
    inline unsigned int get_capacite() const { return capacite; }
};

#endif