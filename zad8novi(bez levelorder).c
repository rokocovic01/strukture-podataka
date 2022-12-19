#define _CRT_SECURE_NO_WARNINGS
#define EXIT_SUCCESS (1)

#include<stdlib.h>
#include<stdio.h>

typedef struct cvor* Pozicija;
typedef struct cvor {
	int broj;
	Pozicija left;
	Pozicija right;
}cvor;

Pozicija UnosNovogElementa(Pozicija p, Pozicija q);
void IspisInorder(Pozicija p);
void IspisPreorder(Pozicija p);
void IspisPostorder(Pozicija p);
Pozicija BrisiElement(Pozicija p, int br);
Pozicija nadiMax(Pozicija p);
Pozicija nadiMin(Pozicija p);
Pozicija TraziElement(Pozicija p, int br);

int main() {
	Pozicija root = NULL;
	int izbor;
	do {
		printf("\nOdaberite:\n 1 - unos novog elementa\n 2 - ispis inorder\n 3 - ispis preorder\n");
		printf(" 4 - ispis postorder\n 5 - ispis level order\n 6 - brisi element\n 7 - nadi element\n 8 - izlaz\n");
		scanf(" %d", &izbor);
		switch (izbor) {
			case 1:
				printf("Unesite novi element:");
				int noviBr;
				scanf(" %d", &noviBr);
				Pozicija novi =(Pozicija)malloc(sizeof(cvor));
				novi->broj = noviBr;
				novi->left = NULL;
				novi->right = NULL;
				root = UnosNovogElementa(root, novi);
				break;
			case 2:
				IspisInorder(root);
				break;
			case 3:
				IspisPreorder(root);
				break;
			case 4:
				IspisPostorder(root);
				break;
			case 5:
				//IspisLevelorder
				break;
			case 6:
				printf("Unesite element koji zelite izbrisati\n");
				int brisiEl;
				scanf(" %d", &brisiEl);
				root = BrisiElement(root, brisiEl);
				break;
			case 7:
				printf("Unesite element koji zelite pronaci\n");
				int trazeniBr; Pozicija temp;
				scanf(" %d", &trazeniBr);
				temp = TraziElement(root, trazeniBr);
				if (temp) {
					printf("element %d nalazi se u stablu na adresi %d\n", temp->broj, temp);
				}
				else {
					printf("Element koji ste unijeli nepostoji u stablu");
				}
				break;
			case 8:
				break;
			default:
				printf("Pogresan unos!");
		}
	} while (izbor != 8);

	return 1;
}

Pozicija UnosNovogElementa(Pozicija p, Pozicija q) {
	if (p == NULL)
		return q;
	if (p->broj < q->broj) {
		p->right= UnosNovogElementa(p->right, q);
	}else if(p->broj > q->broj) {
		p->left = UnosNovogElementa(p->left, q);
	}
	else {
		free(q);
	}
	return p;
}

void IspisInorder(Pozicija p) {
	if (p == NULL) {
		return NULL;
	}
	IspisInorder(p->left);
	printf(" %d", p->broj);
	IspisInorder(p->right);
}

void IspisPreorder(Pozicija p) {
	if (p == NULL) {
		return NULL;
	}
	printf(" %d", p->broj);
	IspisPreorder(p->left);
	IspisPreorder(p->right);
}
	
void IspisPostorder(Pozicija p) {
	if (p == NULL) {
		return NULL;
	}
	IspisPostorder(p->left);
	IspisPostorder(p->right);
	printf(" %d", p->broj);
}

Pozicija BrisiElement(Pozicija p, int br) {
	if (p == NULL) {
		return NULL;
	}

	if (p->broj < br) {
		p->right = BrisiElement(p->right, br);
	}
	else if (p->broj > br) {
		p->left = BrisiElement(p->left, br);
	}
	else {
		if (p->left) {
			Pozicija temp = nadiMax(p->left);
			p->broj = temp->broj;
			p->left = BrisiElement(p->left, temp->broj);
		}
		else if (p->right) {
			Pozicija temp = nadiMin(p->right);
			p->broj = temp->broj;
			p->right = BrisiElement(p->right, temp->broj);
		}
		else {
			free(p);
			return NULL;
		}
	}
	return p;
}

Pozicija nadiMax(Pozicija p) {
	while (p->right) {
		p = p->right;
	}
	return p;
}

Pozicija nadiMin(Pozicija p) {
	while (p->left) {
		p = p->left;
	}
	return p;
}

Pozicija TraziElement(Pozicija p, int br) {
	//*if (p == NULL) {
		//return p;
	//}
	//else if (p->broj < br) {
		//TraziElement(p->right, br);
	//}
	//else if (p->broj > br) {
		//TraziElement(p->left, br);
	//}
	//else {
		//return p;
	//}
	while (p != NULL && p->broj != br) {
		if (p->broj < br) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}return p;
}
	