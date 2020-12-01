#include "alea.h"

int aSrand = 0;

void initialiserAlea(unsigned int n)
{
    srand(n);
    aSrand = 1;
}

/* La fonction à appeler pour générer un entier aléatoire situé entre
*  les valeurs valMin et valMax comprises.
*/
int alea(int valMin,int valMax)
{
    aSrand = 0;
    if(aSrand != 1){
        initialiserAlea((unsigned)time(NULL));
    }
    return rand()%(valMax - valMin + 1) + valMin;
}