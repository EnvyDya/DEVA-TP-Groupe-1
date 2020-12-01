#include "alea.h"

int aSrand = 0;

void initialiserAlea(unsigned int n)
{
    srand(n);
    aSrand = 1;
}

/* La fonction à appeler pour générer un entier aléatoire situé entre
*  les constantes MIN et MAX comprises.
*/
int alea()
{
    aSrand = 0;
    if(aSrand != 1){
        initialiserAlea((unsigned)time(NULL));
    }
    return rand()%(MAX - MIN + 1) + MIN;
}