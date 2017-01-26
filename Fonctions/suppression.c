#include "../projet.h"


void SupprimerAdherant(Adherant tAdherants[], int *nbAdherants, Inscription tInscriptions[], int nbInscriptions) {
    if(*nbAdherants <= 0){
        printf("Aucun adherant n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    int i, numAdherant;
    printf("\n|SUPPRESSION D'UN ADHERANT|\n");
    printf("Saisissez le numero de l'adherant a supprimer: \n");
    numAdherant = SaisirEntier();
    int posAdherant = RechercherAdherant(tAdherants, *nbAdherants, numAdherant);
    while (posAdherant == -1) {
        printf("\nNumero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, *nbAdherants);
        printf("\n");
        numAdherant = SaisirEntier();
        posAdherant = RechercherAdherant(tAdherants, *nbAdherants, numAdherant);
    }
    if(tAdherants[posAdherant].nbEmpCourants > 0){
        system("clear");
        printf("\nImpossible de supprimmer un adherant avec des emprunts en cours. Veuillez retourner premierement ses emprunts.\n");
        return;
    }
    if(AdherantEstDansUneAMT(numAdherant, tInscriptions, nbInscriptions) == 1){
        system("clear");
        printf("\nImpossible de supprimmer un adherant inscrit a une apres-midi. Veuillez premierement lui desinscrire de tous les apres-midis.\n\n");
        return;
    }
    for (i = posAdherant; i < *nbAdherants - 1; i++) {
        tAdherants[i] = tAdherants[i + 1];
    }
    *nbAdherants = *nbAdherants - 1;
    system("clear");
    printf("\nLa suppression a ete realisee avec succes.\n");
}
void SupprimerJeu(Jeu tJeux[], int *nbJeux){
    if(*nbJeux <= 0){
        printf("Aucun jeu n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    int i;
    char nom[20];
    printf("Saisissez le nom du jeu a supprimer : \n");
    fgets(nom, 25, stdin);
    nom[strlen(nom) - 1] = '\0';
    int posJeu = RechercherJeu(tJeux, *nbJeux, nom);
    while (posJeu == -1) {
        printf("\nCe jeu n'existe pas. Voici la liste des jeux existants :\n");

        AfficherJeux(tJeux, *nbJeux);
        printf("\n");
        printf("Saisissez le nom du jeu a emprunter : \n");
        fgets(nom, 25, stdin);
        nom[strlen(nom) - 1] = '\0';
        posJeu = RechercherJeu(tJeux, *nbJeux, nom);
    }
    if (tJeux[posJeu].nbEmprunts > 0 || tJeux[posJeu].nbExemplaires > 0){
        printf("\nLe jeu %s a %d emprunts en cours et %d exemplaires.\nVeuillez retourner l'emprunt de ce jeu avant de effectuer la suppression.\n", tJeux[posJeu].nom, tJeux[posJeu].nbEmprunts, tJeux[posJeu].nbExemplaires);
        printf("\nLa suppression a ete annulee. \n");
        sleep(5);
        system("clear");
        return;
    }
    for (i = posJeu; i < *nbJeux - 1; i++){
        tJeux[i] = tJeux[i +1];
    }
    *nbJeux = *nbJeux - 1;
    system("clear");
    printf("-- La suppression a ete realisee avec succes! --\n");
    return;
}
void RetournerEmprunt(Emprunt tEmprunts[], int *nbEmprunts, Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux) {
    if(*nbEmprunts <= 0 || nbAdherants <= 0){
        printf("Aucun emprunt ou adherant n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    Emprunt emprunt;
    int i;
    printf("\n| RETOURNER UN EMPRUNT |\n");
    printf("Saisissez le numero de l'Adherant qui retourne un emprunt: \n");
    emprunt.numAdherant = SaisirEntier();
    int posAdherant = RechercherAdherant(tAdherants, nbAdherants, emprunt.numAdherant);
    while (posAdherant == -1) {
        printf("Numero d'adherant inconnu. Vos choix sont parmis la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n");
        emprunt.numAdherant = SaisirEntier();
        posAdherant = RechercherAdherant(tAdherants, nbAdherants, emprunt.numAdherant);
    }
    if (tAdherants[posAdherant].nbEmpCourants == 0) {
        printf("Cet adherant n'a aucun emprunt en cours\n");
        return;
    }

    printf("Voici les jeux que cet adherant a emprunte(s) :\n");

    for (i = 0; i < *nbEmprunts; i++) {
        if (tEmprunts[i].numAdherant == emprunt.numAdherant) {
            printf("\t%s", tEmprunts[i].nomJeu);
        }
    }

    printf("\n\nSaissisez le nom du jeu : \n");
    fgets(emprunt.nomJeu, 25, stdin);
    emprunt.nomJeu[strlen(emprunt.nomJeu) - 1] = '\0';

    int posEmprunt = RechercherEmprunt(tEmprunts, *nbEmprunts, emprunt.numAdherant, emprunt.nomJeu);

    if (posEmprunt == -1) {
        printf("\nL'emprunt saisi ne figure pas parmi les emprunts actuels. \n");
        sleep(2);
        return;
    }

    time_t t = time(NULL);
    double seconds = 0;
    seconds = difftime(t, tEmprunts[posEmprunt].dateEmprunt.time);
    seconds = seconds / 60;
    seconds = seconds / 60;
    int jours = (int) (seconds / 24);
    system("clear");
    if (jours > 21) {
        int retard = jours - 21;
        printf("\n\nCet emprunt a ete rendu avec un retard de %d jours.\n", retard);
    }
    int posJeu = RechercherJeu(tJeux, nbJeux, emprunt.nomJeu);
    tJeux[posJeu].nbEmprunts--;
    tAdherants[posAdherant].nbEmpCourants--;
    for (i = posEmprunt; i < *nbEmprunts - 1; i++) {
        tEmprunts[i] = tEmprunts[i + 1];
    }
    *nbEmprunts = *nbEmprunts - 1;

    printf("\n-- Emprunt rendu avec succes! --- \n");
}
void SupprimerInscription(Inscription tInscriptions[], int *nbInscriptions, ApremTh tAprems[], int nbAprems, Adherant tAdherants[], int nbAdherants){
    if(*nbInscriptions <= 0){
        printf("Aucune inscription n'a ete trouvee. Impossible de supprimer. \n");
        return;
    }
    int numAdherant, index;
    char *numAprem;
    numAprem = malloc(sizeof(char) * (6));
    printf("\n|ANNULER L'INSCRIPTION A UNE APRES-MIDI|\n");
    printf("Saisissez le numero de l'adherant qui veut annuler son inscription : ");
    numAdherant = SaisirEntier();
    index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    while (index == -1) {
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n\t Reessayez. Saissisez le numero de l'Adherant a inscrire : \n");
        numAdherant = SaisirEntier();
        index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    }
    printf("Cet adherant est inscrit aux apres-midis suivantes: \n");
    int i, j=0;
    for(i=0; i < *nbInscriptions; i++){
        if(tInscriptions[i].numAdherant == numAdherant){
            Afficher1Aprem(tAprems, nbAprems, tInscriptions[i].codeAprem);
            j++;
        }
    }
    if (j == 0){
        system("clear");
        printf("\nCet adherant n'est inscrit a aucune apres-midi. Impossible d'annuler une inscription.\n");
        return;
    }
    printf("\n\nEntrez le numero d'apres-midi de laquelle il veut se desinscrire.\n");
    scanf("%s", numAprem);
    index = RechercherAprem(tAprems, nbAprems, numAprem);
    while (index == -1) {
        printf("\nL'adherant n'est pas inscrit a cette apres-midi. Voici celles auxquelles il l'est :\n");
        for(i=0; i < nbAprems; i++){
            if(tInscriptions[i].numAdherant == numAdherant){
                Afficher1Aprem(tAprems, nbAprems, tInscriptions[i].codeAprem);
            }
        }
        printf("\n\nEntrez le numero de l'apres-midi: \n");
        scanf("%s", numAprem);
        index = RechercherAprem(tAprems, nbAprems, numAprem);
    }
    tAprems[index].nbAdhInscrits--;

    index = RechercherInscription(tInscriptions, *nbInscriptions, numAprem, numAdherant);
    for (i = index; i < *nbInscriptions - 1; i++){
        tInscriptions[i] = tInscriptions[i +1];
    }
    *nbInscriptions = *nbInscriptions - 1;
    printf("-- Le adherant a bien annule son inscription! --\n");
}
void RenouvellerAdhesion(Adherant tAdherants[], int nbAdherants){
    printf("\n\n|RENOUVELLEMENT D'UN ADHESION ANNUEL|\n\n");
    int posAdherant, numAdherant;

    if (nbAdherants == 0){
        printf("Aucun adherant n'est enregistre. Impossible de renouveller.\n "); return;
    }
    printf("Saisissez le numero de l'adherant qui souhaite renouveller son adhesion : \n");
    numAdherant = SaisirEntier();
    posAdherant = RechercherAdherant(tAdherants, nbAdherants , numAdherant);
    while (posAdherant == -1){
        printf("Cet adherant n'existe pas. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n");
        numAdherant = SaisirEntier();
        posAdherant = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    }
    printf("Vous allez maintenant saisir sa date de readhesion :\n");
    Date date = SaisirDate();
    tAdherants[posAdherant].dateAdhesion = date;

    system("clear");
    printf("\n -- Adhesion renouvelee avec succes! --\n");
}


