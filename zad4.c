#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EXIT_SUCCESS 0
#define MAX_FILE_NAME 128
#define MAX_BUFFER_SIZE 256
#define FILE_DID_NOT_OPEN -1
#define MEMORY_NOT_ALLOCATED -1

struct _polinom;
typedef struct _polinom* Pozicija;
typedef struct _polinom {
	int koeficijent;
	int eksponent;
	Pozicija Next;
}Polinom;

Pozicija newPolinom(int koef, int eksp);
int readFromFile(FILE* fp, Pozicija Head1, Pozicija Head2);
int zbrojiPolinome(Pozicija Head1, Pozicija Head2, Pozicija Head3);
int pomnoziPolinome(Pozicija Head1, Pozicija Head2, Pozicija Head4);


void ispis(Pozicija Head)
{
	Pozicija Temp = Head;

	if (Temp == NULL) {
		printf("Lista ne postoji!\n");
		return 0;
	}

	while (Temp != NULL) {
		printf("%d %d\t", Temp->koeficijent, Temp->eksponent);
		Temp = Temp->Next;
	}

}

int main(void)
{
	int success = 0;

	Polinom Head1 = { 0 }, Head2 = { 0 }, Head3 = { 0 }, Head4 = { 0 };
	Head1.Next = NULL, Head2.Next = NULL, Head3.Next = NULL, Head4.Next = NULL;

	char filename[MAX_FILE_NAME] = { 0 };
	//printf("Unesi ime datoteke: ");
	//scanf(" %s", filename);

	FILE* fp = NULL;
	fp = fopen("polinomi.txt", "r");

	if (fp == NULL) {
		printf("Datoteka nije pronadena!");
		return FILE_DID_NOT_OPEN;
	}

	success = readFromFile(fp, &Head1, &Head2);
	if (success != EXIT_SUCCESS) printf("Funkcija nije izvrsena!");

	success = zbrojiPolinome(Head1.Next, Head2.Next, &Head3);
	if (success != EXIT_SUCCESS) printf("Funkcija nije izvrsena!");

	success = pomnoziPolinome(Head1.Next, Head2.Next, &Head4);
	if (success != EXIT_SUCCESS) printf("Funkcija nije izvrsena!");

	printf("Polinom 1: \n");
	ispis(Head1.Next);
	printf("\nPolinom 2: \n");
	ispis(Head2.Next);
	printf("\nZbroj 2: \n");
	ispis(Head3.Next);
	printf("\nUmnozak 2: \n");
	ispis(Head4.Next);


	fclose(fp);

	return EXIT_SUCCESS;
}

Pozicija newPolinom(int koef, int eksp)
{
	Pozicija New = malloc(sizeof(Polinom));
	if (New == NULL) {
		printf("Memorija nije alocirana!");
		return MEMORY_NOT_ALLOCATED;
	}

	New->koeficijent = koef;
	New->eksponent = eksp;
	New->Next = NULL;

	return New;
}

int readFromFile(FILE* fp, Pozicija Head1, Pozicija Head2)
{
	Pozicija New = NULL;
	char buffer[MAX_BUFFER_SIZE] = { 0 };
	const char s[2] = "\t";
	char* token = NULL;
	int koef = 0;
	int eksp = 0;

	fgets(buffer, MAX_BUFFER_SIZE, fp);
	token = strtok(buffer, s);
	while (token != NULL) {
		sscanf(token, "%d %d", &koef, &eksp);
		New = newPolinom(koef, eksp);
		Head1->Next = New;
		Head1 = Head1->Next;
		token = strtok(NULL, s);
	}

	fgets(buffer, MAX_BUFFER_SIZE, fp);
	token = strtok(buffer, s);
	while (token != NULL) {
		sscanf(token, "%d %d", &koef, &eksp);
		New = newPolinom(koef, eksp);
		Head2->Next = New;
		Head2 = Head2->Next;
		token = strtok(NULL, s);
	}

	return EXIT_SUCCESS;
}

int zbrojiPolinome(Pozicija Head1, Pozicija Head2, Pozicija Head3)
{
	Pozicija Temp1 = Head1;
	Pozicija Temp2 = Head2;
	Pozicija Temp3 = Head3;
	Pozicija New = NULL;

	while (Temp1 != NULL && Temp2 != NULL) {
		if (Temp1->eksponent == Temp2->eksponent) {
			New = newPolinom(Temp1->koeficijent + Temp2->koeficijent, Temp1->eksponent);
			Temp1 = Temp1->Next;
			Temp2 = Temp2->Next;
			Temp3->Next = New;
			Temp3 = Temp3->Next;
		}
		else if (Temp1->eksponent > Temp2->eksponent) {
			New = newPolinom(Temp1->koeficijent, Temp1->eksponent);
			Temp1 = Temp1->Next;
			Temp3->Next = New;
			Temp3 = Temp3->Next;
		}
		else if (Temp1->eksponent < Temp2->eksponent) {
			New = newPolinom(Temp2->koeficijent, Temp2->eksponent);
			Temp2 = Temp2->Next;
			Temp3->Next = New;
			Temp3 = Temp3->Next;
		}
	}
	while (Temp1 != NULL) {
		New = newPolinom(Temp1->koeficijent, Temp1->eksponent);
		Temp1 = Temp1->Next;
		Temp3->Next = New;
		Temp3 = Temp3->Next;
	}
	while (Temp2 != NULL) {
		New = newPolinom(Temp2->koeficijent, Temp2->eksponent);
		Temp2 = Temp2->Next;
		Temp3->Next = New;
		Temp3 = Temp3->Next;
	}

	return EXIT_SUCCESS;
}

int pomnoziPolinome(Pozicija Head1, Pozicija Head2, Pozicija Head4)
{
	Pozicija Temp1 = Head1;
	Pozicija Temp2 = Head2;
	Pozicija Temp4 = Head4;
	Pozicija New = NULL;
	int success = 0;

	while (Temp1 != NULL) {
		while (Temp2 != NULL) {
			New = newPolinom(Temp1->koeficijent * Temp2->koeficijent, Temp1->eksponent + Temp2->eksponent);
			Temp2 = Temp2->Next;
			Temp4->Next = New;
			Temp4 = Temp4->Next;
		}
		Temp1 = Temp1->Next;
		Temp2 = Head2;
	}

	return EXIT_SUCCESS;
}