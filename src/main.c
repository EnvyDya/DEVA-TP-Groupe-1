#include "bouge.h"
#include <SDL.h>

int main(int argc, char **argv){
    Case t[SIZE][SIZE];
    initTab(t);
    afficheGrid(t);
    return (0);
}