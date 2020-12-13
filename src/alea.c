#include "alea.h"

/*
 *  La fonction prend en paramètre les bornes de l'intervalle dans lequel on veut générer un nombre aléatoire.
 *  On fait appel à la fonction srand en plaçant time(NULL) en paramètre afin de modifier la "graine" à chaque appel de la fonction alea.
 *  On stocke ensuite MAX_TAB_ALEA nombres générés pseudo-aléatoirement dans un tableau d'entiers statique.
 *  On affecte à la variable randInt le reste de la division entière d'un nombre généré avec rand() et MAX_TAB_ALEA
 *  On retourne ensuite l'entier stocké de la case du tableau d'indice randInt.
 */
int alea(int borneMin,int borneMax){
    int tempAlea,randInt,tabAlea[MAX_TAB_ALEA];

    srand((unsigned int)time(NULL));
    for(int i;i<MAX_TAB_ALEA;i++){
        tempAlea = rand()%(1 + (borneMax - borneMin));
        tabAlea[i] = tempAlea;
    }
    randInt = rand()%MAX_TAB_ALEA;
    return tabAlea[randInt];
}

//Tentative
int pondAlea(int items[],int pourcentage[])
{
    int somme;
    for(int i=0;i<sizeof(pourcentage);i++){
        somme += pourcentage[i];
    }
    int pond = alea(1,somme);
    for(int i=1;i<sizeof(pourcentage);i++){
        if(pond<=(100+pourcentage[i])%100 && pond>=(100-pourcentage[i])%100){
            return items[i];
        }
    }
}