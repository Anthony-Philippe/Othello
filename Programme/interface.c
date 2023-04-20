#include "directive.h"
#include "prototype.h"

void SDL_init_ALL(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIO_BUFFER_SIZE);
}

void load_Window_ICON(SDL_Window * window, const char * sources){  //// * Gestion des Textures et Images
    SDL_Surface * icon = IMG_Load(sources);
    SDL_SetWindowIcon(window, icon);                               // Définie l'icone avec l'image importée
    SDL_FreeSurface(icon);
}

void disp_Background(SDL_Renderer * Rendu, SDL_Texture ** Textures, enum Pages index_PAGE){
	if(index_PAGE == CHARGER_PARTIE) index_PAGE = GAME_J1;
	SDL_RenderClear(Rendu);
	SDL_RenderCopy(Rendu, Textures[index_PAGE], NULL, NULL);       // Affichage de la page
	SDL_RenderPresent(Rendu);
}

SDL_Texture ** load_Texture(SDL_Renderer * Rendu){
    static const char * sources[] = {                              // Importation des images de fond
        PATH_IMAGES "HOME_bg.png",
        PATH_IMAGES "OPTION_bg.png",
        PATH_IMAGES "SART_MENU1_bg.png",
		PATH_IMAGES "SART_MENU2_bg.png",
		PATH_IMAGES "IA_MENU_bg.png",
		PATH_IMAGES "GAME-IA.png",
		PATH_IMAGES "GAME-J1.png",
		PATH_IMAGES "GAME-J2.png",
		PATH_IMAGES "ENDGAME_bg.png"
    };
    SDL_Texture ** Textures = malloc(sizeof(SDL_Texture *) * 9);
    for (int i = 0; i < 9; i++) Textures[i] = load_Image(Rendu, sources[i]);
    return Textures;
}

SDL_Texture ** load_Parametre(SDL_Renderer * Rendu){
	static const char * sources[] = {                               // Importation des images des pions
        PATH_IMAGES "son-off.png",
		PATH_IMAGES "check.png"
    };
	SDL_Texture ** Parametre = malloc(sizeof(SDL_Texture *) * 2);
    for (int i = 0; i < 2; i++) Parametre[i] = load_Image(Rendu, sources[i]);
    return Parametre;
}

SDL_Texture ** load_Pion(SDL_Renderer * Rendu, Param Settings){
	static const char * sources[] = {                               // Importation des images des pions
        PATH_IMAGES "p1-T1.png",
		PATH_IMAGES "p2-T1.png",
        PATH_IMAGES "p1-T2.png",
		PATH_IMAGES "p2-T2.png",
		PATH_IMAGES "p1-T3.png",
        PATH_IMAGES "p2-T3.png",
		PATH_IMAGES "pj.png"
    };
	SDL_Texture ** Pion = malloc(sizeof(SDL_Texture *) * 3);
	Pion[0] = load_Image(Rendu, sources[Settings.THEME - 1]);			// Charge les images des pions selon le thème choisi
	Pion[1] = load_Image(Rendu, sources[Settings.THEME]);
	Pion[2] = load_Image(Rendu, sources[case_Jouable]);
	return Pion;
}

SDL_Texture * load_Image(SDL_Renderer * rendu, const char * sources){
    SDL_Surface * Image = IMG_Load(sources);
    SDL_Texture * Texture = SDL_CreateTextureFromSurface(rendu, Image);
	SDL_FreeSurface(Image);
    return Texture;
}

void disp_Parametre(SDL_Renderer * Rendu, SDL_Texture ** Parametre, Param Settings){
	SDL_Rect Param = {285, 465, 75, 75};
	if(Settings.SON == false) SDL_RenderCopy(Rendu, Parametre[0], NULL, &Param);
	switch(Settings.THEME){
		case THEME_1: Param = (SDL_Rect){580, 340, 45, 45}; break;
		case THEME_2: Param = (SDL_Rect){580, 405, 45, 45}; break;
		case THEME_3: Param = (SDL_Rect){580, 470, 45, 45}; break;
	}
	SDL_RenderCopy(Rendu, Parametre[1], NULL, &Param);
	SDL_RenderPresent(Rendu);
}

void disp_Plateau(SDL_Renderer * Rendu, SDL_Texture ** Pion, int board[TAILLE][TAILLE]){
    SDL_Rect Case = {0, 0, size_CASE, size_CASE};
    int plateau_x = 402 + OFFSET, plateau_y = 71 + + OFFSET;        // Position du plateau
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Case.x = plateau_x + j * size_CASE + j * 15 + j/3;		// Position des pions
            Case.y = plateau_y + i * size_CASE + i * 15 + i/3;
            if(board[i][j] == 1) SDL_RenderCopy(Rendu, Pion[0], NULL, &Case);
            else if (board[i][j] == 2) SDL_RenderCopy(Rendu, Pion[1], NULL, &Case);
			else if (board[i][j] == case_Jouable) SDL_RenderCopy(Rendu, Pion[2], NULL, &Case);
        }
    }
    SDL_RenderPresent(Rendu);
}

Mix_Music * load_Music(const char* sources){                       //// * Gestion du Son
	Mix_Music * musique = Mix_LoadMUS(PATH_AUDIO "musique.mp3");
	Mix_PlayMusic(musique, -1);                                    // -1: Musique joué en boucle
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);                           // Diminition du volume de 80%
}

void play_Sound(const int sound_ID){
	Mix_Chunk * sound[2];
	sound[SOUND_Opening] = Mix_LoadWAV(PATH_AUDIO "opening.wav");
	sound[SOUND_Click] = Mix_LoadWAV(PATH_AUDIO "click.wav");
	Mix_Volume(SOUND_Opening, MIX_MAX_VOLUME / 6);                  // Diminition du volume de 60%
	Mix_PlayChannel(sound_ID, sound[sound_ID], 0);                  // Joue le son demandé
}

void change_Volume(Param Settings){
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	Mix_Volume(SOUND_Click, MIX_MAX_VOLUME);
	if(Settings.SON == false){
		Mix_Volume(SOUND_Click, 0);
		Mix_VolumeMusic(0);
	}
}

int btn_CLIC(SDL_Event event, enum Pages index_PAGE){               //// * Gestion des Boutons Cliquables
	int clicked_POS = check_POS(event, index_PAGE);                 // Vérifie si un bouton est cliqué
	switch(index_PAGE){
		case HOME:
			if(clicked_POS == 1) return OPTION;
			else if(clicked_POS == 2) return START;
			else if(clicked_POS == 3) return QUITTER;
			break;
		case START:
			if(clicked_POS == 1) return CHARGER_PARTIE;
			else if(clicked_POS == 2) return NOUVELLE_PARTIE;
			else if(clicked_POS == 3) return HOME;
			break;
		case NOUVELLE_PARTIE:
			if(clicked_POS == 1) return GAME_J1;
			else if(clicked_POS == 2) return IA_MENU;
			else if(clicked_POS == 3) return START;
			break;
		case GAME_J1:
			if(clicked_POS == 1) return last_coup;
			else if(clicked_POS == 3) return HOME;
			break;
		case GAME_J2:
			if(clicked_POS == 1) return last_coup;
			else if(clicked_POS == 3) return HOME;
			break;
		case IA_MENU:
			if(clicked_POS == 4) return GAME_IA;
			else if(clicked_POS == 5) return GAME_IA;
			else if(clicked_POS == 6) return GAME_IA;
			else if(clicked_POS == 3) return NOUVELLE_PARTIE;
			break;
		case GAME_IA:
			if(clicked_POS == 1) return last_coup;
			else if(clicked_POS == 3) return HOME;
			break;
		case ENDGAME:
			if(clicked_POS == 3) return HOME;
			break;
		case CHARGER_PARTIE:
			if(clicked_POS == 1) return GAME_J1;
			else if(clicked_POS == 3) return HOME;
			break;
	}
	return index_PAGE;                                              // Retourne l'index de la page à afficher
}

Param change_Parametre(SDL_Event event, enum Pages *index_PAGE, Param Settings){
	int test = check_POS(event, *index_PAGE);                        // Vérifie si un bouton est cliqué
	switch(test){
		case 1: Settings.SON = (Settings.SON == true) ? false : true; break;
		case 4: Settings.THEME = THEME_1; break;
		case 5: Settings.THEME = THEME_2; break;
		case 6: Settings.THEME = THEME_3; break;
		case 3: *index_PAGE = HOME;
	}
	return Settings;
}

int check_POS(SDL_Event event, enum Pages index_PAGE){
	int x = event.button.x;
	int y = event.button.y;
	SDL_Rect * BTN = define_BTN(index_PAGE);                        // Définie les boutons de la page
    for (int i = 0; i < 6; i++) {
        if(SDL_PointInRect(&(SDL_Point){x, y}, &BTN[i])){
			play_Sound(SOUND_Click);                                // Joue le son de clique
            return i + 1;                                           // Retourne le bouton cliqué
        }
    }
    return 0;
}

SDL_Rect * define_BTN(enum Pages index_PAGE){
	static SDL_Rect BTN[6] = {{0}};
	BTN[0] = (SDL_Rect){BTN_Left_size1};
    BTN[1] = (SDL_Rect){BTN_Center_size1};
    BTN[2] = (SDL_Rect){BTN_Right_size1};
	for(int nBTN = 3; nBTN < 6; nBTN++) BTN[nBTN] = BTN_Null
	if(index_PAGE == START){
		BTN[0] = (SDL_Rect){BTN_Left_size2};
		BTN[1] = (SDL_Rect){BTN_Center_size2};
	}
	if(index_PAGE == NOUVELLE_PARTIE) BTN[1] = (SDL_Rect){BTN_Center_size2};
	if(index_PAGE == GAME_IA || index_PAGE == GAME_J1 || index_PAGE == GAME_J2) BTN[0] = (SDL_Rect){BTN_Left_size2};

	if(index_PAGE == IA_MENU || index_PAGE == OPTION){
		if(index_PAGE == IA_MENU) BTN[0] = BTN_Null;
		BTN[1] = BTN_Null
		BTN[3] = (SDL_Rect){BTN_Niveau_1};
		BTN[4] = (SDL_Rect){BTN_Niveau_2};
		BTN[5] = (SDL_Rect){BTN_Niveau_3};
	}
	if(index_PAGE == ENDGAME){
		BTN[0] = BTN_Null;
		BTN[1] = BTN_Null;
		BTN[3] = BTN_Null;
		BTN[4] = BTN_Null;
		BTN[5] = BTN_Null;
		}
	return BTN;                                                     // Retourne les positions des boutons pour chaque pages
}

void free_Textures(SDL_Texture ** textures){                        //// * Gestion de la Mémoire
    for (int i = 0; textures[i] != NULL; i++) SDL_DestroyTexture(textures[i]);
    free(textures);
}

void FERMETURE_SDL(SDL_Window * Window, SDL_Renderer * Rendu, Mix_Music * musique, SDL_Texture ** Textures, SDL_Texture ** Pion, TTF_Font* police){
	free_Textures(Textures);                                        // Libération de la mémoire des Textures
	free_Textures(Pion);										    // Libération de la mémoire des Pions
    Mix_FreeMusic(musique);                                         // Libération de la mémoire de la Musique
    Mix_CloseAudio();
	TTF_CloseFont(police);

	SDL_DestroyRenderer(Rendu);                                     // Fermeture SDL
	SDL_DestroyWindow(Window);
	TTF_Quit();
	SDL_Quit();
}


void afficherResultats(SDL_Renderer* Rendu, TTF_Font* police, int Résultats[3]){
    char J1[20], J2[20];
    sprintf(J1, "%d", Résultats[0]);
    sprintf(J2, "%d", Résultats[1]);
    char g[20] = {"Egalité"};
    if(Résultats[2] == P1) strcpy(g, "Joueur 1");
    else if(Résultats[2] == P2) strcpy(g, "Joueur 2");
	SDL_Color blanc = {255, 255, 255};
    SDL_Surface* texte = TTF_RenderText_Blended(police, g, blanc) ;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Rendu, texte);
    SDL_Rect test1 = {260, 475, texte->w, texte->h};
    SDL_RenderCopy(Rendu, tex, NULL, &test1);
    texte = TTF_RenderText_Blended(police, J1, blanc) ;
    tex = SDL_CreateTextureFromSurface(Rendu, texte);
    SDL_Rect test2 = {545, 500, texte->w, texte->h};
    SDL_RenderCopy(Rendu, tex, NULL, &test2);
    texte = TTF_RenderText_Blended(police, J2, blanc) ;
    tex = SDL_CreateTextureFromSurface(Rendu, texte);
    SDL_Rect test3 = {710, 500, texte->w, texte->h};
    SDL_RenderCopy(Rendu, tex, NULL, &test3);
    SDL_RenderPresent(Rendu);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(texte);
}
