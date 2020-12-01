#include "alea.h"

int appelle_srand(){
    return 0;
}

void initialiser_aleat(unsigned int n)
{
    srand(n);
    int a_srand = appelle_srand();
    a_srand = 1;
}

/* La fonction à appeler pour générer un entier aléatoire situé entre
*  les constantes MIN et MAX comprises.
*/
int alea()
{
    int a_srand = appelle_srand();
    if(a_srand != 1){
        initialiser_aleat((unsigned)time(NULL));
    }
    return rand()%(MAX-MIN+1) + MIN;
}