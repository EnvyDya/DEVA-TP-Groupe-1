#include "partie.h"
#include "affichage.h"
#include <SDL.h>

int main(int argc, char **argv){
    #if 0
    SDL_Surface *ecran = NULL;
    SDL_Surface *menu = NULL;

    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 3;

    //J'appelle la SDL
    SDL_Init(SDL_INIT_VIDEO);

    //J'appelle l'icône du jeu
    SDL_WM_setIcon(IMG_load("Sumotoritest.bmp", NULL));
    ecran = SDL_SetVideoMode(1280,720,32, SDL_SWSURFACE);
    //Je nomme le jeu
    SDL_WM_SetCaption("Tachi-ai !",NULL);

    /*-------------------------*/

    //Création Menu
    menu = IMG_Load("Menu.png");
    positionMenu.x=0;
    positionMenu.y=0;

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
            continuer=0;
            break;

            case SDL_KEYDOWN:
            switch(event.key.keysym.sym){

            }
        }



    }
    #endif
    SDL_Menu();
    /*jeu();*/
    return 0;
 
}
