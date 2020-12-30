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
        printf("Liste des capacites :\n1 - Poser un mur (Dispo : %d)\n2 - Reculer l'adversaire (Dispo : %d)\n3 - Demi-tour (Dispo : %d)\n4 - 2 tours (Dispo : %d)\nQue voulez vous faire ? \n", c1, c2, c3, c4);
        do{
            scanf("%d", &capa);
        }while(capa != 1 && capa != 2 && capa != 3 && capa != 4);
        useCapa(id, capa-1);
        //On affiche la grille après utilisation de capacité 
        afficheGrid();
    }

    //Passage à la gestion classique du tour
    printf("Liste des actions possibles :\nZ - Avancer\nQ - Tourner a gauche\nD - Tourner a droite\nQue voulez vous faire ? \n");
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

void tourOrdi(int difficulte){
    //On considère que l'id de l'ordinateur doit être 2.
        int probCapa,mouv;

        mouv = meilleurMouv();

        if(mouv != 0){
            switch(difficulte){
                case 2:
                    {
                        //L'ordinateur a une chance sur 3 d'utiliser une capacité.
                        probCapa = rand()%3;
                        if(probCapa == 1){
                            //La capacité à utiliser est défini de manière pseudo-aléatoire.
                            int capa = alea(1,4);
                            useCapaOrdi(difficulte,capa-1);
                        }
                        //66% de chances de réaliser le meilleur mouvement
                        int doMouv = rand()%3;
                        if(doMouv == 0 || doMouv == 1){
                            switch(mouv){
                                case 1:
                                    {
                                        avance(2);
                                    }
                                    break;
                                case 2:
                                    {
                                        avance(2);
                                    }
                                    break;
                                case 3:
                                    {
                                        /*
                                        * 0: tourner à gauche
                                        * 1: tourner à doite
                                        */
                                        int tourner = alea(0,1);
                                        if(tourner == 0){
                                            tourne(2,-1);
                                        } else {
                                            tourne(2,1);
                                        }
                                        break;
                                    }

                            }
                        }else{
                            //L'ordinateur a une chance sur 3 d'utiliser une capacité.
                            probCapa = rand()%3;
                            if(probCapa == 1){
                                //La capacité à utiliser est défini de manière pseudo-aléatoire.
                                int capa = alea(1,4);
                                useCapaOrdi(difficulte,capa-1);
                            }
                            //On définit le mouvement à réaliser, 75% de chances d'avancer et 25% de chances de tourner.
                            mouv = rand()%4;
                            if(mouv >= 0 && mouv <= 2){
                                avance(2);
                            } else {
                                /*
                                * 0: tourner à gauche
                                * 1: tourner à doite
                                */
                                int tourner = alea(0,1);
                                if(tourner == 0){
                                    tourne(2,-1);
                                } else {
                                    tourne(2,1);
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    {
                        //L'ordinateur a une chance sur 3 d'utiliser une capacité.
                        probCapa = rand()%2;
                        if(probCapa == 1){
                            //La capacité à utiliser est défini de manière pseudo-aléatoire.
                            int capa = alea(1,4);
                            useCapaOrdi(difficulte,capa-1);
                        }
                        //90% de chances de réaliser le meilleur mouvement
                        int doMouv = rand()%10;
                        if(doMouv >= 0 && doMouv <=8){
                            switch(mouv){
                                case 1:
                                    {
                                        avance(2);
                                    }
                                    break;
                                case 2:
                                    {
                                        avance(2);
                                    }
                                    break;
                                case 3:
                                    {
                                        /*
                                        * 0: tourner à gauche
                                        * 1: tourner à doite
                                        */
                                        int tourner = alea(0,1);
                                        if(tourner == 0){
                                            tourne(2,-1);
                                        } else {
                                            tourne(2,1);
                                        }
                                        break;
                                    }

                            }
                        }else{
                            //L'ordinateur a une chance sur 2 d'utiliser une capacité.
                            probCapa = rand()%2;
                            if(probCapa == 1){
                                //La capacité à utiliser est défini de manière pseudo-aléatoire.
                                int capa = alea(1,4);
                                useCapaOrdi(difficulte,capa-1);
                            }
                            //On définit le mouvement à réaliser, 75% de chances d'avancer et 25% de chances de tourner.
                            mouv = rand()%4;
                            if(mouv >= 0 && mouv <= 2){
                                avance(2);
                            } else {
                                /*
                                * 0: tourner à gauche
                                * 1: tourner à doite
                                */
                                int tourner = alea(0,1);
                                if(tourner == 0){
                                    tourne(2,-1);
                                } else {
                                    tourne(2,1);
                                }
                            }
                        }
                    }
                    break;
            }
        } else {
            //L'ordinateur a une chance sur 3 d'utiliser une capacité.
            probCapa = rand()%3;
            if(probCapa == 1){
                //La capacité à utiliser est défini de manière pseudo-aléatoire.
                int capa = alea(1,4);
                useCapaOrdi(difficulte,capa-1);
            }
            //On définit le mouvement à réaliser, 75% de chances d'avancer et 25% de chances de tourner.
            mouv = rand()%4;
            if(mouv >= 0 && mouv <= 1){
                avance(2);
            } else {
                /*
                * 0: tourner à gauche
                * 1: tourner à doite
                */
                int tourner = alea(0,1);
                if(tourner == 0){
                    tourne(2,-1);
                } else {
                    tourne(2,1);
                }
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

/*
 * La fonction va retourner un entier déterminant le meilleur mouvement à effectuer à faire.
 * 0: Aléatoire
 * 1: Avancer pour écraser
 * 2: Avancer pour séchapper
 * 3: Tourner
 */
int meilleurMouv(){
    int xJoueur,yJoueur,xBot,yBot,orJoueur,orBot;
    //On cherche le bot sur la grille.
    for(int i = 0;i<SIZE;i++){
        for(int j = 0;i>SIZE;j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == 2){
                    //On a trouvé le bot
                    xBot= i;
                    yBot = j;
                    orBot = t[j][i].joueur.orientation;
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
                    xJoueur = j;
                    yJoueur = i;
                    orJoueur = t[j][i].joueur.orientation;
                }
            }
        }
    }
    //On veut tester si le joueur se trouve dans une des cases à proximité du bot.
    if((xJoueur == xBot) && (yJoueur == (yBot + 1))){
        //Si le bot a la même orientation que le joueur, il est préférable d'avancer pour écraser sinon si elles sont égales il est préférable d'avancer pour s'achapper.
        if(orJoueur == ((orBot + 2)%4)){
            return 1;
        } else if(orJoueur == orBot){
            return 2;
        }
    } else if((xJoueur == xBot) && (yJoueur == (yBot -1))){
        if(orJoueur == ((orBot + 2)%4)){
            return 1;
        } else if(orJoueur == orBot){
            return 2;
        }
    } else if((xJoueur == (xBot + 1)) && (yJoueur == yBot)){
        if(orJoueur == ((orBot + 2)%4)){
            return 1;
        } else if(orJoueur == orBot){
            return 2;
        }
    } else if((xJoueur == (xBot - 1)) && (yJoueur == yBot)){
        if(orJoueur == ((orBot + 2)%4)){
            return 1;
        } else if(orJoueur == orBot){
            return 2;
        }
    }

    //On va tester la présence d'un joueur en diagonale.
    if((xJoueur == (xBot - 1) && (yJoueur == (yBot - 1)))){
        if((orJoueur == 1 || orJoueur == 2) && (orBot == 0 || orBot == 3)){
            return 3;
        }
    } else if((xJoueur == (xBot + 1) && (yJoueur == (yBot - 1)))){
        if((orJoueur == 2 || orJoueur == 3) && (orBot == 0 || orBot == 1)){
            return 3;
        }
    } else if((xJoueur == (xBot - 1) && (yJoueur == (yBot + 1)))){
        if((orJoueur == 0 || orJoueur == 1) && (orBot == 2 || orBot == 3)){
            return 3;
        }
    } else if((xJoueur == (xBot + 1) && (yJoueur == (yBot + 1)))){
        if((orJoueur == 0 || orJoueur == 3) && (orBot == 2 || orBot == 1)){
            return 3;
        }
    }

    //Si aucun joueur n'est proche alors aucun mouvement n'est meilleur qu'un autre.
    return 0;
}

int partieSolo(int difficulte){
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

    printf("\n");
    afficheGrid();
    printf("Victoire du joueur %d !", idJoueur);
    return idJoueur;
}

void jeu(){
    printf("Bienvenue dans Tachi-Ai!\nQue voulez vous faire ?\n1 - Jeu multi\n2 - Jeu solo (facile)\n3 - Jeu solo (moins facile)\n");
    int choix, highscore;
    //On récupère la valeur sauvegardée dans le fichier
    highscore = litVal();
    scanf("%d", &choix);
    switch(choix){
        case 1:
            do{ 
                //On lance une partie multijoueur
                partie();
                printf("\nVoulez vous rejouer ?\n1 - Oui\n2 - Non\n");
                scanf("%d", &choix);
            }while(choix == 1);
            break;
        case 2:
            {
                //On initialise le score à 0 en début de partie
                int score = 0;
                int choix2;
                do{
                    //On écrit le score actuel ainsi que le highscore
                    printf("Score : %d\nHighscore : %d\n", score, highscore);
                    int result;
                    //On lance une partie et on stocke le resultat dans le score;
                    result = partieSolo(choix);
                    if(result == 1){
                        //Si c'est le joueur 1, alors on augmente le score
                        score++;
                        //On compare le score au highscore et on sauvegarde le cas échéant
                        if(score > highscore){
                            ecritVal(score);
                            highscore = score;
                        }
                    }else{
                        //Si le joueur a perdu, on remet le score à 0
                        score = 0;
                    }
                    printf("\nVoulez vous rejouer ?\n1 - Oui\n2 - Non\n");
                    scanf("%d", &choix2);
                }while(choix2 == 1);
            }
            break;
        case 3:
            {
                //Même principe que pour le mode solo facile
                int score = 0;
                int choix2;
                do{
                    printf("Score : %d\nHighscore : %d\n", score, highscore);
                    int result;
                    result = partieSolo(choix);
                    if(result == 1){
                        score++;
                        if(score > highscore){
                            ecritVal(score);
                            highscore = score;
                        }
                    }else{
                        score = 0;
                    }
                    printf("\nVoulez vous rejouer ?\n1 - Oui\n2 - Non\n");
                    scanf("%d", &choix2);
                }while(choix2 == 1);
            }
            break;
        default:
            printf("Veuillez saisir une valeur correcte.\n");
    }
}

void ecritVal(int e){
    //On ouvre le fichier en écriture
    FILE *save;
    save = fopen("bin/save.txt", "w");
    //On écrit la valeur dans le fichier
    fprintf(save, "%d", e);
    //On ferme le fichier
    fclose(save);   
}

int litVal(){
    //On ouvre le fichier en lecture
    FILE *save;
    int highscore;
    save = fopen("bin/save.txt", "r");
    if(save == NULL){
        //S'il est vide, alors aucune partie n'a été jouée
        return 0;
    }
    //Sinon on le lit et on retourne la valeur après avoir fermé le fichier
    fscanf(save,"%d", &highscore);
    fclose(save); 
    return highscore;
}