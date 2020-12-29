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

void affichageRenduCoordonnees(char* cheminImage, SDL_Window *fenetre, SDL_Window *rendu, int x, int y){
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

    rectangleMenu.x = x;
    rectangleMenu.y = y;
    
    //Affichage de l'image du menu
    if(SDL_RenderCopy(rendu, textureMenu, NULL, &rectangleMenu)!=0){
        SDL_ExitErrorWindowRender("Erreur lors de l'affichage des textures", fenetre, rendu);
    }
    //Rendu :
    SDL_RenderPresent(rendu);
}

void SDL_affichageTexte(char* texte, SDL_Window *fenetre, SDL_Renderer *rendu, int x, int y){

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
                                                    SDL_partiesolo(2,fenetre,rendu);
                                                case SDLK_3 :
                                                    SDL_partiesolo(3,fenetre,rendu);
                                            }
                                        case SDLK_2 ://Jeu multi choisi
                                            SDL_partie(fenetre,rendu);
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
int SDL_partieSolo(int difficulte, SDL_Window *fenetre, SDL_Renderer *rendu){
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

void SDL_afficheGrid(SDL_Window *fenetre, SDL_Renderer *rendu){
    for(int i = 0; i<SIZE; i++){
        affichageRendu("ecranjeu.bmp",fenetre,rendu);
        //Pour chaque case on teste s'il y a un mur/un joueur ou non
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.orientation == 0){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotoridosbleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("sumotoridosrouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                    printf("^");
                }else if(t[j][i].joueur.orientation == 1){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotoriestbleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("sumotoriestrouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                    printf(">");
                }else if(t[j][i].joueur.orientation == 2){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotorifacebleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("sumotorifacerouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                    printf("v");
                }else if(t[j][i].joueur.orientation == 3){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("sumotoriouestbleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("sumotoriouestrouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                    printf("<");
                }
            }else if(t[j][i].capa != NULL){
                affichageRenduCoordonnees("capa.bmp",fenetre,rendu,(100*j+350),(100*i+70));
            }
            if(t[j][i].murEst){
                affichageRenduCoordonnees("murvertical.bmp",fenetre,rendu,100*j+430,100*i+60);
            }else if (t[j][i].murOuest){
                affichageRenduCoordonnees("murvertical.bmp",fenetre,rendu,100*j+340,100*i+60);
            }else if (t[j][i].murNord){
                affichageRenduCoordonnees("murhorizontal.bmp", fenetre,rendu,j*100+340,i*100+60);
            }else if (t[j][i].murSud){
                affichageRenduCoordonnees("murhorizontal.bmp",fenetre,rendu,j*100+340,i*100+150);
            }
        }
    }   
}

bool SDL_avance(int id){
    //On crée un posX et posY permettant de stocker l'emplacement du joueur
    int posX = 0, posY = 0;
    Joueur p;
    //On recherche la position du joueur j et on le sauvegarde (orientation, et id).
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == id){
                    posX = j;
                    posY = i;
                    p = t[j][i].joueur;
                    break;
                }
            }
        }
    }
    
    //On regarde l'orientation du joueur pour agir en conséquence    
    switch (p.orientation)
    {
    case 0:
        //Dans chaque cas, on vérifie qu'un mur n'empêche pas l'action
        if(!t[posX][posY].murNord){
            t[posX][posY-1].joueur = p;
            t[posX][posY-1].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX][posY-1].capa != NULL){
                capacite *capa = t[posX][posY-1].capa;
                printf("Capacite %d ramassee !\n", capa->type+1);
                t[posX][posY-1].capa = NULL;
                capacite *courant = t[posX][posY-1].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            //Si un mur bloque l'action, on renvoie false et on ne fait pas bouger le joueur.
            return false;
        }
        break;
    
    case 1:
        if(!t[posX][posY].murEst){
            t[posX+1][posY].joueur = p;
            t[posX+1][posY].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX+1][posY].capa != NULL){
                capacite *capa = t[posX+1][posY].capa;
                printf("Capacite %d ramassee !\n", capa->type+1);
                t[posX+1][posY].capa = NULL;
                capacite *courant = t[posX+1][posY].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            return false;
        }
        break;

    case 2:
        if(!t[posX][posY].murSud){
            t[posX][posY+1].joueur = p;
            t[posX][posY+1].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX][posY+1].capa != NULL){
                capacite *capa = t[posX][posY+1].capa;
                printf("Capacite %d ramassee !\n", capa->type+1);
                t[posX][posY+1].capa = NULL;
                capacite *courant = t[posX][posY+1].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            return false;
        }
        break;
    case 3:
        if(!t[posX][posY].murOuest){
            t[posX-1][posY].joueur = p;
            t[posX-1][posY].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX-1][posY].capa != NULL){
                capacite *capa = t[posX-1][posY].capa;
                printf("Capacite %d ramassee !\n", capa->type+1);
                t[posX-1][posY].capa = NULL;
                capacite *courant = t[posX-1][posY].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            return false;
        }
        break;
    }
}