#ifndef _BOUGE_
#define _BOUGE_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    bool joueur;
    bool murEst;
    bool murNord;
    bool murSud;
    bool murOuest;
}Case;

Case tab[6][6];

#endif