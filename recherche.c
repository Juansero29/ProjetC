#include "projet.h"

int RechercherAdherant(Adherant tAdherants[], int nbAdherants, int numAdherant) {
    int i;
    for (i = 0; i < nbAdherants; i++) {
        if (tAdherants[i].numAdherant == numAdherant)
            return i;
    }
    return -1;
}
int RechercherAprem(ApremTh tAprem[], int nbAprem, char numAprem[5]) {
    int i;
    for (i = 0; i < nbAprem; i++) {
        if (strcmp(tAprem[i].codeAprem, numAprem) == 0)
            return i;
    }
    return -1;
}
int RechercherJeu(Jeu tJeux[], int nbJeux, char nomJeu[25]) {
    if (strcmp(tJeux[nbJeux].nom, nomJeu) == 0) {
        return nbJeux;
    }
    if (nbJeux == -1){
        return -1;
    }
    return RechercherJeu(tJeux, nbJeux - 1, nomJeu);
}
int RechercherEmprunt(Emprunt tEmprunts[], int nbEmprunts, int numAdherant, char nomJeu[]){
    if (strcmp(tEmprunts[nbEmprunts].nomJeu, nomJeu) == 0 && tEmprunts[nbEmprunts].numAdherant == numAdherant) {
        return nbEmprunts;
    }
    if (nbEmprunts == -1){
        return -1;
    }
    return RechercherEmprunt(tEmprunts, nbEmprunts - 1, numAdherant, nomJeu);
}
int RechercherInscription(Inscription tInscriptions[], int nbInscriptions, char numAprem[5], int numAdherant){
    if (strcmp(tInscriptions[nbInscriptions].codeAprem, numAprem) == 0 && tInscriptions[nbInscriptions].numAdherant == numAdherant) {
        return nbInscriptions;
    }
    if (nbInscriptions == -1){
        return -1;
    }
    return RechercherInscription(tInscriptions, nbInscriptions - 1, numAprem, numAdherant);
}

