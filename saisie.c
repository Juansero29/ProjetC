#include "projet.h"

Date SaisirDate() {
    Date date;
    printf("\nEntrez la date en format JJ/MM/AAAA:\n");
    scanf("%d/%d/%d",&date.jour,&date.mois,&date.annee);
    while(date.jour < 1 || date.jour > 31 || date.mois < 1 || date.mois > 12 || date.annee < 1900 || date.annee > 2150){
        printf("\nSaisie incorrecte. Reessayez (au format JJ/MM/AAAA) :\n");
        scanf("%d/%d/%d", &date.jour, &date.mois, &date.annee);
    }

    struct tm *temps;
    time_t tempsOr;
    time(&tempsOr);
    temps = localtime(&tempsOr);
    temps->tm_year = date.annee - 1900;
    temps->tm_mon = date.mois - 1;
    temps->tm_mday = date.jour;
    date.time = mktime(temps);
    //printf("\n-- Date saisie avec succes :  %d/%d/%d --\n\n", temps->tm_mday, temps->tm_mon + 1,temps->tm_year + 1900);
    return date;
}
Adherant SaisirAdherant(Adherant tAdherants[], int nbAdherants) {
    printf("\n\n|SAISIE D'UN ADHERANT| \n\n");

    Adherant adherant;

    adherant.numAdherant = ((int) CreerIdentifiant(4))%MAX_NUMADHERANT;
    int index = RechercherAdherant(tAdherants, nbAdherants, adherant.numAdherant);
    while (index != -1) {
        adherant.numAdherant = ((int) CreerIdentifiant(4))%MAX_NUMADHERANT;
        index = RechercherAdherant(tAdherants, nbAdherants, adherant.numAdherant);
    }
    printf("Num. Adherant: %d\n", adherant.numAdherant);
    getchar();
    printf("Entrez son nom (14 caracteres maximum): \n");
    fgets(adherant.nomAdherant, 15, stdin);
    adherant.nomAdherant[strlen(adherant.nomAdherant)-1]= '\0';
    printf("Entrez son prenom (14 caracteres maximum): \n");
    fgets(adherant.prenomAdherant, 15, stdin);
    adherant.prenomAdherant[strlen(adherant.prenomAdherant)-1]= '\0';
    printf("Vous allez maintenant saisir sa date d'adhesion :\n");
    adherant.dateAdhesion = SaisirDate();
    adherant.nbEmpCourants = 0;
    system("cls");
    printf("\n-- Adherant saisi avec succes! --\n");
    return adherant;
}
Emprunt SaisirEmprunt(Jeu tJeux[], Adherant tAdherants[], int nbJeux, int nbAdherants) {
    Emprunt emprunt;
    printf("\n\n|SAISIE D'UN EMPRUNT| \n\n");
    printf("Saisissez le numero de l'Adherant qui veut emprunter : \n");
    getchar();
    scanf("%d", &emprunt.numAdherant);
    int posAdherant = RechercherAdherant(tAdherants, nbAdherants, emprunt.numAdherant);
    while (posAdherant == -1) {
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n");
        scanf("%d", &emprunt.numAdherant);
        posAdherant = RechercherAdherant(tAdherants, nbAdherants, emprunt.numAdherant);
    }
    time_t t = time(NULL);
    double seconds = difftime(t, tAdherants[posAdherant].dateAdhesion.time);
    seconds = seconds / 60;
    seconds = seconds / 60;
    int jours = (int) (seconds / 24);
    if (jours > 365) {
        printf("L'adhesion de cet adherant a expiree!.");
        return emprunt;
    }
    if (tAdherants[posAdherant].nbEmpCourants >= 3){
        printf("L'adherant %s emprunte deja 3 jeux. Il doit en ramener avant de pouvoir reemprunter.", tAdherants[posAdherant].nomAdherant);
    }
    printf("Vous allez saisir la date de l'emprunt: \n");
    emprunt.dateEmprunt = SaisirDate();
    printf("Saisissez le nom du jeu emprunte : \n");
    getchar();
    fgets(emprunt.nomJeu, 25, stdin);
    emprunt.nomJeu[strlen(emprunt.nomJeu) - 1] = '\0';
    int posJeu = RechercherJeu(tJeux, nbJeux, emprunt.nomJeu);
    while (posJeu == -1) {
        printf("\nCe jeu n'existe pas. Voici la liste des jeux existants :\n");

        AfficherJeux(tJeux, nbJeux);
        printf("\n");
        printf("Saisissez le nom du jeu a emprunter : \n");
        fgets(emprunt.nomJeu, 25, stdin);
        emprunt.nomJeu[strlen(emprunt.nomJeu) - 1] = '\0';
        posJeu = RechercherJeu(tJeux, nbJeux, emprunt.nomJeu);
    }
    if (tJeux[posJeu].nbExemplaires - tJeux[posJeu].nbEmprunts == 0){
        printf("Ce jeu ne peut pas etre emprunte, car tous les exemplaires sont actuellement empruntes.");
        return emprunt;
    } else{
        tJeux[posJeu].nbEmprunts++;
        tAdherants[posAdherant].nbEmpCourants++;
    }
    system("cls");
    printf("\n-- Emprunt ajoute avec succes! --\n");
    return emprunt;
}
ApremTh SaisirApremTh(ApremTh tAprems[], int nbAprems) {

    ApremTh apremTh;
    printf("\n\n|SAISIE APRES-MIDI THEMATIQUE|\n\n");
    apremTh.date = SaisirDate();
    printf("Quel est le nombre correspondant a l'heure de debut de l'evenement ? (format 24h) :\n");
    scanf("%d", &apremTh.heureDebut);
    while (apremTh.heureDebut < 1 || apremTh.heureDebut > 23) {
        printf("Saisie incorrecte (format 24h, entrez 2 chiffres). Reessayez :\n");
        scanf("%d", &apremTh.heureDebut);
    }
    printf("Quel sera le nombre de places ?\n");
    scanf("%d", &apremTh.nbPlaces);

    apremTh.nbAdhInscrits = 0;
    strcpy(apremTh.codeAprem, CreerIdentifiant(2));
    int index = RechercherAprem(tAprems, nbAprems, apremTh.codeAprem);
    while (index != -1) {
        strcpy(apremTh.codeAprem, CreerIdentifiant(2));
        index = RechercherAprem(tAprems, nbAprems, apremTh.codeAprem);
    }
    system("cls");
    printf("\n-- Apres-midi thematique cree avec succes! --\n");
    return apremTh;
}
Jeu SaisirJeu(Jeu tJeux[], int nbJeux, int *indexDoublon) {
    printf("\n\n|SAISIE D'UN JEU|\n\n");
    Jeu jeu;
    int nbCateg;
    printf("Saisissez le nom du jeu : \n");
    getchar();
    fgets(jeu.nom, 25, stdin);
    jeu.nom[strlen(jeu.nom) - 1] = '\0';
    int index = RechercherJeu(tJeux, nbJeux, jeu.nom);
    while (index != -1) {
        printf("Le nom saisi figure deja parmi les jeux existants. Voulez vous ajouter un examplaire pour le jeu \"%s\" ? (O / N)\n",
               tJeux[index].nom);
        char rep;
        scanf("%c", &rep);
        getchar();
        while (rep != 'O' && rep != 'N' && rep != 'o' && rep != 'n') {
            printf("Saisie incorrecte, veuillez taper 'O' ou 'N'");
            scanf("%c", &rep);
            getchar();
        }
        if (rep == 'o' || rep == 'O') {
            *indexDoublon = index;
            printf("\n-- Un exemplaire supplementaire a ete ajoute! -- \n");
            return jeu;
        } else {
            printf("Saissisez donc un nom pour le nouveau jeu : \n");
            fgets(jeu.nom, 25, stdin);
            index = RechercherJeu(tJeux, nbJeux, jeu.nom);
            jeu.nom[strlen(jeu.nom) - 1] = '\0';
        }
    }
    printf("Quelle est la categorie du jeu ?(Entrez le numero correspondant)"
                   "\n\t 1: Jeu de construction\n\t 2: Jeu de cartes"
                   "\n\t 3: Jeu de logique\n\t 4: Jeu de plateau\n");
    scanf("%d", &nbCateg);

    while (!(nbCateg == 1 || nbCateg == 2 || nbCateg == 3 || nbCateg == 4)) {
        printf("Saisie incorrecte. (possibilites : 1, 2, 3 ou 4)\n");
        printf("Quelle est la categorie du jeu ?(Entrez le numero correspondant)"
                       "\n\t 1: Jeu de construction\n\t 2: Jeu de cartes"
                       "\n\t 3: Jeu de logique\n\t 4: Jeu de plateau\n");
        scanf("%d", &nbCateg);
    }
    switch (nbCateg) {
        case 1:
            strcpy(jeu.nomCategorie, "Jeu de construction");
            break;
        case 2:
            strcpy(jeu.nomCategorie, "Jeu de cartes");
            break;
        case 3:
            strcpy(jeu.nomCategorie, "Jeu de logique");
            break;
        case 4:
            strcpy(jeu.nomCategorie, "Jeu de plateau");
            break;
        default:
            break;

    }
    jeu.nbEmprunts = 0;
    jeu.nbExemplaires = 1;
    system("cls");
    printf("\n -- Jeu ajoute avec succes! -- \n");
    return jeu;
}
Inscription SaisirInscription(ApremTh tApremTh[], int nbAprem, Adherant tAdherants[], int nbAdherants, Inscription tInscriptions[], int nbInscriptions) {
    printf("\n\n|SAISIE D'UNE INSCRIPTION A UNE APRES-MIDI|");
    Inscription inscrip;
    int indexAprem, indexAdherant;
    char *numAprem;
    numAprem = malloc(sizeof(char) * (6));
    int numAdherant;
    printf("\nSaisissez le numero de l'apres-midi thematique a laquelle l'adherant souhaite s'inscrire: ");
    scanf("%s", numAprem);
    indexAprem = RechercherAprem(tApremTh, nbAprem, numAprem);

    while (indexAprem == -1) {
        printf("\nCet apres-midi n'existe pas, faites votre choix parmi la liste suivante: \n");
        AfficherApremsIncomplets(tApremTh, nbAprem);
        printf("\nTapez le numero de l'apres-midi: \n");
        scanf("%s", numAprem);
        indexAprem = RechercherAprem(tApremTh, nbAprem, numAprem);
    }
    printf("\n\nL'apres-midi a ete trouve: \nNum. Aprem: %s\nDate : %d/%d/%d\nHeure de debut: %d heures.\n\n",
           tApremTh[indexAprem].codeAprem, tApremTh[indexAprem].date.jour, tApremTh[indexAprem].date.mois,
           tApremTh[indexAprem].date.annee, tApremTh[indexAprem].heureDebut);
    if (tApremTh[indexAprem].nbPlaces == tApremTh[indexAprem].nbAdhInscrits) {
        printf("Il ne reste plus de places pour cet evenement. Impossible d'inscrire quelqu'un de plus");
        inscrip.numAdherant = 0;
        return inscrip;
    }
    strcpy(inscrip.codeAprem, numAprem);

    tApremTh[indexAprem].nbAdhInscrits++;

    printf("Quel est le numero de l'Adherant a inscrire ?\n");
    scanf("%d", &numAdherant);
    indexAdherant = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    while (indexAdherant == -1) {
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, nbAdherants);
        printf("\n\t Reessayez. Saissisez le numero de l'Adherant a inscrire: \n");
        scanf("%d", &numAdherant);
        indexAdherant = RechercherAdherant(tAdherants, nbAdherants, numAdherant);
    }
    indexAdherant = RechercherInscription(tInscriptions, nbInscriptions, numAprem, numAdherant);

    if (indexAdherant != -1) {
        printf("L'adherant est deja inscrit a cette apres-midi !\n");
        inscrip.numAdherant = -1;
        return inscrip;
    }
    strcpy(inscrip.codeAprem, numAprem);
    tApremTh[indexAprem].nbAdhInscrits++;
    inscrip.numAdherant = numAdherant;
    system("cls");
    printf("\n -- Adherant inscrit avec succes! --\n");
    return inscrip;
}

