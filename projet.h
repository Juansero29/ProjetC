//
// Created by Juan on 07/01/2017.
//

#ifndef PROJETP2_PROJET_H
#define PROJETP2_PROJET_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif //PROJETP2_PROJET_H

#define PRIXADHESION 15


typedef struct {
    int jour, mois, annee;
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
    int numAprem;
    Date date;
    int heureDebut;
    int nbPlaces;
    int nbAdhInscrits;
    //Contient les numAdherant des inscrits.
}ApremTh;

typedef struct {
    int numAprem;
    int numAdherant;
}Inscription;