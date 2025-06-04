/**
* "CDataframe"
*
* Ce fichier contient l'ensemble des fonctions correspondant aux fonctionnalités développées autour du CDataframe
*/

#include "colonne.h"
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Cdataframe *creer_cdataframe() {
    Cdataframe *cdataframe = malloc(sizeof(Cdataframe));
    if (!cdataframe) {
        return NULL; // En cas d'échec de l'allocation, retourne NULL
    }

    // Initialise les membres du CDataframe
    cdataframe->colonnes = NULL; // Initialise le tableau de colonnes à NULL
    cdataframe->nombre_colonnes = 0; // Initialise le nombre de colonnes à 0
    cdataframe->capacite = 0; // Initialise la capacité à 0

    return cdataframe; // Retourne le pointeur vers le nouveau CDataframe
}

int ajouter_colonne(Cdataframe *cdataframe, Colonne *colonne) {
    // Vérifie si le nombre de colonnes dans le CDataframe atteint sa capacité maximale
    if (cdataframe->nombre_colonnes == cdataframe->capacite) {
        // Augmente la capacité du CDataframe en ajoutant TAILLE_REALLOC colonnes supplémentaires
        cdataframe->capacite += TAILLE_REALLOC;

        // Réalloue de la mémoire pour le tableau de pointeurs de colonnes
        Colonne **nouvelles_colonnes = realloc(cdataframe->colonnes, cdataframe->capacite * sizeof(Colonne *));
        if (!nouvelles_colonnes) {
            return -1; // En cas d'échec de la réallocation, retourne -1
        }

        // Met à jour le pointeur vers le tableau de colonnes avec le nouveau tableau
        cdataframe->colonnes = nouvelles_colonnes;
    }

    // Ajoute la nouvelle colonne à la fin du tableau de colonnes du CDataframe
    cdataframe->colonnes[cdataframe->nombre_colonnes] = colonne;
    cdataframe->nombre_colonnes++; // Incrémente le nombre total de colonnes dans le CDataframe
    return 0; // Retourne 0 pour indiquer que l'opération d'ajout s'est déroulée avec succès
}

void completion_cdataframe(Cdataframe *cdataframe) {
    // Détermine le nombre maximal de lignes parmi toutes les colonnes du CDataframe
    int nombre_lignes_max = retourner_nombre_lignes(cdataframe);

    // Parcourt toutes les colonnes du CDataframe
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        // Obtient le nombre de lignes actuellement dans la colonne
        int j = cdataframe->colonnes[i]->taille_reelle;
    
        // Insère des valeurs NULL dans la colonne pour atteindre le nombre maximal de lignes
        for (int k = j; k < nombre_lignes_max; k++) {
            inserer_valeur(cdataframe->colonnes[i], NULL);
        }
    }
}

void remplir_cdataframe_utilisateur(Cdataframe *cdataframe) {
    int choix_nombre_colonne;

    // Boucle pour demander le nombre de colonnes à ajouter au CDataframe
    do {
        printf("Combien de colonnes voulez-vous ajouter au CDataframe ?\n>");
        scanf(" %d", &choix_nombre_colonne);
        printf("\n");
        if (choix_nombre_colonne < 1) {
            printf("Veuillez entrer un nombre correct de colonnes.\n\n");
        }
    } while (choix_nombre_colonne < 1);

    // Boucle pour chaque colonne à ajouter
    for (int i = 0; i < choix_nombre_colonne; i++) {
        Colonne *colonne;

        // Demande à l'utilisateur de saisir le titre de la colonne
        printf("Veuillez entrer un titre a la colonne d'indice %d :\n>", i);
        char titre[LONGUEUR_MAX];
        scanf(" %s", titre);
        printf("\n");

        // Boucle pour demander le type et les valeurs de chaque colonne
        int continuer_boucle = 1;
        int choix_nombre_valeurs;
        while (continuer_boucle) {
            continuer_boucle = 0;

            int choix_type = 0;
            printf("Choisissez le type de la colonne d'indice %d :\n\n"
            "1: Entier\n"
            "2: Caractere\n"
            "3: Float\n"
            "4: Entier non signe\n"
            "5: Double\n"
            "6: Chaine de caracteres\n>", i);
            scanf("%d", &choix_type);
            printf("\n");

            // Switch pour chaque type choisi par l'utilisateur
            switch(choix_type){
                case 1:
                    colonne = creer_colonne(INT, titre);
                
                    do {
                        printf("Combien de valeurs voulez vous ajouter a cette colonne ?\n>");
                        scanf(" %d", &choix_nombre_valeurs);
                        printf("\n");
                        if (choix_nombre_valeurs < 1) {
                            printf("Veuillez entrer un nombre correct de valeurs.\n\n");
                        }
                    } while (choix_nombre_valeurs < 1);

                    for (int i = 0; i < choix_nombre_valeurs; i++) {
                        printf("Entrez la valeur d'indice %d :\n>", i);
                        int nouvelle_valeur;
                        scanf(" %d", &nouvelle_valeur);
                        inserer_valeur(colonne, &nouvelle_valeur);
                    }
                    printf("\n");

                    ajouter_colonne(cdataframe, colonne);
                    break;

                case 2:
                    colonne = creer_colonne(CHAR, titre);

                    do {
                        printf("Combien de valeurs voulez vous ajouter a cette colonne ?\n>");
                        scanf(" %d", &choix_nombre_valeurs);
                        printf("\n");
                        if (choix_nombre_valeurs < 1) {
                            printf("Veuillez entrer un nombre correct de valeurs.\n\n");
                        }
                    } while (choix_nombre_valeurs < 1);

                    for (int i = 0; i < choix_nombre_valeurs; i++) {
                        printf("Entrez la valeur d'indice %d :\n>", i);
                        char nouvelle_valeur;
                        scanf(" %c", &nouvelle_valeur);
                        inserer_valeur(colonne, &nouvelle_valeur);
                    }
                    printf("\n");

                    ajouter_colonne(cdataframe, colonne);
                    break;

                case 3:
                    colonne = creer_colonne(FLOAT, titre);

                    do {
                        printf("Combien de valeurs voulez vous ajouter a cette colonne ?\n>");
                        scanf(" %d", &choix_nombre_valeurs);
                        printf("\n");
                        if (choix_nombre_valeurs < 1) {
                            printf("Veuillez entrer un nombre correct de valeurs.\n\n");
                        }
                    } while (choix_nombre_valeurs < 1);

                    for (int i = 0; i < choix_nombre_valeurs; i++) {
                        printf("Entrez la valeur d'indice %d :\n>", i);
                        float nouvelle_valeur;
                        scanf(" %f", &nouvelle_valeur);
                        inserer_valeur(colonne, &nouvelle_valeur);
                    }
                    printf("\n");

                    ajouter_colonne(cdataframe, colonne);
                    break;

                case 4:
                    colonne = creer_colonne(UINT, titre);

                    do {
                        printf("Combien de valeurs voulez vous ajouter a cette colonne ?\n>");
                        scanf(" %d", &choix_nombre_valeurs);
                        printf("\n");
                        if (choix_nombre_valeurs < 1) {
                            printf("Veuillez entrer un nombre correct de valeurs.\n\n");
                        }
                    } while (choix_nombre_valeurs < 1);

                    for (int i = 0; i < choix_nombre_valeurs; i++) {
                        printf("Entrez la valeur d'indice %d :\n>", i);
                        unsigned int nouvelle_valeur;
                        scanf(" %u", &nouvelle_valeur);
                        inserer_valeur(colonne, &nouvelle_valeur);
                    }
                    printf("\n");

                    ajouter_colonne(cdataframe, colonne);
                    break;

                case 5:
                    colonne = creer_colonne(DOUBLE, titre);

                    do {
                        printf("Combien de valeurs voulez vous ajouter a cette colonne ?\n>");
                        scanf(" %d", &choix_nombre_valeurs);
                        printf("\n");
                        if (choix_nombre_valeurs < 1) {
                            printf("Veuillez entrer un nombre correct de valeurs.\n\n");
                        }
                    } while (choix_nombre_valeurs < 1);

                    for (int i = 0; i < choix_nombre_valeurs; i++) {
                        printf("Entrez la valeur d'indice %d :\n>", i);
                        double nouvelle_valeur;
                        scanf(" %lf", &nouvelle_valeur);
                        inserer_valeur(colonne, &nouvelle_valeur);
                    }
                    printf("\n");

                    ajouter_colonne(cdataframe, colonne);
                    break;

                case 6:
                    colonne = creer_colonne(STRING, titre);

                    do {
                        printf("Combien de valeurs voulez vous ajouter a cette colonne ?\n>");
                        scanf(" %d", &choix_nombre_valeurs);
                        printf("\n");
                        if (choix_nombre_valeurs < 1) {
                            printf("Veuillez entrer un nombre correct de valeurs.\n\n");
                        }
                    } while (choix_nombre_valeurs < 1);

                    for (int i = 0; i < choix_nombre_valeurs; i++) {
                        printf("Entrez la valeur d'indice %d :\n>", i);
                        char *nouvelle_valeur = malloc(LONGUEUR_MAX * sizeof(char));
                        scanf(" %s", nouvelle_valeur);
                        inserer_valeur(colonne, &nouvelle_valeur);
                    }
                    printf("\n");

                    ajouter_colonne(cdataframe, colonne);
                    break;
                    
                default:
                    entree_invalide();
                    continuer_boucle = 1;
            }
        }
    }

    // Complète le CDataframe avec des valeurs NULL pour toutes les colonnes
    completion_cdataframe(cdataframe);
}


void remplir_cdataframe_en_dur(Cdataframe *cdataframe) {
//*
    Colonne *colonne1 = creer_colonne(UINT, "premiere_colonne");
    inserer_valeur(colonne1, &(unsigned int){11});
    inserer_valeur(colonne1, &(unsigned int){12});
    inserer_valeur(colonne1, &(unsigned int){13});
    ajouter_colonne(cdataframe, colonne1);

    Colonne *colonne2 = creer_colonne(INT, "deuxieme_colonne");
    inserer_valeur(colonne2, &(int){21});
    inserer_valeur(colonne2, &(int){22});
    inserer_valeur(colonne2, &(int){23});
    inserer_valeur(colonne2, &(int){24});
    inserer_valeur(colonne2, &(int){25});
    inserer_valeur(colonne2, &(int){26});
    ajouter_colonne(cdataframe, colonne2);

    Colonne *colonne3 = creer_colonne(CHAR, "troisieme_colonne");
    inserer_valeur(colonne3, &(char){65});
    inserer_valeur(colonne3, &(char){64});
    inserer_valeur(colonne3, &(char){62});
    inserer_valeur(colonne3, &(char){62});
    ajouter_colonne(cdataframe, colonne3);
//*
    Colonne *colonne4 = creer_colonne(FLOAT, "Titre4");
    inserer_valeur(colonne4, &(float){10});
    inserer_valeur(colonne4, &(float){20});
    inserer_valeur(colonne4, &(float){30});
    inserer_valeur(colonne4, &(float){40});
    ajouter_colonne(cdataframe, colonne4);

    Colonne *colonne5 = creer_colonne(DOUBLE, "Titre5");
    inserer_valeur(colonne5, &(double){5});
    inserer_valeur(colonne5, &(double){10});
    inserer_valeur(colonne5, &(double){15});
    inserer_valeur(colonne5, &(double){5});
    inserer_valeur(colonne5, &(double){10});
    inserer_valeur(colonne5, &(double){15});
    inserer_valeur(colonne5, &(double){20});
    inserer_valeur(colonne5, &(double){25});
    ajouter_colonne(cdataframe, colonne5);
//*
    Colonne *colonne6 = creer_colonne(STRING, "Titre6");
    char *chaine1 = "s";
    char *chaine2 = "s";
    char *chaine3 = "testgdfsgd";
    char *chaine4 = "sd";
    inserer_valeur(colonne6, &chaine1);
    inserer_valeur(colonne6, &chaine2);
    inserer_valeur(colonne6, &chaine3);
    inserer_valeur(colonne6, &chaine4);
    ajouter_colonne(cdataframe, colonne6);
//*/
    Colonne *colonne7 = creer_colonne(INT, "Titre7");
    inserer_valeur(colonne7, &(int){50});
    inserer_valeur(colonne7, &(int){100});
    inserer_valeur(colonne7, &(int){150});
    inserer_valeur(colonne7, &(int){200});
    inserer_valeur(colonne7, &(int){250});
    inserer_valeur(colonne7, &(int){300});
    ajouter_colonne(cdataframe, colonne7);

    Colonne *colonne8 = creer_colonne(INT, "Titre8");
    inserer_valeur(colonne8, &(int){-1});
    inserer_valeur(colonne8, &(int){-2});
    inserer_valeur(colonne8, &(int){-3});
    inserer_valeur(colonne8, &(int){-4});
    inserer_valeur(colonne8, &(int){-5});
    ajouter_colonne(cdataframe, colonne8);

    Colonne *colonne9 = creer_colonne(INT, "Titre9");
    inserer_valeur(colonne9, &(int){1000});
    inserer_valeur(colonne9, &(int){2000});
    inserer_valeur(colonne9, &(int){3000});
    inserer_valeur(colonne9, &(int){4000});
    inserer_valeur(colonne9, &(int){2000});
    inserer_valeur(colonne9, &(int){3000});
    inserer_valeur(colonne9, &(int){3000});
    inserer_valeur(colonne9, &(int){4000});
    inserer_valeur(colonne9, &(int){2000});
    inserer_valeur(colonne9, &(int){3000});
    inserer_valeur(colonne9, &(int){4000});
    inserer_valeur(colonne9, &(int){5000});
    ajouter_colonne(cdataframe, colonne9);

    Colonne *colonne10 = creer_colonne(INT, "Titre10");
    inserer_valeur(colonne10, &(int){1});
    inserer_valeur(colonne10, &(int){1});
    inserer_valeur(colonne10, &(int){1});
    ajouter_colonne(cdataframe, colonne10);

    Colonne *colonne11 = creer_colonne(INT, "test");
    inserer_valeur(colonne11, &(int){1});
    inserer_valeur(colonne11, &(int){1});
    inserer_valeur(colonne11, &(int){1});
    ajouter_colonne(cdataframe, colonne11);

    Colonne *colonne12 = creer_colonne(INT, "test2");
    inserer_valeur(colonne12, &(int){1});
    inserer_valeur(colonne12, &(int){1});
    inserer_valeur(colonne12, &(int){1});
    ajouter_colonne(cdataframe, colonne12);
//*/

    // Complète le CDataframe avec des valeurs NULL pour toutes les colonnes
    completion_cdataframe(cdataframe);

//*/
}



void afficher_cdataframe(Cdataframe *cdataframe, int limite_ligne, int limite_colonne) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return;
    }

    int i;

    int nombre_lignes_affichage;
    if (limite_ligne != 0) {
        nombre_lignes_affichage = limite_ligne;
    } else {
        nombre_lignes_affichage = retourner_nombre_lignes(cdataframe);
    }

    int nombre_colonnes_affichage;
    if (limite_colonne != 0) {
        nombre_colonnes_affichage = limite_colonne;
    } else {
        nombre_colonnes_affichage = cdataframe->nombre_colonnes;
    }

    int longueur_caractere_tableau = 0;
    int longueur_nombre_ligne_max = longueur_nombre(nombre_lignes_affichage);
    int longueur_nombre_colonne_max = longueur_nombre(nombre_colonnes_affichage);
    int longueur_titre_maximale = 0;

    for (i = 0; i < nombre_colonnes_affichage; i++) {
        int longueur_titre = strlen(cdataframe->colonnes[i]->titre);
        if (longueur_titre > longueur_titre_maximale) {
            longueur_titre_maximale = longueur_titre;
        }
    }
    int ajout_titre = 3 + 1 + longueur_nombre_colonne_max + 1; // + "  [taille indice]"

    longueur_titre_maximale += ajout_titre;

    int longueur_valeur_max = retourner_taille_max(cdataframe);
    int longueur_taille_max;

    if (longueur_titre_maximale > longueur_valeur_max) {
        longueur_taille_max = longueur_titre_maximale;
    } else {
        longueur_taille_max = longueur_valeur_max;
    }

    for (i = 0; i < nombre_colonnes_affichage; i++) {
        longueur_caractere_tableau += 3 + longueur_taille_max;
    }
    longueur_caractere_tableau -= 1;

    for (i = 0; i < 2 + longueur_nombre_ligne_max + 2; i++) {
        printf(" ");
    }
    for (i = 0; i < longueur_caractere_tableau; i++) {
        printf("_");
    }
    printf("\n");

    for (i = 0; i < 3 + longueur_nombre_ligne_max; i++) {
        printf(" ");
    }
    for (i = 0; i < nombre_colonnes_affichage; i++) {
        afficher_titre_espaces(cdataframe->colonnes[i]->titre, longueur_taille_max, longueur_nombre_colonne_max, ajout_titre, i);
    }
    printf("|\n");

    if (!retourner_nombre_lignes(cdataframe)) {
        printf("    ");
        for (i = 0; i < nombre_colonnes_affichage; i++) {
            printf("|_");
            for (int j = 0; j < longueur_taille_max; j++)
                printf("_");
            printf("_");
        }
        printf("|\n");

        printf("    | Le CDataframe ne contient aucune ligne.\n"
               "    |");
        for (i = 0; i < longueur_caractere_tableau; i++) {
            printf("_");
        }

    } else {
        printf(" _");
        for (i = 0; i < longueur_nombre_ligne_max; i++) {
            printf("_");
        }
        printf("_");
        for (i = 0; i < nombre_colonnes_affichage; i++) {
            printf("|_");
            for (int j = 0; j < longueur_taille_max; j++)
                printf("_");
            printf("_");
        }
        printf("|\n");

        for (i = 0; i < nombre_lignes_affichage; i++) {
            printf("| ");

            char *position = malloc(LONGUEUR_MAX * sizeof(char));
            snprintf(position, LONGUEUR_MAX, "%d", i);
            afficher_valeur_espaces(position, longueur_nombre_ligne_max, 1);
            free(position);
            position = NULL;
            
            printf(" ");
            for (int j = 0; j < nombre_colonnes_affichage; j++) {
                printf("| ");

                char *chaine = convertir_valeur(cdataframe->colonnes[j], i);
                afficher_valeur_espaces(chaine, longueur_taille_max, 0);
                free(chaine);
                chaine = NULL;
                
                printf(" ");
            }
            printf("|\n");
            fermer_tableau(nombre_colonnes_affichage, longueur_taille_max, longueur_nombre_ligne_max);
        }
    }
    printf("\n\n");
}

void afficher_cdataframe_brut(Cdataframe *cdataframe, int limite_ligne, int limite_colonne) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return;
    }

    int nombre_lignes_affichage;
    if (limite_ligne != 0) {
        nombre_lignes_affichage = limite_ligne;
    } else {
        nombre_lignes_affichage = retourner_nombre_lignes(cdataframe);
    }

    int nombre_colonnes_affichage;
    if (limite_colonne != 0) {
        nombre_colonnes_affichage = limite_colonne;
    } else {
        nombre_colonnes_affichage = cdataframe->nombre_colonnes;
    }

    // Affichage des colonnes
    for (int i = 0; i < nombre_colonnes_affichage; i++) {
        afficher_colonne(cdataframe->colonnes[i], nombre_lignes_affichage);
        printf("\n");
    }
    printf("\n\n");
}

void ecrire_cdataframe_fichier(char *nom_fichier, Cdataframe *cdataframe, int limite_ligne, int limite_colonne) {
    // Ouvre un fichier en mode ecriture avec le nom specifie dans la variable et stocke le pointeur de fichier dans la variable "fichier"
    FILE *fichier = fopen(nom_fichier, "w");

    // Redirige la sortie standard (stdout) vers le fichier specifie par "nom_fichier". a partir de maintenant, toutes les sorties de printf seront ecrites dans le fichier.
    freopen(nom_fichier, "w", stdout);
    
    // Appelle la fonction "afficher_cdataframe" pour afficher le contenu du CDataframe. Comme la sortie standard a ete redirigee, le resultat sera ecrit dans le fichier.
    afficher_cdataframe(cdataframe, limite_ligne, limite_colonne);

    // Restaure la sortie standard (stdout) en la redirigeant vers la console ("CON"). Les sorties de printf reviendront a leur comportement normal (affichage a l'ecran).
    freopen("CON", "w", stdout);

    // Ferme le fichier ouvert precedemment.
    fclose(fichier);

    printf("L'affichage du CDataframe a ete exporte dans un fichier \"%s\".\n\n", nom_fichier);
}

void afficher_cdataframe_limite(Cdataframe *cdataframe, int limite_ligne, int limite_colonne) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return;
    } if (limite_ligne > retourner_nombre_lignes(cdataframe) || limite_ligne < 0) {
        printf("Nombre de lignes saisi trop faible ou trop eleve.\n\n");
        return;
    } if (limite_colonne > cdataframe->nombre_colonnes || limite_colonne < 0) {
        printf("Nombre de colonnes saisi trop faible ou trop eleve.\n\n");
        return;
    }
    afficher_cdataframe(cdataframe, limite_ligne, limite_colonne);
}



void ajouter_ligne(Cdataframe *cdataframe) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
    } else {
        for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
            printf("Entrez la valeur de la colonne d'indice %d que vous souhaitez ajouter (type %s) :\n>", i, retourner_nom_type(cdataframe->colonnes[i]->type_colonne));
            
            switch (cdataframe->colonnes[i]->type_colonne) {
                case INT:
                    {int choix_valeur;
                    scanf(" %d", &choix_valeur);
                    inserer_valeur(cdataframe->colonnes[i], &choix_valeur);
                    break;}
                case CHAR:
                    {char choix_valeur;
                    scanf(" %c", &choix_valeur);
                    inserer_valeur(cdataframe->colonnes[i], &choix_valeur);
                    break;}
                case FLOAT:
                    {float choix_valeur;
                    scanf(" %f", &choix_valeur);
                    inserer_valeur(cdataframe->colonnes[i], &choix_valeur);
                    break;}
                case UINT:
                    {unsigned int choix_valeur;
                    scanf(" %u", &choix_valeur);
                    inserer_valeur(cdataframe->colonnes[i], &choix_valeur);
                    break;}
                case DOUBLE:
                   {double choix_valeur;
                    scanf(" %lf", &choix_valeur);
                    inserer_valeur(cdataframe->colonnes[i], &choix_valeur);
                    break;}
                case STRING:
                    {char *choix_valeur = malloc(LONGUEUR_MAX * sizeof(char));
                    scanf(" %s", choix_valeur);
                    inserer_valeur(cdataframe->colonnes[i], &choix_valeur);
                    break;}
            }
        }
        // Complète le CDataframe avec des valeurs NULL pour toutes les colonnes
        completion_cdataframe(cdataframe);
        
        printf("\nLes valeurs ont ete ajoutees.\n\n");
    }
}

void supprimer_ligne_indice(Cdataframe *cdataframe, int indice_ligne) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return;
    } if (indice_ligne > retourner_nombre_lignes(cdataframe) - 1 || indice_ligne < 0) {
        printf("L'indice de ligne saisi est trop faible ou trop eleve.\n\n");
        return;
    }

    // Supprimer la ligne pour chaque colonne
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        Colonne *colonne = cdataframe->colonnes[i];
        // Decaler les donnees des lignes suivantes vers le haut
        for (int j = indice_ligne; j < colonne->taille_logique - 1; j++) {
            colonne->donnees[j] = colonne->donnees[j + 1];
        }
        // Mettre a jour la taille logique de la colonne
        colonne->taille_logique--;
        colonne->taille_reelle--;
    }
    printf("La suppression de la ligne a bien eu lieu.\n\n");
}

void supprimer_colonne_indice(Cdataframe *cdataframe, int indice_colonne) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return;
    } if (indice_colonne > cdataframe->nombre_colonnes - 1 || indice_colonne < 0) {
        printf("L'indice de colonne saisi est trop faible ou trop eleve.\n\n");
        return;
    }

    // Liberer la memoire de la colonne specifiee
    supprimer_colonne(&(cdataframe->colonnes[indice_colonne]));

    // Decaler les pointeurs pour combler le trou
    for (int i = indice_colonne; i < cdataframe->nombre_colonnes - 1; i++) {
        cdataframe->colonnes[i] = cdataframe->colonnes[i + 1];
    }

    // Reduire le nombre de colonnes
    cdataframe->nombre_colonnes--;

    printf("La suppression de la colonne a bien eu lieu.\n\n");
}

void renommer_colonne(Cdataframe *cdataframe, int indice_colonne) {
    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return;
    } if (indice_colonne > cdataframe->nombre_colonnes - 1 || indice_colonne < 0) {
        printf("L'indice de colonne saisi est trop faible ou trop eleve.\n\n");
        return;
    }

    Colonne *colonne = cdataframe->colonnes[indice_colonne];

    if (colonne->titre) {
        free(colonne->titre);
    }

    char nouveau_titre[LONGUEUR_MAX];
    printf("Entrez le nouveau titre que vous souhaitez donner a cette colonne :\n>");
    scanf(" %s", nouveau_titre);

    // Allocation du nouveau titre
    colonne->titre = malloc(LONGUEUR_MAX * sizeof(char)); // + 1 pour le caractere de fin '\0'

    int i;

    for (i = 0; nouveau_titre[i] != '\0'; i++) {
        colonne->titre[i] = nouveau_titre[i];
    }
    colonne->titre[i] = '\0'; // Ajout du caractere de fin '\0'

    printf("Le titre de la colonne d'indice %d a bien ete change.\n\n", indice_colonne);
}

int choix_type(Cdataframe *cdataframe, char fonction) {
    int choix_type = 0;
    printf("Choisissez le type de la valeur dont vous souhaitez verifier l'existence :\n\n"
    "1: Entier\n"
    "2: Caractere\n"
    "3: Float\n"
    "4: Entier non signe\n"
    "5: Double\n"
    "6: Chaine de caracteres\n>");
    scanf("%d", &choix_type);

    int continuer_boucle = 1;
    while (continuer_boucle) {
        continuer_boucle = 0;

        if (fonction == '=' || fonction == '!') {
            printf("Entrez la valeur que vous recherchez :\n>");
        } else {
            printf("Entrez la valeur que vous voulez comparer :\n>");
        }

        switch(choix_type){
            case 1:
                {int valeur_recherchee;
                scanf(" %d", &valeur_recherchee);
                printf("\n");

                if (fonction == '!') {
                    return existence_valeur(cdataframe, INT, &valeur_recherchee);
                } else if (fonction == '=') {
                    return compter_cellules_valeur(cdataframe, INT, &valeur_recherchee);
                } else if (fonction == '<') {
                    return compter_cellules_inferieures(cdataframe, INT, &valeur_recherchee);
                } else {
                    return compter_cellules_superieures(cdataframe, INT, &valeur_recherchee);
                }

                break;}

            case 2:
                {char valeur_recherchee;
                scanf(" %c", &valeur_recherchee);
                printf("\n");

                if (fonction == '!') {
                    return existence_valeur(cdataframe, CHAR, &valeur_recherchee);
                } else if (fonction == '=') {
                    return compter_cellules_valeur(cdataframe, CHAR, &valeur_recherchee);
                } else if (fonction == '<') {
                    return compter_cellules_inferieures(cdataframe, CHAR, &valeur_recherchee);
                } else {
                    return compter_cellules_superieures(cdataframe, CHAR, &valeur_recherchee);
                }
                
                break;}

            case 3:
                {float valeur_recherchee;
                scanf(" %f", &valeur_recherchee);
                printf("\n");

                if (fonction == '!') {
                    return existence_valeur(cdataframe, FLOAT, &valeur_recherchee);
                } else if (fonction == '=') {
                    return compter_cellules_valeur(cdataframe, FLOAT, &valeur_recherchee);
                } else if (fonction == '<') {
                    return compter_cellules_inferieures(cdataframe, FLOAT, &valeur_recherchee);
                } else {
                    return compter_cellules_superieures(cdataframe, FLOAT, &valeur_recherchee);
                }
                
                break;}

            case 4:
                {unsigned int valeur_recherchee;
                scanf(" %u", &valeur_recherchee);
                printf("\n");

                if (fonction == '!') {
                    return existence_valeur(cdataframe, UINT, &valeur_recherchee);
                } else if (fonction == '=') {
                    return compter_cellules_valeur(cdataframe, UINT, &valeur_recherchee);
                } else if (fonction == '<') {
                    return compter_cellules_inferieures(cdataframe, UINT, &valeur_recherchee);
                } else {
                    return compter_cellules_superieures(cdataframe, UINT, &valeur_recherchee);
                }
                
                break;}

            case 5:
                {double valeur_recherchee;
                scanf(" %lf", &valeur_recherchee);
                printf("\n");

                if (fonction == '!') {
                    return existence_valeur(cdataframe, DOUBLE, &valeur_recherchee);
                } else if (fonction == '=') {
                    return compter_cellules_valeur(cdataframe, DOUBLE, &valeur_recherchee);
                } else if (fonction == '<') {
                    return compter_cellules_inferieures(cdataframe, DOUBLE, &valeur_recherchee);
                } else {
                    return compter_cellules_superieures(cdataframe, DOUBLE, &valeur_recherchee);
                }
                
                break;}

            case 6:
                {char *valeur_recherchee = malloc(LONGUEUR_MAX * sizeof(char));
                scanf(" %s", valeur_recherchee);
                printf("\n");

                if (fonction == '!') {
                    return existence_valeur(cdataframe, STRING, &valeur_recherchee);
                } else if (fonction == '=') {
                    return compter_cellules_valeur(cdataframe, STRING, &valeur_recherchee);
                } else if (fonction == '<') {
                    return compter_cellules_inferieures(cdataframe, STRING, &valeur_recherchee);
                } else {
                    return compter_cellules_superieures(cdataframe, STRING, &valeur_recherchee);
                }
                
                break;}

            default:
                {entree_invalide();
                continuer_boucle = 1;
                break;}
        }
    }
}

int existence_valeur(Cdataframe *cdataframe, EnumType type, void* valeur_recherchee) {
    if (!cdataframe->nombre_colonnes) {
        return -1;
    }

    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        Colonne *colonne = cdataframe->colonnes[i];
        if(colonne->type_colonne == type){
            for(int i = 0; i < colonne->taille_logique; i++){
                if (colonne->donnees[i] != NULL)
                switch(type) {
                    case INT:
                        if(*(int*)colonne->donnees[i] == *(int*)valeur_recherchee) {
                            return 1;
                        }
                        break;
                    case CHAR:
                        if(*(char*)colonne->donnees[i] == *(char*)valeur_recherchee) {
                            return 1;
                        }
                        break;
                    case FLOAT:
                        if(*(float*)colonne->donnees[i] == *(float*)valeur_recherchee) {
                            return 1;
                        }
                        break;
                    case UINT:
                        if(*(unsigned int*)colonne->donnees[i] == *(unsigned int*)valeur_recherchee) {
                            return 1;
                        }
                        break;
                    case DOUBLE:
                        if(*(double*)colonne->donnees[i] == *(double*)valeur_recherchee) {
                            return 1;
                        }
                        break;
                    case STRING:
                        if(comparer_chaines(*(char**)colonne->donnees[i], *(char**)valeur_recherchee) == 0) {
                            return 1;
                        }
                        break;
                }
            }
        }
    }

    return 0;
}

int *afficher_valeur_indice(Cdataframe *cdataframe) {
    int *indices = (int *) calloc(2, sizeof(int));
    indices[0] = -1; indices[1] = 0;

    if (!cdataframe->nombre_colonnes) {
        cdataframe_vide();
        return indices;
    }

    int indice_ligne, indice_colonne;
    printf("Entrez l'indice de colonne de la valeur recherchee (vous pouvez afficher le CDataframe pour acceder a son indice) :\n>");
    scanf(" %d", &indice_colonne);
    if (indice_colonne > cdataframe->nombre_colonnes - 1 || indice_colonne < 0) {
        printf("L'indice de colonne saisi est trop faible ou trop eleve.\n\n");
        return indices;
    }
    printf("Entrez l'indice de ligne de la valeur recherchee (vous pouvez afficher le CDataframe pour acceder a son indice) :\n>");
    scanf(" %d", &indice_ligne);
    if (indice_ligne > retourner_nombre_lignes(cdataframe) - 1 || indice_ligne < 0) {
        printf("L'indice de ligne saisi est trop faible ou trop eleve.\n\n");
        return indices;
    }

    indices[0] = indice_colonne; indices[1] = indice_ligne;

    printf("La valeur d'indice de colonne %d et d'indice de ligne %d est : %s\n\n", indice_colonne, indice_ligne, convertir_valeur(cdataframe->colonnes[indice_colonne], indice_ligne));
    return indices; // Cela sert lors de l'utilisation de la fonction remplacer indices, pour éviter de récréer une fonction intégralement différente qui ne change finalement que peu
}

void remplacer_valeur_cdataframe(Cdataframe *cdataframe) {
    int *indices = afficher_valeur_indice(cdataframe);

    int indice_colonne = indices[0]; int indice_ligne = indices[1];

    if (indices[0] != -1) {

        if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] && cdataframe->colonnes[indice_colonne]->taille_logique < indice_ligne) {
            cdataframe->colonnes[indice_colonne]->taille_logique = indice_ligne;
        } // Cette condition permet de traiter le cas où la valeur à remplacer est NULL : dans ce cas, elle est remplacée comme n'importe quelle autre valeur sauf qu'ici, la taille logique de la colonne prend désormais la valeur de l'indice de la ligne
        // (en considérant ainsi toutes les potentielles valeurs NULL précédentes comme de réelles valeurs. Ainsi l'ajout d'une valeur se fera à la suite et ne remplacera pas l'une de ces valeurs)

        printf("Entrez la nouvelle valeur (type %s) :\n>", retourner_nom_type(cdataframe->colonnes[indice_colonne]->type_colonne));
        switch (cdataframe->colonnes[indice_colonne]->type_colonne) {
            case INT:
                {int choix_valeur;
                scanf(" %d", &choix_valeur);
                if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) {
                    cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] = malloc(sizeof(int)); // Si cet emplacement a une valeur NULL, alors il faut allouer de l'espace mémoire pour ajouter une valeur différente.
                    cdataframe->colonnes[indice_colonne]->taille_logique++;
                }
                *((int *)cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) = choix_valeur;
                break;}
            case CHAR:
                {char choix_valeur;
                scanf(" %c", &choix_valeur);
                if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) {
                    cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] = malloc(sizeof(char));
                    cdataframe->colonnes[indice_colonne]->taille_logique++;
                }
                *((char *)cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) = choix_valeur;
                break;}
            case FLOAT:
                {float choix_valeur;
                scanf(" %f", &choix_valeur);
                if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) {
                    cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] = malloc(sizeof(float));
                    cdataframe->colonnes[indice_colonne]->taille_logique++;
                }
                *((float *)cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) = choix_valeur;
                break;}
            case UINT:
                {unsigned int choix_valeur;
                scanf(" %u", &choix_valeur);
                if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) {
                    cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] = malloc(sizeof(unsigned int));
                    cdataframe->colonnes[indice_colonne]->taille_logique++;
                }
                *((unsigned int *)cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) = choix_valeur;
                break;}
            case DOUBLE:
                {double choix_valeur;
                scanf(" %lf", &choix_valeur);
                if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) {
                    cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] = malloc(sizeof(double));
                    cdataframe->colonnes[indice_colonne]->taille_logique++;
                }
                *((double *)cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) = choix_valeur;
                break;}
            case STRING:
                {char *choix_valeur = malloc(LONGUEUR_MAX * sizeof(char));
                scanf(" %s", choix_valeur);
                if (!cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) {
                    cdataframe->colonnes[indice_colonne]->donnees[indice_ligne] = malloc(LONGUEUR_MAX * sizeof(char));
                    cdataframe->colonnes[indice_colonne]->taille_logique++;
                }
                *((char **)cdataframe->colonnes[indice_colonne]->donnees[indice_ligne]) = choix_valeur;
                break;}
        printf("\nLa valeur a bien ete remplace !\n\n");
        }
    }
}

void afficher_noms_colonnes(Cdataframe *cdataframe) {
    if (!cdataframe->colonnes) {
        cdataframe_vide();
        return;
    }

    printf("Noms des colonnes du CDataframe :\n");
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        printf("   - Nom de la colonne d'indice %d : \"%s\"\n", i, cdataframe->colonnes[i]->titre);
    }
    printf("\n");
}



int retourner_nombre_lignes(Cdataframe *cdataframe) {
    // Vérifie si le CDataframe est vide
    if (!cdataframe->nombre_colonnes) {
        return -1; // Retourne -1 si le CDataframe est vide
    }

    // Initialise le nombre de lignes maximal à 0
    int nombre_lignes_max = 0;

    // Parcourt les colonnes du CDataframe
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        // Met à jour le nombre de lignes maximal si la taille logique de la colonne actuelle est supérieure
        if (cdataframe->colonnes[i]->taille_logique > nombre_lignes_max) {
            nombre_lignes_max = cdataframe->colonnes[i]->taille_logique;
        }
    }

    // Retourne le nombre de lignes maximal trouvé dans les colonnes du CDataframe
    return nombre_lignes_max;
}

int compter_cellules_valeur(Cdataframe *cdataframe, EnumType type, void *valeur_recherchee) {
    if (!cdataframe->nombre_colonnes) {
        return -1;
    }

    int compteur = 0;
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        compteur += retourner_egal(cdataframe->colonnes[i], type, valeur_recherchee);
    }

    return compteur;
}

int compter_cellules_superieures(Cdataframe *cdataframe, EnumType type, void *valeur_comparee) {
    if (!cdataframe->nombre_colonnes) {
        return -1;
    }

    int compteur = 0;
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        compteur += retourner_superieur(cdataframe->colonnes[i], type, valeur_comparee);
    }

    return compteur;
}

int compter_cellules_inferieures(Cdataframe *cdataframe, EnumType type, void *valeur_comparee) {
    if (!cdataframe->nombre_colonnes) {
        return -1;
    }

    int compteur = 0;
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        compteur += retourner_inferieur(cdataframe->colonnes[i], type, valeur_comparee);
    }

    return compteur;
}



void exporter_cdataframe(Cdataframe *cdataframe, char *nom_fichier, char separateur) {
    // Ouvre le fichier en mode écriture
    FILE *fichier = fopen(nom_fichier, "w");

    // Redirige la sortie standard vers le fichier
    freopen(nom_fichier, "w", stdout);

    int i;

    // Affiche les titres des colonnes séparés par le séparateur
    printf("%s", cdataframe->colonnes[0]->titre);
    for (i = 1; i < cdataframe->nombre_colonnes; i++) {
        printf("%c%s", separateur, cdataframe->colonnes[i]->titre);
    }
    printf("\n");

    // Obtient le nombre de lignes du CDataframe
    int nombre_lignes_cdataframe = retourner_nombre_lignes(cdataframe);

    // Boucle sur les lignes du CDataframe
    for (i = 0; i < nombre_lignes_cdataframe; i++) {
        // Affiche la valeur de la première colonne pour la ligne actuelle
        printf("%s", convertir_valeur(cdataframe->colonnes[0], i));
        // Boucle sur les colonnes à partir de la deuxième
        for (int j = 1; j < cdataframe->nombre_colonnes; j++) {
            // Affiche la valeur de chaque colonne pour la ligne actuelle, séparées par le séparateur
            printf("%c%s", separateur, convertir_valeur(cdataframe->colonnes[j], i));
        }
        printf("\n"); // Nouvelle ligne pour chaque ligne du CDataframe
    }

    // Rétablit la sortie standard
    freopen("CON", "w", stdout);

    // Ferme le fichier
    fclose(fichier);

    // Affiche un message indiquant que l'export s'est terminé avec succès
    printf("L'export du CDataframe s'est termine correctement dans le fichier : \"%s\".\n\n", nom_fichier);
}




// Cette fonction retourne la taille maximale parmi toutes les valeurs stockées dans le CDataFrame
int retourner_taille_max(Cdataframe *cdataframe) {
    int taille_max = 4; // taille de la chaine NULL
    int taille_chaine;

    // Parcourt chaque colonne et chaque valeur pour trouver la taille maximale
    for (int i = 0; i < cdataframe->nombre_colonnes; i++) {
        for (int j = 0; j < cdataframe->colonnes[i]->taille_logique; j++) {
            taille_chaine = strlen(convertir_valeur(cdataframe->colonnes[i], j));
            if (taille_chaine > taille_max) {
                taille_max = taille_chaine;
            }
        }
    }

    return taille_max;
}

int longueur_nombre(int nombre) {
    // Vérifie si le nombre est égal à zéro
    if (!nombre) {
        return 1; // Si oui, retourne 1 car la taille d'un nombre zéro est 1
    }

    // Initialise la taille du nombre à 0
    int taille_nombre = 0;

    // Si le nombre est négatif, ajoute 1 à la taille pour prendre en compte le signe "-"
    if (nombre < 0) {
        taille_nombre += 1;
    }

    // Boucle tant que le nombre n'est pas égal à zéro
    while (nombre != 0) {
        // Divise le nombre par 10 pour obtenir le prochain chiffre
        nombre /= 10;
        // Incrémente la taille du nombre
        taille_nombre++;
    }

    // Retourne la taille du nombre
    return taille_nombre;
}

// Cette fonction affiche le titre d'une colonne en ajoutant des espaces pour l'alignement
void afficher_titre_espaces(char *chaine, int taille_chaine_maximale, int longueur_indice_maximale, int longueur_ajout_titre, int indice_colonne) {
    int taille_chaine = strlen(chaine);
    int taille_restante = taille_chaine_maximale - taille_chaine - longueur_ajout_titre;

    printf("| %s", chaine);
    for (int i = 0; i < taille_restante + longueur_indice_maximale - longueur_nombre(indice_colonne); i++) {
        printf(" ");
    }
    printf("   [%d] ", indice_colonne);
}

// Cette fonction affiche une valeur en ajoutant des espaces pour l'alignement
void afficher_valeur_espaces(char *chaine, int taille_chaine_maximale, int cote_affichage) {
    int nombre_espaces = taille_chaine_maximale - strlen(chaine);
    if (!cote_affichage) {
        printf("%s", chaine);
        for (int i = 0; i < nombre_espaces; i++) {
            printf(" ");
        }
    } else {
        for (int i = 0; i < nombre_espaces; i++) {
            printf(" ");
        }
        printf("%s", chaine);
    }
}

// Cette fonction affiche les caractères de fermeture pour une ligne du tableau
void fermer_tableau(int nombre_colonnes, int longueur_chaine, int longueur_nombre_ligne_max) {
    int i;

    printf("|_");
    for (i = 0; i < longueur_nombre_ligne_max; i++) {
        printf("_");
    }
    printf("_");
    for (i = 0; i < nombre_colonnes; i++) {
        printf("|_");
        for (int j = 0; j < longueur_chaine; j++) {
            printf("_");
        }
        printf("_");
    }
    printf("|\n");
}

// Cette fonction affiche un message indiquant que le CDataFrame est vide
void cdataframe_vide() {
    printf("Le CDataframe est vide.\n\n");
}

// Cette fonction affiche un message indiquant qu'une entrée est invalide
void entree_invalide() {
    printf("Entree invalide.\n\n");
}

// Cette fonction retourne le nom du type de données correspondant à une position donnée
char *retourner_nom_type(int position) {
    char *TYPES_CHAINES[] = {"UINT", "INT", "CHAR", "FLOAT", "DOUBLE", "STRING"};
    return TYPES_CHAINES[position];
}
