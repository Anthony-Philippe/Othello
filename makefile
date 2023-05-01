PG = Programme/
c = rm -rf $(PG)*.o

SDL_OPTIONS = SDL2 -D_REENTRANT
SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

run: $(PG)main.o $(PG)interface.o $(PG)jeu.o $(PG)partie.o $(PG)ia.o
	gcc -o run $(PG)main.o $(PG)interface.o $(PG)jeu.o $(PG)partie.o $(PG)ia.o $(SDL_LIBS) -lm
	$(c)

main.o: $(PG)main.c $(PG)directive.h $(PG)prototype.h
	gcc -c -Wall -g $(PG)main.c $(SDL_OPTIONS) -lm
interface.o: $(PG)interface.c
	gcc -c -Wall -g $(PG)interface.c -lm
jeu.o: $(PG)jeu.c
	gcc -c -Wall -g $(PG)jeu.c -lm
partie.o: $(PG)partie.c
	gcc -c -Wall -g $(PG)partie.c -lm
ia.o: $(PG)ia.c
	gcc -c -Wall -g $(PG)ia.c -lm

clean:
	$(c) run *.txt