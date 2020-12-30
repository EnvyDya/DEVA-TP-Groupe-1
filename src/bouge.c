#include "bouge.h"
#include "partie.h"
#include "alea.h"

/*
*   Le tableau est de la forme : t[abscisse][ordonnées].
*   Il est par défaut rempli de vide, mur extérieurs créés.
*   Les deux joueurs sont placés en bas à gauche et en haut à droite.
*   Celui en haut à droite regarde en bas.
*   Celui en bas à gauche regarde en haut.
*/

void initTab(){
    //On met toutes les cases "vides"
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            t[i][j].joueurPresent = false;
            t[i][j].murEst = false;
            t[i][j].murNord = false;
            t[i][j].murOuest = false;
            t[i][j].murSud = false;
            t[i][j].capa = NULL;
        }
    }
    //On met les cases extérieures avec leurs murs
    for(int i = 0; i<SIZE; i++){
        t[i][0].murNord = true;
        t[i][SIZE-1].murSud = true;
        t[0][i].murOuest = true;
        t[SIZE-1][i].murEst = true;
    }

    //Création des deux joueurs avec id et orientation
    Joueur j1;
    j1.id = 1;
    j1.orientation = 0;
    //Création de la liste de capacités du joueur 1
    j1.capacite = creaListe();

    Joueur j2;
    j2.id = 2;
    j2.orientation = 2;
    j2.capacite = creaListe();

    //Placement des joueurs sur la carte
    t[0][SIZE-1].joueur = j1;
    t[0][SIZE-1].joueurPresent = true;
    t[SIZE-1][0].joueur = j2;
    t[SIZE-1][0].joueurPresent = true;
};

void initTabMurs(){
    //On met toutes les cases "vides"
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            t[i][j].joueurPresent = false;
            t[i][j].murEst = false;
            t[i][j].murNord = false;
            t[i][j].murOuest = false;
            t[i][j].murSud = false;
            t[i][j].capa = NULL;
        }
    }
    //On met les cases extérieures avec leurs murs
    for(int i = 0; i<SIZE; i++){
        t[i][0].murNord = true;
        t[i][SIZE-1].murSud = true;
        t[0][i].murOuest = true;
        t[SIZE-1][i].murEst = true;
    }

    //Création des deux joueurs avec id et orientation
    Joueur j1;
    j1.id = 1;
    j1.orientation = 0;
    //Création de la liste de capacités du joueur 1
    j1.capacite = creaListe();

    Joueur j2;
    j2.id = 2;
    j2.orientation = 2;
    j2.capacite = creaListe();

    for(int i = 1;i<SIZE-1;i++){
        for(int j = 1;j<SIZE-1;j++){
            int probaMur = rand()%4;

            if(probaMur == 0){
                t[i][j].murNord = true;
            } else if(probaMur == 1){
                t[i][j].murEst = true;
            } else if(probaMur == 2){
                t[i][j].murSud = true;
            } else if(probaMur == 3){
                t[i][j].murOuest = true;
            }

            if(t[i][j].murNord){
                t[i-1][j].murSud = true;
            }
            if(t[i][j].murEst){
                t[i][j+1].murOuest = true;
            }
            if(t[i][j].murSud){
                t[i+1][j].murNord = true;
            }
            if(t[i][j].murOuest){
                t[i][j-1].murEst = true;
            }
        }
    }

    //Placement des joueurs sur la carte
    t[0][SIZE-1].joueur = j1;
    t[0][SIZE-1].joueurPresent = true;
    t[0][SIZE-1].murNord = false;
    t[0][SIZE-1].murEst = false;
    t[0][SIZE-2].murSud = false;
    t[1][SIZE-1].murOuest = false;
    t[SIZE-1][0].joueur = j2;
    t[SIZE-1][0].joueurPresent = true;
    t[SIZE-1][0].murSud = false;
    t[SIZE-1][0].murOuest = false;
    t[SIZE-1][1].murNord = false;
    t[SIZE-2][0].murEst = false;
}

/*
*   Fonction qui permet de renvoyer une liste de capacité pleine en début de partie.
*/
Liste_Capacites creaListe(){
    Liste_Capacites l;
    capacite *b1 = (capacite *)malloc(sizeof(capacite));
    b1->type = 0;
    b1->s = NULL;
    capacite *b2 = (capacite *)malloc(sizeof(capacite));
    b2->type = 1;
    b2->s = b1;
    capacite *b3 = (capacite *)malloc(sizeof(capacite));
    b3->type = 2;
    b3->s = b2;
    capacite *b4 = (capacite *)malloc(sizeof(capacite));
    b4->type = 3;
    b4->s = b3;
    l.p = b4;
    return l;
}

/*
*   Fonction qui fait pivoter le joueur
*   On rentre un entier qui correspond à l'id du joueur.
*   La direction peut être à -1 (pour tourner à gauche) ou à 1 (pour tourner à droite).
*   Le tableau t correspond à la grille de jeu
*/
void tourne(int id, int dir){
    //On recherche la position du joueur j.
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == id){
                    //On modifie son orientation quand on l'a trouvé
                    t[j][i].joueur.orientation = (unsigned)(t[j][i].joueur.orientation+dir)%4;
                    break;
                }
            }
        }
    }
}

/*
*   Fonction qui affiche le terrain de jeu dans la console.
*   Affiche les joueurs par un ^ < > v (selon l'orientation), et les murs par --- ou |
*/
void afficheGrid(){
    //On affiche le mur du haut (x3 par case pour éventuel mur gauche, joueur, mur droit)
    printf("  ");
    for(int i = 0; i<SIZE; i++){
        printf("-%c-", 'a'+i);
    }
    printf("\n");
    for(int i = 0; i<SIZE; i++){
        printf("%d|", i);
        //Pour chaque case on teste s'il y a un mur/un joueur ou non, si rien on affiche un espace
        for(int j = 0; j<SIZE; j++){
            printf(" ");
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.orientation == 0){
                    printf("^");
                }else if(t[j][i].joueur.orientation == 1){
                    printf(">");
                }else if(t[j][i].joueur.orientation == 2){
                    printf("v");
                }else if(t[j][i].joueur.orientation == 3){
                    printf("<");
                }
            }else if(t[j][i].capa != NULL){
                printf("o");
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
        printf("\n");
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

/*
*   Fonction qui permet de faire avancer un joueur sur le tableau.
*   id permet de stocker l'identifiant du joueur qui bouge.
*   La fonction retourne true si l'action a pu s'executer, false sinon.
*   Le false permettra au joueur (s'étant peut être trompé) de ne pas perdre son tour.
*/

bool avance(int id){
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

void useCapa(int id, int n){
    bool possible = false;
    switch (n)
    {
    case 0:
        /* Création Mur */
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(t[j][i].joueurPresent){
                    if(t[j][i].joueur.id == id){
                        capacite *c = (capacite *)malloc(sizeof(capacite));
                        c = t[j][i].joueur.capacite.p;
                        capacite *prec = (capacite *)malloc(sizeof(capacite));
                        prec = t[j][i].joueur.capacite.p;
                        //Si le joueur a la capacité, on notifie que l'action est possible et on supprime la capacité de l'inventaire
                        while(c != NULL){
                            if(c->type == n){
                                possible = true;
                                //Si on pointe sur la tête de la liste, alors il ne faut pas oublier de changer la tête avant de la supprimer
                                if(prec == c){
                                    t[j][i].joueur.capacite.p = c->s; 
                                }
                                prec->s = c->s;
                                free(c);
                                break;
                            }
                            prec = c;
                            c = c->s;
                        }
                    }
                }
            }
        }
        if(possible){
            char choix, temp;
            int posY, posX;
            //On lit la position par lettres + chiffre (comme affiché par le tableau);
            printf("En quelle case voulez vous placer un mur ?\n");
            do{
                printf("Rentrez une lettre valide (entre a et f) : ");
                scanf(" %c", &choix);
            }while(choix<65 || choix>70 && choix<97 || choix>102);
            do{
                printf("Rentrez le numero valide (entre 0 et 5): ");
                scanf("%d", &posY);
            }while(posY < 0 || posY >5);
            //On va maintenant convertir la lettre en chiffre correspondant à la case
            if(choix >= 97 && choix <= 102){
                //Cas d'une minuscule
                posX = choix - 97;
            }else if(choix >= 65 && choix <= 70){
                //Cas d'une majuscule
                posX = choix - 65;
            }
            //Choix de où placer le mur
            printf("Quel mur voulez vous creer ?\nZ pour nord, S pour sud, Q pour ouest et d pour est.\n");
            do{
                /*Z = 90, S = 83, Q = 81, D = 68
                z = 122, s = 115, q = 113, d = 100*/
                printf("Choix : ");
                scanf(" %c", &choix);
            }while(choix != 68 && choix != 81 && choix != 83 && choix != 90 && choix != 122 && choix != 115 && choix != 113 && choix != 100);
            //Pour éviter de multiplier les case, je vais passer le choix en majuscule s'il est en majuscule
            if(choix == 122 || choix == 115 || choix == 113 || choix == 100){
                choix -= 32;
            }
            switch(choix)
            {
                case 90:
                    {
                        //On place un mur au Nord (Sans oublier celui au sud de la case au dessus)
                        t[posX][posY].murNord = true;
                        t[posX][posY-1].murSud = true;
                    }
                    break;
                
                case 83:
                    {
                        //On place un mur au Sud (Sans oublier celui au nord de la case en dessous)
                        t[posX][posY].murSud = true;
                        t[posX][posY+1].murNord = true;
                    }
                    break;
                
                case 81:
                    {
                        //On place un mur au à l'Ouest (Sans oublier celui à l'est de la case à gauche)
                        t[posX][posY].murOuest = true;
                        t[posX-1][posY].murEst = true;
                    }
                    break;

                case 68:
                    {
                        //On place un mur à l'Est (Sans oublier celui à l'ouest de la case à droite)
                        t[posX][posY].murEst = true;
                        t[posX+1][posY].murOuest = true;
                    }
                    break;
            }
        }else{
            printf("Action impossible\n");
        }    
        break;
    
    case 1:
        /* Recule adversaire */
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(t[j][i].joueurPresent){
                    if(t[j][i].joueur.id == id){
                        capacite *c = (capacite *)malloc(sizeof(capacite));
                        c = t[j][i].joueur.capacite.p;
                        capacite *prec = (capacite *)malloc(sizeof(capacite));
                        prec = t[j][i].joueur.capacite.p;
                        //Si le joueur a la capacité, on notifie que l'action est possible et on supprime la capacité de l'inventaire
                        while(c != NULL){
                            if(c->type == n){
                                possible = true;
                                if(prec == c){
                                    t[j][i].joueur.capacite.p = c->s; 
                                }
                                prec->s = c->s;
                                free(c);
                                break;
                            }
                            prec = c;
                            c = c->s;
                        }
                    }
                }
            }
        }
        if(possible){
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[j][i].joueurPresent){
                        //Si le joueur présent est j+1 ou j-1 (l'autre joueur) on fait l'action
                        if(t[j][i].joueur.id == id+1 || t[j][i].joueur.id == id-1){
                            if(t[j][i].joueur.id == id+1){
                                tourne(id+1, -1);
                                tourne(id+1, -1);
                                avance(id+1);
                                tourne(id+1, -1);
                                tourne(id+1, -1);
                                i = SIZE;
                                j = SIZE;
                                break;
                            }else{
                                tourne(id-1, -1);
                                tourne(id-1, -1);
                                avance(id-1);
                                tourne(id-1, -1);
                                tourne(id-1, -1);
                                i = SIZE;
                                j = SIZE;
                                break;
                            }
                        }
                    }
                }
            }
        }else{
            printf("Mouvement impossible\n");
        }
        break;
        
    case 2:
        /* Demi-tour */
        //On cherche le joueur dans le tableau
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(t[j][i].joueurPresent){
                    if(t[j][i].joueur.id == id){
                        capacite *c = (capacite *)malloc(sizeof(capacite));
                        c = t[j][i].joueur.capacite.p;
                        capacite *prec = (capacite *)malloc(sizeof(capacite));
                        prec = t[j][i].joueur.capacite.p;
                        //On parcourt les capacités jusqu'au bout
                        while(c != NULL){
                            //Si le joueur a la capacité, on execute l'action
                            if(c->type == n){
                                tourne(id, 1);
                                tourne(id, 1);
                                possible = true;
                                if(prec == c){
                                    t[j][i].joueur.capacite.p = c->s; 
                                }
                                prec->s = c->s;
                                free(c);
                                break;
                            }
                            prec = c;
                            c = c->s;
                        }
                    }
                }
            }
        }
        if(!possible){
            printf("Mouvement impossible\n");
        }
        break;

    case 3:
        {
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[j][i].joueurPresent){
                        if(t[j][i].joueur.id == id){
                            capacite *c = (capacite *)malloc(sizeof(capacite));
                            c = t[j][i].joueur.capacite.p;
                            capacite *prec = (capacite *)malloc(sizeof(capacite));
                            prec = t[j][i].joueur.capacite.p;
                            //Si le joueur a la capacité, on notifie que l'action est possible et on supprime la capacité de l'inventaire
                            while(c != NULL){
                                if(c->type == n){
                                    possible = true;
                                    if(prec == c){
                                       t[j][i].joueur.capacite.p = c->s; 
                                    }
                                    prec->s = c->s;
                                    free(c);
                                    break;
                                }
                                prec = c;
                                c = c->s;
                            }
                        }
                    }
                }
            }

            if(possible){
                tour(id);
            }else{
                printf("Nouveau tour impossible\n");
            }
        }
        break;
    }
}

void useCapaOrdi(int difficulte,int n){
    bool possible = false;
    switch(n){
        case 0: //Création d'un mur
        {
                for(int i = 0;i<SIZE;i++){
                    for(int j = 0;j<SIZE;j++){
                        if(t[j][i].joueurPresent){
                            if(t[j][i].joueur.id == 2){
                                capacite *c = (capacite *)malloc(sizeof(capacite));
                                c = t[j][i].joueur.capacite.p;
                                capacite *prec = (capacite *)malloc(sizeof(capacite));
                                prec = t[j][i].joueur.capacite.p;
                                while(c != NULL){
                                    if(c->type == n){
                                        possible = true;
                                        if(prec == c){
                                            t[j][i].joueur.capacite.p = c->s;
                                        }
                                        prec->s = c->s;
                                        free(c);
                                        break;
                                    }
                                    prec = c;
                                    c = c->s;
                                }
                            }
                        }
                    }
                }
                if(possible){
                    int posX,posY,orientation;
                    posX = alea(0,5);
                    posY = alea(0,5);
                    orientation = alea(0,3);
                    switch(orientation){
                        case 0: //Nord
                            {
                                t[posX][posY].murNord = true;
                                t[posX][posY-1].murSud = true;
                            }
                            break;
                        case 1: //Est
                            {
                                t[posX][posY].murEst = true;
                                t[posX+1][posY].murOuest = true;
                            }
                            break;
                        case 2: //Sud
                            {
                                t[posX][posY].murSud = true;
                                t[posX][posY+1].murNord = true;
                            }
                            break;
                        case 3: //Ouest
                            {
                                t[posX][posY].murOuest = true;
                                t[posX-1][posY].murEst = true;
                            }
                            break;
                    }
                } else {
                    printf("La capacité du bot a échoué\n");
                }
                break;
        }
        case 1: //Faire reculer l'adversaire
        {
                for(int i=0;i<SIZE;i++){
                    for(int j = 0;j<SIZE;j++){
                        if(t[j][i].joueurPresent){
                            if(t[j][i].joueur.id == 2){
                                capacite *c = (capacite *)malloc(sizeof(capacite));
                                c = t[j][i].joueur.capacite.p;
                                capacite *prec = (capacite *)malloc(sizeof(capacite));
                                prec = t[j][i].joueur.capacite.p;
                                while(c != NULL){
                                    if(c->type == n){
                                        possible = true;
                                        if(prec == c){
                                            t[j][i].joueur.capacite.p = c->s;
                                        }
                                        prec->s = c->s;
                                        free(c);
                                        break;
                                    }
                                    prec = c;
                                    c = c->s;
                                }
                            }
                        }
                    }
                }
            if(possible){
                for(int i = 0;i<SIZE;i++){
                    for(int j = 0;j<SIZE;j++){
                        if(t[j][i].joueur.id == 1){
                            tourne(1,-1);
                            tourne(1,-1);
                            avance(1);
                            tourne(1,-1);
                            tourne(1,-1);
                            i = SIZE;
                            j = SIZE;
                            break;
                        }
                    }
                }
            } else {
                printf("La capacité du bot a échoué\n");
            }
            break;
        }    
        case 2: //Demi-tour
        {
                for(int i = 0;i<SIZE;i++){
                    for(int j =0;j<SIZE;j++){
                        if(t[j][i].joueurPresent){
                            if(t[j][i].joueur.id == 2){
                                capacite *c = (capacite *)malloc(sizeof(capacite));
                                c = t[j][i].joueur.capacite.p;
                                capacite *prec = (capacite *)malloc(sizeof(capacite));
                                prec = t[j][i].joueur.capacite.p;
                                //On parcourt les capacités jusqu'au bout
                                while(c != NULL){
                                    //Si le joueur a la capacité, on execute l'action
                                    if(c->type == n){
                                        tourne(2, 1);
                                        tourne(2, 1);
                                        possible = true;
                                        if(prec == c){
                                            t[j][i].joueur.capacite.p = c->s; 
                                        }
                                        prec->s = c->s;
                                        free(c);
                                        break;
                                    }
                                    prec = c;
                                    c = c->s;
                                }
                            }
                        }
                    }
                }
                if(!possible){
                    printf("La capacité du bot a échoué\n");
                }
                break;
        }
        case 3: //Rejouer un tour
        {
                for(int i = 0;i<SIZE;i++){
                    for(int j = 0;j<SIZE;j++){
                        if(t[j][i].joueurPresent){
                            if(t[j][i].joueur.id == 2){
                                capacite *c = (capacite *)malloc(sizeof(capacite));
                                c = t[j][i].joueur.capacite.p;
                                capacite *prec = (capacite *)malloc(sizeof(capacite));
                                prec = t[j][i].joueur.capacite.p;
                                while(c != NULL){
                                    if(c->type == n){
                                        possible = true;
                                        if(prec == c){
                                            t[j][i].joueur.capacite.p = c->s;
                                        }
                                        prec->s = c->s;
                                        free(c);
                                        break;
                                    }
                                    prec = c;
                                    c = c->s;
                                }
                            }
                        }
                    }
                }
                if(possible){
                    tourOrdi(difficulte);
                } else {
                    printf("La capacité du bot a échoué\n");
                }
                break;
        }
    }
}