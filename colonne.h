/**
* "CDataframe"
*
* Ce fichier contient l'ensemble des prototypes des fonctions du fichier colonne.c correspondant à l'ensemble des fonctionnalités développées autour des colonnes
*/

#ifndef UNTITLED_COLONNE_H
#define UNTITLED_COLONNE_H

// Définition de la taille de réallocation pour les colonnes
#define TAILLE_REALLOC 256

// Définition de la longueur maximale des chaînes, avec une longueur de 32 caractères plus le caractère de fin de chaîne
#define LONGUEUR_MAX (32 + 1)

// Déclaration d'une énumération pour les types de données supportés
typedef enum {
    UINT, INT, CHAR, FLOAT, DOUBLE, STRING
} EnumType;

// Déclaration d'une union pouvant contenir différents types de valeurs
typedef union {
    unsigned int        uint_value;
    signed int          int_value;
    char                char_value;
    float               float_value;
    double              double_value;
    char*               string_value;
} TypeCol;

// Définition de la structure de colonne
typedef struct {
    char *titre;                                // Titre de la colonne
    unsigned int taille_logique;                // Taille logique de la colonne
    unsigned int taille_physique;               // Taille physique allouée pour la colonne
    unsigned int taille_reelle;                 // Taille réelle de la colonne
    EnumType type_colonne;                      // Type de données stockées dans la colonne
    TypeCol **donnees;                          // Tableau de pointeurs sur les valeurs stockées
} Colonne;

/**
* @brief: Crée une nouvelle colonne
* @param1 : Type de la colonne
* @param2 : Titre de la colonne
* @return : Pointeur sur la colonne créée
*/
Colonne *creer_colonne(EnumType type, char *titre);

/**
* @brief: Insère une nouvelle valeur dans une colonne
* @param1: Pointeur sur la colonne
* @param2: Pointeur sur la valeur à insérer
* @return: 1 si la valeur est correctement insérée, 0 sinon
*/
int inserer_valeur(Colonne *colonne, void *valeur);

/**
* @brief: Libère l'espace alloué à une colonne
* @param1: Pointeur sur la colonne
*/
void supprimer_colonne(Colonne **colonne);

/**
* @brief: Convertit une valeur en une chaîne de caractères
* @param1: Pointeur sur la colonne
* @param2: Position de la valeur dans le tableau de données
* @param3: Chaîne de caractères dans laquelle la valeur sera écrite
* @param4: Taille maximale de la chaîne de caractères
* @return: Pointeur sur la chaîne de caractères résultante
*/
char *convertir_valeur(Colonne *colonne, unsigned long long int position);

/**
* @brief: Affiche le contenu d'une colonne
* @param1: Pointeur sur la colonne à afficher
* @param2: Entier correspondant à la limite de lignes d'affichage
*/
void afficher_colonne(Colonne *colonne, int limite_ligne);

/**
* @brief: Compare deux chaînes de caractères
* @param1: Première chaîne à comparer
* @param2: Deuxième chaîne à comparer
* @return: 0 si les chaînes sont identiques, 1 si la première est "supérieure" à la deuxième, et -1 sinon
*/
int comparer_chaines(char *chaine_1, char *chaine_2);

/**
* @brief: Retourne le nombre d'occurrences d'une valeur dans une colonne
* @param1: Pointeur sur la colonne
* @param2: Type de la valeur recherchée
* @param3: Valeur recherchée
* @return: Nombre d'occurrences de la valeur recherchée, -1 si aucune colonne
*/
int retourner_egal(Colonne *colonne, EnumType type, void* valeur_recherchee);

/**
* @brief: Retourne la valeur dans une position donnée dans une colonne
* @param1: Pointeur sur la colonne
* @param2: Position recherchée
* @return: Pointeur sur la valeur trouvée
*/
void *retourner_position(Colonne *colonne, int position);

/**
* @brief: Retourne le nombre de valeurs inférieures à une valeur donnée dans une colonne
* @param1: Pointeur sur la colonne
* @param2: Type de la valeur recherchée
* @param3: Valeur à comparer
* @return: Nombre de valeurs inférieures à la valeur donnée, -1 si aucune colonne
*/
int retourner_inferieur(Colonne *colonne, EnumType type, void* valeur_comparee);

/**
* @brief: Retourne le nombre de valeurs supérieures à une valeur donnée dans une colonne
* @param1: Pointeur sur la colonne
* @param2: Type de la valeur recherchée
* @param3: Valeur à comparer
* @return: Nombre de valeurs supérieures à la valeur donnée, -1 si aucune colonne
*/
int retourner_superieur(Colonne *colonne, EnumType type, void* valeur_comparee);


#endif //UNTITLED_COLONNE_H
