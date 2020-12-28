#include "affichage.h"
#include <stdio.h>
#include <stdbool.h>
#include "bouge.h"
#include "alea.h"
#include "partie.h"

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
                
                case SDL_KEYDOWN :{
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE :
                            stop = true;

                        case SDLK_1 :{
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/reglesjeu.bmp",fenetre,rendu);
                            bool retour = false;
                            do {
                                while(SDL_PollEvent (&event)){
                                    switch (event.key.keysym.sym){
                                        case SDLK_m :
                                            retour=true;

                                        case SDLK_ESCAPE :
                                            retour=true;

                                        case SDL_QUIT :
                                            retour = true;

                                    }
                                }
                            }while(!retour);
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/menujeu.bmp",fenetre,rendu);
                        }
                        case SDLK_p :
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/modesjeu.bmp",fenetre,rendu);
                            bool retour = false;
                            do {
                                while(SDL_PollEvent (&event)){
                                    switch (event.key.keysym.sym){
                                        case SDLK_m :
                                            retour=true;

                                        case SDLK_0: //Jeu solo choisi
                                            switch(event.key.keysym.sym){
                                                case SDLK_2 :
                                                    partiesolo(2);
                                                case SDLK_3 :
                                                    partiesolo(3);
                                            }
                                        case SDLK_2 ://Jeu multi choisi
                                            partie();
                                        case SDLK_ESCAPE :
                                            retour=true;

                                        case SDL_QUIT :
                                            retour = true;
                                    }
                                }
                            }while(!retour);
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/menujeu.bmp",fenetre,rendu);
                            bool stop = false;
                    }   
                }   
            }
        }   
    }
    while(!stop);
}
int SDL_partieSolo(int difficulte){
    int idJoueur = 2;
    if(difficulte == 2){
        initTab();
        bool gagne = false;
        int cpJoueur = 0;
        while(!gagne){
            if(idJoueur == 1){
                idJoueur++;
                tourOrdi(difficulte);
            } else {
                idJoueur--;
                tour(idJoueur);
            }
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[i][j].joueurPresent){
                        cpJoueur++;
                    }
                }
            }
            if(cpJoueur == 1){
                gagne = true;
            }
            cpJoueur = 0;
        }
    } else if(difficulte == 3){
        initTabMurs();
        bool gagne = false;
        int cpJoueur = 0;
        while(!gagne){
            if(idJoueur == 1){
                idJoueur++;
                tourOrdi(difficulte);
            } else {
                idJoueur--;
                tour(idJoueur);
            }
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[i][j].joueurPresent){
                        cpJoueur++;
                    }
                }
            }
            if(cpJoueur == 1){
                gagne = true;
            }
            cpJoueur = 0;
        }
    }

    afficheGrid();
    switch (idJoueur){
        case 1 :
            affichageRendu("victoirejoueur1.bmp",&fenetre,&rendu);
        case 2 :
            affichageRendu("victoirejoueur2.bmp",&fenetre,&rendu);
    }
    return idJoueur;
}

void SDL_afficheGrid(){
    for(int i = 0; i<SIZE; i++){
        affichageRendu("ecranjeu.bmp",fenetre,rendu);
        //Pour chaque case on teste s'il y a un mur/un joueur ou non
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.orientation == 0){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotoridosbleu.bmp",fenetre,rendu,);
                    }else{
                        affichageRenduCoordonnees("sumotoridosrouge.bmp",fenetre,rendu,);
                    }
                    printf("^");
                }else if(t[j][i].joueur.orientation == 1){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotoriestbleu.bmp",fenetre,rendu,x,y);
                    }else{
                        affichageRenduCoordonnees("sumotoriestrouge.bmp",fenetre,rendu,x,y);
                    }
                    printf(">");
                }else if(t[j][i].joueur.orientation == 2){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotorifacebleu.bmp",fenetre,rendu,x,y);
                    }else{
                        affichageRenduCoordonnees("sumotorifacerouge.bmp",fenetre,rendu,x,y);
                    }
                    printf("v");
                }else if(t[j][i].joueur.orientation == 3){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotoriouestbleu.bmp",fenetre,rendu,x,y);
                    }else{
                        affichageRenduCoordonnees("sumotoriouestrouge.bmp",fenetre,rendu,x,y);
                    }
                    printf("<");
                }
            }else if(t[j][i].capa != NULL){
                affichageRenduCoordonnees("capa.bmp",fenetre,rendu,x,y);
            }
            else{
                printf(" ");
            }
            if(t[j][i].murEst){
                printf("|");
            }else{
                printf(" ");
            }
        }
        //Même chose pour les murs sud
        printf("  ");
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].murSud == true){
                printf("---");
            }else{
                printf("   ");
            }
        }
        printf("\n");
    }
    printf("\n");
}