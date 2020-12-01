#ifndef _ALEA_
#define _ALEA_

#include <stdlib.h>
#include <time.h>

/* Les constantes MIN et MAX définissent les valeurs extrêmes attribuées à
*  chaque orientation qu'un joueur peut avoir.
*/
#define MIN 0
#define MAX 3

int appelle_srand();

void initialiser_aleat(unsigned int n);

int alea();

#endif