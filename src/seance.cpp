#include "seance.hpp"

Seance::Seance(unsigned int ns, Film *f, std::string h) : numero_salle(ns), ptr_film(f), horaire(h) {}

Seance::Seance(unsigned int ns, Film *f, std::string h, unsigned int p) : numero_salle(ns), ptr_film(f), horaire(h), places_vendues(p) {}

void Seance::set_ptr_film(Film *pt) { ptr_film = pt; }

unsigned int Seance::get_id_film() const { return this->ptr_film->get_id(); }

void Seance::print() const
{
    ptr_film->print();
    std::cout << ", Salle " << numero_salle << ", " << horaire;
}

void Seance::vente_place(unsigned int n) { places_vendues += n; }

std::string Seance::return_ligne() const
{
    return std::to_string(numero_salle) + ";" + std::to_string(ptr_film->get_id()) + ";" + horaire + ";" + std::to_string(places_vendues) + "\n";
}