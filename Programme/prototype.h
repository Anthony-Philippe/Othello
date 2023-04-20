enum Pages{                            //  Enumération des pages de l'application
    HOME = 0,
    OPTION,
    START,
    NOUVELLE_PARTIE,
    IA_MENU,
    GAME_IA,
    GAME_J1,
    GAME_J2,
    ENDGAME,
    CHARGER_PARTIE,
    QUITTER,
    last_coup
};

typedef struct liste_Coup liste_Coup;    //  Structure de la liste des coups
typedef struct Partie Partie;            //  Structure de la partie
typedef struct Param Param;              //  Structure des paramètres
typedef struct partie_Data partie_Data;  //  Structure des données de la partie

struct liste_Coup{
    int board[TAILLE][TAILLE], who_played;
    liste_Coup* prec;
    liste_Coup* suiv;
};

struct Partie{
    int nbCoups ,type;
    liste_Coup* premier;
    liste_Coup* dernier;
};

struct Param{
    bool SON;
    int THEME;
};

struct partie_Data{
    bool partie_Started;
    int Mode, Joueur;
};

//!                                                                                                                                //  PROTOTYPES SDL2
void SDL_init_ALL();                                                                                                               //  Initalisation SDL
void load_Window_ICON(SDL_Window * window, const char * sources);                                                                  //  Gestion Textures et Images
void disp_Background(SDL_Renderer * Rendu, SDL_Texture ** Textures, enum Pages index_PAGE);
SDL_Texture ** load_Texture(SDL_Renderer * Rendu);
SDL_Texture ** load_Parametre(SDL_Renderer * Rendu);
SDL_Texture ** load_Pion(SDL_Renderer * Rendu, Param Settings);
SDL_Texture * load_Image(SDL_Renderer * rendu, const char * sources);
void disp_Parametre(SDL_Renderer * Rendu, SDL_Texture ** Parametre, Param Settings);
void disp_Plateau(SDL_Renderer * Rendu, SDL_Texture ** Pion, int board[TAILLE][TAILLE]);
void afficherResultats(SDL_Renderer* Rendu, TTF_Font* police, int Résultats[3]);
Mix_Music * load_Music(const char * sources);                                                                                      //  Gestion du Son
void play_Sound(const int sound_ID);
void change_Volume(Param Settings);
int btn_CLIC(SDL_Event event, enum Pages index_PAGE);                                                                              //  Gestion des Boutons
Param change_Parametre(SDL_Event event, enum Pages *index_PAGE, Param Settings);
int check_POS(SDL_Event event, enum Pages index_PAGE);
SDL_Rect * define_BTN(enum Pages index_PAGE);
void free_Textures(SDL_Texture ** textures);                                                                                       //  Gestion de la Mémoire
void FERMETURE_SDL(SDL_Window * Window, SDL_Renderer * Rendu, Mix_Music * musique, SDL_Texture ** Textures, SDL_Texture ** Pion, TTF_Font* police);

//!          
partie_Data start_Game(partie_Data game, int board[TAILLE][TAILLE], Partie * p);                                                   //  PROTOTYPES DU JEU
partie_Data initialiser_la_Partie(partie_Data game, int board[TAILLE][TAILLE], Partie * p);                                        //  Gestion du Jeu
int joueur_Aléatoire();
int afficher_la_Partie(SDL_Renderer * Rendu, enum Pages index_PAGE, SDL_Texture ** Textures, int board[TAILLE][TAILLE], SDL_Texture ** Pion, partie_Data game);
int quitter_la_Partie(SDL_Renderer * Rendu, SDL_Event event, enum Pages index_PAGE, SDL_Texture ** Textures);
partie_Data gameplay(SDL_Renderer * Rendu, enum Pages *index_PAGE, SDL_Texture ** Textures, int board[TAILLE][TAILLE], SDL_Texture ** Pion, partie_Data game, Partie * p);
partie_Data annuler_dernier_Coup(Partie * p, int board[TAILLE][TAILLE], partie_Data game);
int fin_de_partie(SDL_Renderer * Rendu, enum Pages index_PAGE, SDL_Texture ** Textures, int board[TAILLE][TAILLE], SDL_Texture ** Pion, partie_Data game);
void init_board(int board[TAILLE][TAILLE]);                                                                                        //  Gestion du tableau
void check_Pos_Jouable(int board[TAILLE][TAILLE], partie_Data game);
bool poser_pion(int board[TAILLE][TAILLE], partie_Data game);
void place_Selection(int board[TAILLE][TAILLE], partie_Data game, int pos_Case[2]);
bool check_Direction(int board[TAILLE][TAILLE], partie_Data game, int pos_Case[2], int Direction[2]);
bool is_full_board(int board[TAILLE][TAILLE]);
partie_Data IA_Niveau1(int board[TAILLE][TAILLE], partie_Data game, Partie * p);                                                   //* IA Niveau 1
void ResultatsPartie(SDL_Renderer* Rendu, TTF_Font* police, int board[TAILLE][TAILLE]);
void Result(int board[TAILLE][TAILLE], int Résultats[3]);

//!                                                                                                                                //  PROTOTYPES DE PARTIE
void init_Partie(Partie * p, int board[TAILLE][TAILLE]);
void ajout_Coup_Partie(Partie * p, int board[TAILLE][TAILLE], partie_Data game);
void annuler_Coup(Partie * p);
void save_Partie(Partie * p, const char * name);
Partie * import_Partie(const char * name);
void charger_Partie(Partie * p, int board[TAILLE][TAILLE]);
partie_Data chargement_Partie_data(Partie * p, int board[TAILLE][TAILLE], partie_Data game);
void free_Partie(Partie * p);