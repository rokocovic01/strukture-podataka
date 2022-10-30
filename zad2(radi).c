#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define MAX_STRING_LENGHT 128
#define FUNCTION_EXIT_SUCCESS 5
#define MEMORY_NOT_ALLOCATED -1
#define LIST_DOES_NOT_EXIST 4

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba {
	char ime[MAX_STRING_LENGHT];
	char prezime[MAX_STRING_LENGHT];
	int god_rod;
	Pozicija Next;
}Osoba;

Pozicija newPerson(void);

int printList(Pozicija Head);
int newPocetak(Pozicija Head);
int newKraj(Pozicija Head);
int Trazi(Pozicija Head);
Pozicija traziPret(Pozicija Head);
int Brisi(Pozicija Head);


int main(void)
{
	Osoba Head;
	Head.Next = NULL;
	int success = 0;

	success = newPocetak(&Head);
	if (success == FUNCTION_EXIT_SUCCESS);

	success = newKraj(&Head);
	if (success == FUNCTION_EXIT_SUCCESS);

	success = printList(Head.Next);
	if (success == FUNCTION_EXIT_SUCCESS);

	success = Trazi(&Head);
	if (success == FUNCTION_EXIT_SUCCESS);

	success = Brisi(&Head);
	if (success == FUNCTION_EXIT_SUCCESS);

	success = printList(Head.Next);
	if (success == FUNCTION_EXIT_SUCCESS);

	return EXIT_SUCCESS;
}

Pozicija newPerson(void)
{
	Pozicija New = malloc(sizeof(Osoba));
	if (New == NULL) {
		printf("Memorija nije alocirana!");
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
		printf("Lista ne postoji!");
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

	printf("Unesite prezime osobe koju trazite: ");
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

	printf("Unesite prezime osobe koju trazite: ");
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
		printf("Nema osobe s takvim prezimenom!\n");
	}
	else {
		Head->Next = Head->Next->Next;
	}

	return FUNCTION_EXIT_SUCCESS;
}