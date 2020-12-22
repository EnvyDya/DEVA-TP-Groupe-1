#include "alea.h"

/*
 *  La fonction prend en paramètre les bornes de l'intervalle dans lequel on veut générer un nombre aléatoire.
 *  On retourne le résultat du modulo entre rand() et la différence des bornes de l'intervalle à laquelle on ajoute 1 afin de prendre le cas où 0 est une borne.
 */
int alea(int borneMin,int borneMax){
    return rand()%((borneMax-borneMin)+1);
}