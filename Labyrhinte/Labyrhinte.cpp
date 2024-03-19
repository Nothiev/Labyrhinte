#include <iostream>
#include <vector>
#include <fstream> 
#include <string>

using namespace std;
// Position du joueur
vector<string> labyrinthe;
int joueurX = -1;
int joueurY = -1;

// Dimensions du labyrinthe
const int WIDTH = 10;
const int HEIGHT = 5;

// Directions de déplacement
enum Direction { HAUT, BAS, DROITE, GAUCHE };

void chargerLabyrintheDepuisFichier(const string& cheminFichier) {
    ifstream fichier(cheminFichier);
    string ligne;

    if (fichier.is_open()) {
        while (getline(fichier, ligne)) {
            labyrinthe.push_back(ligne);
        }
        fichier.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier de la carte." << endl;
    }
}



// Fonction pour trouver la position de l'entrée (E) et initialiser le joueur
void trouverEtInitialiserEntree() {
    for (int y = 0; y < labyrinthe.size(); y++) {
        size_t x = labyrinthe[y].find('E');
        if (x != string::npos) {
            joueurX = static_cast<int>(x);
            joueurY = y;
            labyrinthe[y][x] = 'P'; // Marque le joueur à l'entrée
            break;
        }
    }
}

void afficherLabyrinthe() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            cout << labyrinthe[y][x];
        }
        cout << endl;
    }
}

bool deplacerJoueur(Direction dir) {
    int newX = joueurX, newY = joueurY;

    switch (dir) {
    case HAUT: newY--; break;
    case BAS: newY++; break;
    case DROITE: newX++; break;
    case GAUCHE: newX--; break;
    }

    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT || labyrinthe[newY][newX] == '#') {
        return false; // Empêche le joueur de passer à travers les murs ou de sortir du labyrinthe
    }

    // Mise à jour de la position du joueur dans le labyrinthe
    labyrinthe[joueurY][joueurX] = ' ';
    joueurX = newX;
    joueurY = newY;
    if (labyrinthe[newY][newX] == 'S') {
        cout << "Gagné!" << endl;
        return true; // Retourner true ici signifie un mouvement réussi
    }
    labyrinthe[joueurY][joueurX] = 'P';
    return true;
}

int main() {
   chargerLabyrintheDepuisFichier("C:\\Users\\arnau\\OneDrive\\Documents\\Labyrhinte\\labyrhinte.txt");
    trouverEtInitialiserEntree();

    char input;
    bool finDuJeu = false;

    while (!finDuJeu) {
        afficherLabyrinthe();
        cout << "Déplacez-vous (haut, bas, droite, gauche): ";
        cin >> input;

        switch (input) {
        case 'h': deplacerJoueur(HAUT); break;
        case 'b': deplacerJoueur(BAS); break;
        case 'd': deplacerJoueur(DROITE); break;
        case 'g': deplacerJoueur(GAUCHE); break;
        default: cout << "Entree invalide." << endl; break;
        }

        // Ajouter ici la vérification pour voir si le joueur a atteint la sortie 'S'
        if (labyrinthe[joueurY][joueurX] == 'S') {
            cout << "Felicitations ! Vous avez trouve la sortie." << endl;
            finDuJeu = true;
        }
    }

    return 0;
}
