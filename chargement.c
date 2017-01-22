#include "projet.h"

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
        if (*nbJeux == *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
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


