#include "bouge.h"
#include <SDL.h>

int main(int argc, char **argv){
    Case t[SIZE][SIZE];
    initTab(t);
    afficheGrid(t);
    avance(1, t);
    avance(1, t);
    avance(1, t);
    tourne(2, -1, t);
    avance(2, t);
    if(!avance(2, t)){
        printf("Mouvement impossible, il y a un mur.");
    }
    tourne(1, -1, t);
    printf("\n");
    afficheGrid(t);
    return (0);
}