/**
* "CDataframe"
*
* Ce fichier contient l'ensemble des prototypes des fonctions du fichier cdataframe.c correspondant à l'ensemble des fonctionnalités développées autour du CDataframe
*/

#include "colonne.h"

#ifndef UNTITLED_CDATAFRAME_H
#define UNTITLED_CDATAFRAME_H


// Définition des noms de fichiers pour l'affichage et l'exportation CSV
#define NOM_FICHIER_AFFICHAGE "affichage_cdataframe.txt"
#define NOM_FICHIER_CSV "cdataframe_export.csv"

// Définition de la structure CDataframe qui représente un DataFrame de colonnes
typedef struct {
    Colonne **colonnes;    // Tableau de pointeurs vers les colonnes
    int nombre_colonnes;   // Nombre de colonnes actuellement dans le DataFrame
    int capacite;          // Capacité maximale du DataFrame
} Cdataframe;

// ------------------
// 1. Alimentation
// ------------------

// Crée un nouveau CDataframe vide
Cdataframe *creer_cdataframe();

// Ajoute une colonne à un CDataframe existant
int ajouter_colonne(Cdataframe *cdataframe, Colonne *colonne);

// Complète un CDataframe avec des valeurs NULL en fonction du nombre de ligne du CDataframe
void completion_cdataframe(Cdataframe *cdataframe);

// Remplit un CDataframe en demandant à l'utilisateur d'entrer les valeurs pour chaque colonne
void remplir_cdataframe_utilisateur(Cdataframe *cdataframe); 

// Remplit un CDataframe avec des valeurs prédéfinies
void remplir_cdataframe_en_dur(Cdataframe *cdataframe);

// ------------------
// 2. Affichage
// ------------------

// Affiche un CDataframe dans la console avec des limites spécifiées
void afficher_cdataframe(Cdataframe *cdataframe, int limite_ligne, int limite_colonne);

// Affiche un CDataframe dans la console sans aucune limite
void afficher_cdataframe_brut(Cdataframe *cdataframe, int limite_ligne, int limite_colonne);

// Écrit un CDataframe dans un fichier texte spécifié
void ecrire_cdataframe_fichier(char *nom_fichier, Cdataframe *cdataframe, int limite_ligne, int limite_colonne);

// Affiche un CDataframe dans la console avec des limites spécifiées
void afficher_cdataframe_limite(Cdataframe *cdataframe, int limite_ligne, int limite_colonne);

// ------------------
// 3. Opérations usuelles
// ------------------

// Ajoute une nouvelle ligne au CDataframe
void ajouter_ligne(Cdataframe *cdataframe);

// Supprime une ligne du CDataframe selon son indice
void supprimer_ligne_indice(Cdataframe *cdataframe, int indice_ligne);

// Supprime une colonne du CDataframe selon son indice
void supprimer_colonne_indice(Cdataframe *cdataframe, int indice_colonne);

// Renomme une colonne du CDataframe selon son indice
void renommer_colonne(Cdataframe *cdataframe, int indice_colonne);

// Effectue le choix du type de données pour une opération donnée
int choix_type(Cdataframe *cdataframe, char fonction);

// Vérifie l'existence d'une valeur dans le CDataframe
int existence_valeur(Cdataframe *cdataframe, EnumType type, void* valeur_recherchee);

// Affiche les indices des valeurs du CDataframe (et les retourne)
int *afficher_valeur_indice(Cdataframe *cdataframe);

// Remplace une valeur du CDataframe par une nouvelle valeur saisie par l'utilisateur
void remplacer_valeur_cdataframe(Cdataframe *cdataframe);

// Affiche les noms des colonnes du CDataframe
void afficher_noms_colonnes(Cdataframe *cdataframe);

// ------------------
// 4. Analyse et statistiques
// ------------------

// Retourne le nombre de lignes dans le CDataframe
int retourner_nombre_lignes(Cdataframe *cdataframe);

// Compte le nombre de cellules contenant une valeur spécifique dans le CDataframe
int compter_cellules_valeur(Cdataframe *cdataframe, EnumType type, void *valeur_recherchee);

// Compte le nombre de cellules contenant une valeur supérieure à une valeur spécifique dans le CDataframe
int compter_cellules_superieures(Cdataframe *cdataframe, EnumType type, void *valeur_comparee);

// Compte le nombre de cellules contenant une valeur inférieure à une valeur spécifique dans le CDataframe
int compter_cellules_inferieures(Cdataframe *cdataframe, EnumType type, void *valeur_comparee);

// ------------------
// Fonction CSV
// ------------------

// Exporte le CDataframe vers un fichier CSV avec un séparateur spécifié
void exporter_cdataframe(Cdataframe *cdataframe, char *nom_fichier, char separateur);

// ------------------
// Fonctions réservées à l'affichage du CDataframe
// ------------------

// Retourne la taille maximale des données du CDataframe
int retourner_taille_max(Cdataframe *cdataframe);

// Calcule la longueur d'un nombre entier
int longueur_nombre(int nombre);

// Affiche un titre avec des espaces pour aligner les colonnes
void afficher_titre_espaces(char *chaine, int taille_chaine_maximale, int longueur_indice_maximale, int longueur_ajout_titre, int indice_colonne);

// Affiche une valeur avec des espaces pour aligner les colonnes
void afficher_valeur_espaces(char *chaine, int taille_chaine_maximale, int cote_affichage);

// Ferme le tableau affiché dans la console
void fermer_tableau(int nombre_colonnes, int longueur_chaine, int longueur_nombre_ligne_max);

// ------------------
// Autres fonctions
// ------------------

// Retourne le nom d'un type de données selon sa position
char *retourner_nom_type(int position);

// Affiche un message d'erreur lorsque le CDataframe est vide
void cdataframe_vide();

// Affiche un message d'erreur pour une entrée invalide
void entree_invalide();

#endif //UNTITLED_CDATAFRAME_H
