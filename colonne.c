/**
* "CDataframe"
*
* Ce fichier contient l'ensemble des fonctions correspondant aux fonctionnalités développées autour des colonnes
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colonne.h"

Colonne *creer_colonne(EnumType type, char *titre) {
// Allocation dynamique de mémoire pour une nouvelle colonne
    Colonne *colonne = (Colonne *) malloc(sizeof(Colonne));

    // Allocation dynamique de mémoire pour le titre de la colonne
    colonne->titre = (char *) malloc(LONGUEUR_MAX * sizeof(char));

    // Copie du titre dans la mémoire allouée caractère par caractère
    int i;
    for (i = 0; titre[i] != '\0'; i++) {
        colonne->titre[i] = titre[i];
    }
    colonne->titre[i] = '\0'; // Ajout du caractère de fin '\0'

    // Initialisation des autres champs de la colonne
    colonne->type_colonne = type;
    colonne->taille_logique = 0;
    colonne->taille_reelle = 0; // La taille reelle correspond à la taille logique + le nombre de fois que la valeur NULL a été insérée pour compléter le CDataframe
    colonne->taille_physique = 0;
    colonne->donnees = NULL;

    // Retourne le pointeur vers la colonne créée
    return colonne;
}

int inserer_valeur(Colonne *colonne, void *valeur) {
    void *donnees_realloc = NULL;
    int taille_octets;
    
    // Vérifie si la colonne existe
    if (!colonne) {
        return 0; // Retourne 0 si la colonne n'existe pas
    }
    
    // Vérifie si l'espace alloué est insuffisant
    if (colonne->taille_reelle == colonne->taille_physique) {
        // Augmente la taille physique de la colonne
        colonne->taille_physique += TAILLE_REALLOC;
        
        // Réalloue de la mémoire pour stocker les données de la colonne
        taille_octets = colonne->taille_physique * sizeof(void *);
        donnees_realloc = realloc(colonne->donnees, colonne->taille_physique * sizeof(void *));

        // Vérifie si la réallocation de mémoire a échoué
        if (!donnees_realloc) {
            return -1; // Retourne -1 en cas d'échec de réallocation de mémoire
        } else {
            colonne->donnees = donnees_realloc; // Met à jour le pointeur vers les données
        }
    }
    
    // Insère la valeur dans la colonne en fonction de son type
    if (valeur == NULL) {
        colonne->donnees[colonne->taille_reelle] = NULL; // Insère NULL si la valeur est NULL
    } else {
        switch (colonne->type_colonne) {
            // Alloue de la mémoire et copie la valeur en fonction du type de colonne
            case INT:
                // Alloue de la mémoire pour un entier et copie la valeur
                colonne->donnees[colonne->taille_logique] = malloc(sizeof(int));
                *((int *)colonne->donnees[(colonne->taille_logique)++]) = *((int *)valeur);
                break;
            case CHAR:
                // Alloue de la mémoire pour un caractère et copie la valeur
                colonne->donnees[colonne->taille_logique] = malloc(sizeof(char));
                *((char *)colonne->donnees[(colonne->taille_logique)++]) = *((char *)valeur);
                break;
            case FLOAT:
                colonne->donnees[colonne->taille_logique] = malloc(sizeof(float));
                *((float *)colonne->donnees[(colonne->taille_logique)++]) = *((float *)valeur);
                break;
            case UINT:
                colonne->donnees[colonne->taille_logique] = malloc(sizeof(unsigned int));
                *((unsigned int *)colonne->donnees[(colonne->taille_logique)++]) = *((unsigned int *)valeur);
                break;
            case DOUBLE:
                colonne->donnees[colonne->taille_logique] = malloc(sizeof(double));
                *((double *)colonne->donnees[(colonne->taille_logique)++]) = *((double *)valeur);
                break;
            case STRING:
                colonne->donnees[colonne->taille_logique] = malloc(LONGUEUR_MAX * sizeof(char));
                *((char **)colonne->donnees[(colonne->taille_logique)++]) = *((char **)valeur);
                break;
        }
    }

    // Incrémente la taille réelle de la colonne
    if (!(colonne->taille_logique < colonne->taille_reelle && valeur != NULL)) {
        colonne->taille_reelle++;
    }

    return 0; // Retourne 0 pour indiquer que l'insertion s'est déroulée avec succès
}

void supprimer_colonne(Colonne **colonne) {
    // Libère la mémoire allouée pour chaque élément de données de la colonne
    for (int i = 0; i < (*colonne)->taille_logique; i++) {
        if ((*colonne)->donnees[i] != NULL) {
            free((*colonne)->donnees[i]);
            (*colonne)->donnees[i] = NULL;
        }
    }

    // Libère la mémoire allouée pour le tableau de données
    free((*colonne)->donnees);
    (*colonne)->donnees = NULL;

    // Libère la mémoire allouée pour la structure de colonne elle-même
    free(*colonne);
    
    // Réinitialise le pointeur à NULL
    *colonne = NULL;
}

char *convertir_valeur(Colonne *colonne, unsigned long long int position){
    // Vérifie si la valeur est NULL
    if (!colonne->donnees[position]) {
        return "NULL"; // Retourne "NULL" sous forme de chaîne de caractères
    } else {
        // Alloue de la mémoire pour stocker la valeur convertie
        char *chaine = malloc(LONGUEUR_MAX * sizeof(char));

        // Convertit la valeur en fonction du type de colonne
        switch (colonne->type_colonne) {
            case INT:
                snprintf(chaine, LONGUEUR_MAX, "%d", *((int*)colonne->donnees[position])); // Convertit et stocke la valeur entière à la position donnée dans la colonne dans la chaîne 'chaine'
                break;
            case CHAR:
                snprintf(chaine, LONGUEUR_MAX, "%c", *((char*)colonne->donnees[position]));
                break;
            case FLOAT:
                snprintf(chaine, LONGUEUR_MAX, "%f", *((float*)colonne->donnees[position]));
                break;
            case UINT:
                snprintf(chaine, LONGUEUR_MAX, "%u", *((unsigned int*)colonne->donnees[position]));
                break;
            case DOUBLE:
                snprintf(chaine, LONGUEUR_MAX, "%lf", *((double*)colonne->donnees[position]));
                break;
            case STRING:
                snprintf(chaine, LONGUEUR_MAX, "%s", *((char**)colonne->donnees[position]));
                break;
        }
        return chaine; // Retourne la chaîne de caractères convertie
    }
}

void afficher_colonne(Colonne *colonne, int limite_ligne) {
    printf("%s\n", colonne->titre);
    for (int i = 0; i < limite_ligne; i++) {
        printf("[%d] %s\n", i, convertir_valeur(colonne, i));
    }
}

int comparer_chaines(char *chaine_1, char *chaine_2) {
    int i = 0;

    // Parcourt les deux chaînes caractère par caractère tant qu'ils sont égaux jusqu'à trouver le caractère différent
    while (chaine_1[i] != '\0' && chaine_2[i] != '\0' && chaine_1[i] == chaine_2[i]) {
        i++;
    }

    // Compare les caractères à l'indice courant
    if (!(chaine_1[i] - chaine_2[i])) {
        return 0; // Les chaînes sont égales
    } else {
        if ((chaine_1[i] - chaine_2[i]) < 0) {
            return -1; // chaine_1 est inférieure à chaine_2
        } else {
            return 1; // chaine_1 est supérieure à chaine_2
        }
    };
}

int retourner_egal(Colonne *colonne, EnumType type, void* valeur_recherchee){
    int compteur = 0; // Initialise le compteur pour le nombre d'occurrences trouvées

    // Vérifie si le type de la colonne correspond au type spécifié
    if(colonne->type_colonne == type){
        // Parcourt chaque élément de la colonne
        for(int i = 0; i < colonne->taille_logique; i++){
            // Vérifie si l'élément n'est pas NULL et compare les valeurs en fonction du type
            if (colonne->donnees[i] != NULL)
                switch(type) {
                    case INT:
                        if(*(int*)colonne->donnees[i] == *(int*)valeur_recherchee) {
                            compteur++; // Incrémente le compteur si les valeurs sont égales
                        }
                        break;
                    case CHAR:
                        if(*(char*)colonne->donnees[i] == *(char*)valeur_recherchee) {
                            compteur++;
                        }
                        break;
                    case FLOAT:
                        if(*(float*)colonne->donnees[i] == *(float*)valeur_recherchee) {
                            compteur++;
                        }
                        break;
                    case UINT:
                        if(*(unsigned int*)colonne->donnees[i] == *(unsigned int*)valeur_recherchee) {
                            compteur++;
                        }
                        break;
                    case DOUBLE:
                        if(*(double*)colonne->donnees[i] == *(double*)valeur_recherchee) {
                            compteur++;
                        }
                        break;
                    case STRING:
                        if(comparer_chaines(*(char**)colonne->donnees[i], *(char**)valeur_recherchee) == 0) {
                            compteur++;
                        }
                        break;
                }
        }
    }

    return compteur; // Retourne le nombre d'occurrences trouvées
}

void *retourner_position(Colonne *colonne, int position) {
    if (colonne->donnees[position]) {
        return colonne->donnees[position];
    } else {
        return NULL;
    }
}

int retourner_inferieur(Colonne *colonne, EnumType type, void* valeur_comparee){
    int compteur = 0; // Initialise le compteur pour le nombre de valeurs inférieures trouvées

    // Vérifie si le type de la colonne correspond au type spécifié
    if(colonne->type_colonne == type){
        // Parcourt chaque élément de la colonne
        for(int i = 0; i < colonne->taille_logique; i++){
            // Vérifie si l'élément n'est pas NULL et compare les valeurs en fonction du type
            if (colonne->donnees[i] != NULL)
                switch(type) {
                    case INT:
                        if(*(int*)colonne->donnees[i] < *(int*)valeur_comparee) {
                            compteur++; // Incrémente le compteur si la valeur est inférieure
                        }
                        break;
                    case CHAR:
                        if(*(char*)colonne->donnees[i] < *(char*)valeur_comparee) {
                            compteur++;
                        }
                        break;
                    case FLOAT:
                        if(*(float*)colonne->donnees[i] < *(float*)valeur_comparee) {
                            compteur++;
                        }
                        break;
                    case UINT:
                        if(*(unsigned int*)colonne->donnees[i] < *(unsigned int*)valeur_comparee) {
                            compteur++;
                        }
                        break;
                    case DOUBLE:
                        if(*(double*)colonne->donnees[i] < *(double*)valeur_comparee) {
                            compteur++;
                        }
                        break;
                    case STRING:
                        if(comparer_chaines(*(char**)colonne->donnees[i], *(char**)valeur_comparee) == -1) {
                            compteur++;
                        }
                        break;
                }
        }
    }

    return compteur; // Retourne le nombre de valeurs inférieures trouvées
}

int retourner_superieur(Colonne *colonne, EnumType type, void* valeur_comparee){
    int compteur = 0;

    if(colonne->type_colonne == type){
        for(int i = 0; i < colonne->taille_logique; i++){
            if (colonne->donnees[i] != NULL)
            switch(type) {
                case INT:
                    if(*(int*)colonne->donnees[i] > *(int*)valeur_comparee) {
                        compteur++;
                    }
                    break;
                case CHAR:
                    if(*(char*)colonne->donnees[i] > *(char*)valeur_comparee) {
                        compteur++;
                    }
                    break;
                case FLOAT:
                    if(*(float*)colonne->donnees[i] > *(float*)valeur_comparee) {
                        compteur++;
                    }
                    break;
                case UINT:
                    if(*(unsigned int*)colonne->donnees[i] > *(unsigned int*)valeur_comparee) {
                        compteur++;
                    }
                    break;
                case DOUBLE:
                    if(*(double*)colonne->donnees[i] > *(double*)valeur_comparee) {
                        compteur++;
                    }
                    break;
                case STRING:
                    if(comparer_chaines(*(char**)colonne->donnees[i], *(char**)valeur_comparee) == 1) {
                        compteur++;
                    }
                    break;
            }
        }
    }

    return compteur;
}
