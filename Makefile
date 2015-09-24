CC = gcc
FLAGS = -ansi -Wall
OBJS = Utilitaires.o StringTypes.o Ligne.o Operands.o Analyse.o ListeChaineeOperands.o Fonctions.o main.o Calculs.o Directives.o AdMode.o S19.o Listing.o
EXE = projet

$(EXE) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(EXE) 

Utilitaires.o : main.h Utilitaires.h Utilitaires.c
	$(CC) $(FLAGS) -c Utilitaires.c

StringTypes.o : main.h StringTypes.c
	$(CC) $(FLAGS) -c StringTypes.c

Ligne.o : main.h Utilitaires.h Ligne.h Ligne.c
	$(CC) $(FLAGS) -c Ligne.c

Operands.o : main.h Utilitaires.h Operands.h Operands.c
	$(CC) $(FLAGS) -c Operands.c

Analyse.o : main.h Utilitaires.c Ligne.h Operands.h Analyse.c
	$(CC) $(FLAGS) -c Analyse.c

ListeChaineeOperands.o : main.h ListeChaineeOperands.c
	$(CC) $(FLAGS) -c ListeChaineeOperands.c

Calculs.o : main.h Calculs.h Calculs.c 
	$(CC) $(FLAGS) -c Calculs.c

Fonctions.o : main.h Fonctions.h Fonctions.c 
	$(CC) $(FLAGS) -c Fonctions.c

Directives.o : main.h Directives.h Directives.c 
	$(CC) $(FLAGS) -c Directives.c

AdMode.o : main.h AdMode.h AdMode.c 
	$(CC) $(FLAGS) -c AdMode.c

S19.o : main.h S19.h S19.c 
	$(CC) $(FLAGS) -c S19.c

Listing.o : main.h Listing.h Listing.c 
	$(CC) $(FLAGS) -c Listing.c

main.o : main.h main.c
	$(CC) $(FLAGS) -c main.c

clean : 
	rm *.o
	rm projet
