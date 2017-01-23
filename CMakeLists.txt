cmake_minimum_required(VERSION 3.6)
project(PROJET)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c)

set(SOURCE_FILES main.c affichage.c sauvegarde.c chargement.c saisie.c recherche.c projet.h suppression.c lecture.c)
add_executable(PROJET ${SOURCE_FILES} main.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
