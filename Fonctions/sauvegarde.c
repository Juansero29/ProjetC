#include "../projet.h"

void SauverAdherants(Adherant tAdherants[], int nbAdherants) {

    FILE *fb;
    fb = fopen("bin/adherants.bin", "wb");
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nbAdherants, sizeof(int), 1, fb);
    fwrite(tAdherants, sizeof(Adherant), (size_t) nbAdherants, fb);
    fclose(fb);
}
void SauverJeux(Jeu tJeux[], int nbJeux) {
    FILE *fb;
    fb = fopen("bin/jeux.bin", "wb");
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nbJeux, sizeof(int), 1, fb);
    fwrite(tJeux, sizeof(Jeu), (size_t) nbJeux, fb);
    fclose(fb);
}
void SauverAprems(ApremTh tAprem[], int nbAprem) {

    FILE *fb;
    fb = fopen("bin/am_thematiques.bin", "wb");
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nbAprem, sizeof(int), 1, fb);
    fwrite(tAprem, sizeof(ApremTh), (size_t) nbAprem, fb);
    fclose(fb);
}
void SauverEmprunts(Emprunt tEmprunts[], int nbEmprunts) {

    FILE *fb;
    fb = fopen("bin/emprunts.bin", "wb");
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nbEmprunts, sizeof(int), 1, fb);
    fwrite(tEmprunts, sizeof(Emprunt), (size_t) nbEmprunts, fb);
    fclose(fb);
}
void SauverInscriptions(Inscription tInscriptions[], int nbInscrits) {
    FILE *fb;
    fb = fopen("bin/inscriptions_am_th.bin", "wb");
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nbInscrits, sizeof(int), 1, fb);
    fwrite(tInscriptions, sizeof(Inscription), (size_t) nbInscrits, fb);
    fclose(fb);
}
void Sauvegarder(Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux, ApremTh tAprem[], int nbAprem, Emprunt tEmprunts[], int nbEmprunts, Inscription tInscriptions[], int nbInscrits) {

    SauverAdherants(tAdherants, nbAdherants);
    SauverJeux(tJeux, nbJeux);
    SauverAprems(tAprem, nbAprem);
    SauverEmprunts(tEmprunts, nbEmprunts);
    SauverInscriptions(tInscriptions, nbInscrits);

}
