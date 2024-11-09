#ifndef FILM_HPP
#define FILM_HPP

#include <string>
#include <iostream>
#include <iomanip>

class Film
{
private:
    // Attributs
    std::string titre;
    std::string realisateur;
    int sortie; // annee de sortie du film
    // id
    unsigned int id;
    inline static unsigned int next_id = 1;

public:
    Film(std::string, std::string, int);
    void print() const;
    std::string return_ligne() const;
    bool operator==(const Film &) const;
    inline unsigned int get_id() const { return id; }
};

#endif