#include "cinema.hpp"

// Constructeur qui ajoute les films de la liste
Cinema::Cinema(const std::string &fichier)
{
    this->maj_films(fichier);
    this->init_salles();
    if (!liste_films.empty())
        this->init_seances();
}

// Cosntructeur par défaut
Cinema::Cinema() { this->init_salles(); }

// Destructeur
Cinema::~Cinema() { delete[] liste_salles; }

void Cinema::init_salles()
{
    nb_salles = 3; // consigne

    liste_salles = new Salle[nb_salles];

    // Les salles définies pour ce cinéma
    Salle S1(1, 300, true);
    Salle S2(2, 250, true);
    Salle S3(3, 100, false);

    liste_salles[0] = S1;
    liste_salles[1] = S2;
    liste_salles[2] = S3;
}

void Cinema::ecrire_seances() const
{
    std::ofstream fic(FIC_LISTE_SEANCES);

    if (!fic.is_open())
    {
        std::cerr << "Erreur à l'ouverture du fichier " << FIC_LISTE_FILM << std::endl;
        return;
    }

    for (const auto &it : liste_seances)
        fic << it.return_ligne();

    fic.close();
}

void Cinema::init_seances()
{
    std::ifstream fic(FIC_LISTE_SEANCES);
    std::string ligne, num_salle_str, id_film_str, hor, places_vendues_str;
    long unsigned int i = 0;

    if (!fic.is_open())
    {
        std::cerr << "Erreur à l'ouverture du fichier " << FIC_LISTE_FILM << std::endl;
    }

    while (getline(fic, ligne))
    {
        // if (ligne.empty())
        //     break;

        std::istringstream flux_tmp(ligne);

        getline(flux_tmp, num_salle_str, ';');

        getline(flux_tmp, id_film_str, ';');

        getline(flux_tmp, hor, ';');

        getline(flux_tmp, places_vendues_str, ';');

        Film *pt;
        // Retrouver le film par son id
        while (liste_films[i].get_id() != (unsigned int)std::stoi(id_film_str) && i < liste_films.size() - 1)
            i++;

        if (i >= liste_films.size())
        {
            continue;
        }

        pt = &liste_films[i];

        Seance S(std::stoi(num_salle_str), pt, hor, std::stoi(places_vendues_str));

        liste_seances.push_back(S);
    }

    fic.close();
}

// Extrait du fichier txt la liste des films
void Cinema::maj_films(const std::string &fichier)
{
    std::ifstream fic(fichier);
    std::string ligne;
    std::string real, str_an, titre;
    bool doublon;

    if (!fic.is_open())
    {
        std::cerr << "Erreur à l'ouverture du fichier." << std::endl;
        return;
    }

    while (std::getline(fic, ligne))
    {
        doublon = false;

        // On met la string ligne sur un flux
        std::istringstream flux_tmp(ligne);

        // Titre
        std::getline(flux_tmp, titre, ';');
        titre.erase(titre.size() - 1, 1);

        // Annee
        std::getline(flux_tmp, str_an, ';');

        // Réalisateur
        std::getline(flux_tmp, real);
        real.erase(0, 1);

        Film F(titre, real, std::stoi(str_an));

        // Détecter si le film est déjà dans la liste
        for (const auto &it : liste_films)
            if (it == F)
                doublon = true;

        if (!doublon)
            liste_films.push_back(F);
    }

    fic.close();
}

// Affiche la liste des films à l'affiche
void Cinema::afficher_films() const
{
    int cnt = 1;

    if (liste_films.size() == 0)
    {
        std::cout << "Aucun film à l'affiche." << std::endl;
        return;
    }

    std::cout << "Voici la liste des films disponibles :"
              << std::endl;

    for (const auto &i : liste_films)
    {
        std::cout << cnt << ". ";
        i.print();
        std::cout << std::endl;
        cnt++;
    }
}

void Cinema::afficher_salle() const
{
    unsigned int i;

    std::cout << "\nVoici la liste des salles disponibles :"
              << std::endl;

    for (i = 0; i < nb_salles; i++)
    {
        liste_salles[i].print();
        std::cout << std::endl;
    }
}

void Cinema::ajouter_seance()
{
    unsigned int numero_film, salle, i = 0;
    std::string horaire;

    if (liste_films.size() == 0)
    {
        std::cout << "\nVous devez d'abord ajouter des films à l'affiche." << std::endl;
        return;
    }

    while (true)
    {
        std::cout << "\nEntrez le numéro du film de la séance (0 pour terminer) : ";
        std::cin >> numero_film;
        if (numero_film == 0)
            return;

        std::cout << "Entrez le numéro de la salle : ";
        std::cin >> salle;
        std::cout << "Entrez l'horaire souhaité (jour hh mm) : ";
        std::getline(std::cin, horaire);
        std::getline(std::cin, horaire);
        std::cout << std::endl;

        while (liste_films[i].get_id() != numero_film)
            i++;

        Seance S(salle, &liste_films[i], horaire);

        liste_seances.push_back(S);
    }
}

void Cinema::supprimer_seance()
{
    int n;

    while (!liste_seances.empty())
    {
        std::cout << "Entrez le numéro de la séance à supprimer (0 pour terminer) : ";
        std::cin >> n;

        if (n == 0)
            return;

        liste_seances.erase(liste_seances.begin() + n - 1);
    }

    std::cout << "Il n'y a aucune séance programmée." << std::endl;
}

void Cinema::afficher_seances() const
{
    int i = 0;

    if (liste_seances.size() == 0)
    {
        std::cout << "Aucune séance programmée." << std::endl;
        return;
    }

    std::cout << "Voici la liste des séances :" << std::endl;

    for (const auto &it : liste_seances)
    {
        std::cout << i + 1 << ". ";
        it.print();
        std::cout << std::endl;
        i++;
    }
}

void Cinema::vente_place()
{
    unsigned int seance;
    int places_restantes, places_vendues = 0;

    std::cout << "\nEntrez le numéro de la séance : ";
    std::cin >> seance;
    --seance;
    places_restantes = liste_salles[liste_seances[seance].get_numero_salle() - 1].get_capacite() - liste_seances[seance].get_places_vendues();
    std::cout << "Nombre de places restantes : " << places_restantes << std::endl;

    std::cout << "Entrez le nombre de places vendues : ";
    std::cin >> places_vendues;

    while (places_restantes - places_vendues < 0)
    {
        std::cout << places_vendues << " places ne peuvent pas être vendues. Capacité de la salle dépassée." << std::endl;
        std::cout << "Entrez le nombre de places vendues : ";
        std::cin >> places_vendues;
    }

    std::cout << "Il reste maintenant " << places_restantes - places_vendues << " places pour cette séance." << std::endl;

    liste_seances[seance].vente_place(places_vendues);
}

unsigned int Cinema::nb_places_vendues() const
{
    unsigned int bilan_places = 0;

    for (const auto &it : liste_seances)
        bilan_places += it.get_places_vendues();

    return bilan_places;
}

void Cinema::ecrire_film() const
{
    std::ofstream fic(FIC_LISTE_FILM);

    if (!fic.is_open())
    {
        std::cerr << "Erreur à l'ouverture du fichier " << FIC_LISTE_FILM << std::endl;
        return;
    }

    for (const auto &it : liste_films)
    {
        fic << it.return_ligne();
    }

    fic.close();
}

void Cinema::supprimer_film()
{
    unsigned int id_film_tableau;
    int i = 0;

    afficher_films();
    std::cout << "\nEntrez l'id du film à supprimer" << std::endl;
    std::cin >> id_film_tableau;
    id_film_tableau--;

    if (id_film_tableau >= liste_films.size())
    {
        std::cout << "Indice non reconnu." << std::endl;
        return;
    }

    // Effacer les séances qui affichent le film supprimé
    for (const auto &it : liste_seances)
    {
        if (it.get_id_film() == liste_films[id_film_tableau].get_id())
            liste_seances.erase(liste_seances.begin() + i);

        i++;
    }

    std::cout << "Le film a bien été supprimé." << std::endl;

    liste_films.erase(liste_films.begin() + id_film_tableau);
}

void Cinema::launcher()
{
    unsigned int choix;
    std::string nom_fic;

    while (true)
    {
        std::cout << "\nQue voulez-vous faire ?" << std::endl
                  << "1. Afficher les films et les salles" << std::endl
                  << "2. Ajouter des séances" << std::endl
                  << "3. Afficher les séances" << std::endl
                  << "4. Vendre des places pour une séance" << std::endl
                  << "5. Supprimer une séance" << std::endl
                  << "6. Ajouter des films à partir d'un fichier" << std::endl
                  << "7. Nombre de places vendues" << std::endl
                  << "8. Supprimer un film" << std::endl
                  << "9. Sauvegarder et quitter le programme" << std::endl;

        std::cin >> choix;
        std::cout << std::endl;

        switch (choix)
        {
        case 1:
            this->afficher_films();
            this->afficher_salle();
            break;

        case 2:
            this->afficher_films();
            this->afficher_salle();
            this->ajouter_seance();
            break;

        case 3:
            this->afficher_seances();
            break;

        case 4:
            this->vente_place();
            break;

        case 5:
            this->supprimer_seance();
            break;

        case 6:
            std::cout << "Entrez le nom du fichier pour importer les films : ";
            std::getline(std::cin, nom_fic);
            std::getline(std::cin, nom_fic);
            this->maj_films(nom_fic);
            break;

        case 7:
            std::cout << this->nb_places_vendues() << " places vendues à ce jour." << std::endl;
            break;

        case 8:
            this->supprimer_film();
            break;

        case 9:
            this->ecrire_film();
            this->ecrire_seances();
            std::cout << "Au revoir." << std::endl;
            return;

        default:
            break;
        }
    }
}