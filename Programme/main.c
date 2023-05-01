#include "directive.h"
#include "prototype.h"

int main(void){
	SDL_init_ALL();											                                                       //! Initialisation SDL2
	SDL_Event event;
    SDL_Window * Window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer * Rendu = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	play_Sound(SOUND_Opening);                                                                                     //  Jouer le son d'ouverture
	load_Window_ICON(Window, PATH "icon.png");                                                                     //  Chargement de l'icone de la fenetre
	SDL_Texture ** Textures = load_Texture(Rendu);                                                                 //  Chargement des textures des pages
	SDL_Texture ** Parametre = load_Parametre(Rendu);                                                              //  Chargement des textures des parametres
	TTF_Font * police = TTF_OpenFont(PATH "font.ttf", 40);                                                         //  Chargement de la police
	Mix_Music * musique = load_Music(PATH_AUDIO "musique.mp3");                                                    //  Lecture de la musique

	Param Settings = {true, THEME_1}; 							                                                   //  Définie les paramètres par défaut
	enum Pages index_PAGE = HOME;								                                                   //  Définie la page de démarrage
	SDL_Texture ** Pion = load_Pion(Rendu, Settings);                                                              //  Chargement des textures des pions
	Partie * p = malloc(sizeof(Partie));                                                                           //  Déclaration de la partie

	disp_Background(Rendu, Textures, index_PAGE);                                                                  //* Affichage de la page d'accueil
	bool Close = false;
	while(!Close){
		static partie_Data game = {false, 0, 0}; 															       //  Données de la partie par default
		static int board[TAILLE][TAILLE]; 																	       //  Plateau de jeu
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
                case SDL_KEYDOWN:
                    Close = true;								   												   //* Fermeture rapide
                    break;
                case SDL_MOUSEBUTTONDOWN:
					if(!game.partie_Started){ 	                                                                   //? Si aucune partie est en cours
						if(index_PAGE == OPTION) Settings = change_Parametre(event, &index_PAGE, Settings);        //? Changement des paramètres
						else index_PAGE = btn_CLIC(event, index_PAGE);											   //  Changement de page
						disp_Background(Rendu, Textures, index_PAGE); 											   //  Affichage de la page
						if(index_PAGE == GAME_J1 || index_PAGE == GAME_J2) game.Mode = JvsJ;
						else if(index_PAGE == GAME_IA) game.Mode = JvsIA;
						switch(index_PAGE){
							case OPTION: disp_Parametre(Rendu, Parametre, Settings);							   //? Affichage des paramètres
								Pion = load_Pion(Rendu, Settings); 												   //  Chargement du thème des pions
								change_Volume(Settings);    													   //  Changement du volume
								break;
							case CHARGER_PARTIE: 																   //  Chargement dernière partie
                        		p = import_Partie("partie.txt");
								game = chargement_Partie_data(p, board, game);
								break;
							case GAME_IA ... GAME_J2: game = start_Game(game, board, p);                           //? Lancement de la partie
							    break;
							case ENDGAME: ResultatsPartie(Rendu, police, board);                                   //? Affichage des résultats de la partie
								break;
							case QUITTER: Close = true; 														   //  Bouton de fermeture
								break;
						}
						if((index_PAGE >= GAME_IA && index_PAGE <= GAME_J2) || index_PAGE == CHARGER_PARTIE)
							index_PAGE = afficher_la_Partie(Rendu, index_PAGE, Textures, board, Pion, game);       //  Affichage de la partie
					}
					else if(game.partie_Started){ 																   //? Si une partie est en cours
						index_PAGE = quitter_la_Partie(Rendu, event, index_PAGE, Textures);						   //  Bouton de fermeture
						game = gameplay(Rendu, &index_PAGE, Textures, board, Pion, game, p);			   	       //  Déroulement de la partie
						if(btn_CLIC(event, index_PAGE) == last_coup){                                              //* Annuler le dernier coup
							if((p->nbCoups > 1 && game.Mode == JvsJ) || (p->nbCoups > 2 && game.Mode == JvsIA)){                      
								game = annuler_dernier_Coup(p, board, game);
								index_PAGE = afficher_la_Partie(Rendu, index_PAGE, Textures, board, Pion, game);
							}
						}
						if(index_PAGE == HOME || index_PAGE == ENDGAME){                                           //  Retour à l'accueil
							game.partie_Started = false;
							save_Partie(p, "partie.txt");   													   //  Sauvegarde de la partie
						}
					}
                break;
			}
		}
	}

	free_Partie(p);	         																					   //  Libératiion mémoire Partie
	FERMETURE_SDL(Window, Rendu, musique, Textures, Pion, police);         										   //! Libération mémoire/fermeture SDL

    return 0;
}