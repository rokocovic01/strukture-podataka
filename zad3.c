#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define MAX_STRING_LENGHT 128
#define FUNCTION_EXIT_SUCCESS 5
#define MEMORY_NOT_ALLOCATED -1
#define LIST_DOES_NOT_EXIST 4
#define FILE_DIDNT_OPEN -2

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba {
	char ime[MAX_STRING_LENGHT];
	char prezime[MAX_STRING_LENGHT];
	int god_rod;
	Pozicija Next;
}Osoba;

Pozicija newPerson(void);
Pozicija traziPret(Pozicija Head);

void mainMenu(void);

int printList(Pozicija Head);
int newPocetak(Pozicija Head);
int newKraj(Pozicija Head);
int Trazi(Pozicija Head);
int Brisi(Pozicija Head);
int dodajIza(Pozicija Head);
int dodajIspred(Pozicija Head);
int Sort(Pozicija Head);
int saveInFile(Pozicija Head);
int FileNewEl(Pozicija Head, char name[], char surname[], int year);
int ReadFromFile(Pozicija Head);

int main(void)
{
	Osoba Head;
	Head.Next = NULL;
	int success = 0;
	char odabir = { 0 };

	do {
		mainMenu();
		printf("Odabir: ");
		scanf(" %c", &odabir);
		odabir = toupper(odabir);

		switch (odabir) {
		case 'A':
			success = newPocetak(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'B':
			success = printList(Head.Next);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'C':
			success = newKraj(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'D':
			success = Trazi(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'E':
			success = Brisi(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'F':
			success = dodajIza(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'G':
			success = dodajIspred(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'H':
			success = Sort(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'I':
			success = saveInFile(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		case 'J':
			success = ReadFromFile(&Head);
			if (success == FUNCTION_EXIT_SUCCESS);
			break;
		default:
			printf("Niste odabrali niti jednu opciju!\n");
		}
	} while (odabir != 'Z');

	return EXIT_SUCCESS;
}

void mainMenu(void)
{
	printf("\t\tMAIN MENU\n");
	printf("(A)Add new person at the start of the list.\n");
	printf("(B)Print the list.\n");
	printf("(C)Add new person at the end od the list.\n");
	printf("(D)Find a person in the list by surname.\n");
	printf("(E)Delete a person from the list.\n");
	printf("(F)Add new person after selected.\n");
	printf("(G)Add new person before selected.\n");
	printf("(H)Sort the list.\n");
	printf("(I)Save the list into a file.\n");
	printf("(J)Read the list from a file.\n");
	printf("(Z)End program.\n");
}

Pozicija newPerson(void)
{
	Pozicija New = malloc(sizeof(Osoba));
	if (New == NULL) {
		printf("Memorija nije alocirana!\n");
		return MEMORY_NOT_ALLOCATED;
	}
	printf("Unos nove osobe: \n");
	printf("\tIme: ");
	scanf(" %s", New->ime);
	printf("\tPrezime: ");
	scanf(" %s", New->prezime);
	printf("\tGodina rodenja: ");
	scanf("%d", &New->god_rod);
	New->Next = NULL;

	return New;
}

int printList(Pozicija Head)
{
	Pozicija Temp = Head;

	if (Temp == NULL) {
		printf("Lista ne postoji!\n");
		return LIST_DOES_NOT_EXIST;
	}

	printf("Lista: \n");
	while (Temp != NULL) {
		printf("\t%s\t%s\t%d\n", Temp->ime, Temp->prezime, Temp->god_rod);
		Temp = Temp->Next;
	}

	return FUNCTION_EXIT_SUCCESS;
}

int newPocetak(Pozicija Head)
{
	Pozicija New = newPerson();
	New->Next = Head->Next;
	Head->Next = New;

	return FUNCTION_EXIT_SUCCESS;
}

int newKraj(Pozicija Head)
{
	Pozicija New = newPerson();

	while (Head->Next != NULL) {
		Head = Head->Next;
	}
	Head->Next = New;
	New->Next = NULL;

	return FUNCTION_EXIT_SUCCESS;
}

int Trazi(Pozicija Head)
{
	Pozicija Temp = Head;
	char temp[MAX_STRING_LENGHT] = { 0 };

	printf("\nUnesite prezime osobe koju trazite: ");
	scanf(" %s", temp);

	while (Temp != NULL && strcmp(Temp->prezime, temp)) {
		Temp = Temp->Next;
	}
	if (Temp == NULL) {
		printf("Osoba s tim prezimenom nije pronadena!\n");
	}
	else {
		printf("\t%s\t%s\t%d\n", Temp->ime, Temp->prezime, Temp->god_rod);
	}

	return FUNCTION_EXIT_SUCCESS;
}

Pozicija traziPret(Pozicija Head)
{
	Pozicija Prev = Head;
	Head = Head->Next;
	char temp[MAX_STRING_LENGHT] = { 0 };

	printf("\nUnesite prezime osobe koju trazite: ");
	scanf(" %s", temp);

	while (Head != NULL && strcmp(Head->prezime, temp)) {
		Prev = Prev->Next;
		Head = Head->Next;
	}
	if (Head == NULL) {
		return NULL;
	}
	else {
		return Prev;
	}
}

int Brisi(Pozicija Head)
{
	Head = traziPret(Head);

	if (Head == NULL) {
		printf("Osoba s tim prezimenom nije pronadena!\n");
	}
	else {
		Head->Next = Head->Next->Next;
	}

	return FUNCTION_EXIT_SUCCESS;
}

int dodajIza(Pozicija Head)
{
	Pozicija Temp = traziPret(Head);
	if (Temp == NULL) {
		printf("Osoba s tim prezimenom nije pronadena!\n");
		return FUNCTION_EXIT_SUCCESS;
	}
	Pozicija New = newPerson();

	New->Next = Temp->Next->Next;
	Temp->Next->Next = New;

	return FUNCTION_EXIT_SUCCESS;
}

int dodajIspred(Pozicija Head)
{
	Pozicija Temp = traziPret(Head);
	if (Temp == NULL) {
		printf("Osoba s tim prezimenom nije pronadena!\n");
		return FUNCTION_EXIT_SUCCESS;
	}
	Pozicija New = newPerson();

	New->Next = Temp->Next;
	Temp->Next = New;

	return FUNCTION_EXIT_SUCCESS;
}

int Sort(Pozicija Head)
{
	Pozicija X, prevX, Temp, End;
	End = NULL;

	while (Head->Next != End)
	{
		prevX = Head;
		X = Head->Next;
		while (X->Next != End)
		{
			if (strcmp(X->prezime, X->Next->prezime) > 0)
			{
				Temp = X->Next;
				prevX->Next = Temp;
				X->Next = Temp->Next;
				Temp->Next = X;

				X = Temp;
			}

			prevX = X;
			X = X->Next;
		}

		End = X;
	}

	printf("List sorted.\n");

	return FUNCTION_EXIT_SUCCESS;
}

int saveInFile(Pozicija Head)
{
	FILE* file = fopen("file.txt", "w");
	if (file == NULL) return FILE_DIDNT_OPEN;

	for (Pozicija Temp = Head->Next; Temp != NULL; Temp = Temp->Next)
	{
		fprintf(file, "%s\t%s\t%d\n", Temp->ime, Temp->prezime, Temp->god_rod);
	}

	printf("List saved into a file\n");

	fclose(file);

	return FUNCTION_EXIT_SUCCESS;
}

int FileNewEl(Pozicija Head, char name[], char surname[], int year)
{
	Pozicija New = malloc(sizeof(Osoba));
	if (New == NULL) {
		printf("Memorija nije alocirana!\n");
		return MEMORY_NOT_ALLOCATED;
	}
	New->Next = NULL;
	strcpy(New->ime, name);
	strcpy(New->prezime, surname);
	New->god_rod = year;

	Pozicija Now = Head;
	while (Now->Next != NULL) {
		Now = Now->Next;
	}
	Now->Next = New;

	return FUNCTION_EXIT_SUCCESS;
}
int ReadFromFile(Pozicija Head)
{
	FILE* file = fopen("file.txt", "r");
	if (file == NULL) return FILE_DIDNT_OPEN;

	char name[MAX_STRING_LENGHT] = {0};
	char surname[MAX_STRING_LENGHT] = {0};
	int year = 0;
	int success = 0;

	while (!feof) {
		fscanf(file, "\t%s\t%s\t%d", name, surname, &year);
		success = FileNewEl(Head, name, surname, year);
		if (success == FUNCTION_EXIT_SUCCESS);
	}

	fclose(file);

	return FUNCTION_EXIT_SUCCESS;
}