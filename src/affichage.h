#ifndef SPRITE_
#define SPRITE_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define L=1280
#define h=720

    void SDL_ExitError(char *messageerreur);
    
    void SDL_ExitErrorWindowRender(char* messageerreur, SDL_Window *fenetre, SDL_Renderer *rendu);

    void SDL_Menu();
#endif
