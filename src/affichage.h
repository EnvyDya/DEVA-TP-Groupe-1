#ifndef SPRITE_
#define SPRITE_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define Largeur 1280
#define Hauteur 720

    //Création d'une fonction d'erreur lors de l'exécution
    void SDL_ExitError(char *messageerreur);
    
    //Cette fonction envoie un message d'erreur si la création du rendu échoue
    void SDL_ExitErrorWindowRender(char* messageerreur, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction est une fonction permettant de laisser la fenêtre ouverte tant que la fenêtre n'est pas fermée manuellement
    void SDL_Pause_Fenetre(void);

    void affichageRendu(char* cheminImage, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction permet d'afficher le menu du jeu
    void SDL_Menu();
#endif