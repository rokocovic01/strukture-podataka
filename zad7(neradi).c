#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define EXIT_SUCCESS 0
#define MAX_STRING_LENGHT 128
#define ERROR -1

struct _directory;
typedef struct _directory* Pozicija;
typedef struct _directory {
	char name[MAX_STRING_LENGHT];
	Pozicija sibling;
	Pozicija child;
}Directory;

struct _stog;
typedef struct _stog* Stogzicija;
typedef struct _stog {
	Pozicija stogrektorij;
	Stogzicija next;
}Stog;

void mainMenu(void);
Pozicija insert(Pozicija P, Pozicija Q);
Pozicija openDirectory(Pozicija P, Stogzicija Q);
int printDirectory(Pozicija P);
int addDirectory(Pozicija P);

int push(Stogzicija P, Pozicija Q);
Pozicija pop(Stogzicija P);

int main(void)
{
	Directory Root = { .name = "C: ", .sibling = NULL, .child = NULL };
	Pozicija Temp = &Root;
	Stog Head = { .stogrektorij = NULL, .next = NULL };
	char odabir = '0';
	int success = 0;
	char ime[MAX_STRING_LENGHT] = "";

	do {
		mainMenu();
		printf("Odabir: ");
		scanf(" %c", &odabir);
		odabir = toupper(odabir);

		switch (odabir) {
		case 'A':
			success = addDirectory(&Root);
			if (success != EXIT_SUCCESS)printf("Funkcija nije pravilno izvrsena!");
			break;
		case 'B':
			if (NULL == Head.next) {
				Temp = openDirectory(&Root, &Head);
			}
			else {
				Temp = openDirectory(pop(&Head), &Head);
			}
			break;
		case 'C':
			success = printDirectory(Temp);
			if (success != EXIT_SUCCESS)printf("Funkcija nije pravilno izvrsena!");
			break;
		case 'Z':
			printf("Program je zavrsen!");
			break;
		default:
			printf("Niste odabrali niti jednu opciju!\n");
		}
	} while (odabir != 'Z');

	return EXIT_SUCCESS;
}

int push(Stogzicija P, Pozicija Q)
{
	Stogzicija New = malloc(sizeof(Stog));
	if (NULL == New) {
		printf("Memorija nije alocirana!\n");
		return ERROR;
	}

	New->stogrektorij = Q;
	New->next = NULL;

	if (NULL == P->next) {
		P->next = New;
	}
	else {
		New->next = P->next;;
		P->next = New;
	}

	return EXIT_SUCCESS;
}

Pozicija pop(Stogzicija P)
{
	Pozicija Vrati = NULL;
	Stogzicija Temp = P->next;

	if (NULL == P->next) {
		printf("Stog je prazan!");
		return NULL;
	}

	Vrati = Temp->stogrektorij;
	P->next = Temp->next;
	free(Temp);
	Temp = NULL;

	return Vrati;
}

Pozicija insert(Pozicija P, Pozicija Q)
{
	if (NULL == P) {
		return Q;
	}

	if (strcmp(P->name, Q->name) > 0) {
		Q->sibling = P;
		return Q;
	}

	P->sibling = insert(P->sibling, Q);

	return P;
}

void printStog(Stogzicija P)
{
	Stogzicija Temp = P->next;

	if (NULL == Temp) {
		printf("C: ");
		return;
	}

	printStog(Temp->next);

	printf("%s: ", Temp->stogrektorij->name);

	return;
}

void mainMenu(void)
{
	printf("\t\tMAIN MENU\n");
	printf("(A)Add directory.\n");
	printf("(B)Open directory.\n");
	printf("(C)Print directory.\n");
	printf("(D)Go to previous directory.\n");
	printf("(Z)Ext program.\n");
}

int addDirectory(Pozicija P)
{
	char name[MAX_STRING_LENGHT] = "";

	printf("Unesi ime novog direktorija: ");
	scanf(" %s", name);

	Pozicija New = malloc(sizeof(Directory));

	if (NULL == New) {
		printf("Memorija nije alocirana!\n");
		return ERROR;
	}

	strcpy(New->name, name);
	New->sibling = NULL;
	New->child = NULL;

	P->child = insert(P->child, New);

	return EXIT_SUCCESS;
}

Pozicija openDirectory(Pozicija P, Stogzicija Q)
{
	Pozicija Vrati = NULL;
	Pozicija Temp = P->child;
	char ime[MAX_STRING_LENGHT] = "";
	int success = 0;

	printf("Unesi ime direktorija kojeg zelis otvoriti: ");
	scanf(" %s", ime);

	if (strcmp(Temp->name, ime) == 0) {
		Vrati = Temp;
		success = push(Q, Vrati);
		if (success != EXIT_SUCCESS)printf("Funkcija nije pravilno izvrsena!");
		printStog(Q);
		return Vrati;
	}
	else {
		while (strcmp(Temp->name, ime) != 0) {
			Temp = Temp->sibling;
		}
		Vrati = Temp;
		success = push(Q, Vrati);
		if (success != EXIT_SUCCESS)printf("Funkcija nije pravilno izvrsena!");
		printStog(Q);
		return Vrati;
	}
}

int printDirectory(Pozicija P)
{
	Pozicija Temp = P->child;

	if (NULL == Temp) {
		printf("Direktorij je prazan.");
		return EXIT_SUCCESS;
	}

	while (Temp->sibling != NULL) {
		printf("\t%s\n", Temp->name);
		Temp = Temp->sibling;
	}

	return EXIT_SUCCESS;
}