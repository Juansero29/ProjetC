//
// Created by Juan on 21/01/2017.
//


#define PRIXADHESION 15
#define MAX_NUMADHERANT 999
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct {
    int jour, mois, annee;
    char date[12];
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