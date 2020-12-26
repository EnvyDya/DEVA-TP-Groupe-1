#include "affichage.h"
#include <stdio.h>
#include <stdbool.h>

//Je crée une fonction qui va me permettre d'entrer un message d'erreur

void SDL_ExitError(char*messageerreur){
    SDL_Log("ERREUR : %s > %s\n", messageerreur,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_ExitErrorWindowRender(char* messageerreur, SDL_Window *fenetre, SDL_Renderer *rendu){
    SDL_Log("ERREUR : %s > %s\n", messageerreur,SDL_GetError());
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
//Création d'une fonction permettant de laisser la fenêtre ouverte tant qu'elle n'est pas fermée manuellement par l'utilisateur
void SDL_Pause_Fenetre(void){
    SDL_Event event;
    bool stop = false;
    do{
        while (SDL_PollEvent (&event)){
            if (event.type == SDL_QUIT){
                stop = true;
            }
        }
    }
    while (!stop);
}

void affichageRendu(char* cheminImage, SDL_Window *fenetre, SDL_Renderer *rendu){
        SDL_Surface *surfaceMenu = NULL;
    SDL_Texture *textureMenu = NULL;

    surfaceMenu = SDL_LoadBMP(cheminImage);

    if(surfaceMenu == NULL){
        SDL_ExitErrorWindowRender("La surface n'a pas pu être créée.", fenetre, rendu);
    }

    textureMenu = SDL_CreateTextureFromSurface(rendu,surfaceMenu);
    SDL_FreeSurface(surfaceMenu);
    if(textureMenu == NULL){
        SDL_ExitErrorWindowRender("La texture n'a pas pu être créée.", fenetre, rendu);
    }

    //Création du rectangle pour afficher la texture
    SDL_Rect rectangleMenu;

    //Je charge l'image dans la mémoire
    if(SDL_QueryTexture(textureMenu, NULL, NULL, &rectangleMenu.w,&rectangleMenu.h)!=0){
        SDL_ExitErrorWindowRender("Erreur pendant le chargement de la texture", fenetre, rendu);
    }

    rectangleMenu.x = (Largeur - rectangleMenu.w)/2;
    rectangleMenu.y = (Hauteur - rectangleMenu.h)/2;
    
    //Affichage de l'image du menu
    if(SDL_RenderCopy(rendu, textureMenu, NULL, &rectangleMenu)!=0){
        SDL_ExitErrorWindowRender("Erreur lors de l'affichage des textures", fenetre, rendu);
    }
    //Rendu :
    SDL_RenderPresent(rendu);
}

void SDL_Menu(){
    //Pointeurs à déclarer :
    SDL_Window *fenetre = NULL; 
    SDL_Renderer *rendu = NULL;
    //Initialisation de la SDL

    //Si l'initialisation n'est pas à 0, cela veut dire qu'elle présente une erreur. Alors, un message d'erreur s'affiche.
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_ExitError("Erreur lors de l'initialisation de la SDL");
    }

    //Je crée une fenêtre avec son nom, la position en x, la position en y, sa largeur, sa hauteur, et son mode d'affichage)
    fenetre = SDL_CreateWindow("Tachi-ai !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280,720,0); 

    //Encore une fois, je teste s'il n'y a pas eu d'erreur dans la création de la fenêtre.
    if(fenetre == NULL){
        SDL_ExitError("Erreur lors de la création de l'écran");
    }

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
    if(rendu == NULL){
        SDL_ExitError("Erreur lors de la création du rendu");
    }

    affichageRendu("assets/menujeu.bmp",fenetre,rendu);
    //Cas de passage aux autres affichages du menu
    SDL_Event event;
    bool stop = false;
    do {
        while (SDL_PollEvent (&event)){
            switch (event.type){
                case SDL_QUIT :
                    stop = true;
                
                case SDL_KEYDOWN :
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE :
                            stop = true;

                        case SDLK_1 :{
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/reglesjeu.bmp",fenetre,rendu);

                            switch (event.key.keysym.sym){
                                case SDLK_m :
                                    SDL_RenderClear(rendu);
                                    affichageRendu("assets/menujeu.bmp",fenetre,rendu);
                            }
                        }
                        case SDLK_SPACE :
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/modesjeu.bmp",fenetre, rendu);
                    }
            }
        }   
    }
    while(!stop);
}