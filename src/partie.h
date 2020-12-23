#ifndef _PARTIE_
#define _PARTIE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Une partie est constituée de plusieurs tours.
 * Pour qu'une partie se termine, il faut qu'un joueur en écrase un autre (autrement dit qu'il n'y ait qu'un seul joueur sur la grille).
 * Si une partie se termine, on peut récupérer l'id du vainqueur qui sera le dernier sur la grille.
 * On retourne alors cet id.
 */

int partie();

/*
* Comme dit au dessus, une partie a plusieurs tours.
* Chaque tour renverra un booleen précisant si une victoire est là.
* On entre en paramètre l'id du joueur pour pouvoir faire les actions associées sur lui.
*/
void tour(int id);


/*
* La structure est similaire à "tour" mais est effectué pour le joueur "ordinateur"
*/
void tourOrdi(int id);

/*
* La fonction possède la même structure que partie() mais met en place un joueur contre l'"ordinateur".
*/
int partieSolo();

#endif