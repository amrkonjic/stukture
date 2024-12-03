///*Napisat program koji iz dat cita kategoriju,naziv i kolicinu artikala u skladistu.
//Izgradit vezanu listu u kojoj su el slozeni po kategorijama a onda iz druge dat koja prestavlja racun cita podatke i umanjuje stanje na skladistu.
//Ispisat kategoriju a zatim nazive artikala cija je kolicina pala ispod 5.*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define EXIT_SUCCESS 0
//#define ERROR -1
//#define MAX_NAME 50
//#define MAX_FILENAME 256
//
//struct artikl;
//typedef struct artikl* position;
//typedef struct artikl {
//	char kategorija[MAX_NAME];
//	char naziv[MAX_NAME];
//	int kolicina;
//	position next;
//}Artikl;
//
//
//int citaj_dat_skladiste(position, char*);
//int sortirani_unos(position, position);
//int print_list(position);
//int citaj_dat_racun(position, char*);
//int article_compare(position, position);
//
//int main()
//{
//	char filename[MAX_FILENAME] = { 0 };
//	char filename_r[MAX_FILENAME] = { 0 };
//	Artikl headA = {
//		.kategorija = {0},
//		.naziv = {0},
//		.kolicina = 0,
//		.next = NULL
//	};
//	Artikl headR = {
//		.kategorija = {0},
//		.naziv = {0},
//		.kolicina = 0,
//		.next = NULL
//	};
//	printf("unesite ime dat iz koje se cita stanje u skladistu\n");
//	scanf("%s", filename);
//	citaj_dat_skladiste(&headA, filename);
//	print_list(&headA);
//
//	printf("unesite ime dat u kojoj se nalazi racun\n");
//	scanf("%s", filename_r);
//	citaj_dat_racun(&headR, filename_r);
//	article_compare(&headA,&headR);
//
//	
//
//	return 0;
//}
//int citaj_dat_skladiste(position head, char* filename)
//{
//	char kategorija[MAX_NAME] = { 0 }, naziv[MAX_NAME] = { 0 };
//	int kolicina = 0;
//	FILE* fp = NULL;
//	fp = fopen(filename, "r");
//	if (fp == NULL)
//	{
//		perror("greska pri otvaranju dat: ");
//		return ERROR;
//	}
//	while (!feof(fp))
//	{
//		fscanf(fp, "%s %s %d", kategorija,naziv,&kolicina);
//		position q = NULL;
//		q = (position)malloc(sizeof(Artikl));
//		if (q == NULL)
//		{
//			printf("greska  pri alokaciji mem\n");
//			return ERROR;
//		}
//		strcpy(q->kategorija,kategorija);
//		strcpy(q->naziv,naziv);
//		q->kolicina = kolicina;
//
//		sortirani_unos(head, q);
//	}
//	fclose(fp);
//	return EXIT_SUCCESS;
//}
//int sortirani_unos(position p, position q) {
//	while (p->next != NULL && strcmp(p->next->kategorija, q->kategorija) < 0)
//		p = p->next;
//	q->next = p->next;
//	p->next = q;
//	return EXIT_SUCCESS;
//
//}
//
//int print_list(position head)
//{
//	if (head == NULL)
//	{
//		printf("lista je praza");
//		return ERROR;
//	}
//	position p = head->next;
//	while (p != NULL)
//	{
//		printf("%s %s %d\n", p->kategorija, p->naziv, p->kolicina);
//		p = p->next;
//	}
//	return EXIT_SUCCESS;
//}
//
//int citaj_dat_racun(position headR, char* filename)
//{
//	char kategorija[MAX_NAME] = { 0 }, naziv[MAX_NAME] = { 0 };
//	int kolicina = 0;
//	FILE* fp = NULL;
//	fp = fopen(filename, "r");
//	if (fp == NULL)
//	{
//		perror("greska pri otvaranju dat: ");
//		return ERROR;
//	}
//	while (!feof(fp))
//	{
//		fscanf(fp, "%s %s %d", kategorija, naziv, &kolicina);
//		position q = NULL;
//		q = (position)malloc(sizeof(Artikl));
//		if (q == NULL)
//		{
//			printf("greska  pri alokaciji mem\n");
//			return ERROR;
//		}
//		strcpy(q->kategorija, kategorija);
//		strcpy(q->naziv, naziv);
//		q->kolicina = kolicina;
//
//		sortirani_unos(headR, q);
//	}
//	fclose(fp);
//	return EXIT_SUCCESS;
//}
//
//int article_compare(position p, position q) {
//	
//	while (q->next != NULL)
//	{
//		
//		if (strcmp(p->next->naziv, q->next->naziv) == 0)
//		{
//			p->next->kolicina = p->next->kolicina - q->next->kolicina;
//			if (p->next->kolicina < 5)
//			{
//				printf("%s %s\n", p->next->kategorija, p->next->naziv);
//			}
//		}
//		
//		p = p->next;
//	}
//	return EXIT_SUCCESS;
//}

/*Napisat program koji iz dat cita kategoriju,naziv i kolicinu artikala u skladistu.
Izgradit vezanu listu u kojoj su el slozeni po kategorijama a onda iz druge dat koja prestavlja racun cita podatke i umanjuje stanje na skladistu.
Ispisat kategoriju a zatim nazive artikala cija je kolicina pala ispod 5.*/
																					// NE RADI

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX_NAME 50
#define MAX_FILENAME 256

struct artikl;
typedef struct artikl* position;
typedef struct artikl {
	char kategorija[MAX_NAME];
	char naziv[MAX_NAME];
	int kolicina;
	position next;
}Artikl;


int citaj_dat_skladiste(position, char*);
int sortirani_unos(position, position);
int print_list(position);
int citaj_dat_racun(position, char*);
int article_compare(position, position);
int brisiListu(position);

int main()
{
	char filename[MAX_FILENAME] = { 0 };
	Artikl headA = {
		.kategorija = {0},
		.naziv = {0},
		.kolicina = 0,
		.next = NULL
	};
	Artikl headR = {
		.kategorija = {0},
		.naziv = {0},
		.kolicina = 0,
		.next = NULL
	};
	printf("unesite ime dat iz koje se cita stanje u skladistu\n");
	scanf("%s", filename);
	citaj_dat_skladiste(&headA, filename);
	print_list(&headA);

	printf("unesite ime dat u kojoj se nalazi racun\n");
	scanf("%s", filename);
	citaj_dat_racun(&headR, filename);
	article_compare(&headA, &headR);

	print_list(&headA);
	brisiListu(&headA);
	brisiListu(&headR);

	return 0;
}

int brisiListu(position head)
{
	position temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int citaj_dat_skladiste(position head, char* filename)
{
	char kategorija[MAX_NAME] = { 0 }, naziv[MAX_NAME] = { 0 };
	int kolicina = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("greska pri otvaranju dat: ");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", kategorija, naziv, &kolicina);
		position q = NULL;
		q = (position)malloc(sizeof(Artikl));
		if (q == NULL)
		{
			printf("greska  pri alokaciji mem\n");
			return ERROR;
		}
		strcpy(q->kategorija, kategorija);
		strcpy(q->naziv, naziv);
		q->kolicina = kolicina;

		sortirani_unos(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
int sortirani_unos(position p, position q) {
	while (p->next != NULL && strcmp(p->next->kategorija, q->kategorija) < 0)
		p = p->next;
	q->next = p->next;
	p->next = q;
	return EXIT_SUCCESS;

}

int print_list(position head)
{
	if (head == NULL)
	{
		printf("lista je praza");
		return ERROR;
	}
	position p = head->next;
	while (p != NULL)
	{
		printf("%s %s %d\n", p->kategorija, p->naziv, p->kolicina);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int citaj_dat_racun(position headR, char* filename)
{
	char kategorija[MAX_NAME] = { 0 }, naziv[MAX_NAME] = { 0 };
	int kolicina = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("greska pri otvaranju dat: ");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", kategorija, naziv, &kolicina);
		position q = NULL;
		q = (position)malloc(sizeof(Artikl));
		if (q == NULL)
		{
			printf("greska  pri alokaciji mem\n");
			return ERROR;
		}
		strcpy(q->kategorija, kategorija);
		strcpy(q->naziv, naziv);
		q->kolicina = kolicina;

		sortirani_unos(headR, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int article_compare(position p, position q) {

	while (q->next != NULL)
	{

		if (strcmp(p->next->naziv, q->next->naziv) == 0)
		{
			p->next->kolicina = p->next->kolicina - q->next->kolicina;
			if (p->next->kolicina < 5)
			{
				printf("%s %s\n", p->next->kategorija, p->next->naziv);
			}
		}

		p = p->next;
	}
	return EXIT_SUCCESS;
}