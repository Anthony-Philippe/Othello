PG = Programme/
c = rm -rf $(PG)*.o

run: $(PG)main.o $(PG)jeu.o $(PG)ia.o $(PG)interface.o
	gcc -o run $(PG)main.o $(PG)jeu.o $(PG)ia.o $(PG)interface.o -lm
	$(c)

main.o: $(PG)main.c $(PG)prototype.h
	gcc -c -Wall -g $(PG)main.c -lm
jeu.o: $(PG)jeu.c
	gcc -c -Wall -g $(PG)jeu.c -lm
ia.o: $(PG)ia.c
	gcc -c -Wall -g $(PG)ia.c -lm
interface.o: $(PG)interface.c
	gcc -c -Wall -g $(PG)interface.c -lm

clean:
	$(c) run partie.txt