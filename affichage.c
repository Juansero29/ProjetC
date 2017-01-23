//
// Created by Juan on 1/22/2017.
//

#include "projet.h"

void Afficher1Adherant(Adherant adherant)  {
    printf("\n\n ADHERANT # : %d\n\tnom : %s\n\tprenom : %s\n\tnbEmpCourants : %d\n\tdateAdhesion : %d/%d/%d\n\n",
           adherant.numAdherant, adherant.nomAdherant, adherant.prenomAdherant, adherant.nbEmpCourants,
           adherant.dateAdhesion.jour, adherant.dateAdhesion.mois, adherant.dateAdhesion.annee);
}
void AfficherAdherants(Adherant tAdherants[], int nbAdherants) {
    int i;
    for (i = 0; i < nbAdherants; i++) {
        Afficher1Adherant(tAdherants[i]);
    }
    if(nbAdherants == 0){
        printf("\nAucun adherant n'a ete trouve.\n");
        return;
    }
}
void AfficherJeux(Jeu tJeux[], int nbJeux) {

    int i;
    for (i = 0; i < nbJeux; i++) {
        printf("\n\nNom : %s (%s) - # Exemplaires: %d \n", tJeux[i].nom, tJeux[i].nomCategorie, tJeux[i].nbExemplaires);
    }
    if(nbJeux == 0){
        printf("\nAucun jeu n'a ete trouve.\n");
        return;
    }
}
void AfficherAprems(ApremTh tAprems[], int nbAprems){
    if (nbAprems == 0) {
        printf("\nAucune apres-midi n'a ete trouvee.\n");
        return;
    }
    int i;
    for (i = 0; i < nbAprems; i++) {
        printf("\n\nNum. Aprem: %s\nDate : %d/%d/%d\nHeure de debut: %d heures.\n", tAprems[i].codeAprem, tAprems[i].date.jour, tAprems[i].date.mois, tAprems[i].date.annee, tAprems[i].heureDebut);
    }
}
void AfficherApremsIncomplets(ApremTh tAprems[], int nbAprems) {

    if (nbAprems == 0) {
        printf("\nAucune apres-midi n'a ete trouvee.\n");
        return;
    }
    int i;
    for (i = 0; i < nbAprems; i++) {
        if (tAprems[i].nbPlaces != tAprems[i].nbAdhInscrits) {
            printf("\n\nNum. Aprem: %s\nDate : %d/%d/%d\nHeure de debut: %d heures.\n", tAprems[i].codeAprem,
                   tAprems[i].date.jour,
                   tAprems[i].date.mois, tAprems[i].date.annee, tAprems[i].heureDebut);
        }
    }
}
void Afficher1Aprem(ApremTh tAprems[], int nbAprems, char codeAprem[5]){

    int i = RechercherAprem(tAprems, nbAprems, codeAprem);
    if(i != -1){
        printf("\n\nNum. Aprem: %s\nDate : %d/%d/%d\nHeure de debut: %d heures.\nNombre de places: %d\nAdherants inscrits: %d\n", tAprems[i].codeAprem, tAprems[i].date.jour, tAprems[i].date.mois, tAprems[i].date.annee, tAprems[i].heureDebut, tAprems[i].nbPlaces, tAprems[i].nbAdhInscrits);
    } else {
        printf("\nCette apres-midi n'a pas ete trouvee.\n");
    }
}
void AfficherAprem(ApremTh tAprems[], int nbAprems, Inscription tInscriptions[], int nbInscriptions, Adherant tAdherants[], int nbAdherants){
    if(nbAprems == 0){
        printf("\nAucune apres-midi n'a ete trouve. \n");
        return;
    }
    int index; char numAprem[5];
    printf("\nSaisissez le code de l'apres-midi thematique dont vous souhaitez voir la liste d'inscrits: \n");
    scanf("%s", numAprem);
    index = RechercherAprem(tAprems, nbAprems, numAprem);
    while (index == -1) {
        printf("\nCette apres-midi n'existe pas, choissisez-en une parmi la liste suivante: \n");
        AfficherAprems(tAprems, nbAprems);
        printf("\nTapez le numero de l'apres-midi:\n");
        scanf("%s", numAprem);
        index = RechercherAprem(tAprems, nbAprems, numAprem);
    }
    int i;
    printf("\n| ADHERANTS INSCRITS |\n");
    if(tAprems[index].nbAdhInscrits == 0){
        printf("\nAucun adherent n'est inscrit dans cette apres-midi\n");
    }
    for(i=0; i < nbInscriptions; i++){
        if(strcmp(tInscriptions[i].codeAprem, numAprem) == 0){
            index = RechercherAdherant(tAdherants,nbAdherants,tInscriptions[i].numAdherant);
            printf("\n\n ADHERANT # : %d\n\tnom : %s\n\tprenom : %s\n\tnbEmpCourants : %d\n\tdateAdhesion : %d/%d/%d\n\n",
                   tAdherants[index].numAdherant, tAdherants[index].nomAdherant, tAdherants[index].prenomAdherant, tAdherants[index].nbEmpCourants,
                   tAdherants[index].dateAdhesion.jour, tAdherants[index].dateAdhesion.mois, tAdherants[index].dateAdhesion.annee);
        }
    }

}
void AfficherEmprunts(Emprunt tEmprunts[], int nbEmprunts){
    int i;
    for(i=0; i<nbEmprunts;i++){
        printf("\n\nNom du jeu: %s\nNum. Emprunteur: %d\nDate d'emprunt : %d/%d/%d\n\n",tEmprunts[i].nomJeu, tEmprunts[i].numAdherant, tEmprunts[i].dateEmprunt.jour, tEmprunts[i].dateEmprunt.mois, tEmprunts[i].dateEmprunt.annee);
    }
    if(nbEmprunts == 0){
        printf("\nAucun emprunt n'a ete trouve.\n");
        return;
    }
}
void AfficherRetards(Adherant tAdherants[], int nbadherants, Emprunt tEmprunts[], int nbEmprunts) {
    if(nbadherants <= 0 && nbEmprunts <= 0){
        printf("\nAucun adherant ni emprunt enregistre. Impossible de detecter des retards.\n");
        return;
    }
    if(nbadherants <=  0){
        printf("\nAucun adherant n'a ete trouve. Il n'y a donc pas de retards.\n");
        return;
    }
    if(nbEmprunts <= 0){
        printf("\nAucun emprunt en cours. Il n'y a donc pas de retards.\n");
        return;
    }
    int i, j=0;
    for (i = 0; i < nbEmprunts; i++) {
        time_t t = time(NULL);
        double seconds;
        seconds = difftime(t, tEmprunts[i].dateEmprunt.time);
        seconds = seconds / 60;
        seconds = seconds / 60;
        int days = (int) (seconds / 24);
        if (days >= 21) {
            int pos = RechercherAdherant(tAdherants, nbadherants, tEmprunts[i].numAdherant);
            Afficher1Adherant(tAdherants[pos]);
            j++;
        }
    }
    if(j==0){
        printf("\nAucun emprunt n'est en retard a la date.\n");
    }
}

void permuter(Jeu t[], int i, int j){
    Jeu tmp;
    tmp=t[i];
    t[i]=t[j];
    t[j]=tmp;
}
int partition(Jeu t[], int deb, int fin) {
    int compt = deb;
    Jeu pivot = t[deb];
    int i;
    for (i = deb + 1; i <= fin; i++) {
        if (strcmp(t[i].nom, pivot.nom) <= 0){
            compt++;
            permuter(t, compt, i);
        }
    }
    permuter(t, compt, deb);
    return (compt);
}
void tri_rapide_(Jeu t[], int debut, int fin) {
    if (debut < fin) {
        int pivot = partition(t, debut, fin);
        tri_rapide_(t, debut, pivot - 1);
        tri_rapide_(t, pivot + 1, fin);
    }
}
void tri_rapide(Jeu t[], int nbJeux) {
    tri_rapide_(t, 0, nbJeux - 1);
}

/* TriRapide:
 * D'abord, cette fonction fait un partitionnemment du tableau des jeux en deux parties. Puis, elle fait un tri indépendant des deux sous-tableaux obtenus.
 * Le point de départ pour effectuer cet partitionnement est indiqué par l'index 'pivot'. Le pivot sera placé toujours à ça place definitive (trié).
 * Puis, on procède donc a permuter les elements de telle sorte que tous les éléments dans la partie gauche soient inferieurs au pivot et tous les éléments dans la partie droite soient supérieurs au pivot.
 * Finalement on définit un pivot pour chacun des sous-tablaux et on repète le partitionnement.
 * Ce processus est répété de manière recursive jusqu'à ce que tous les éléments soient triés.*/