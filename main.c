/**
* "CDataframe"
*
* Ce fichier est le fichier principal du projet
*/

#include "colonne.h"
#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("Entrez n'importe quelle touche pour creer un CDataframe, entrez \"n\" pour quitter le programme.\n>");
    
    char choix_caractere;
    scanf("%c", &choix_caractere);
    printf("\n");
    
    if (choix_caractere == 'n') {
        return 0;
    } else {
        // Crée un nouveau CDataframe
        Cdataframe *cdataframe = creer_cdataframe();

        // Vérifie si l'allocation du CDataframe a réussi
        if (!cdataframe) {
            printf("Une erreur d'allocation est survenue.\nFin du programme.\n");
            return -1; // Termine le programme avec un code d'erreur
        }

        // Remplit le CDataframe avec des données prédéfinies et les écrit dans un fichier
        remplir_cdataframe_en_dur(cdataframe); ecrire_cdataframe_fichier(NOM_FICHIER_AFFICHAGE, cdataframe, 0, 0); //afficher_cdataframe(cdataframe, 0, 0); // à commenter si remplir par utilisateur

        // Vérifie si le CDataframe est vide
        if (!cdataframe->nombre_colonnes) {
            printf("Votre CDataframe est vide.\nEntrez n'importe quelle touche afin de remplir le CDataframe, entrez \"n\" sinon.\n>");
            scanf("%c", &choix_caractere);
            printf("\n");
            
            // Vérifie si l'utilisateur souhaite remplir le CDataframe
            if (choix_caractere != 'n') {
                remplir_cdataframe_utilisateur(cdataframe);
            }
        }

        int boucle_1;
        int resultat;
        
        while (1) {
            int choix_entier;
            printf("Voici les differentes fonctionnalites auxquelles vous pouvez acceder en entrant le numero associe :\n\n"
            "1 : Affichage\n"
            "2 : Operations usuelles\n"
            "3 : Analyses statistiques\n"
            "4 : Exporter le CDataframe dans un fichier CSV\n"
            "5 : Quitter\n\n>");
            scanf(" %d", &choix_entier);
            printf("\n");

            switch (choix_entier) {
                case 1:
                    boucle_1 = 1;
                    while (boucle_1) {
                        printf("Entrez le numero associe a la fonctionnalite :\n\n"
                        "1 : Afficher l'integralite du CDataframe\n"
                        "2 : Afficher l'integralite du CDataframe en brut\n"
                        "3 : Afficher une partie du CDataframe\n"
                        "4 : Afficher une partie du CDataframe en brut\n"
                        "5 : Exporter l'affichage du CDataframe dans un fichier\n"
                        "6 : Retour\n\n>");
                        scanf(" %d", &choix_entier);
                        printf("\n");

                        int limite_lignes, limite_colonnes;

                        switch (choix_entier) {
                            case 1:
                                afficher_cdataframe(cdataframe, 0, 0);

                                printf("Souhaitez vous exporter l'affichage dans un fichier \"affichage_cdataframe.txt\" ?\nEntrez n'importe quelle touche pour continuer, entrez \"n\" sinon.\n>");
                                scanf(" %c", &choix_caractere);
                                printf("\n");
                                if (choix_caractere != 'n') {
                                    ecrire_cdataframe_fichier(NOM_FICHIER_AFFICHAGE, cdataframe, 0, 0);
                                }
                                break;

                            case 2:
                                afficher_cdataframe_brut(cdataframe, 0, 0);
                                break;

                            case 3:
                                printf("Entrez une limite de lignes (entrez \"0\" si vous voulez afficher l'ensemble des lignes) :\n>");
                                scanf(" %d", &limite_lignes);
                                printf("Entrez une limite de colonnes (entrez \"0\" si vous voulez afficher l'ensemble des colonnes) :\n>");
                                scanf(" %d", &limite_colonnes);
                                printf("\n");

                                afficher_cdataframe_limite(cdataframe, limite_lignes, limite_colonnes);

                                printf("Souhaitez vous exporter l'affichage dans un fichier \"affichage_cdataframe.txt\" ?\nEntrez n'importe quelle touche pour continuer, entrez \"n\" sinon.\n>");
                                scanf(" %c", &choix_caractere);
                                printf("\n");
                                if (choix_caractere != 'n') {
                                    ecrire_cdataframe_fichier(NOM_FICHIER_AFFICHAGE, cdataframe, limite_lignes, limite_colonnes);
                                }
                                break;

                            case 4:
                                printf("Entrez une limite de lignes (entrez \"0\" si vous voulez afficher l'ensemble des lignes) :\n>");
                                scanf(" %d", &limite_lignes);
                                printf("Entrez une limite de colonnes (entrez \"0\" si vous voulez afficher l'ensemble des colonnes) :\n>");
                                scanf(" %d", &limite_colonnes);
                                printf("\n");

                                afficher_cdataframe_brut(cdataframe, limite_lignes, limite_colonnes); 
                                break;

                            case 5:
                                ecrire_cdataframe_fichier(NOM_FICHIER_AFFICHAGE, cdataframe, 0, 0);
                                break;

                            case 6:
                                boucle_1 = 0;
                                break;
                            default:
                                entree_invalide();
                        }
                    }
                    break;

                case 2:
                    boucle_1 = 1;
                    while (boucle_1) {
                        printf("Entrez le numero associe a la fonctionnalite :\n\n"
                        "1 : Ajouter une ligne de valeurs\n"
                        "2 : Supprimer une ligne de valeurs d'indice i\n"
                        "3 : Ajouter des colonnes au CDataframe\n"
                        "4 : Supprimer une colonne d'indice i\n"
                        "5 : Renommer le titre d'une colonne du CDataframe d'indice i\n"
                        "6 : Verifier l'existence d'une valeur x\n"
                        "7 : Acceder a la valeur se trouvant dans une cellule du CDataframe a partir de ses indices de positions\n"
                        "8 : Remplacer la valeur se trouvant dans une cellule du CDataframe a partir de ses indices de positions\n"
                        "9 : Afficher les noms de l'integralite des colonnes\n"
                        "10 : Inserer une valeur dans une colonne d'indice i\n"
                        "11 : Retour\n\n>");
                        scanf(" %d", &choix_entier);
                        printf("\n");

                        switch (choix_entier) {
                            case 1:
                                ajouter_ligne(cdataframe);
                                break;

                            case 2:
                                printf("Entrez l'indice de la ligne que vous souhaitez supprimer (vous pouvez afficher le CDataframe pour acceder a son indice) :\n>");
                                scanf(" %d", &choix_entier);
                                supprimer_ligne_indice(cdataframe, choix_entier);
                                break;

                            case 3:
                                remplir_cdataframe_utilisateur(cdataframe);
                                break;

                            case 4:
                                printf("Entrez l'indice de la colonne que vous souhaitez supprimer (vous pouvez afficher le CDataframe pour acceder a son indice) :\n>");
                                scanf(" %d", &choix_entier);
                                supprimer_colonne_indice(cdataframe, choix_entier);
                                break;

                            case 5:
                                printf("Entrez l'indice de la colonne que vous souhaitez renommer (vous pouvez afficher le CDataframe pour acceder a son indice) :\n>");
                                scanf(" %d", &choix_entier);
                                renommer_colonne(cdataframe, choix_entier);
                                break;

                            case 6:
                                resultat = choix_type(cdataframe, '!');
                                if (!resultat) {
                                    printf("La valeur n'existe pas dans le CDataframe.\n\n");
                                } else if (resultat == 1) {
                                    printf("La valeur existe dans le CDataframe.\n\n");
                                }
                                break;

                            case 7:
                                afficher_valeur_indice(cdataframe);
                                break;

                            case 8:
                                remplacer_valeur_cdataframe(cdataframe);
                                break;

                            case 9:
                                afficher_noms_colonnes(cdataframe);
                                break;

                            case 10:
                                printf("Entrez l'indice de la colonne ou vous souhaitez ajouter une valeur (vous pouvez afficher le CDataframe pour acceder a son indice) :\n>");
                                scanf(" %d", &choix_entier);
                                if (choix_entier > cdataframe->nombre_colonnes - 1 || choix_entier < 0) {
                                    printf("L'indice de colonne saisi est trop faible ou trop eleve.\n\n");
                                } else {
                                    printf("Entrez la valeur de la colonne d'indice %d que vous souhaitez ajouter (type %s) :\n>", choix_entier, retourner_nom_type(cdataframe->colonnes[choix_entier]->type_colonne));
                                    
                                    switch (cdataframe->colonnes[choix_entier]->type_colonne) {
                                        case INT:
                                            {int choix_valeur;
                                            scanf(" %d", &choix_valeur);
                                            inserer_valeur(cdataframe->colonnes[choix_entier], &choix_valeur);
                                            break;}
                                        case CHAR:
                                            {char choix_valeur;
                                            scanf(" %c", &choix_valeur);
                                            inserer_valeur(cdataframe->colonnes[choix_entier], &choix_valeur);
                                            break;}
                                        case FLOAT:
                                            {float choix_valeur;
                                            scanf(" %f", &choix_valeur);
                                            inserer_valeur(cdataframe->colonnes[choix_entier], &choix_valeur);
                                            break;}
                                        case UINT:
                                            {unsigned int choix_valeur;
                                            scanf(" %u", &choix_valeur);
                                            inserer_valeur(cdataframe->colonnes[choix_entier], &choix_valeur);
                                            break;}
                                        case DOUBLE:
                                        {double choix_valeur;
                                            scanf(" %lf", &choix_valeur);
                                            inserer_valeur(cdataframe->colonnes[choix_entier], &choix_valeur);
                                            break;}
                                        case STRING:
                                            {char *choix_valeur = malloc(LONGUEUR_MAX * sizeof(char));
                                            scanf(" %s", choix_valeur);
                                            inserer_valeur(cdataframe->colonnes[choix_entier], &choix_valeur);
                                            break;}
                                    }
                                    // Complète le CDataframe avec des valeurs NULL pour toutes les colonnes
                                    completion_cdataframe(cdataframe);

                                    printf("\nLa valeur a bien ete ajoute.\n\n");
                                }
                                break;

                            case 11:
                                boucle_1 = 0;
                                break;
                            default:
                                entree_invalide();
                        }
                    }
                    break;
                case 3:
                    boucle_1 = 1;
                    while (boucle_1) {
                        printf("Entrez le numero associe a la fonctionnalite :\n\n"
                            "1 : Afficher le nombre de lignes du CDataframe\n"
                            "2 : Afficher le nombre de colonnes du CDataframe\n"
                            "3 : Nombre de cellules contenant une valeur egale a x\n"
                            "4 : Nombre de cellules contenant une valeur superieure a x\n"
                            "5 : Nombre de cellules contenant une valeur inferieure a x\n"
                            "6 : Retour\n\n>");
                        scanf(" %d", &choix_entier);
                        switch (choix_entier) {
                            case 1:
                                resultat = retourner_nombre_lignes(cdataframe);
                                if (resultat == -1) {
                                    cdataframe_vide();
                                } else {
                                    printf("Le CDataframe contient %d lignes.\n\n", retourner_nombre_lignes(cdataframe));
                                }
                                break;

                            case 2:
                                printf("Le CDataframe contient %d colonnes.\n\n", cdataframe->nombre_colonnes);
                                break;

                            case 3:
                                resultat = choix_type(cdataframe, '=');
                                if (resultat == -1) {
                                    cdataframe_vide();
                                } else {
                                    printf("Le nombre de cellules contenant la valeur entree est : %d\n\n", resultat);
                                }
                                break;

                            case 4:
                                resultat = choix_type(cdataframe, '>');
                                if (resultat == -1) {
                                    cdataframe_vide();
                                } else {
                                    printf("Le nombre de cellules superieures a la valeur entree est : %d\n\n", resultat);
                                }
                                break;

                            case 5:
                                resultat = choix_type(cdataframe, '<');
                                if (resultat == -1) {
                                    cdataframe_vide();
                                } else {
                                    printf("Le nombre de cellules inferieures a la valeur entree est : %d\n\n", resultat);
                                }
                                break;

                            case 6:
                                boucle_1 = 0;
                                break;
                            default:
                                entree_invalide();
                        }
                    }
                    break;

                case 4:
                    printf("Entrez le caractere que vous souhaitez utiliser pour separer les valeurs parmi : \",\" ou \";\" :\n>");
                    scanf(" %c", &choix_caractere);
                    if (choix_caractere == ',' || choix_caractere == ';') {
                        exporter_cdataframe(cdataframe, NOM_FICHIER_CSV, choix_caractere);
                    } else {
                        entree_invalide();
                    }
                    break;

                case 5:
                    return 0;
                default:
                    entree_invalide();
            }
        }
    }
}