exclusions.o : exclusions.c exclusions.h
	gcc -c exclusions.c exclusions.h

precedencetemps.o : precedencetemps.c precedencetemps.h
	gcc -c precedencetemps.c precedencetemps.h

main.o : main.c
	gcc -c main.c

exec : exclusions.o precedencetemps.o main.o
	gcc -o exec exclusions.o precedencetemps.o main.o