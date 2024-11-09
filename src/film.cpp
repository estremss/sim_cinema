#include "film.hpp"

Film::Film(std::string t, std::string r, int s) : titre(t), realisateur(r), sortie(s), id(next_id) { next_id++; }

void Film::print() const
{
    std::cout << std::setw(2) << titre << ", " << sortie << ", " << realisateur;
}

std::string Film::return_ligne() const
{
    return titre + " ; " + std::to_string(sortie) + " ; " + realisateur + "\n";
}

bool Film::operator==(const Film &autre) const
{
    return titre == autre.titre && sortie == autre.sortie && realisateur == autre.realisateur;
}