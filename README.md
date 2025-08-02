# CDataframe - Langage C

Projet en langage C visant à créer une structure de type tableau (dataframe) avec colonnes typées, manipulation de données et export en CSV. Ce projet est inspiré de la bibliothèque `pandas` de Python, dans le but de reproduire certaines de ses fonctionnalités fondamentales en langage bas niveau.

## Fonctionnalités
- Création d’un tableau dynamique avec plusieurs colonnes
- Ajout, suppression, modification de lignes et colonnes
- Affichage formaté du tableau
- Export des données au format CSV
- Gestion mémoire dynamique (avec `malloc`, `realloc`, `free`)

## Fichiers
- `main.c` : programme principal de test
- `colonne.c/.h` : gestion des colonnes
- `cdataframe.c/.h` : gestion de la structure principale
- `cdataframe_export.csv` : exemple d’export CSV
- `affichage_cdataframe.txt` : exemple de sortie texte

## Lancer le programme

Compiler avec :
```bash
gcc main.c cdataframe.c colonne.c -o cdataframe
./cdataframe
```

---

Projet réalisé en avril 2024, mis en ligne ici en juin 2025.
