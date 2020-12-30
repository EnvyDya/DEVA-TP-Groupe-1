#ifndef SPRITE_
#define SPRITE_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

//Définition de la taille de l'écran
#define Largeur 1280
#define Hauteur 720

    //Création d'une fonction d'erreur lors de l'exécution
    void SDL_ExitError(char *messageerreur);
    
    //Cette fonction envoie un message d'erreur si la création du rendu échoue
    void SDL_ExitErrorWindowRender(char* messageerreur, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction est une fonction permettant de laisser la fenêtre ouverte tant que la fenêtre n'est pas fermée manuellement
    void SDL_Pause_Fenetre(void);

    //Cette fonction permet d'afficher un rendu plein écran de l'image
    void affichageRendu(char* cheminImage, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction permet d'afficher un rendu image à une position précise de l'écran
    void affichageRenduCoordonnees(char* cheminImage, SDL_Window *fenetre, SDL_Renderer *rendu, int x, int y);

    //cette fonction permet d'afficher un rendu texte à une position précise de l'écran
    void SDL_affichageTexte(char* texte, SDL_Window *fenetre, SDL_Renderer *rendu, int x, int y);

    //cette fonction est la traduction SDL de partieSolo
    int SDL_partieSolo(int difficulte, SDL_Window *fenetre, SDL_Renderer *rendu);

    //cette fonction est la traduction SDL de partie
    int SDL_partie(SDL_Window *fenetre, SDL_Renderer *rendu);

    //cette fonction est la traduction SDL de afficheGrid
    void SDL_afficheGrid(SDL_Window *fenetre, SDL_Renderer *rendu);

    //cette fonction est la traduction SDL de avance
    bool SDL_avance(int id, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction est la traduction SDL de tour
    void SDL_tour(int id, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction est la traduction SDL de tourOrdi
    void SDL_tourOrdi(int difficulte,SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction est la traduction SDL de useCapa
    void SDL_useCapa(int id, int n, SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction est la traduction SDL de useCapaOrdi
    void SDL_useCapaOrdi(int difficulte,int n,SDL_Window *fenetre, SDL_Renderer *rendu);

    //Cette fonction permet d'afficher le menu du jeu, et de choisir de commencer une partie. 
    void SDL_Menu();
#endif