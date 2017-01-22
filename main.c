#include "projet.h"
#define MAX_NUMADHERANT 999


char *CreerIdentifiant(int length) {
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    size_t stringLen = 69;
    char *Identifiant;

    Identifiant = malloc(sizeof(char) * (length +1));

    if (!Identifiant) {
        return (char*)0;
    }

    unsigned int cle = 0;

    for (int n = 0;n < length;n++) {
        cle = rand() % stringLen;
        Identifiant[n] = string[cle];
    }

    Identifiant[length] = '\0';

    return Identifiant;
}

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

void Afficher1Adherant(Adherant adherant) {
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
void Afficher1Aprem(ApremTh tAprems[], int nbAprems, char numAprem[5]){

    int i = RechercherAprem(tAprems, nbAprems, numAprem);
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
        printf("\nAucun emprunt n'est pas en retard a la date.\n");
    }
}


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
    printf("\n-- Date saisie avec succes :  %d/%d/%d --\n\n", temps->tm_mday, temps->tm_mon + 1,temps->tm_year + 1900);
    return date;
}
Adherant SaisirAdherant(Adherant tAdherants[], int nbAdherants) {
    printf("\n");
    printf("|SAISIE D'UN ADHERANT| \n");
    printf("\n");
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
    printf("\n");
    printf("|SAISIE D'UN EMPRUNT| \n");

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
    }
    system("cls");
    printf("\n-- Emprunt ajoute avec succes! --\n");
    return emprunt;
}
ApremTh SaisirApremTh(ApremTh tAprems[], int nbAprems) {

    ApremTh apremTh;
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
    // todo voulez-vous inscrire l'adhérant à une autre aprem ?

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
        printf("L'adherant est deja inscrit pour cette apres-midi !\n");
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


Adherant *ChargerTAdherants(Adherant tAdherants[], int *nbAdherants, int *taillePhysique, int nbAjouts) {
    if(*nbAdherants == 0) {
        *taillePhysique += 3;
        tAdherants = (Adherant *) malloc(*taillePhysique * sizeof(Adherant));
        if (tAdherants == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);
        }
    }
    Adherant a, *tAdherantsBuffer;
    int adherantsDeb = *nbAdherants;
    for (; *nbAdherants < (nbAjouts + adherantsDeb); *nbAdherants+=1) {
        if (*nbAdherants == *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            tAdherantsBuffer = (Adherant *) realloc(tAdherants, *taillePhysique * sizeof(Adherant));
            if (tAdherantsBuffer == NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            tAdherants = tAdherantsBuffer;
        }
        a = SaisirAdherant(tAdherants, *nbAdherants);
        tAdherants[*nbAdherants] = a;
    }
    return tAdherants;
}
Jeu *ChargerTJeux(Jeu tJeux[], int *nbJeux, int *taillePhysique, int nbAjouts) {
    if(*nbJeux == 0) {
        *taillePhysique += 3;
        tJeux = (Jeu *) malloc(*taillePhysique * sizeof(Jeu));
        if (tJeux == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);
        }
    }
    Jeu jeu, *tJeuxBuffer;
    int jeuxDeb = *nbJeux;
    for (; *nbJeux < (nbAjouts + jeuxDeb); *nbJeux += 1) {
        if (*nbJeux ==
            *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            tJeuxBuffer = (Jeu *) realloc(tJeux, *taillePhysique * sizeof(Jeu));
            if (tJeuxBuffer == NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            tJeux = tJeuxBuffer;
        }
        int indexDoublon = -1;
        jeu = SaisirJeu(tJeux, *nbJeux, &indexDoublon);
        if (indexDoublon != -1) {
            tJeux[indexDoublon].nbExemplaires += 1;
            jeuxDeb-=1;
            *nbJeux-=1;
        } else {
            tJeux[*nbJeux] = jeu;
        }
    }
    return tJeux;
}
ApremTh *ChargerTAprem(ApremTh tAprem[], int *nbAprems, int *taillePhysique, int nbAjouts) {
    if(*nbAprems == 0) {
        *taillePhysique += 3;
        tAprem = (ApremTh *) malloc(*taillePhysique * sizeof(ApremTh));
        if (tAprem == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);
        }
    }
    ApremTh aprem, *tApremBuffer;
    int apremDeb = *nbAprems;
    for (; *nbAprems < (nbAjouts + apremDeb); *nbAprems+=1) {
        if (*nbAprems == *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            tApremBuffer = (ApremTh *) realloc(tAprem, *taillePhysique * sizeof(ApremTh));
            if (tApremBuffer == NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            tAprem = tApremBuffer;
        }
        aprem = SaisirApremTh(tAprem, *nbAprems);
        tAprem[*nbAprems] = aprem;
    }
    return tAprem;
}
Emprunt *ChargerTEmprunts(Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux, Emprunt tEmprunt[], int *nbEmprunts, int *taillePhysique, int nbAjouts){
    if(*nbEmprunts == 0) {
        *taillePhysique += 3;
        tEmprunt = (Emprunt *) malloc(*taillePhysique * sizeof(Emprunt));
        if (tEmprunt == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);
        }
    }
    Emprunt emprunt, *tEmpruntBuffer;
    int empruntDeb = *nbEmprunts;
    for (; *nbEmprunts < (nbAjouts + empruntDeb); *nbEmprunts+=1) {
        if (*nbEmprunts == *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            tEmpruntBuffer = (Emprunt *) realloc(tEmprunt, *taillePhysique * sizeof(Emprunt));
            if (tEmpruntBuffer == NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            tEmprunt = tEmpruntBuffer;
        }
        emprunt = SaisirEmprunt(tJeux, tAdherants, nbJeux, nbAdherants);
        tEmprunt[*nbEmprunts] = emprunt;
    }
    return tEmprunt;
}
Inscription *ChargerTInscriptions(Inscription tInscriptions[], int *nbInscriptions,  int *taillePhysique, ApremTh tApremTh[], int nbAprems, Adherant tAdherants[], int nbAdherants, int nbAjouts) {
    if(*nbInscriptions == 0) {
        *taillePhysique += 3;
        tInscriptions = (Inscription *) malloc(*taillePhysique * sizeof(Inscription));
        if (tInscriptions == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);
        }
    }
    Inscription inscription, *tInscriptionBuffer;
    int inscriptionsDeb = *nbInscriptions;
    for (; *nbInscriptions < (nbAjouts + inscriptionsDeb); *nbInscriptions += 1) {
        if (*nbInscriptions == *taillePhysique) {
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            tInscriptionBuffer = (Inscription *) realloc(tInscriptions, *taillePhysique * sizeof(Inscription));
            if (tInscriptionBuffer == NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            tInscriptions = tInscriptionBuffer;
        }
        inscription = SaisirInscription(tApremTh, nbAprems, tAdherants, nbAdherants, tInscriptions, *nbInscriptions);
        if (inscription.numAdherant != -1) {
            tInscriptions[*nbInscriptions] = inscription;
        } else {
            *nbInscriptions -= 1;
            inscriptionsDeb -= 1;
        }
    }
    return tInscriptions;
}


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

void SauverAdherants(Adherant tAdherants[], int nbAdherants) {

    FILE *fb;
    fb = fopen("adherants.bin", "wb");
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
    fb = fopen("jeux.bin", "wb");
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
    fb = fopen("am_thematiques.bin", "wb");
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
    fb = fopen("emprunts.bin", "wb");
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
    fb = fopen("inscriptions_am_th.bin", "wb");
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

/*void ToutLire(Adherant tAdherants[], int *nbAdherants, Jeu tJeux[], int *nbJeux, ApremTh tAprem[], int *nbAprems, Emprunt tEmprunts[], int *nbEmprunts, Inscription tInscriptions[], int *nbInscrits){
    if( access( "adherants.bin", F_OK ) == -1 ) {
        SauverAdherants(tAdherants, *nbAdherants);
    }
    if( access( "am_thematiques.bin", F_OK ) == -1 ) {
        SauverAprems(tAprem, *nbAprems);
    }
    if( access( "emprunts.bin", F_OK ) == -1 ) {
        SauverEmprunts(tEmprunts, *nbEmprunts);
    }
    if( access( "inscriptions_am_th.bin", F_OK ) == -1 ) {
        SauverInscriptions(tInscriptions, *nbInscrits);
    }
    if( access( "jeux.bin", F_OK ) == -1 ) {
        SauverJeux(tJeux, *nbJeux);
    }

    tAdherants = LireTAdherants(nbAdherants);
    if(tAdherants==NULL){printf("Probleme de lissage.");}
    tJeux = LireTJeux(nbJeux);
    if(tJeux==NULL){printf("Probleme de lissage.");}
    tAprem = LireTAprems(nbAprems);
    if(tAprem==NULL){printf("Probleme de lissage.");}
    tEmprunts = LireEmprunts(nbEmprunts);
    if(tEmprunts==NULL){printf("Probleme de lissage.");}
    tInscriptions = LireInscriptions(nbInscrits);
    if(tInscriptions==NULL){printf("Probleme de lissage.");}
}*/

void SupprimerAdherant(Adherant tAdherants[], int *nbAdherants) {

    int i, numAdherant;
    printf("\n|SUPPRESSION D'UN ADHERANT|\n");
    printf("Saisissez le numero de l'adherant a supprimer: ");
    scanf("%d", &numAdherant);
    int posAdherant = RechercherAdherant(tAdherants, *nbAdherants, numAdherant);
    while (posAdherant == -1) {
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(tAdherants, *nbAdherants);
        printf("\n");
        scanf("%d", &numAdherant);
        posAdherant = RechercherAdherant(tAdherants, *nbAdherants, numAdherant);
    }
    for (i = posAdherant; i < *nbAdherants - 1; i++) {
        tAdherants[i] = tAdherants[i + 1];
    }
    *nbAdherants = *nbAdherants - 1;
    printf("La suppression a ete realisee avec succes.\n");
}
void SupprimerJeu(Jeu tJeux[], int *nbJeux){
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
void RetournerEmprunt(Emprunt tEmprunts[], int *nbEmprunts, Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux){
    Emprunt emprunt; int i;
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

    printf("Saissisez le nom du jeu : \n");
    getchar();
    fgets(emprunt.nomJeu, 25, stdin);
    emprunt.nomJeu[strlen(emprunt.nomJeu) - 1] = '\0';
    // todo a ameliorer : on montre les emprunts qu'a fait cet adherant, et on fait un while pour que l'utilisateur selectionne un des elements de la liste

    int posEmprunt = RechercherEmprunt(tEmprunts, *nbEmprunts, emprunt.numAdherant, emprunt.nomJeu);
    if(posEmprunt == -1){
        printf("L'emprunt saisi ne figure pas parmi les emprunts actuels. \n");
        sleep(2);
        return;
    }

    time_t t = time(NULL);
    double seconds=0;
    seconds = difftime(t, tEmprunts[posEmprunt].dateEmprunt.time);
    seconds = seconds / 60;
    seconds = seconds / 60;
    int jours = (int)(seconds / 24);
    if(jours > 21){
        int retard = jours - 21;
        printf("Cet emprunt a ete rendu avec un retard de %d jours.\n", retard);
    }
    int posJeu = RechercherJeu(tJeux, nbJeux, emprunt.nomJeu);
    tJeux[posJeu].nbEmprunts--;
    tAdherants[posAdherant].nbEmpCourants--;
    for (i = posEmprunt; i < *nbEmprunts - 1; i++){
        tEmprunts[i] = tEmprunts[i +1];
    }
    *nbEmprunts = *nbEmprunts - 1;
    printf(" -- Emprunt retourne avec succes! --");
}
void SupprimerInscription(Inscription tInscriptions[], int *nbInscriptions, ApremTh tAprems[], int nbAprems, Adherant tAdherants[], int nbAdherants){
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
        }
    }
    if (j == 0){
        system("cls");
        printf("\nCet adherant n'est inscrit a aucun apres-midi. Impossible d'annuller une inscription.\n");
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


int main() {
/*Penser à implementer les constraintes nécessaires:
     *  todo - mettre fonctions dans .h
    */

    //Initialisation des tailles logiques.
    int nbAdherants=0, nbJeux=0, nbEmprunts=0, nbInscrits=0, nbAprems=0;

    //Initialisation des tableaux utilises dans le programme.
    Adherant *tAdherants=NULL; Jeu *tJeux=NULL; Emprunt *tEmprunt=NULL; Inscription *tInscription=NULL; ApremTh *tAprem=NULL;


    //Initialisation des tailles physiques.
    int tP_tAdh=0, tP_tJe=0, tP_tEmp=0, tP_tInsc=0, tP_tApr=0, choix = 0;

    //Lire les fichiers qui sont dans le repertoire courant, récuperer les informations.}
    if( access( "adherants.bin", F_OK ) == -1 ) {
        SauverAdherants(tAdherants, nbAdherants);
    }
    if( access( "am_thematiques.bin", F_OK ) == -1 ) {
        SauverAprems(tAprem, nbAprems);
    }
    if( access( "emprunts.bin", F_OK ) == -1 ) {
        SauverEmprunts(tEmprunt, nbEmprunts);
    }
    if( access( "inscriptions_am_th.bin", F_OK ) == -1 ) {
        SauverInscriptions(tInscription, nbInscrits);
    }
    if( access( "jeux.bin", F_OK ) == -1 ) {
        SauverJeux(tJeux, nbJeux);
    }
    tAdherants = LireTAdherants(&nbAdherants);
    tJeux = LireTJeux(&nbJeux);
    tEmprunt = LireEmprunts(&nbEmprunts);
    tInscription = LireInscriptions(&nbInscrits);
    tAprem = LireTAprems(&nbAprems);


    //Presenter le menu
    do
    {   int choix2 = 0;
        printf("\n\n| MENU PRINCIPAL |\n\n");
        printf("1. ENREGISTRER UN NOUVEL ADHERENT. \n");
        printf("2. ENREGISTRER UN EMPRUNT\n");
        printf("3. AJOUTER UN NOUVEAU JEU\n");
        printf("4. ENREGISTRER UN NOUVEL APREM THEMATIQUE\n");
        printf("5. ENREGISTRER INSCRIPTION A APREM THEMATIQUE\n");
        printf("6. AFFICHER UNE LISTE. \n");
        printf("7. SUPPRIMER UN ADHERENT. \n");
        printf("8. SUPPRIMER UN JEU.\n");
        printf("9. RETOURNER UN EMPRUNT. \n");
        printf("10. ANNULER UNE INSCRIPTION \n");
        printf("11. QUITTER.\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                system("cls");
                tAdherants = ChargerTAdherants(tAdherants, &nbAdherants, &tP_tAdh, 1); //Chargue le tableau 'tAdherants' avec un Adherant.
                SauverAdherants(tAdherants, nbAdherants); //Sauvegarde le tableau retourne dans le fichier correspondant.
                break;
            case 2:
                system("cls");
                tEmprunt = ChargerTEmprunts(tAdherants, nbAdherants, tJeux, nbJeux, tEmprunt, &nbEmprunts, &tP_tEmp, 1);
                SauverEmprunts(tEmprunt, nbEmprunts);
                break;
            case 3:
                system("cls");
                tJeux = ChargerTJeux(tJeux, &nbJeux, &tP_tJe, 1);
                SauverJeux(tJeux, nbJeux);
                break;
            case 4:
                system("cls");
                tAprem = ChargerTAprem(tAprem, &nbAprems, &tP_tApr, 1);
                SauverAprems(tAprem, nbAprems);
                break;
            case 5:
                system("cls");
                tInscription = ChargerTInscriptions(tInscription, &nbInscrits, &tP_tInsc, tAprem, nbAprems, tAdherants, nbAdherants, 1);
                SauverInscriptions(tInscription, nbInscrits);
                break;
            case 6:
                system("cls");
                choix2 = 0;
                do {
                    printf("\n\n| AFFICHER |\n\n");
                    printf("1. AFFICHER LA LISTE DE JEUX. (ORDRE ALPHABETIQUE). \n");
                    printf("2. AFFICHER LA LISTE DES ADHERENTS.\n");
                    printf("3. AFFICHER LES EMPRUNTS EN COURS. \n");
                    printf("4. AFFICHER LA LISTE D'INSCRITS A UNE APRES-MIDI THEMATIQUE. \n");
                    printf("5. AFFICHER LES EMPRUNTEURS QUI ONT UN RETARD. \n");
                    printf("6. RETOURNER AU MENU PRINCIPAL. \n");
                    scanf("%d", &choix2);
                    switch (choix2) {
                        case 1:
                            system("cls");
                            AfficherJeux(tJeux, nbJeux);
                            break;
                        case 2:
                            system("cls");
                            AfficherAdherants(tAdherants, nbAdherants);
                            break;
                        case 3:
                            system("cls");
                            AfficherEmprunts(tEmprunt, nbEmprunts);
                            break;
                        case 4:
                            system("cls");
                            AfficherAprem(tAprem,nbAprems,tInscription,nbInscrits,tAdherants,nbAdherants);
                            break;
                        case 5:
                            system("cls");
                            AfficherRetards(tAdherants, nbAdherants, tEmprunt, nbEmprunts);
                            break;
                        case 6:
                            system("cls");
                            break;
                        default:
                            printf("Faites une choix parmi les options presentees.\n");
                            scanf("%d", &choix2);
                            break;
                    }
                } while (choix2 != 6);
                break;

            case 7:
                system("cls");
                SupprimerAdherant(tAdherants, &nbAdherants);
                SauverAdherants(tAdherants, nbAdherants);
                break;
            case 8:
                system("cls");
                SupprimerJeu(tJeux, &nbJeux);
                SauverJeux(tJeux, nbJeux);
                break;
            case 9:
                system("cls");
                RetournerEmprunt(tEmprunt, &nbEmprunts, tAdherants, nbAdherants, tJeux, nbJeux);
                SauverEmprunts(tEmprunt, nbEmprunts);
                break;
            case 10:
                system("cls");
                SupprimerInscription(tInscription, &nbInscrits, tAprem, nbAprems, tAdherants, nbAdherants);
                SauverInscriptions(tInscription, nbInscrits);
                break;
            case 11:
                system("cls");
                printf("Merci d'avoir utilise cette application!\n");
                sleep(2);
                system("cls");
                break;
            default:
                printf("Faites une choix parmi les options presentees.\n");
                scanf("%d", &choix);
                break;
        }

    } while (choix != 11);
    Sauvegarder(tAdherants, nbAdherants, tJeux, nbJeux, tAprem, nbAprems, tEmprunt, nbEmprunts, tInscription, nbInscrits);
    return 0;
}