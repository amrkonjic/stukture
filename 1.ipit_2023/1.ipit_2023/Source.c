/* Nap program koji iz datoteka "subject1.txt", "subect2.txt" i "subject3.txt" cita studente i ocjene koje su ostvarili iz odredenog kolegija te
* gradi tri vezane liste. Nakon toga te tri vezane liste spojiti u jednu tako da se isti student ne pojavljuje vise puta nego mu se samo upise ocj.
* Ispisat listu u formatu: ime-prezme-ocj1-ocj2-ocj3. ( Ako neki kolegij nije polozen upisat ocjenu 1)
*/
																														// radi
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256
#define MAX_NAME 50
#define EXIT_SUCCESS 0
#define ERROR -1

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char firstname[MAX_NAME];
	char lastname[MAX_NAME];
	int subject1;
	int subject2;
	int subject3;
	StudentP Next;
}Student;


int loadFile1(char*, StudentP);
int loadFile2(char*, StudentP);
int loadFile3(char*, StudentP);
int makeList_subject(StudentP, StudentP);
int printList_students(StudentP);
StudentP napraviCvor1(char*, char*, int);
StudentP napraviCvor2(char*, char*, int);
StudentP napraviCvor3(char*, char*, int);
int unosIstih1_2(StudentP, StudentP);
int unosIstih1_3(StudentP, StudentP);
int unosIstih2_3(StudentP, StudentP);
int novaLista(StudentP, StudentP, StudentP);
int brisiSve(StudentP);


int main() {
	
	Student head1 = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.Next = NULL
	};
	Student head2 = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.Next = NULL
	};
	Student head3 = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.Next = NULL
	};

	loadFile1("Subject1.txt", &head1);
	printList_students(&head1);
	printf("\n________________________");
	loadFile2("Subject1.txt", &head2);
	printList_students(&head2);
	printf("\n________________________");
	loadFile3("Subject1.txt", &head3);
	printList_students(&head3);
	printf("\n________________________\n");
	
	
	novaLista(&head1, &head2, &head3);
	printList_students(&head1);

	brisiSve(&head1);
	printList_students(&head1);

	return 0;
}


int loadFile1(char* filename, StudentP head) {
	StudentP q = NULL;
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 };
	int ocj1 = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju datoteke\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", prezime, ime, &ocj1);
		q = napraviCvor1(ime, prezime, ocj1);
		makeList_subject(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int loadFile2(char* filename, StudentP head) {
	StudentP q = NULL;
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 };
	int ocj2 = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju datoteke\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", prezime, ime, &ocj2);
		q = napraviCvor2(ime, prezime, ocj2);
		makeList_subject(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int loadFile3(char* filename, StudentP head) {
	StudentP q = NULL;
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 };
	int ocj3 = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju datoteke\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", prezime, ime, &ocj3);
		q = napraviCvor3(ime, prezime, ocj3);
		makeList_subject(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

StudentP napraviCvor1(char* ime, char* prezime, int ocj1) {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject1 = ocj1;
	new->subject2 = 1;
	new->subject3 = 1;
	new->Next = NULL;

	return new;
}

StudentP napraviCvor2(char* ime, char* prezime, int ocj2) {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject2 = ocj2;
	new->subject1 = 1;
	new->subject3 = 1;
	new->Next = NULL;

	return new;
}

StudentP napraviCvor3(char* ime, char* prezime, int ocj3) {
	StudentP new = NULL;
	new = (StudentP)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject3 = ocj3;
	new->subject2 = 1;
	new->subject1 = 1;
	new->Next = NULL;

	return new;
}

int makeList_subject(StudentP head, StudentP q) {
	
	q->Next = head->Next;
	head->Next = q;
	
	return EXIT_SUCCESS;
}

int unosIstih1_2(StudentP head1, StudentP head2) {					//listu jedan smo uzeli kao "novu"
	StudentP temp = NULL, p2=NULL;
	p2 = head2;
	while (head1->Next != NULL) {									// prolazimo kroz listu 1
		head2=p2;
		while (head2->Next != NULL) {								//ako meðu elementima liste2 postoji student koji je takoðer i el liste1
			if (strcmp(head1->Next->lastname, head2->Next->lastname) == 0)							
			{
				head1->Next->subject2 = head2->Next->subject2;							// onda ocjenu iz predmeta2 liste2 upisemo tom istom studentu
				temp = head2->Next;														// u predmet2 liste1 te zatim tog studenta brisemo iz liste2
				head2->Next = temp->Next;
				free(temp);
			}
			else
				head2 = head2->Next;													
		}
		head1 = head1->Next;
	}
	return EXIT_SUCCESS;
}

int unosIstih1_3(StudentP head1, StudentP head3) {								// na istom principu kao i  unosIstih1_2
	StudentP temp = NULL, p3 = NULL;
	p3 = head3;								// BITNO!!! TREBA ZAPAMTIT ADRESU DRUGE LISTE (tj liste3) JER CE SE PO NJOJ VRTIT VISE PUTA(za svaki el prve liste)
	while (head1->Next != NULL) {
		head3 = p3;							// svaki put ponovo vratit head3 na pocetnu poziciju(inace bi ostao na kraju)
		while (head3->Next != NULL) {
			if (strcmp(head1->Next->lastname, head3->Next->lastname) == 0)
			{
				head1->Next->subject3 = head3->Next->subject3;
				temp = head3->Next;
				head3->Next = temp->Next;
				free(temp);
			}
			else
				head3 = head3->Next;
		}
		head1 = head1->Next;
	}
	return EXIT_SUCCESS;
}

int unosIstih2_3(StudentP head2, StudentP head3) {
	StudentP temp = NULL, p3 = NULL;
	p3 = head3;
	while (head2->Next != NULL) {
		head3 = p3;
		while (head3->Next != NULL) {
			if (strcmp(head2->Next->lastname, head3->Next->lastname) == 0)
			{
				head2->Next->subject3 = head3->Next->subject3;
				temp = head3->Next;
				head3->Next = temp->Next;
				free(temp);
			}
			else
				head3 = head3->Next;
		}
		head2 = head2->Next;
	}
	return EXIT_SUCCESS;
}

int novaLista(StudentP p1, StudentP p2, StudentP p3) {
	unosIstih1_2(p1, p2);							
	unosIstih2_3(p2, p3);
	unosIstih1_3(p1, p3);
							// nakon sto smo upisali sve koji su se bar dvaput pojavljivali u bilo kojoj od tri liste,izbrisali smo ih iz
							// maticne liste sto znaci da su u listama 2 i 3 ostali samo el koji se ne ponavljaju tj studenti koji su polozili samo predmet2(3)
							// pa je potrebno samo preostale el listi2(3) dodat u listu1
	while (p1->Next != NULL)
		p1 = p1->Next;							// pronalazimo kraj prve liste (tj. nove liste)
	p1->Next = p2->Next;						// spajamo pocetak druge na kraj prve
	
	while (p2->Next != NULL)
		p2 = p2->Next;
	p2->Next = p3->Next;						// spajamo pocetak trece na kraj druge
	
	return EXIT_SUCCESS;
}

int printList_students(StudentP head) {
	StudentP p = head->Next;
	if (p == NULL)
		printf("lista je prazna\n");
	while (p != NULL)
	{
		printf("%s %s\n%d\t%d\t%d\n", p->firstname, p->lastname, p->subject1, p->subject2, p->subject3);
		p = p->Next;
	}
	return EXIT_SUCCESS;
}

int brisiSve(StudentP head) {
	StudentP temp = NULL;
	while (head->Next != NULL) {
		temp = head->Next;
		head->Next = temp->Next;
		free(temp);

		head = head->Next;
	}
	return EXIT_SUCCESS;
}