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
        int capa, c1 = 0, c2 = 0, c3 = 0, c4 = 0;
        //On compte d'abord le nombre de capacités en stock
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(t[j][i].joueurPresent){
                    if(t[j][i].joueur.id == id){
                        //On a trouvé le bon joueur
                        capacite *cap = t[j][i].joueur.capacite.p;
                        //On compte chaque capacité
                        while(cap != NULL){
                            switch (cap->type)
                            {
                                case 0:
                                    c1++;
                                    break;
                                
                                case 1:
                                    c2++;
                                    break;

                                case 2:
                                    c3++;
                                    break;
                                
                                case 3:
                                    c4++;
                                    break;
                                
                            }
                            cap = cap->s;
                        }
                        break;
                    }
                }
        }
    }
        printf("Liste des capacites :\n1 - Poser un mur (Dispo : %d)\n2 - Reculer l'adversaire (Dispo : %d)\n3 - Demi-tour (Dispo : %d)\n4 - 2 tours (Dispo : %d)\nQue voulez vous faire ? ", c1, c2, c3, c4);
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

void tourOrdi(){
    //On considère que l'id de l'ordinateur doit être 2.
        int probCapa,action,tourner;

        afficheGrid();

        //L'ordinateur a une chance sur 3 d'utiliser une capacité.
        probCapa = rand()%3;
        if(probCapa == 1){
            //La capacité à utiliser est défini de manière pseudo-aléatoire.
            int capa = alea(1,4);
            useCapaOrdi(capa-1);
            afficheGrid();
        }


        //On défini l'action à réaliser, 75% de chances d'avancer et 25% de chances de tourner.
        action = rand()%4;
        if(action >= 0 && action <= 2){
            avance(2);
        } else {
            /*
            * 0: tourner à gauche
            * 1: tourner à doite
            */
            tourner = alea(0,1);
            if(tourner == 0){
                tourne(2,-1);
            } else {
                tourne(2,1);
            }
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

bool joueurProche(){
    int xJ,yJ,posX,posY;
    //On cherche le bot sur la grille.
    for(int i = 0;i<SIZE;i++){
        for(int j = 0;i>SIZE;j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == 2){
                    //On a trouvé le bot
                    posX = i;
                    posY = j;
                }
            }
        }
    }
    //On cherche le joueur sur la grille.
    for(int i = 0;i<SIZE;i++){
        for(int j = 0;j<SIZE;j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == 1){
                    //On a trouvé le joueur
                    xJ = j;
                    yJ = i;
                }
            }
        }
    }
    if((xJ == posX) && (yJ == (posY + 1))){
        return true;
    } else if((xJ == posX) && (yJ == (posY -1))){
        return true;
    } else if((xJ == (posX + 1)) && (yJ == posY)){
            return true;
    } else if((xJ == (posX - 1)) && (yJ == posY)){
        return true;
    }
    return false;
}

int partieSolo(){
    initTab();
    bool gagne = false;
    int cpJoueur = 0, idJoueur = 2;
    while(!gagne){
        if(idJoueur == 1){
            idJoueur++;
            tourOrdi();
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
    printf("\n");
    afficheGrid();
    printf("Victoire du joueur %d !", idJoueur);
    return idJoueur;
}

void jeu(){
    printf("Bienvenue dans Tachi-Ai!\nQue voulez vous faire ?\n1 - Jeu multi\n2 - Jeu solo (facile)\n3 - Jeu solo (moins facile)\n");
    int choix, highscore;
    highscore = litVal();
    scanf("%d", &choix);
    switch(choix){
        case 1:
            do{ 
                partie();
                printf("\nVoulez vous rejouer ?\n1 - Oui\n2 - Non\n");
                scanf("%d", &choix);
            }while(choix == 1);
            break;
        case 2:
            {
                int score = 0;
                do{
                    int result;
                    result = partieSolo();
                    if(result == 1){
                        score++;
                        if(score > highscore){
                            ecritVal(score);
                            highscore = score;
                        }
                    }else{
                        score = 0;
                    }
                    printf("\nVoulez vous rejouer ?\n1 - Oui\n2 - Non");
                    scanf("%d", &choix);
                }while(choix == 1);
            }
            break;
        case 3:
            printf("Non implemente");
            break;
        default:
            printf("Veuillez saisir une valeur correcte.\n");
    }
}

void ecritVal(int e){
    FILE *save;
    save = fopen("bin/save.txt", "w");
    fprintf(save, "%d", e);
    fclose(save);   
}

int litVal(){
    FILE *save;
    int highscore;
    save = fopen("bin/save.txt", "r");
    if(save == NULL){
        return 0;
    }
    fscanf(save,"%d", &highscore);
    fclose(save); 
    return highscore;
}