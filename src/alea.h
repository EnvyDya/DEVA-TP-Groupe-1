#ifndef _ALEA_
#define _ALEA_

#include <stdlib.h>
#include <time.h>

/* Les constantes OMIN et OMAX définissent les valeurs extrêmes attribuées à
*  chaque orientation qu'un joueur peut avoir.
*/
#define OMIN 0
#define OMAX 3

int aSrand;

void initialiserAlea(unsigned int n);

int alea(int valMin,int valMax);

#endif