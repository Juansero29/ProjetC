#include "projet.h"


void SupprimerAdherant(Adherant tAdherants[], int *nbAdherants) {
    if(*nbAdherants <= 0){
        printf("Aucun adherant n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    int i, numAdherant;
    printf("\n|SUPPRESSION D'UN ADHERANT|\n");
    printf("Saisissez le numero de l'adherant a supprimer: \n");
    scanf("%d", &numAdherant);
    int posAdherant = RechercherAdherant(tAdherants, *nbAdherants, numAdherant);
    while (posAdherant == -1) {
        printf("\nNumero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, *nbAdherants);
        printf("\n");
        scanf("%d", &numAdherant);
        posAdherant = RechercherAdherant(tAdherants, *nbAdherants, numAdherant);
    }
    if(tAdherants[posAdherant].nbEmpCourants > 0){
        printf("\nImpossible de supprimmer un adherant avec des emprunts en cours.\n");
        return;
    }
    for (i = posAdherant; i < *nbAdherants - 1; i++) {
        tAdherants[i] = tAdherants[i + 1];
    }
    *nbAdherants = *nbAdherants - 1;
    printf("La suppression a ete realisee avec succes.\n");
}
void SupprimerJeu(Jeu tJeux[], int *nbJeux){
    if(*nbJeux <= 0){
        printf("Aucun jeu n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    int index, i;
    char nom[20];
    printf("Saissisez le nom du jeu a supprimer: \n");
    getchar();
    fgets(nom, 25, stdin);
    nom[strlen(nom) - 1] = '\0';
    index = RechercherJeu(tJeux, *nbJeux, nom);
    if (index == -1){
        printf("Le jeu a supprimer n'existe pas. \n");
    } else if (tJeux[index].nbEmprunts > 0 || tJeux[index].nbExemplaires > 0){
        char rep;
        printf("Le jeu \"%s\" a %d emprunts en cours et %d exemplaires en stock. Etes-vous sur de vouloir effectuer cette suppression? (O / N)\n", tJeux[index].nom, tJeux[index].nbEmprunts, tJeux[index].nbExemplaires);
        scanf("%c", &rep);
        while (rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n') {
            printf("Saisie incorrecte, veuillez taper 'O' ou 'N'");
            scanf("%c", &rep);
            getchar();
        }
        if (rep == 'o' || rep == 'O') {
            for (i = index; i < *nbJeux - 1; i++){
                tJeux[i] = tJeux[i +1];
            }
            *nbJeux = *nbJeux - 1;
            printf("La suppression a ete realisee avec succes. \n");
            return;
        } else {
            printf("La suppression a ete annulee");
            return;
        }
    }
    for (i = index; i < *nbJeux - 1; i++){
        tJeux[i] = tJeux[i +1];
    }
    *nbJeux = *nbJeux - 1;
    printf("-- La suppression a ete realisee avec succes! --\n");
    return;
}
void RetournerEmprunt(Emprunt tEmprunts[], int *nbEmprunts, Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux) {
    if(*nbEmprunts <= 0){
        printf("Aucun emprunt n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    Emprunt emprunt;
    int i;
    printf("\n| RETOURNER UN EMPRUNT |\n");
    printf("Saisissez le numero de l'Adherant qui retourne un emprunt: \n");
    getchar();
    scanf("%d", &emprunt.numAdherant);
    int posAdherant = RechercherAdherant(tAdherants, nbAdherants, emprunt.numAdherant);
    while (posAdherant == -1) {
        printf("Numero d'adherant inconnu. Vos choix sont parmis la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n");
        scanf("%d", &emprunt.numAdherant);
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
    getchar();
    fgets(emprunt.nomJeu, 25, stdin);
    emprunt.nomJeu[strlen(emprunt.nomJeu) - 1] = '\0';

    int posEmprunt = RechercherEmprunt(tEmprunts, *nbEmprunts, emprunt.numAdherant, emprunt.nomJeu);

    if (posEmprunt == -1) {
        printf("L'emprunt saisi ne figure pas parmi les emprunts actuels. \n");
        sleep(2);
        return;
    }

    time_t t = time(NULL);
    double seconds = 0;
    seconds = difftime(t, tEmprunts[posEmprunt].dateEmprunt.time);
    seconds = seconds / 60;
    seconds = seconds / 60;
    int jours = (int) (seconds / 24);
    if (jours > 21) {
        int retard = jours - 21;
        printf("Cet emprunt a ete rendu avec un retard de %d jours.\n", retard);
    }
    int posJeu = RechercherJeu(tJeux, nbJeux, emprunt.nomJeu);
    tJeux[posJeu].nbEmprunts--;
    tAdherants[posAdherant].nbEmpCourants--;
    for (i = posEmprunt; i < *nbEmprunts - 1; i++) {
        tEmprunts[i] = tEmprunts[i + 1];
    }
    *nbEmprunts = *nbEmprunts - 1;
    system("cls");
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
    scanf("%d", &numAdherant);
    index = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    while (index == -1) {
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n\t Reessayez. Saissisez le numero de l'Adherant a inscrire : \n");
        scanf("%d", &numAdherant);
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
        system("cls");
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
    scanf("%d", &numAdherant);
    posAdherant = RechercherAdherant(tAdherants, nbAdherants , numAdherant);
    while (posAdherant == -1){
        printf("Cet adherant n'existe pas. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n");
        scanf("%d", &numAdherant);
        posAdherant = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    }
    printf("Vous allez maintenant saisir sa date de readhesion :\n");
    Date date = SaisirDate();
    tAdherants[posAdherant].dateAdhesion = date;

    system("cls");
    printf("\n -- Adhesion renouvelee avec succes! --\n");
}


