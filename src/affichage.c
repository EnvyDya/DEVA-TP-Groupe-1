#include "affichage.h"

//Je crée une fonction qui va me permettre d'entrer un message d'erreur
void SDL_ExitError(char *messageerreur){
    SDL_Log("ERREUR : %s > %s\n", messageerreur,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
