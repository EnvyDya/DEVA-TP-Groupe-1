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
/*
 *  On considère en paramètre un tableau d'entier items contenant les valeurs qui doivent sortir du tirage de la fontion et un tableau d'entier contenant le pourcentage
 *  de chance d'apparition de la valeur correspondante à la case dans items.
 *  On vérifie que la somme des pourcentages du tableau est bien égale à 100.
 *  On tire un nombre aléatoire entre 1 et 100 qui va déterminer quelle valeur dans items va être renvoyée.
 *  On teste alors si le nombre tiré est bien compris dans l'intervalle borné avec le pourcentage précédent et le pourcentage suivant.
 */
int pondAlea(int items[],int pourcentage[])
{
    int sommePourcents = 0;
    for(int i=0;i<sizeof(pourcentage);i++){
        sommePourcents += pourcentage[i];
    }
    if(sommePourcents != 100){
        exit(EXIT_FAILURE);
    }
    int pond = alea(1,100);

    //Partie à améliorer
    if(pond>=1 && pond<=25){
        return items[0];
    } else if(pond>=26 && pond<=50) {
        return items[1];
    } else if (pond>=51 && pond<=75){
        return items[2];
    } else if (pond>=76 && pond<=100){
        return items[3];
    }
}