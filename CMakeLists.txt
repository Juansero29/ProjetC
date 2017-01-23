cmake_minimum_required(VERSION 3.6)
project(PROJET)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c)

set(SOURCE_FILES main.c Fonctions/affichage.c Fonctions/sauvegarde.c Fonctions/chargement.c Fonctions/saisie.c Fonctions/recherche.c Fonctions/suppression.c Fonctions/lecture.c projet.h)
add_executable(PROJET ${SOURCE_FILES} main.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
