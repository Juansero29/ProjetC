#include "projet.h"
Adherant *LireTAdherants(int *nbAdherants) {
    Adherant *tAdherants;
    FILE *fb;
    fb = fopen("adherants.bin", "rb");
    if (fb == NULL) {
        printf("Probleme d'ouverture de fichier.\n");
        *nbAdherants = -1;
        return NULL;
    }
    fread(nbAdherants, sizeof(int), 1, fb);
    tAdherants = (Adherant *) malloc(*nbAdherants * sizeof(Adherant));
    if (tAdherants == NULL) {
        printf("Probleme d'allocation de memoire (lecture tAdherants)");
        exit(1);
    }
    fread(tAdherants, sizeof(Adherant), (size_t)*nbAdherants, fb);
    fclose(fb);
    return tAdherants;
}
Jeu *LireTJeux(int *nbJeux) {
    Jeu *tJeux;
    FILE *fb;
    fb = fopen("jeux.bin", "rb");
    if (fb == NULL) {
        printf("Probleme d'ouverture de fichier.\n");
        *nbJeux = -1;
        return NULL;
    }
    fread(nbJeux, sizeof(int), 1, fb);
    tJeux = (Jeu *) malloc(*nbJeux * sizeof(Jeu));
    if (tJeux == NULL) {
        printf("Probleme d'allocation de memoire (lecture tJeux)");
        exit(1);
    }
    fread(tJeux, sizeof(Jeu), (size_t)*nbJeux, fb);
    fclose(fb);
    return tJeux;
}
ApremTh *LireTAprems(int *nbAprems) {
    ApremTh *tAprems;
    FILE *fb;
    fb = fopen("am_thematiques.bin", "rb");
    if (fb == NULL) {
        printf("Probleme d'ouverture de fichier.\n");
        *nbAprems = -1;
        return NULL;
    }
    fread(nbAprems, sizeof(int), 1, fb);
    tAprems = (ApremTh *) malloc(*nbAprems * sizeof(ApremTh));
    if (tAprems == NULL) {
        printf("Probleme d'allocation de memoire (lecture tAprems)");
        exit(1);
    }

    fread(tAprems, sizeof(ApremTh), (size_t)*nbAprems, fb);
    fclose(fb);
    return tAprems;
}
Emprunt *LireEmprunts(int *nbEmprunts){
    FILE *fb;
    fb = fopen("emprunts.bin", "rb");
    if (fb == NULL){
        printf("Probleme d'ouverture de ficiher. \n");
        *nbEmprunts = -1;
        return NULL;
    }
    fread(nbEmprunts, sizeof(int), 1, fb);
    Emprunt *tEmprunt;
    tEmprunt = (Emprunt*) malloc (*nbEmprunts * sizeof(Emprunt));
    if (tEmprunt == NULL){
        printf("Probleme d'allocation de memoire (lecture tEmprunts)");
        exit(1);
    }

    fread(tEmprunt, sizeof(Emprunt), (size_t)*nbEmprunts, fb);
    return tEmprunt;
}
Inscription *LireInscriptions(int *nbInscriptions){
    Inscription *tInscription;
    FILE *fb;
    fb = fopen("inscriptions_am_th.bin", "rb");
    if (fb == NULL) {
        printf("Probleme d'ouverture de fichier.\n");
        *nbInscriptions = -1;
        return NULL;
    }

    fread(nbInscriptions, sizeof(int), 1, fb);

    tInscription = (Inscription*) malloc(*nbInscriptions * sizeof(Inscription));
    if (tInscription == NULL) {
        printf("Probleme d'allocation de memoire (lecture tInscriptions)");
        exit(1);
    }

    fread(tInscription, sizeof(ApremTh), (size_t)*nbInscriptions, fb);
    fclose(fb);
    return tInscription;
}


