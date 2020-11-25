#ifndef _BOUGE_
#define _BOUGE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 6

/*
*   Une case de tableau a une présence ou non de murs.
*   Ces murs peuvent empêcher le déplacement du joueur (pour le retenir dans la carte ou le gêner).
*   La case peut aussi contenir un joueur. 
*   C'est dans ces cases que les tests de victoire seront fait.
*   Enfin la case peut contenir une capacité à ramasser.
*/
typedef struct{
    bool murEst;
    bool murNord;
    bool murSud;
    bool murOuest;

    Joueur joueur;
    //Capacite capacite;
}Case;

/*
*   Un joueur possède une orientation.
*   Orientation Nord : 0
*   Orientation Est : 1
*   Orientation Sud : 2
*   Orientation Ouest : 3
*
*   Il possède aussi un id, permettant de le repérer (Joueur 1 et Joueur 2 ou Ordi)
*   Le joueur 1 a pour id 1 et le joueur 2 a pour id 2
*/
typedef struct{
    int orientation;
    short int id;
    //Capacite *capacite;
}Joueur;

void creaTab(Case tab[SIZE][SIZE]); //Fonction qui initialise le tableau en début de partie

void tourne(Joueur *j, int dir); //Fonction qui fait tourner un joueur

#endif