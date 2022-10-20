#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define ERROR_BROJ_BODOVA (-5)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define USPJESNO_IZVRSEN_PROGRAM (0)

int izbrojiStudente(char* filename);

typedef struct student {
    char ime[50];
    char prezime[50];
    int bodovi;
} student;

void unosStudenata(int, student*, char* filename);
int nadiMaxBrBodova(student*, int);
void ispisStudenata(int, int, student*);

int main(void) {

    student* nizStudenata;
    char filename[MAX_FILE_NAME] = { 0 };
    printf("Unesi ime dokumenta: ");
    scanf(" %s", filename);
    int brojStudenata = izbrojiStudente(filename);
    printf("Broj studenata u datoteci je: %d \n", brojStudenata);

    nizStudenata = (student*)malloc(brojStudenata * sizeof(student));
    if (nizStudenata == NULL) {
        printf("Memorija nije alocirana\n");
        exit(0);
    }
    else {
        printf("memorija je alocirana\n");
    }
    unosStudenata(brojStudenata, nizStudenata, filename);
    int maxBrBodova = nadiMaxBrBodova(nizStudenata, brojStudenata);
    if (maxBrBodova == ERROR_BROJ_BODOVA) {
        printf("problem pri trazenju najveceg broja bodova\n");
    }
    else {
        printf("najveci broj bodova je: %d", maxBrBodova);
    }
    ispisStudenata(brojStudenata, maxBrBodova, nizStudenata);

    return USPJESNO_IZVRSEN_PROGRAM;
}

int izbrojiStudente(char* filename) {
    FILE* fp = NULL;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("datoteka nije uspjesno otvorena\n");
        return  FILE_DIDNT_OPEN_ERROR;
    }
    while (!feof(fp)) {
        fgets(buffer, MAX_LINE, fp);
        if (strcmp("\n", buffer) != 0) {
            count++;
        }
    }
    fclose(fp);
    return count;
}
void unosStudenata(int brojStudenata, student* nizStudenata, char* filename) {
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    int i;
    for (i = 0; i < brojStudenata; i++) {
        fscanf(fp, " %s %s %d", nizStudenata[i].ime, nizStudenata[i].prezime, nizStudenata[i].bodovi);
        printf(" %s %s %d \n", nizStudenata[i].ime, nizStudenata[i].prezime, nizStudenata[i].bodovi);
    }
    fclose(fp);
}
int nadiMaxBrBodova(student* nizStudenata, int brojStudenata) {
    int maxBrojBodova = ERROR_BROJ_BODOVA;
    int i;
    for (i = 0; i < brojStudenata; i++) {
        if (nizStudenata[i].bodovi > maxBrojBodova) {
            maxBrojBodova = nizStudenata[i].bodovi;
        }
    }
    return maxBrojBodova;
}
void ispisStudenata(int brojStudenata, int maxBrBodova, student* nizStudenata) {
    int i;
    printf("IME \t PREZIME \t RELATIVAN BROJ BODOVA\n");
    for (i = 0; i < brojStudenata; i++) {
        float relativanBrBodova = (float)nizStudenata[i].bodovi / maxBrBodova * 100;
        printf("%s\t %s\t\t %f\n", nizStudenata[i].ime, nizStudenata[i].prezime, relativanBrBodova);
    }
}
