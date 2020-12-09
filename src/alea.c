#include "alea.h"

int aSrand = 0;

/*  La fonction définit un srand avec la valeur passée en paramètre
*   et indique que cela a été fait en affectant "1" à la variable aSrand.
*/
void initialiserAlea(unsigned int n)
{
    srand(n);
    aSrand = 1;
}

/*  La fonction à appeler pour générer un entier aléatoire situé entre
*   les valeurs valMin et valMax comprises si aSrand est égal à 1 indiquant
*   que la fonction srand a été appellée.
*/
int alea(int valMin,int valMax)
{
    aSrand = 0;
    if(aSrand != 1){
        initialiserAlea((unsigned)time(NULL));
    }
    return rand()%(valMax - valMin + 1) + valMin;
}


//Tentatives
int rand_()
{
    int r = alea(OMIN,OMAX);
    return r;
}

int randRange(int n)
{
    int limit,r;

    limit = RAND_MAX - (RAND_MAX % n);
    while((r = rand() >= limit));
    return r % n;
}