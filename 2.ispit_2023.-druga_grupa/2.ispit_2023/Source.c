/* Nap program koji cita datoteku koja sadrzi podatke o kategorijama proizvoda("kategorije.txt") te kreirat vezanu listu kategorija sortiranu po abecedi.
Nakon toga iz dat "proizvodi.txt" prociat proizvode i smjestit ih u dodatnu vezanu listu za pojedinu kategoriju.
za 2: ispisat konacnu listu tkd prvo ide nazv kategorije pa nazivi i cijene proizvoda u toj kategoriji. */
							
																	// RADI
				
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 32

struct proizvod;
typedef struct proizvod* proizvodP;
typedef struct proizvod {
	char porizvodIme[MAX];
	int cijena;
	proizvodP next;
}Proizvod;

struct kategorija;
typedef struct kategorija* kategorijaK;
typedef struct kategorija {
	char imeKatgorije[MAX];
	int minCijena;
	int maxCijena;
	float avgCijena;
	kategorijaK next;
	proizvodP child;
}Kategorija;

int citajKat(kategorijaK, char*);
int unosiSortiranoKat(kategorijaK, kategorijaK);
int ispisi(kategorijaK);
int citajProizvode(kategorijaK, char*);
int Random(int min, int max);
int unesiProizvode(kategorijaK, char*, char*);
proizvodP napraviProizvod(kategorijaK, char*);
int ispisiDjecu(proizvodP);
int brisiSve(kategorijaK);
int brisiProizvod(proizvodP);

int main() {
	srand(time(0));
	Kategorija head;
	head.next = NULL;


	citajKat(&head, "kategorije.txt");
	//ispisi(&head);
	citajProizvode(&head, "proizvodi.txt");
	ispisi(&head);

	brisiSve(&head);
	ispisi(&head);

	return 0;
}

int citajKat(kategorijaK head, char* filename) {
	float avg = 0.0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		kategorijaK q = NULL;
		q = (kategorijaK)malloc(sizeof(Kategorija));
		if (q == NULL) {
			printf("greska pri alokaciji memorije");
			return ERROR;
		}
		fscanf(fp, "%s %d %d", q->imeKatgorije, &q->minCijena, &q->maxCijena);
		avg = (float)(q->minCijena + q->maxCijena) / 2;
		q->avgCijena = avg;
		q->next = NULL;
		q->child = NULL;

		unosiSortiranoKat(head, q);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int unosiSortiranoKat(kategorijaK p, kategorijaK q) {
	while (p->next != NULL && strcmp(p->next->imeKatgorije, q->imeKatgorije) < 0)
		p = p->next;
	q->next = p->next;
	p->next = q;
	return EXIT_SUCCESS;
}

int ispisi(kategorijaK head) {
	if (head->next == NULL) {
		printf("lista je prazna\n");
		return EXIT_SUCCESS;
	}
	while (head->next != NULL) {
		printf("%s:\t", head->next->imeKatgorije);
		printf("\n");
		ispisiDjecu(head->next->child);
		head = head->next;
	}
	return EXIT_SUCCESS;
}

int citajProizvode(kategorijaK headk, char* filename) {
	char ime_kat[MAX] = { 0 }, ime_proiz[MAX] = { 0 };
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("greska pri otvaranju dat");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s", ime_proiz, ime_kat);
		unesiProizvode(headk, ime_proiz, ime_kat);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int unesiProizvode(kategorijaK headk, char* ime_proizvoda, char* ime_kat) {
	while (headk->next != NULL)
	{
		if (strcmp(headk->next->imeKatgorije, ime_kat) == 0)
		{
			proizvodP q = NULL;
			q = napraviProizvod(headk->next, ime_proizvoda);

			q->next = headk->next->child;											// ide head->next->child a ne head->next->child->next jer 																	
			headk->next->child= q;													// nema "head-a" tjst odma se u prvi element upisuju podatci
		}
		headk = headk->next;
	}
	return EXIT_SUCCESS;
}

int Random(int min, int max) {
	int rez = 0;
	rez = (rand() % (max - min + 1) + min);
	return rez;
}

proizvodP napraviProizvod(kategorijaK headk, char* ime_proiz) {
	proizvodP new = NULL;
	new = (proizvodP)malloc(sizeof(Proizvod));
	if (new == NULL) {
		printf("greska pri alokaciji memorije za novi proizvod");
		return NULL;
	}
	strcpy(new->porizvodIme, ime_proiz);
	new->cijena = Random(headk->minCijena, headk->maxCijena);
	new->next = NULL;
	return new;
}

int ispisiDjecu(proizvodP p) {
	if (p == NULL)
		printf("nema proizvoda u ovoj kategoriji\n");
	while (p != NULL) {
		printf("\t%s\t%d\n", p->porizvodIme, p->cijena);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int brisiProizvod(proizvodP p) {
	proizvodP temp = NULL;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	p = p->next;
	return EXIT_SUCCESS;
}

int brisiSve(kategorijaK head) {
	kategorijaK temp = NULL;
	while (head->next != NULL) {
		brisiProizvod(head->next->child);
		temp = head->next;
		head->next = temp->next;
		free(temp);

	}
	//head = head->next;
	return EXIT_SUCCESS;
}