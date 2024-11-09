#ifndef SEANCE_HPP
#define SEANCE_HPP
#include <string>
#include <iostream>
#include "film.hpp"

class Seance
{
private:
    unsigned int numero_salle;
    Film *ptr_film;
    std::string horaire;
    unsigned int places_vendues = 0;

public:
    Seance(unsigned int, Film *, std::string);
    Seance(unsigned int, Film *, std::string, unsigned int);
    void print() const;
    void vente_place(unsigned int);
    std::string return_ligne() const;
    void set_ptr_film(Film *);
    unsigned int get_id_film() const;
    inline unsigned int get_numero_salle() const { return numero_salle; }
    inline unsigned int get_places_vendues() const { return places_vendues; }
};

#endif