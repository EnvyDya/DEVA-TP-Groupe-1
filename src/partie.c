#include "partie.h"
#include "bouge.h"
#include "alea.h"

int partie(){
    //On fait un tableau neuf au début d'une partie
    initTab();
    bool gagne = false;
    int cpJoueur = 0, idJoueur = 2;
    while(!gagne){
        //On commence par changer de joueur
        if(idJoueur == 1){
            idJoueur++;
        }else{
            idJoueur--;
        }

        tour(idJoueur);
        //Après un tour, on compte le nombre de joueurs sur le plateau
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(t[i][j].joueurPresent){
                    cpJoueur++;
                }
            }
        }
        //Si on a un joueur (donc qu'il a gagné) alors on notifie la victoire
        if(cpJoueur == 1){
            gagne = true;
        }
        cpJoueur = 0;
    }
    afficheGrid();
    printf("Victoire du joueur %d !", idJoueur);
    return idJoueur;
}

void tour(int id){
    //On affiche la grille au début du tour.
    afficheGrid();
    char choix, retour;   
    printf("Joueur %d.\nVoulez vous utiliser une capacite ? (o/n) ",  id);
    do{
        //O = 79, o = 111, n = 110, N = 78
        scanf(" %c", &choix);
    }while(choix != 79 && choix != 111 && choix != 110 && choix != 78);

    //Cas ou on utilise une capacité
    if(choix == 79 || choix == 111){
        int capa;
        printf("Liste des capacites :\n1 - Poser un mur\n2 - Reculer l'adversaire\n3 - Demi-tour\n4 - 2 tours\nQue voulez vous faire ? ");
        do{
            scanf("%d", &capa);
        }while(capa != 1 && capa != 2 && capa != 3 && capa != 4);
        useCapa(id, capa-1);
        //On affiche la grille après utilisation de capacité 
        afficheGrid();
    }

    //Passage à la gestion classique du tour
    printf("Liste des actions possibles :\nZ - Avancer\nQ - Tourner a gauche\nD - Tourner a droite\nQue voulez vous faire ? ");
    do{
        //z = 122, Z = 90, q = 113, Q = 81, d = 100, D = 68
        scanf(" %c", &choix);
    }while(choix != 122 && choix != 90 && choix != 113 && choix != 81 && choix != 100 && choix != 68);

    if(choix == 122 || choix == 90){
        avance(id);
    }else if(choix == 113 || choix == 81){
        tourne(id, -1);
    }else{
        tourne(id, 1);
    }

    time_t tps;
    srand((unsigned) time(&tps));
    int nbAlea = rand()%10;
    //Une chance sur 10 qu'une nouvelle capacité apparaisse sur la carte
    if(nbAlea == 1){
        //On crée alors une position pour notre nouvelle capacité
        int posX = rand()%SIZE;
        int posY = rand()%SIZE;
        capacite *capa = (capacite *)malloc(sizeof(capacite));
        capa->s = NULL;
        //On génère un type aléatoirement
        capa->type = rand()%4;
        t[posX][posY].capa = capa;
    }  
}