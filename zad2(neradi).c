#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (128)
#define exitSuccess (0)
#define NEUSPJELA_DINAMICKA_ALOKACIJA (-1)

typedef struct Osoba* Pozicija;

typedef struct Osoba {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godiste;
	Pozicija Next;
}Osoba;


void UnosNaPocetak(Osoba, Pozicija);
void UnosNaKraj(Osoba, Pozicija);
void Ispis(Pozicija);
void TraziPoPrezimenu(Osoba, Pozicija);
Pozicija TaziPrethodnika(Osoba, Pozicija);
void Brisi(Osoba, Pozicija);

int main(void) {
	Osoba o;
	Osoba Head;
	Head.Next = NULL;
	int brojOsoba = 0;
	int i = 0; int godiste = 0;
	char ime[MAX_LINE] = { 0 };
	char prezime[MAX_LINE] = { 0 };
	printf("Koliko osoba zelite unijeti?");
	scanf(" %d", &brojOsoba);
	for (i = 0; i < brojOsoba; i++) {
		printf("Unesite ime osobe: ");
		scanf(" %s", o.ime);
		printf("Unesite prezime osobe: ");
		scanf(" %s", o.prezime);
		printf("Unesite godiste osobe: ");
		scanf(" %d", &o.godiste);
		UnosNaPocetak(o, &Head);
	}
	Ispis(Head.Next);
	printf("Unesi osobu na kraj liste:\n");
	printf("Unesite ime osobe: ");
	scanf(" %s", o.ime);
	printf("Unesite prezime osobe: ");
	scanf(" %s", o.prezime);
	printf("Unesite godiste osobe: ");
	scanf(" %d", &o.godiste);
	UnosNaKraj(o, &Head);
	Ispis(Head.Next);

	printf("Unesi trazeno prezime\n");
	scanf(" %s", o.prezime);
	TraziPoPrezimenu(o, &Head);
	printf("Unesi prezime osobe koju zelis izbrisati\n");
	scanf(" %s", o.prezime);
	Brisi(o, &Head);
	printf("Vasa lista:\n");
	Ispis(Head.Next);
	return exitSuccess;
}

void UnosNaPocetak(Osoba a, Pozicija p) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije alocirana\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	*q = a;
	q->Next = p->Next;
	p->Next = q;
}

void UnosNaKraj(Osoba a, Pozicija p) {
	Pozicija q;
	while (p->Next != NULL) {
		p = p->Next;
	}
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije alocirana\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	*q = a;
	p->Next = q->Next;
	q->Next = NULL;
}
void Ispis(Pozicija p) {
	while (p != 0) {
		printf(" %s\t %s\t %d\n", p->ime, p->prezime, p->godiste);
		p = p->Next;
	}
}
void TraziPoPrezimenu(Osoba a, Pozicija p) {
	while (p != NULL && strcmp(p->prezime, a.prezime)) {
		p = p->Next;
	}
	if (p == NULL) {
		printf("Osoba s tim prezimenom nije pronadena\n");
	}
	else {
		printf(" %s\t %s\t %d\n", p->ime, p->prezime, p->godiste);
	}
}
Pozicija TaziPrethodnika(Osoba a, Pozicija p) {
	Pozicija prev;
	prev = p;
	p = p->Next;
	while (p != NULL && strcmp(p->prezime, a.prezime)) {
		prev = prev->Next;
		p = p->Next;
	}
	if (p == NULL) {
		return NULL;
	}
	else {
		return prev;
	}
}
void Brisi(Osoba a, Pozicija p) {
	p = TaziPrethodnika(a, p);
	if (p == NULL) {
		printf("Nema osobe s takvim prezimenom\n");
	}
	else {
		p->Next = p->Next->Next;
	}
}