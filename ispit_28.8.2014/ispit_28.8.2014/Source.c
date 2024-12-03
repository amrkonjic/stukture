/* Napisati program koji za tri razlièita predmeta èita ime i prezime studenta te njegovu ocjenu. Podaci o
svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i
ispisati je.
a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri
predmeta.
b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena
studenata, sadrži i njihovu prosjeènu ocjenu iz ta tri predmeta. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 256
#define MAX_NAME 50
#define EXIT_SUCCESS 0
#define ERROR -1

struct student;
typedef struct student* studentP;
typedef struct student {
	char firstname[MAX_NAME];
	char lastname[MAX_NAME];
	int subject1;
	int subject2;
	int subject3;
	studentP next;
}Student;

struct studentTrazeni;
typedef struct studentTrazeni* studentT;
typedef struct studentTrazeni {
	char firstname[MAX_NAME];
	char lastname[MAX_NAME];
	int subject1;
	int subject2;
	int subject3;
	float avg;
	studentT next;
}StudentTrazeni;

int loadFile1(char*, studentP);
int loadFile2(char*, studentP);
int loadFile3(char*, studentP);
studentP napraviCvor1(char*, char*, int);
studentP napraviCvor2(char*, char*, int);
studentP napraviCvor3(char*, char*, int);
int makeList_subject(studentP, studentP);
int printList_students(studentP);
int brisiSve(studentP);

int findStudent(studentT, studentP, studentP, studentP);
studentT napraviCvor(char*, char*, int, int, int,float);
int makeList_subjectT(studentT, studentT);
float racunajProsjecnu(int, int, int);
int printList_studentsT(studentT);
int brisiSveT(studentT);

int main() {
	Student head1 = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.next = NULL
	};
	Student head2 = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.next = NULL
	};
	Student head3 = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.next = NULL
	};

	StudentTrazeni head = {
	.firstname = {0},
	.lastname = {0},
	.subject1 = 1,
	.subject2 = 1,
	.subject3 = 1,
	.avg=0.0,
	.next = NULL
	};

	loadFile1("sub1.txt", &head1);
	printList_students(&head1);
	printf("\n__________\n\n");
	loadFile2("sub2.txt", &head2);
	printList_students(&head2);
	printf("\n__________\n\n");
	loadFile3("sub3.txt", &head3);
	printList_students(&head3);
	printf("\n__________\n");

	findStudent(&head, &head1, &head2, &head3);
	printf("\nstudenti koji su polozili sva tri predmeta:\n");
	printList_studentsT(&head);

	brisiSve(&head1);
	brisiSve(&head2);
	brisiSve(&head3);
	brisiSveT(&head);

	return 0;
}

float racunajProsjecnu(int ocj1, int ocj2, int ocj3) {
	float rez = 0.0;
	rez = (float)(ocj1 + ocj2 + ocj3) / 3;
	return rez;
}

int findStudent(studentP p,studentP p1, studentP p2, studentP p3) {
	float avg_grade = 0.0;
	studentP q = NULL,head2=NULL,head3=NULL;
	head2 = p2;
	head3 = p3;
	while (p1->next != NULL) {
		p2 = head2;
		while (p2->next != NULL) {
			if (strcmp(p1->next->lastname, p2->next->lastname) == 0) {
				p3 = head3;
				while (p3->next != NULL) {
					if (strcmp(p2->next->lastname, p3->next->lastname) == 0) {
						avg_grade = racunajProsjecnu(p1->next->subject1, p2->next->subject2, p3->next->subject3);
						q = napraviCvor(p3->next->firstname, p3->next->lastname, p1->next->subject1, p2->next->subject2, p3->next->subject3,avg_grade);
						makeList_subjectT(p, q);
						p3 = p3->next;
					}
					else
						p3 = p3->next;
				}
				p2 = p2->next;
			}
			else
				p2 = p2->next;
		}
		p1 = p1->next;
	}

	return EXIT_SUCCESS;
}

int loadFile1(char* filename, studentP head) {
	studentP q = NULL;
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 };
	int ocj = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju datoteke\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", ime, prezime, &ocj);
		q = napraviCvor1(ime, prezime, ocj);
		makeList_subject(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int loadFile2(char* filename, studentP head) {
	studentP q = NULL;
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 };
	int ocj = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju datoteke\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", ime, prezime, &ocj);
		q = napraviCvor2(ime, prezime, ocj);
		makeList_subject(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int loadFile3(char* filename, studentP head) {
	studentP q = NULL;
	char ime[MAX_NAME] = { 0 }, prezime[MAX_NAME] = { 0 };
	int ocj = 0;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("greska pri otvaranju datoteke\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", ime, prezime, &ocj);
		q = napraviCvor3(ime, prezime, ocj);
		makeList_subject(head, q);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

studentP napraviCvor1(char* ime, char* prezime, int ocj1) {
	studentP new = NULL;
	new = (studentP)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject1 = ocj1;
	new->subject2 = 1;
	new->subject3 = 1;
	new->next = NULL;

	return new;
}

studentP napraviCvor2(char* ime, char* prezime, int ocj2) {
	studentP new = NULL;
	new = (studentP)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject1 = 1;
	new->subject2 = ocj2;
	new->subject3 = 1;
	new->next = NULL;

	return new;
}

studentP napraviCvor3(char* ime, char* prezime, int ocj3) {
	studentP new = NULL;
	new = (studentP)malloc(sizeof(Student));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject1 = 1;
	new->subject2 = 1;
	new->subject3 = ocj3;
	new->next = NULL;

	return new;
}

int makeList_subject(studentP head, studentP q) {

	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}

int makeList_subjectT(studentT head, studentT q) {
	q->next = head->next;
	head->next = q;

	return EXIT_SUCCESS;
}

int printList_students(studentP head) {
	studentP p = head->next;
	if (p == NULL)
		printf("lista je prazna\n");
	while (p != NULL)
	{
		printf("%s %s\n%d\t%d\t%d\n", p->firstname, p->lastname, p->subject1, p->subject2, p->subject3);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int printList_studentsT(studentT head) {
	studentT p = head->next;
	if (p == NULL)
		printf("lista je prazna\n");
	while (p != NULL)
	{
		printf("%s %s\n%d\t%d\t%d\t%f\n", p->firstname, p->lastname, p->subject1, p->subject2, p->subject3,p->avg);
		p = p->next;
	}
	return EXIT_SUCCESS;
}

studentT napraviCvor(char* ime, char* prezime, int ocj1, int ocj2, int ocj3,float avg) {
	studentT new = NULL;
	new = (studentT)malloc(sizeof(StudentTrazeni));
	if (new == NULL) {
		printf("greska pri alokaciji memorije");
		return NULL;
	}
	strcpy(new->firstname, ime);
	strcpy(new->lastname, prezime);
	new->subject1 = ocj1;
	new->subject2 = ocj2;
	new->subject3 = ocj3;
	new->avg = avg;
	new->next = NULL;

	return new;
}

int brisiSve(studentP head) {
	studentP temp = NULL;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int brisiSveT(studentT head) {
	studentT temp = NULL;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}