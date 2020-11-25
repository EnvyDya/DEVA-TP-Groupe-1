#include "bouge.h"

/*
*   Le tableau est de la forme : t[abscisse][ordonnées].
*   Il est par défaut rempli de vide, mur extérieurs créés.
*   Les deux joueurs sont placés en bas à gauche et en haut à droite.
*   Celui en haut à gauche regarde en bas.
*   Celui en bas à droite regarde en haut.
*/

void creaTab(Case t[SIZE][SIZE]){
    //On met toutes les cases "vides"
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            t[i][j].joueur = NULL;
            t[i][j].murEst = false;
            t[i][j].murNord = false;
            t[i][j].murOuest = false;
            t[i][j].murSud = false;
        }
    }
    //On met les cases extérieures avec leurs murs
    for(int i = 0; i<SIZE; i++){
        t[i][0].murNord = true;
        t[i][SIZE-1].murSud = true;
        t[0][i].murOuest = true;
        t[SIZE-1][i].murEst = true;
    }

    //Création des deux joueurs avec id et orientation
    Joueur j1;
    j1.id = 1;
    j1.orientation = 0;

    Joueur j2;
    j2.id = 2;
    j2.orientation = 2;

    //Placement des joueurs sur la carte
    t[0][SIZE-1].joueur = j1;
    t[SIZE-1][0].joueur = j2;
};


/*
*   Fonction qui fait pivoter le joueur
*   On rentre un pointeur sur joueur ainsi qu'une direction.
*   La direction peut être à -1 (pour tourner à gauche) ou à 1 (pour tourner à droite).
*/
void tourne(Joueur *j, int dir){
    j->orientation = (j->orientation+dir)%4;
}