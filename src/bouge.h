#ifndef _BOUGE_
#define _BOUGE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 6

/*
*   Définition du type capacite, il possède un entier qui détermine le type de capacité.
*   (0 pour un mur, 1 pour reculer l'adversaire, 2 pour faire demi-tour, 3 pour rejouer un tour).
*/
typedef struct capacite capacite;

struct capacite{
    int type;
    capacite *s;
};

/*
*   Liste chaînée de capacités, pointe sur la dernière capacité ramassée.
*/
typedef struct Liste_Capacites{
    capacite *p;
}Liste_Capacites;

/*
*   Un joueur possède une orientation.
*   Orientation Nord : 0
*   Orientation Est : 1
*   Orientation Sud : 2
*   Orientation Ouest : 3
*
*   Il possède aussi un id, permettant de le repérer (Joueur 1 et Joueur 2 ou Ordi).
*   Le joueur 1 a pour id 1 et le joueur 2 a pour id 2.
*/
typedef struct{
    int orientation;
    short int id;
    Liste_Capacites capacite;
}Joueur;

/*
*   Une case de tableau a une présence ou non de murs.
*   Ces murs peuvent empêcher le déplacement du joueur (pour le retenir dans la carte ou le gêner).
*   La case peut aussi contenir un joueur. Un booléen y est associé pour savoir si un joueur est dedans.
*   C'est dans ces cases que les tests de victoire seront fait.
*   Enfin la case peut contenir une capacité à ramasser.
*/
typedef struct{
    bool murEst;
    bool murNord;
    bool murSud;
    bool murOuest;

    bool joueurPresent;
    Joueur joueur;
    capacite *capa;
}Case;

Case t[SIZE][SIZE];

void initTab(); //Fonction qui initialise le tableau en début de partie.

Liste_Capacites creaListe(); //Fonction qui crée une liste de pouvoirs au début de la partie.

void tourne(int id, int dir); //Fonction qui fait tourner un joueur.

void afficheGrid(); //Fonction qui affiche le tableau, avec ses murs et ses joueurs.

bool avance(int j); //Fonction qui fait avancer le joueur (repéré par son id dans j).

void useCapa(int id, int n); //Fonction qui permet au joueur (repéré par son id) d'utiliser une capacité n (n entré au clavier).
#endif