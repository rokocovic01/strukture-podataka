#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>	
#include<ctype.h>
#include<time.h>

#define EXIT_SUCCESS 0

struct _stablo;
typedef struct _stablo* Pozicija;
typedef struct _stablo {
	int br;
	Pozicija left;
	Pozicija right;
}Stablo;

void mainMenu(void);
Pozicija new(int br);
Pozicija insert(Pozicija P, Pozicija Q);
int add(Pozicija P);
void print(Pozicija P);
void sum(Pozicija P);
void delete(Pozicija P);
void filePrint(Pozicija P, FILE* fp);

int main(void)
{
	Pozicija Root = NULL;
	Pozicija Temp = NULL;
	int odabir = 0;
	int br = 0;
	srand((unsigned)time(NULL));
	int size = 0;
	int i = 0;
	FILE* fp = NULL;

	do {
		mainMenu();
		scanf("%d", &odabir);
		switch (odabir) {
		case 1:
			printf("Unesite broj koji zelite unijeti: ");
			scanf("%d", &br);
			Temp = new(br);
			Root = insert(Root, Temp);
			break;
		case 2:
			sum(Root);
			print(Root);
			printf("\n");
			break;
		case 3:
			delete(Root);
			Root = NULL;
			printf("Unesite velicinu binarnog stabla pretrazivanja(maksimalno 10): ");
			scanf(" %d", &size);
			if (size < 1 || size > 10) {
				printf("Nepriznata velicina!\n");
				break;
			}
			for (i = 0; i < size; i++) {
				Temp = new((rand() % 79) + 11);
				Root = insert(Root, Temp);
			}
			i = 0;
			print(Root);
			printf("\n");
			fp = fopen("stablo.txt", "w");
			filePrint(Root, fp);
			fclose(fp);
			break;
		case 4:
			sum(Root);
			print(Root);
			printf("\n");
			fp = fopen("stablo.txt", "a");
			fprintf(fp, "\n");
			filePrint(Root, fp);
			fprintf(fp, "\n");
			fclose(fp);
			break;
		case 5:
			print(Root);
			printf("\n");
			break;
		case 6:
			printf("Program zavrsen!\n");
			break;
		default:
			printf("Niste odabrali nijednu opciju!\n");
		}
	} while (odabir != 6);

	return EXIT_SUCCESS;
}

void mainMenu(void)
{
	printf("\t\tMAIN MENU\n");
	printf("1 - insert\n");
	printf("2 - replace\n");
	printf("3 - rand\n");
	printf("4 - rand replace\n");
	printf("5 - print\n");
	printf("6 - izlaz\n");
	printf("\nOdabir: ");
}

Pozicija new(int br)
{
	Pozicija New = malloc(sizeof(Stablo));

	if (NULL == New) {
		printf("Memorija nije alocirana!\n");
		return NULL;
	}

	New->br = br;
	New->left = NULL;
	New->right = NULL;

	return New;
}

Pozicija insert(Pozicija P, Pozicija Q)
{
	if (NULL == P) {
		return Q;
	}

	if (P->br > Q->br) {
		P->right = insert(P->right, Q);
	}
	else if (P->br < Q->br) {
		P->left = insert(P->left, Q);
	}
	else if (P->br == Q->br) {
		P->left = insert(P->left, Q);
	}
	else {
		free(Q);
	}

	return P;
}

void print(Pozicija P)
{
	if (NULL == P) return;

	print(P->left);
	printf("%d ", P->br);
	print(P->right);
}

int add(Pozicija P)
{
	int sum = 0;

	if (NULL == P) {
		return 0;
	}

	sum = P->br + add(P->left) + add(P->right);

	return sum;
}

void sum(Pozicija P)
{
	if (NULL == P) return;

	P->br = add(P) - P->br;
	sum(P->left);
	sum(P->right);
}

void delete(Pozicija P)
{
	if (NULL == P) return;

	delete(P->left);
	delete(P->right);
	free(P);
}

void filePrint(Pozicija P, FILE* fp)
{
	if (NULL == P) return;

	filePrint(P->left, fp);
	fprintf(fp, "%d ", P->br);
	filePrint(P->right, fp);
}