#include "projet.h"


//Recherches Recursives
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
int RechercherJeu(Jeu tJeux[], int nbJeux, char nomJeu[25]) {
    if (strcmp(tJeux[nbJeux].nom, nomJeu) == 0) {
        return nbJeux;
    }
    if (nbJeux == -1){
        return -1;
    }
    return RechercherJeu(tJeux, nbJeux - 1, nomJeu);
}


/*Cette fonction effectue une recheche de facon dichotomique. On divise l'ensemble en deux moitiés.
 * On commence par comparer le nom recherché avec le milieu du tableau. Si le nom est inférieur au nom du milieu,
 * le nom recherché doit se trouver forcement dans la premier moitié du tableau.
 * Sinon, le nom doit se trouver dans la deuxième moitié du tableau.
 * Pur chaque cas cas, on fait un appel récursif en passant a parametres la moitié du tableau concerné.*/
/*int RechercherJeu(Jeu tJeux[], int nbJeux, char nom[25]){
    int pos, m;
    if(nbJeux == 0){
        return nbJeux;
    }
    if(nbJeux == 1) {
        if (strcmp(nom, tJeux[nbJeux].nom) <= 0) {
            return 0;
        } else {
            return 1;
        }
    }
    m = (nbJeux -1)/ 2;
    if(strcmp(nom, tJeux[m].nom) <= 0) {
        pos = RechercherJeu(tJeux, m + 1, nom);
    }
    else{
        pos = m+1+RechercherJeu(tJeux+m+1, nbJeux-(m + 1), nom );
    }
    return pos;
}
*/