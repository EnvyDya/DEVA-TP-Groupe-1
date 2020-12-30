#ifndef _ALEA_
#define _ALEA_

#include <stdlib.h>
#include <time.h>

#define MAX_TAB_ALEA 10

time_t tps;

//La fonction prend en paramètre les bornes de l'intervalle dans lequel on veut générer un nombre aléatoire.
int alea(int borneInf,int borneSup);

#endif