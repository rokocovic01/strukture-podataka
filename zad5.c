#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EXIT_SUCCESS 0
#define MAX_STRING_LENGHT 128
#define MAX_BUFFER_SIZE 256
#define FILE_DOES_NOT_EXIST -1
#define MEMORY_NOT_ALLOCATED -1
#define STOG_IS_EMPTY -1
#define NAZIVNIK_NULA -1
#define NEPOZNAT_ZNAK -1

struct _stog;
typedef struct _stog* Pozicija;
typedef struct _stog {
	int vrijednost;
	Pozicija Next;
}Stog;

int push(Pozicija P, int x);
int pop(Pozicija P);
int ispis(Pozicija P);
void brisi(Pozicija P);

int main(void)
{
	int success = 0;
	int br = 0;
	int value = 0;
	Stog Head = { .vrijednost = 0, .Next = NULL };
	FILE* fp = NULL;
	char buffer[MAX_BUFFER_SIZE] = { 0 };
	char* pB = NULL;
	char filename[MAX_STRING_LENGHT] = { 0 };
	char znamenka[MAX_STRING_LENGHT] = { 0 };
	printf("Unesi ime datoteke: ");
	scanf(" %s", filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File didn't open!");
		return FILE_DOES_NOT_EXIST;
	}

	fgets(buffer, MAX_BUFFER_SIZE, fp);
	pB = buffer;

	while (sscanf(pB, "%s%n", znamenka, &br) > 0) {
		if (sscanf(znamenka, "%d", &value) > 0) {
			success = push(&Head, value);
			if (success != EXIT_SUCCESS) printf("Funkcija nije izvrsena!");
		}
		else if (strcmp(znamenka, "+") == 0) {
			int x1 = pop(&Head);
			int x2 = pop(&Head);
			int rez = x2 + x1;
			success = push(&Head, rez);
			if (success != EXIT_SUCCESS) printf("Funkcija nije pravilno izvrsena!");
		}
		else if (strcmp(znamenka, "-") == 0) {
			int x1 = pop(&Head);
			int x2 = pop(&Head);
			int rez = x2 - x1;
			success = push(&Head, rez);
			if (success != EXIT_SUCCESS) printf("Funkcija nije pravilno izvrsena!");
		}
		else if (strcmp(znamenka, "*") == 0) {
			int x1 = pop(&Head);
			int x2 = pop(&Head);
			int rez = x2 * x1;
			success = push(&Head, rez);
			if (success != EXIT_SUCCESS) printf("Funkcija nije pravilno izvrsena!");
		}
		else if (strcmp(znamenka, "/") == 0) {
			int x1 = pop(&Head);
			if (x1 == 0) {
				printf("Nazivnik ne moze biti nula!");
				return NAZIVNIK_NULA;
			}
			int x2 = pop(&Head);
			int rez = x2 / x1;
			success = push(&Head, rez);
			if (success != EXIT_SUCCESS) printf("Funkcija nije pravilno izvrsena!");
		}
		else {
			printf("Nepoznati znak u postfixu!");
			return NEPOZNAT_ZNAK;
		}

		for (int i = 0; i < br; i++) {
			pB++;
		}
	}

	success = ispis(&Head);
	if (success != EXIT_SUCCESS) printf("Funkcija nije pravilno izvrsena!");

	fclose(fp);

	brisi(&Head);

	return EXIT_SUCCESS;
}

int push(Pozicija P, int x)
{
	Pozicija New = NULL;
	New = malloc(sizeof(Stog));
	if (New == NULL) {
		printf("Memorija nije alocirana!");
		return MEMORY_NOT_ALLOCATED;
	}
	New->vrijednost = x;
	New->Next = NULL;

	if (P->Next == NULL) {
		P->Next = New;
	}
	else {
		New->Next = P->Next;;
		P->Next = New;
	}

	return EXIT_SUCCESS;
}

int pop(Pozicija P)
{
	int x = 0;
	Pozicija Temp = P->Next;
	if (Temp == NULL) {
		printf("Stog je prazan!");
		return STOG_IS_EMPTY;
	}

	x = Temp->vrijednost;
	P->Next = Temp->Next;
	free(Temp);

	return x;
}

int ispis(Pozicija P)
{
	if (P->Next == NULL) {
		printf("Stog je prazan!");
		return STOG_IS_EMPTY;
	}
	else {
		while (P->Next != NULL) {
			printf("%d\t", P->Next->vrijednost);
			P = P->Next;
		}
	}

	return EXIT_SUCCESS;
}

void brisi(Pozicija P)
{
	Pozicija Temp = NULL;
	if (P->Next == NULL) {
		free(P);
	}
	else{
		while (P->Next != NULL) {
			Temp = P->Next;
			P->Next = P->Next->Next;
			free(Temp);
		}
	}
}