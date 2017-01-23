#include "projet.h"

int main() {
    //Initialisation des tailles logiques.
    int nbAdherants = 0, nbJeux = 0, nbEmprunts = 0, nbInscrits = 0, nbAprems = 0;

    //Initialisation des tableaux utilises dans le programme.
    Adherant *tAdherants = NULL;
    Jeu *tJeux = NULL;
    Emprunt *tEmprunt = NULL;
    Inscription *tInscription = NULL;
    ApremTh *tAprem = NULL;

    //Initialisation des tailles physiques.
    int tP_tAdh = 0, tP_tJe = 0, tP_tEmp = 0, tP_tInsc = 0, tP_tApr = 0, choix = 0;

    //Lire les fichiers qui sont dans le repertoire courant, récuperer les informations.
    //Si on peut pas acceder le fichier, on le crée.
    if (access("bin/adherants.bin", F_OK) == -1) {
        SauverAdherants(tAdherants, nbAdherants);
    }
    if (access("bin/am_thematiques.bin", F_OK) == -1) {
        SauverAprems(tAprem, nbAprems);
    }
    if (access("bin/emprunts.bin", F_OK) == -1) {
        SauverEmprunts(tEmprunt, nbEmprunts);
    }
    if (access("bin/inscriptions_am_th.bin", F_OK) == -1) {
        SauverInscriptions(tInscription, nbInscrits);
    }
    if (access("bin/jeux.bin", F_OK) == -1) {
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
        printf("PROGRAMME: GESTION D'UNE LUDOTHEQUE %c V.10.0.0\n",184);
        printf("Realise par: Juan RODRIGUEZ - Gerben DE VRIES\n");
        printf("Encadr%cs par: BRIGOULET Pascale\n",130);
        printf("\n\n| MENU PRINCIPAL |\n\n");
        printf("1. MENU AJOUTER.\n");
        printf("2. MENU AFFICHAGE\n");
        printf("3. MENU SUPPRESSION\n");
        printf("4. QUITTER\n");
        choix = SaisirEntier();
        system("cls");
        switch (choix) {
            case 1:
                do {
                    printf("\n\n| MENU AJOUTER|\n\n");
                    printf("1. AJOUTER UN NOUVEL ADHERENT. \n");
                    printf("2. RENOUVELLER UNE ADHESION. \n");
                    printf("3. AJOUTER UN JEU.\n");
                    printf("4. AJOUTER UN EMPRUNT.\n");
                    printf("5. AJOUTER UNE APREM THEMATIQUE.\n");
                    printf("6. INSCRIRE UN ADHERANT A UNE APREM THEMATIQUE.\n");
                    printf("7. RETOURNER AU MENU PRINCIPAL.\n");
                    choix2 = SaisirEntier();
                    switch (choix2) {
                        case 1:
                            system("cls");
                            tAdherants = ChargerTAdherants(tAdherants, &nbAdherants, &tP_tAdh, 1); //Chargue le tableau 'tAdherants' avec un Adherant.
                            SauverAdherants(tAdherants, nbAdherants); //Sauvegarde le tableau retourne dans le fichier correspondant.
                            break;
                        case 2:
                            system("cls");
                            RenouvellerAdhesion(tAdherants, nbAdherants);
                            SauverAdherants(tAdherants, nbAdherants);
                            break;
                        case 3:
                            system("cls");
                            tJeux = ChargerTJeux(tJeux, &nbJeux, &tP_tJe, 1);
                            SauverJeux(tJeux, nbJeux);
                            break;
                        case 4:
                            system("cls");
                            if (nbJeux > 0 && nbAdherants > 0) {
                                tEmprunt = ChargerTEmprunts(tAdherants, nbAdherants, tJeux, nbJeux, tEmprunt,
                                                            &nbEmprunts, &tP_tEmp, 1);
                                SauverEmprunts(tEmprunt, nbEmprunts);
                            } else {
                                printf("Impossible d'emprunter. Aucun jeu ou adherant trouve.\n");
                            }
                            break;
                        case 5:
                            system("cls");
                            tAprem = ChargerTAprem(tAprem, &nbAprems, &tP_tApr, 1);
                            SauverAprems(tAprem, nbAprems);
                            break;
                        case 6:
                            system("cls");
                            if (nbAprems != 0 && nbAdherants != 0) {
                                tInscription = ChargerTInscriptions(tInscription, &nbInscrits, &tP_tInsc, tAprem,
                                                                    nbAprems, tAdherants, nbAdherants, 1);
                                SauverInscriptions(tInscription, nbInscrits);
                            } else {
                                printf("Impossible de faire une inscription. Aucun adherant ou apres-midi trouve. \n");
                            }
                            break;
                        case 7:
                            system("cls");
                            break;
                        default:
                            printf("Faites une choix parmi les options presentees.\n");
                            choix2 = SaisirEntier();
                            break;
                    }
                } while (choix2 != 7);
                break;
            case 2:
                do {
                    printf("\n\n| MENU AFFICHAGE |\n\n");
                    printf("1. AFFICHER LA LISTE DES ADHERENTS.\n");
                    printf("2. AFFICHER LA LISTE DE JEUX. (PAR ORDRE ALPHABETIQUE). \n");
                    printf("3. AFFICHER LES EMPRUNTS EN COURS. \n");
                    printf("4. AFFICHER LES ADHERANTS AYANT AU MOINS UN RETARD. \n");
                    printf("5. AFFICHER LA LISTE D'INSCRITS A UNE APRES-MIDI THEMATIQUE. \n");
                    printf("6. RETOURNER AU MENU PRINCIPAL. \n");
                    choix2 = SaisirEntier();
                    switch (choix2) {
                        case 1:
                            system("cls");
                            AfficherAdherants(tAdherants, nbAdherants);
                            break;
                        case 2:
                            system("cls");
                            tri_rapide(tJeux, nbJeux);
                            //On appelle la fonction tri_rapide qui tri le tableau de jeux par ordre alphabetique.
                            AfficherJeux(tJeux, nbJeux); //On affiche les jeux.
                            break;
                        case 3:
                            system("cls");
                            AfficherEmprunts(tEmprunt, nbEmprunts);
                            break;
                        case 4:
                            system("cls");
                            AfficherRetards(tAdherants, nbAdherants, tEmprunt, nbEmprunts);
                            break;
                        case 5:
                            system("cls");
                            AfficherAprem(tAprem, nbAprems, tInscription, nbInscrits, tAdherants, nbAdherants);
                            break;

                        case 6:
                            system("cls");
                            break;
                        default:
                            printf("Faites une choix parmi les options presentees.\n");
                            choix2 = SaisirEntier();
                            break;
                    }
                } while (choix2 != 6);
                break;

            case 3:
                do {
                    printf("\n\n| MENU SUPPRESSION |\n\n");
                    printf("1. SUPPRIMER UN ADHERENT. \n");
                    printf("2. SUPPRIMER UN JEU.\n");
                    printf("3. RETOURNER UN EMPRUNT.\n");
                    printf("4. DESINSCRIRE UN ADHERANT D'UNE APRES-MIDI.\n");
                    printf("5. RETOURNER AU MENU PRINCIPAL.\n");
                    choix2 = SaisirEntier();
                    switch (choix2) {
                        case 1:
                            system("cls");
                            SupprimerAdherant(tAdherants, &nbAdherants);
                            SauverAdherants(tAdherants, nbAdherants);
                            break;
                        case 2:
                            system("cls");
                            SupprimerJeu(tJeux, &nbJeux);
                            SauverJeux(tJeux, nbJeux);
                            break;
                        case 3:
                            system("cls");
                            RetournerEmprunt(tEmprunt, &nbEmprunts, tAdherants, nbAdherants, tJeux, nbJeux);
                            SauverEmprunts(tEmprunt, nbEmprunts);
                            break;
                        case 4:
                            system("cls");
                            SupprimerInscription(tInscription, &nbInscrits, tAprem, nbAprems, tAdherants,
                                                 nbAdherants);
                            SauverInscriptions(tInscription, nbInscrits);
                            break;
                        case 5:
                            system("cls");
                            break;
                        default:
                            printf("Faites une choix parmi les options presentees.\n");
                            choix2 = SaisirEntier();
                            break;
                    }
                } while (choix2 != 5);
                break;
            case 4:
                system("cls");
                printf("\n\tMerci d'avoir utlise cette application! \n");
                sleep(2);
                break;
            default:
                system("cls");
                printf("\n\nFaites une choix parmi les options presentees.\n\n");
                break;
        }
    } while (choix != 4);
    Sauvegarder(tAdherants, nbAdherants, tJeux, nbJeux, tAprem, nbAprems, tEmprunt, nbEmprunts, tInscription, nbInscrits);
    return 0;
}