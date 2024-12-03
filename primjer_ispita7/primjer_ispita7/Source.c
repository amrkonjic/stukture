/*Napisati program koji generira sluèajne brojeve u opsegu od 50-80. Ukoliko je generirani broj paran
sprema se u vezanu listu parnih brojeva i to u padajuæem redoslijedu (od najveæeg prema najmanjem).
Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, takoðer u padajuæem redoslijedu. Niti
jedna vezana lista ne smije sadržavati dva ista elementa. Unos traje sve dok obje liste ne sadrže 10
elemenata. Treba ispisivati koji se broj generira i na kraju ispisati obje liste.*/

										// NE ISPISUJE NISTA NARAVNO

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX_LINE 1024

struct lista;
typedef struct lista* position;
typedef struct lista {
	int broj;
	position next;
}Lista;

int generateRandNum(int,int);
position makeNode(int);
int insertInList(position,position,int);
int printList(position);

int main() {
	Lista headP = {
	.broj = 0,
	.next = NULL
	};
	Lista headN = {
	.broj = 0,
	.next = NULL
	};
	srand(time(0));
	int i = 0;
	int brojac1=0, brojac2 = 0;
	while (brojac1 <= 10 && brojac2 <= 10) {
		i = generateRandNum(50, 80);
		position q = NULL;
		q = makeNode(i);
		if (q == NULL)
			printf("greska pri stvaranju novog elementa liste");
		else if (i % 2 == 0 && brojac1 < 10) {
			brojac1 = insertInList(&headP, q, brojac1);
			brojac1++;
		}
		else if (i % 2 != 0 && brojac2 < 10) {
			brojac2 = insertInList(&headN, q, brojac2);
			brojac2++;
		}
		else
			free(q);
	}

	printList(&headP);
	printList(&headN);
	


	return 0;
}

int generateRandNum(int min,int max) {
	
	int br = 0;
	br = (rand() % (max - min + 1)) + min;
	return br;
}

position makeNode(int br) {
	position new = NULL;
	new = (position)malloc(sizeof(Lista));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	new->broj = br;
	new->next = NULL;
	return new;
}

int insertInList(position head, position q,int brojac) {
	
	while (head->next != NULL && head->next->broj > q->broj) {
		head = head->next;
	}

		q->next = head->next;
		head->next = q;
		brojac++;
	
	return brojac;
}

int printList(position head) {
	while (head->next != NULL)
	{
		printf("%d\n", head->next->broj);
		head = head->next;
	}
	return EXIT_SUCCESS;
}