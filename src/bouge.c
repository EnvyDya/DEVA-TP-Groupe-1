#include "bouge.h"

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
    printf(" ");
    for(int i = 0; i<SIZE; i++){
        printf("-%c-", 'a'+i);
    }
    printf("\n");
    for(int i = 0; i<SIZE; i++){
        printf("%d", i);
        //Pour chaque case on teste s'il y a un mur/un joueur ou non, si rien on affiche un espace
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].murOuest){
                printf("|");
            }else{
                printf(" ");
            }
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
            }else{
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
        if(i == SIZE-1){
            printf(" ");
        }
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
                        while(c->s != NULL){
                            if(c->type == n){
                                possible = true;
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
                                break;
                            }else{
                                tourne(id-1, -1);
                                tourne(id-1, -1);
                                avance(id-1);
                                tourne(id-1, -1);
                                tourne(id-1, -1);
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
                        while(c->s != NULL){
                            //Si le joueur a la capacité, on execute l'action
                            if(c->type == n){
                                tourne(id, 1);
                                tourne(id, 1);
                                possible = true;
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
        /* Nouveau tour */
        break;
            
    default:
        break;
    }
}