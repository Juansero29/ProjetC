#define MAX_NUMADHERANT 999
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <windows.h>

typedef struct {
    int jour, mois, annee;
    time_t time;
}Date;

typedef struct {
    char nom[25];
    char nomCategorie[20];
    int nbExemplaires;
    int nbEmprunts;
}Jeu;

typedef struct {
    Date dateEmprunt;
    char nomJeu[25];
    int numAdherant;
}Emprunt;

typedef struct {
    int numAdherant;
    char nomAdherant[15];
    char prenomAdherant[15];
    int nbEmpCourants;
    Date dateAdhesion;
}Adherant;

typedef struct {
    char codeAprem[6];
    Date date;
    int heureDebut;
    int nbPlaces;
    int nbAdhInscrits;
    //Contient les numAdherant des inscrits.
}ApremTh;

typedef struct {
    char codeAprem[6];
    int numAdherant;
}Inscription;

char *CreerIdentifiant(int length);
Date SaisirDate() ;
int SaisirEntier(void);
Adherant SaisirAdherant(Adherant tAdherants[], int nbAdherants) ;
Emprunt SaisirEmprunt(Jeu tJeux[], Adherant tAdherants[], int nbJeux, int nbAdherants);
ApremTh SaisirApremTh(ApremTh tAprems[], int nbAprems) ;
Jeu SaisirJeu(Jeu tJeux[], int nbJeux, int *indexDoublon) ;
Inscription SaisirInscription(ApremTh tApremTh[], int nbAprem, Adherant tAdherants[], int nbAdherants, Inscription tInscriptions[], int nbInscriptions) ;

Adherant *LireTAdherants(int *nbAdherants);
Jeu *LireTJeux(int *nbJeux) ;
ApremTh *LireTAprems(int *nbAprems) ;
Emprunt *LireEmprunts(int *nbEmprunts);
Inscription *LireInscriptions(int *nbInscriptions);

int partition(Jeu t[], int deb, int fin);
void tri_rapide_(Jeu t[], int debut, int fin);
void tri_rapide(Jeu t[], int nbJeux);

void Afficher1Adherant(Adherant adherant) ;
void AfficherAdherants(Adherant tAdherants[], int nbAdherants) ;
void AfficherJeux(Jeu tJeux[], int nbJeux) ;
void AfficherAprems(ApremTh tAprems[], int nbAprems);
void AfficherApremsIncomplets(ApremTh tAprems[], int nbAprems);
void Afficher1Aprem(ApremTh tAprems[], int nbAprems, char codeAprem[5]);
void AfficherAprem(ApremTh tAprems[], int nbAprems, Inscription tInscriptions[], int nbInscriptions, Adherant tAdherants[], int nbAdherants);
void AfficherEmprunts(Emprunt tEmprunts[], int nbEmprunts);
void AfficherRetards(Adherant tAdherants[], int nbadherants, Emprunt tEmprunts[], int nbEmprunts) ;

int RechercherAdherant(Adherant tAdherants[], int nbAdherants, int numAdherant) ;
int RechercherAprem(ApremTh tAprem[], int nbAprem, char numAprem[5]) ;
int RechercherJeu(Jeu tJeux[], int nbJeux, char nomJeu[25]) ;
int RechercherEmprunt(Emprunt tEmprunts[], int nbEmprunts, int numAdherant, char nomJeu[]);
int RechercherInscription(Inscription tInscriptions[], int nbInscriptions, char numAprem[5], int numAdherant);
int AdherantEstDansUneAMT(int numAdherant, Inscription tInscriptions[], int nbInscriptions);

void SupprimerAdherant(Adherant tAdherants[], int *nbAdherants, Inscription tInscriptions[], int nbInscriptions);
void SupprimerJeu(Jeu tJeux[], int *nbJeux);
void RetournerEmprunt(Emprunt tEmprunts[], int *nbEmprunts, Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux) ;
void SupprimerInscription(Inscription tInscriptions[], int *nbInscriptions, ApremTh tAprems[], int nbAprems, Adherant tAdherants[], int nbAdherants);
void RenouvellerAdhesion(Adherant tAdherants[], int nbAdherants);

Adherant *ChargerTAdherants(Adherant tAdherants[], int *nbAdherants, int *taillePhysique, int nbAjouts);
Jeu *ChargerTJeux(Jeu tJeux[], int *nbJeux, int *taillePhysique, int nbAjouts);
ApremTh *ChargerTAprem(ApremTh tAprem[], int *nbAprems, int *taillePhysique, int nbAjouts);
Emprunt *ChargerTEmprunts(Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux, Emprunt tEmprunt[], int *nbEmprunts, int *taillePhysique, int nbAjouts);
Inscription *ChargerTInscriptions(Inscription tInscriptions[], int *nbInscriptions,  int *taillePhysique, ApremTh tApremTh[], int nbAprems, Adherant tAdherants[], int nbAdherants, int nbAjouts);

void SauverAdherants(Adherant tAdherants[], int nbAdherants);
void SauverJeux(Jeu tJeux[], int nbJeux);
void SauverAprems(ApremTh tAprem[], int nbAprem) ;
void SauverEmprunts(Emprunt tEmprunts[], int nbEmprunts) ;
void SauverInscriptions(Inscription tInscriptions[], int nbInscrits) ;
void Sauvegarder(Adherant tAdherants[], int nbAdherants, Jeu tJeux[], int nbJeux, ApremTh tAprem[], int nbAprem, Emprunt tEmprunts[], int nbEmprunts, Inscription tInscriptions[], int nbInscrits);
