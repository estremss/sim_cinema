#ifndef CINEMA_HPP
#define CINEMA_HPP

#define FIC_LISTE_FILM "src/save_data/liste_films.txt"
#define FIC_LISTE_SEANCES "src/save_data/liste_seances.txt"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "salle.hpp"
#include "film.hpp"
#include "seance.hpp"

class Cinema
{
private:
    // Attributs
    unsigned int nb_salles;
    Salle *liste_salles;
    std::vector<Film> liste_films;
    std::vector<Seance> liste_seances;

    // Méthodes
    void init_salles();
    void maj_films(const std::string &);
    void supprimer_film();
    void afficher_films() const;
    void afficher_salle() const;
    void afficher_seances() const;
    void ajouter_seance();
    void supprimer_seance();
    void vente_place();
    void ecrire_film() const;
    void ecrire_seances() const;
    void init_seances();
    unsigned int nb_places_vendues() const;

public:
    Cinema(const std::string &);
    Cinema();
    ~Cinema();
    void launcher();
};

#endif