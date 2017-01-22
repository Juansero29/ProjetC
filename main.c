#include "projet.h"


int main() {
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
        printf("1. MENU AJOUTER.\n");
        printf("2. MENU AFFICHAGE\n");
        printf("3. MENU SUPPRESSION\n");
        printf("4. QUITTER\n");
        scanf("%d", &choix);
        system("cls");
        switch (choix) {
            case 1:
                choix2 = 0;
                do {
                    printf("\n\n| MENU AJOUTER|\n\n");
                    printf("1. AJOUTER UN NOUVEL ADHERENT. \n");
                    printf("2. AJOUTER UN EMPRUNT\n");
                    printf("3. AJOUTER UN JEU\n");
                    printf("4. AJOUTER UNE APREM THEMATIQUE\n");
                    printf("5. AJOUTER UNE INSCRIPTION A APREM THEMATIQUE\n");
                    printf("6. AJOUTER UN RENOUVELLEMENT D'ADHESION. \n");
                    printf("7. RETOURNER AU MENU PRINCIPAL.\n");
                    scanf("%d", &choix2);
                    switch (choix2) {
                        case 1:
                            system("cls");
                            tAdherants = ChargerTAdherants(tAdherants, &nbAdherants, &tP_tAdh, 1); //Chargue le tableau 'tAdherants' avec un Adherant.
                            SauverAdherants(tAdherants, nbAdherants); //Sauvegarde le tableau retourne dans le fichier correspondant.
                            break;
                        case 2:
                            system("cls");
                            if(nbJeux > 0 && nbAdherants > 0){
                                tEmprunt = ChargerTEmprunts(tAdherants, nbAdherants, tJeux, nbJeux, tEmprunt, &nbEmprunts, &tP_tEmp, 1);
                                SauverEmprunts(tEmprunt, nbEmprunts);
                            }else{
                                printf("Impossible d'emprunter. Aucun jeu ou adherant trouve.\n");
                            }
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
                            if (nbAprems != 0 && nbAdherants!= 0) {
                                tInscription = ChargerTInscriptions(tInscription, &nbInscrits, &tP_tInsc, tAprem,
                                                                    nbAprems, tAdherants, nbAdherants, 1);
                                SauverInscriptions(tInscription, nbInscrits);
                            } else {
                                printf("Impossible de faire une inscription. Aucun adherant ou apres-midi trouve. \n");
                            }
                            break;
                        case 6:
                            system("cls");
                            RenouvellerAdhesion(tAdherants, nbAdherants);
                            break;
                        case 7:
                            system("cls");
                            break;
                        default:
                            printf("Faites une choix parmi les options presentees.\n");
                            scanf("%d", &choix2);
                            break;
                    }
                }while (choix2 != 7);
                break;
            case 2:
                choix2 = 0;
                do {
                    printf("\n\n| MENU AFFICHAGE |\n\n");
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
                            trier(tJeux, nbJeux);
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
                            AfficherAprem(tAprem, nbAprems, tInscription, nbInscrits, tAdherants, nbAdherants);
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

            case 3:
                choix2 = 0;

                do {
                    printf("\n\n| MENU SUPPRESSION |\n\n");
                    printf("1. SUPPRIMER UN ADHERENT. \n");
                    printf("2. SUPPRIMER UN JEU.\n");
                    printf("3. RETOURNER UN EMPRUNT.\n");
                    printf("4. DESINSCRIRE UN ADHERANT D'UNE APRES-MIDI.\n");
                    printf("5. RETOURNER AU MENU PRINCIPAL.\n");
                    scanf("%d", &choix2);
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
                            scanf("%d", &choix2);
                            break;
                    }
                } while (choix2 != 5);
                break;

            default:
                printf("Faites une choix parmi les options presentees.\n");
                scanf("%d", &choix);
                break;
        }
    } while (choix != 4);
    Sauvegarder(tAdherants, nbAdherants, tJeux, nbJeux, tAprem, nbAprems, tEmprunt, nbEmprunts, tInscription, nbInscrits);
    return 0;
}