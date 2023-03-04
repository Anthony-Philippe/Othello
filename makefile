PG = Programme/
c = rm -rf $(PG)*.o

run: $(PG)main.o $(PG)jeu.o
	gcc -o run $(PG)main.o $(PG)jeu.o -lm
	$(c)

main.o: $(PG)main.c $(PG)prototype.h
	gcc -c -Wall -g $(PG)main.c -lm
jeu.o: $(PG)jeu.c
	gcc -c -Wall -g $(PG)jeu.c -lm

clean:
	$(c) run