#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#define MAX_STRING_LENGHT 128

struct _direktorij;
typedef struct _direktorij* Pozicija;
typedef struct _direktorij {
	char name[MAX_STRING_LENGHT];
	Pozicija sibling;
	Pozicija child;
}Direktorij;

struct _stog;
typedef struct _stog* Stogzicija;
typedef struct _stog {
	Pozicija dir;
	Stogzicija next;
}Stog;

void mainMenu(void);
Pozicija insert(Pozicija P, Pozicija Q);
int makeDirectory(Pozicija P);
int printDirectory(Pozicija P);
int push(Stogzicija P, Pozicija Q);
Pozicija pop(Stogzicija P);
void stogPrint(Stogzicija P);
Pozicija openDirectory(Pozicija P, Stogzicija Q);

int main(void)
{
	Direktorij Root = { .name = "C", .sibling = NULL, .child = NULL };
	Stog Head = { .dir = NULL, .next = NULL };
	Pozicija Trenutni = &Root;
	char odabir = '0';
	int success = 0;

	printf("C:\n\n");

	do {
		mainMenu();
		scanf(" %c", &odabir);
		switch (odabir) {
		case '1':
			success = makeDirectory(Trenutni);
			if (success != EXIT_SUCCESS) printf("Funkcija nije uspjesno izvrsena!\n");
			break;
		case '2':
			Trenutni = openDirectory(Trenutni, &Head);
			break;
		case '3':
			Trenutni = pop(&Head);
			if (NULL == Trenutni) {
				printf("Vec se nalazite u C direktoriju!\n");
				Trenutni = &Root;
			}
			stogPrint(Head.next);
			printf("\n");
			break;
		case '4':
			success = printDirectory(Trenutni);
			if (success != EXIT_SUCCESS) printf("Funkcija nije uspjesno izvrsena!\n");
			break;
		case '5':
			printf("Program je zavrsen!\n");
			break;
		default: printf("Niste odabrali niti jednu opciju!\n");
		}
		printf("\n");
	} while (odabir != '5');

	return EXIT_SUCCESS;
}

void mainMenu(void)
{
	printf("\t\tMAIN MENU\n");
	printf("1 - md\n");//napraviti novi direktorij
	printf("2 - cd dir\n");//uci u novi direktorij
	printf("3- cd..\n");//vratiti se na roditelj direktorij
	printf("4 - dir\n");//prikazati sadrzaj direktorija
	printf("5 - izlaz\n");
	printf("\nOdabir: ");
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

int makeDirectory(Pozicija P)
{
	Pozicija Temp = P->child;
	Pozicija New = malloc(sizeof(Direktorij));

	if (NULL == New) {
		printf("Memorija nije alcirana!\n");
		return EXIT_FAILURE;
	}

	printf("Unesi ime novog direktorija: ");
	scanf(" %s", New->name);
	New->sibling = NULL;
	New->child = NULL;

	P->child = insert(P->child, New);

	return EXIT_SUCCESS;
}

int printDirectory(Pozicija P)
{
	Pozicija Temp = P->child;

	if (NULL == P->child) {
		printf("Direktorij je prazan!\n");
		return EXIT_SUCCESS;
	}

	printf("%s:\n", P->name);
	
	while (Temp != NULL) {
		printf("\t%s\n", Temp->name);
		Temp = Temp->sibling;
	}

	return EXIT_SUCCESS;
}

int push(Stogzicija P, Pozicija Q)
{
	Stogzicija New = malloc(sizeof(Stog));
	if (NULL == New) {
		printf("Memorija nije alocirana!\n");
		return EXIT_FAILURE;
	}

	New->dir = Q;
	New->next = P->next;;
	P->next = New;

	return EXIT_SUCCESS;
}

Pozicija pop(Stogzicija P)
{
	Pozicija Vrati = NULL;
	Stogzicija Temp = P->next;

	if (NULL == P->next) {
		return NULL;
	}

	Vrati = Temp->dir;
	P->next = Temp->next;
	free(Temp);
	Temp = NULL;

	return Vrati;
}

void stogPrint(Stogzicija P)
{
	if (NULL == P) {
		printf("C: ");
		return;
	}

	stogPrint(P->next);

	printf("%s: ", P->dir->name);
}

Pozicija openDirectory(Pozicija P, Stogzicija Q)
{
	Pozicija Temp = P->child;
	char ime[MAX_STRING_LENGHT] = "";
	int success = 0;

	printf("Unesi ime direktorija kojeg zelis otvoriti: ");
	scanf(" %s", ime);

	if (NULL == P->child) {
		printf("Trenutni direktorij je prazan!\n");
		return P;
	}

	while (strcmp(Temp->name, ime) != 0) {
		Temp = Temp->sibling;
	}

	if (NULL == Temp) {
		printf("Ime koje ste upisali ne postoji u ovom direktoriju!\n");
		return NULL;
	}

	success = push(Q, Temp);
	if (success != EXIT_SUCCESS) {
		printf("Funkcija nije uspjesno izvrsena!\n");
		return NULL;
	}

	stogPrint(Q->next);
	printf("\n");

	return Temp;
}