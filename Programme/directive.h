#include <stdio.h>                           //! Importation des librairies standards
#include <stdlib.h>   
#include <stdbool.h>  
#include <string.h>   
#include <time.h>

#include "SDL2/SDL.h"                        //! Importation des librairies SDL2
#include "SDL2/SDL_image.h"  
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"


#define PATH "Ressources/"                   //? PATH des ressources du programme
#define PATH_AUDIO PATH "Audio/"             //  Fichiers audio
#define PATH_IMAGES PATH "Images/"           //  Fichiers images

#define WINDOW_WIDTH 1280                    //  Largeur de la fenêtre
#define WINDOW_HEIGHT 720                    //  Hauteur de la fenêtre

#define size_CASE 45                         //  Taille des cases du plateau
#define OFFSET 5                             //  Décalage des cases du plateau

#define THEME_1 1                            //? Thèmes des pions par default
#define THEME_2 3                            //  Thèmes des pions: Colorés
#define THEME_3 5                            //  Thèmes des pions: Noir et Blanc

#define AUDIO_FREQUENCY 44100                //? Définition valeurs sonnores utiles
#define AUDIO_BUFFER_SIZE 2048
#define SOUND_Opening 0                      //  Entrée audio: Opening
#define SOUND_Click 1                        //  Entrée audio: Click

#define BTN_Null (SDL_Rect){0, 0, 0, 0};     //? Position des boutons de l'application
#define BTN_Left_size1 240, 490, 151, 36
#define BTN_Left_size2 240, 460, 151, 68
#define BTN_Center_size1 480, 440, 312, 50
#define BTN_Center_size2 520, 400, 256, 108
#define BTN_Right_size1 890, 490, 150, 40
#define BTN_Niveau_1 570, 360, 154, 35
#define BTN_Niveau_2 565, 420, 165, 36
#define BTN_Niveau_3 565, 480, 164, 36

#define TAILLE 8                             //  Taille du plateau de jeu
#define P1 1                                 //  Valeurs: Joueur 1
#define P2 2                                 //  Valeurs: Joueur 2
#define VIDE 0                               //  Valeurs: case vide
#define case_Jouable 6                       //  Valeurs: case jouable
#define JvsJ 1                               //  Valeurs: Mode de jeu
#define JvsIA 2                              //  Valeurs: Mode de jeu