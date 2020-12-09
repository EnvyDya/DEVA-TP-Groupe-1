#include "bouge.h"
#include <SDL.h>

int main(int argc, char **argv){
    initTab();
    afficheGrid();
    avance(1);
    afficheGrid();
    avance(1);
    afficheGrid();
    avance(1);
    afficheGrid();
    tourne(2, -1);
    afficheGrid();
    avance(2);
    afficheGrid();
    if(!avance(2)){
        printf("Mouvement impossible, il y a un mur.\n");
    }
    tourne(1, -1);
    afficheGrid();
    useCapa(1, 1);
    afficheGrid();
    useCapa(2, 1);
    afficheGrid();
    useCapa(2, 1);
    return (0);
}
//Work in progress
#if 0 
#include "affichage.h"

int main(int argc, char **argv){
    //Pointeurs à déclarer :
    SDL_Window *fenetre = NULL; 
    SDL_Renderer *rendu = NULL;
    //Initialisation de la SDL

    //Si l'initialisation n'est pas à 0, cela veut dire qu'elle présente une erreur. Alors, un message d'erreur s'affiche.
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_ExitError("Erreur lors de l'initialisation de la SDL");
    }

    //Création de fenêtre 

    //J'initialise la SDL en activant la fonction vidéo de la SDL, pour diffuser une image.
    SDL_Init(SDL_INIT_VIDEO);

    //Je crée une fenêtre avec son nom, la position en x, la position en y, sa largeur, sa hauteur, et son mode d'affichage)
    fenetre = SDL_CreateWindow("Tachi-ai !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280,720,0); 

    //Encore une fois, je teste s'il n'y a pas eu d'erreur dans la création de la fenêtre.
    if(fenetre == NULL){
        SDL_ExitError("Erreur lors de la création de l'écran");
    }
    /*----------------------------------------------------------------------------------*/

    //Création rendu
    //On veut créer un rendu dans la fenêtre fenetre, et on veut que celui ci soit rendu avec le processeur, par conséquent on utilise SOFTWARE.
    rendu = SDL_CreateRenderer(fenetre, -1,SDL_RENDERER_SOFTWARE);
    if(rendu==NULL){
        SDL_ExitError("Erreur dans la création du rendu");
    }

    //On utilise la fonction SDL_RenderPresent pour passer le rendu dans la fenêtre
    SDL_RenderPresent(rendu);

    //Charger des images dans ma fenêtre
    SDL_Surface *imagetest = NULL;
    
    //Afficher ma fenêtre pour tester mes rendus pendant 3 secondes (temporaire)
    SDL_Delay(3000);

    /*----------------------------------------------------------------------------------*/
    // Permet de libérer la mémoire du rendu
    SDL_DestroyRenderer(rendu);
    // Permet de libérer la mémoire de la fenêtre
    SDL_DestroyWindow(fenetre);
    // Permet d'arrêter la SDL.
    SDL_Quit();

    return EXIT_SUCCESS;
}
#endif