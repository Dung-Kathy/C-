#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ETUDIANTS 100
#define MAX_NOTES 5

typedef struct {
    char nom[50];
    float notes[MAX_NOTES];
    int nb_notes;
} Etudiant;

void ajouterEtudiant(Etudiant etudiants[], int *nb_etudiants) {
    if (*nb_etudiants >= MAX_ETUDIANTS) {
        printf("Nombre maximum d'étudiants atteint !\n");
        return;
    }
    
    Etudiant e;
    printf("Nom de l'étudiant : ");
    scanf(" %[^\n]", e.nom);

    printf("Combien de notes (max %d) ? ", MAX_NOTES);
    scanf("%d", &e.nb_notes);

    for (int i = 0; i < e.nb_notes; i++) {
        printf("Note %d : ", i + 1);
        scanf("%f", &e.notes[i]);
    }

    etudiants[*nb_etudiants] = e;
    (*nb_etudiants)++;
    printf("Étudiant ajouté avec succès !\n");
}

void afficherMoyennes(Etudiant etudiants[], int nb_etudiants) {
    printf("\n---- Moyennes des Étudiants ----\n");
    for (int i = 0; i < nb_etudiants; i++) {
        float somme = 0.0;
        for (int j = 0; j < etudiants[i].nb_notes; j++) {
            somme += etudiants[i].notes[j];
        }
        float moyenne = somme / etudiants[i].nb_notes;
        printf("%s : %.2f\n", etudiants[i].nom, moyenne);
    }
    printf("--------------------------------\n");
}

void sauvegarderFichier(Etudiant etudiants[], int nb_etudiants) {
    FILE *fichier = fopen("etudiants.txt", "w");
    if (!fichier) {
        printf("Erreur lors de la sauvegarde des données.\n");
        return;
    }

    for (int i = 0; i < nb_etudiants; i++) {
        fprintf(fichier, "%s\n%d\n", etudiants[i].nom, etudiants[i].nb_notes);
        for (int j = 0; j < etudiants[i].nb_notes; j++) {
            fprintf(fichier, "%.2f\n", etudiants[i].notes[j]);
        }
    }
    fclose(fichier);
    printf("Données sauvegardées avec succès !\n");
}

void chargerFichier(Etudiant etudiants[], int *nb_etudiants) {
    FILE *fichier = fopen("etudiants.txt", "r");
    if (!fichier) {
        printf("Aucune donnée à charger.\n");
        return;
    }

    *nb_etudiants = 0;
    while (fscanf(fichier, " %[^\n]", etudiants[*nb_etudiants].nom) == 1) {
        fscanf(fichier, "%d", &etudiants[*nb_etudiants].nb_notes);
        for (int j = 0; j < etudiants[*nb_etudiants].nb_notes; j++) {
            fscanf(fichier, "%f", &etudiants[*nb_etudiants].notes[j]);
        }
        (*nb_etudiants)++;
    }
    fclose(fichier);
    printf("Données chargées avec succès !\n");
}

int main() {
    Etudiant etudiants[MAX_ETUDIANTS];
    int nb_etudiants = 0;

    int choix;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Afficher les moyennes\n");
        printf("3. Sauvegarder dans un fichier\n");
        printf("4. Charger depuis un fichier\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterEtudiant(etudiants, &nb_etudiants);
                break;
            case 2:
                afficherMoyennes(etudiants, nb_etudiants);
                break;
            case 3:
                sauvegarderFichier(etudiants, nb_etudiants);
                break;
            case 4:
                chargerFichier(etudiants, &nb_etudiants);
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Essayez à nouveau.\n");
        }
    } while (choix != 5);

    return 0;
}
