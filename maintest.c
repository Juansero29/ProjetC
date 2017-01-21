#include <stdio.h>
#include "test.h"
void Afficher1Adherant(Adherant adherant) {

    printf("\n ADHERANT # : %d\n\tnom : %s\n\tprenom : %s\n\tnbEmpCourants : %d\n\t dateAdhesion : %d/%d/%d\n",
           adherant.numAdherant, adherant.nomAdherant, adherant.prenomAdherant, adherant.nbEmpCourants,
           adherant.dateAdhesion.jour, adherant.dateAdhesion.mois, adherant.dateAdhesion.annee);
}
void AfficherAdherants(Adherant tAdherants[], int nbAdherants) {

    int i;
    for (i = 0; i < nbAdherants; i++) {
        Afficher1Adherant(tAdherants[i]);
    }
}
int RechercherAdherant(Adherant tAdherants[], int nbAdherants, int numAdherant) {

    int i;
    for (i = 0; i < nbAdherants; i++) {
        if (tAdherants[i].numAdherant == numAdherant)
            return i;
    }
    return -1;
}

Date SaisirDate() {
    Date date;
    //todo FAIRE VERIFICATIONS POUR UNE DATE CORRECTE
    printf("\n\nEntrez le numero du jour :\n");
    scanf("%d", &date.jour);
    while (date.jour < 1 || date.jour > 31) {
        printf("\nSaisie incorrecte. Reessayez :\n");
        scanf("%d", &date.jour);
    }

    printf("\nEntrez numero du mois :\n");
    scanf("%d", &date.mois);
    while (date.mois < 1 || date.mois > 12) {
        printf("\nSaisie incorrecte. Reessayez :\n");
        scanf("%d", &date.mois);
    }

    printf("\nEntrez l'annee (au format AAAA):\n");
    scanf("%d", &date.annee);
    while (date.annee < 1900 || date.annee > 2150) {
        printf("\nSaisie incorrecte. Reessayez (au format AAAA) :\n");
        scanf("%d", &date.annee);
    }
    printf("Date saisi avec succes! \n");
    return date;
}
Adherant SaisirAdherant(Adherant tAdherants[], int nbAdherants) {
    printf("\n");
    printf("|SAISIE D'UN ADHERANT| \n");
    printf("\n");
    Adherant adherant;
    printf("Entrez le numero de l'adherant : \n");
    scanf("%d%*c", &adherant.numAdherant);
    int index = RechercherAdherant(tAdherants, nbAdherants, adherant.numAdherant);
    while (index != -1) {
        printf("Ce numero d'adherant existe deja ! Veuillez tapper un autre. \n");
        scanf("%d", &adherant.numAdherant);
        index = RechercherAdherant(tAdherants, nbAdherants, adherant.numAdherant);
    }
    printf("Entrez son nom (14 caracteres maximum): \n");
    fgets(adherant.nomAdherant, 15, stdin);
    adherant.nomAdherant[strlen(adherant.nomAdherant)-1]= '\0';
    printf("Entrez son prenom (14 caracteres maximum): \n");
    fgets(adherant.prenomAdherant, 15, stdin);
    adherant.prenomAdherant[strlen(adherant.prenomAdherant)-1]= '\0';
    printf("Vous allez maintenant saisir sa date d'adhesion :\n");
    adherant.dateAdhesion = SaisirDate();
    adherant.nbEmpCourants = 0;
    printf("Adherant saisi avec succes! \n");
    return adherant;
}


Adherant *ChargerTAdherants(Adherant tAdherants[], int *nbAdherants, int *taillePhysique, int nbAjouts) {

    Adherant a, *tAdherantsBuffer;
    int adherantsDeb = *nbAdherants;
    for (; *nbAdherants < (nbAjouts + adherantsDeb); *nbAdherants+=1) {
        if (*nbAdherants == *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            tAdherantsBuffer = (Adherant *) realloc(tAdherants, *taillePhysique * sizeof(Adherant));
            if (tAdherantsBuffer == NULL) {
                printf("Probleme d'allocation de memoire");
                exit(1);
            }
            tAdherants = tAdherantsBuffer;
        }
        a = SaisirAdherant(tAdherants, *nbAdherants);
        tAdherants[*nbAdherants] = a;
    }
    return tAdherants;
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
        printf("Probleme d'allocation de memoire2");
        exit(1);
    }

    fread(tAdherants, sizeof(Adherant), (size_t)*nbAdherants, fb);
    fclose(fb);
    return tAdherants;
}

void SauverAdherants(Adherant tAdherants[], int nbAdherants) {

    FILE *fb;
    fb = fopen("adherants.bin", "wb");
    if (fb == NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    //Ici ça crash et on sait pas pourquoi.
    fwrite(&nbAdherants, sizeof(int), 1, fb);
    fwrite(tAdherants, sizeof(Adherant), (size_t) nbAdherants, fb);
    fclose(fb);
}


int main() {
    /*Penser à implementer les constraintes nécessaires:
     *  todo - adhérent peut emprunter jusqu'à 3 jeux pour une durée maximale de 3 semaines.
     *  todo - vérifier si un adhérant est en retard. (utilisateur demande une liste des emprunteurs qui ont un redard).
    */
    int nbAdherants=0;
    //Initialisation des variables utilises dans le programme.

    Adherant *tAdherants=NULL;
    int tphysique = 0;

    if( access( "adherants.bin", F_OK ) == -1 ) {
        SauverAdherants(tAdherants, nbAdherants);
    }
    tAdherants = LireTAdherants(&nbAdherants); //Lecture directe dans le main.
    AfficherAdherants(tAdherants, nbAdherants);
    SauverAdherants(tAdherants, nbAdherants);
    free(tAdherants);


    printf("\nRien\n");
    AfficherAdherants(tAdherants, nbAdherants);

    printf("\nTout\n");
    tAdherants = LireTAdherants(&nbAdherants);
    AfficherAdherants(tAdherants, nbAdherants);
    free(tAdherants);

    printf("\nEssaie avec tout lire\n");
    AfficherAdherants(tAdherants, nbAdherants);
    return 0;
}