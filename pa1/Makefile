# Strother Woog
# 1618221
# CMPS 101
# 7/3/19
# Makefile for CMPS 101 Programming Assignment 1
# Makefile
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o
	
Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o
 