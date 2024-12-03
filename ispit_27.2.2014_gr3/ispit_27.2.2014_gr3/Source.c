///* Napisati program koji èita iz datoteka podatke o studentima i ispitima, te kreira dvije vezane liste (zadane dvi razl strukt)
//Potrebno je ispisati koliko je studenata položilo svaki pojedini ispit (po nazivu ispita), te nabrojati koji su
//to studenti.*/
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define EXIT_SUCCESS 0
//#define ERROR -1
//#define MAX 1024
//
//struct student;
//typedef struct student* position;
//typedef struct student {
//	char sifra_studenta[MAX];
//	char ime[MAX];
//	char prezime[MAX];
//	char sifra_ispita[MAX];
//	position next;
//}Student;
//
//struct ispit;
//typedef struct ispit* pos;
//typedef struct ispit { 
//	char sifra_ispita[MAX];
//	char naziv[MAX];
//	pos Next;
//} Ispit;
//
//int readStudents(char*, position);
//position makeNodeS(char*, char*, char*, char*);
//int insertInListS(position, position);
//int printS(position);
//int brisiS(position);
//
//int citajIspite(char*,pos);
//pos makeNodeI(char*, char*);
//int insertInListI(pos, pos);
//int printI(pos);
//int brisiI(pos);
//
//int findStudents(char*,position);
//
//int main() {
//	Student headS = {
//		.ime = {0},
//		.prezime={0},
//		.sifra_ispita={0},
//		.sifra_studenta={0},
//		.next=NULL
//	};
//
//	Ispit headI = {
//		.sifra_ispita = {0},
//		.naziv = {0},
//		.Next = NULL
//	};
//	readStudents("stud.txt", &headS);
//	printS(&headS);
//	citajIspite("ispiti.txt", &headI);
//	printI(&headI);
//
//	char predmet[MAX] = {0};
//	int br = 0;
//	printf("odaberite predmet za koji zelite procitati studente koji su polozili\n(upisati sifru predmeta)\n");
//	scanf("%s", predmet);
//	br=findStudents(predmet, &headS);
//	printf("br studenata koji su polozili taj predmet: %d\n", br);
//
//	brisiS(&headS);
//	brisiI(&headI);
//	return 0;
//}
//
//int findStudents(char* pr, position head) {
//	int brojac = 0;
//	while (head->next != NULL) {
//		if (strcmp(head->next->sifra_ispita, pr) == 0)
//		{
//			brojac++;
//			printf("%s\t%s\t%s\n", head->next->sifra_studenta, head->next->ime, head->next->prezime);
//			head = head->next;
//		}
//		else
//			head = head->next;
//	}
//	return brojac;
//}
//
//int citajIspite(char* filename, pos head) {
//	char sifra[MAX] = { 0 }, naziv[MAX] = { 0 };
//	pos q = NULL;
//	FILE* fp = NULL;
//	fp = fopen(filename, "r");
//	if (fp == NULL) {
//		printf("greska pri otvaranju dat");
//		return ERROR;
//	}
//	while (!feof(fp)) {
//		fscanf(fp, "%s %s", sifra,naziv);
//		q = makeNodeI(sifra, naziv);
//		insertInListI(head, q);
//	}
//
//	fclose(fp);
//	return EXIT_SUCCESS;
//}
//
//pos makeNodeI(char* sifra, char* naziv) {
//	pos new = NULL;
//	new = (pos)malloc(sizeof(Ispit));
//	if (new == NULL) {
//		printf("greska pri alokacij memorije");
//		return NULL;
//	}
//	strcpy(new->sifra_ispita, sifra);
//	strcpy(new->naziv, naziv);
//	new->Next = NULL;
//
//	return new;
//}
//
//int insertInListI(pos head, pos q) {
//	q->Next = head->Next;
//	head->Next = q;
//
//	return EXIT_SUCCESS;
//}
//
//int printI(pos head) {
//	while (head->Next != NULL)
//	{
//		printf("%s\t%s\n", head->Next->naziv, head->Next->sifra_ispita);
//		head = head->Next;
//	}
//	return EXIT_SUCCESS;
//}
//
//int brisiI(pos head) {
//	pos temp = NULL;
//	while (head->Next != NULL) {
//		temp = head->Next;
//		head->Next = temp->Next;
//		free(temp);
//	}
//	return EXIT_SUCCESS;
//}
//
//int readStudents(char* filename, position head) {
//	char s_s[MAX] = { 0 }, s_i[MAX] = { 0 }, ime[MAX] = { 0 }, prezime[MAX] = { 0 };
//	position q = NULL;
//	FILE* fp = NULL;
//	fp = fopen(filename, "r");
//	if (fp == NULL) {
//		printf("greska pri otvaranju dat");
//		return ERROR;
//	}
//	while (!feof(fp)) {
//		fscanf(fp, "%s %s %s %s", s_s,ime,prezime,s_i);
//		q = makeNodeS(s_s, ime, prezime, s_i);
//		//printf("%s\t%s\t%s\t%s\n", q->ime,q->prezime,q->sifra_studenta, q->sifra_ispita);
//		insertInListS(head, q);
//	}
//
//	fclose(fp);
//	return EXIT_SUCCESS;
//}
//
//position makeNodeS(char* s_s, char* ime, char* prezime, char* s_i) {
//	position new = NULL;
//	new = (position)malloc(sizeof(Student));
//	if (new == NULL) {
//		printf("greska pri alokacij memorije");
//		return NULL;
//	}
//	strcpy(new->sifra_studenta,s_s);
//	strcpy(new->sifra_ispita, s_i);
//	strcpy(new->ime, ime);
//	strcpy(new->prezime, prezime);
//	new->next = NULL;
//
//	return new;
//}
//
//int insertInListS(position head, position q) {
//	q->next = head->next;
//	head->next = q;
//
//	return EXIT_SUCCESS;
//}
//
//int printS(position head){
//	while (head->next != NULL) {
//		printf("%s\t%s\t%s\t%s\n", head->next->ime, head->next->prezime, head->next->sifra_studenta, head->next->sifra_ispita);
//		head = head->next;
//	}
//	return EXIT_SUCCESS;
//}
//
//int brisiS(position head) {
//	position temp = NULL;
//	while (head->next != NULL) {
//		temp = head->next;
//		head->next = temp->next;
//		free(temp);
//	}
//	return EXIT_SUCCESS;
//}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 1024

struct student;
typedef struct student* position;
typedef struct student {
    char student_id[MAX];
    char first_name[MAX];
    char last_name[MAX];
    char exam_id[MAX];
    position next;
} Student;

struct exam;
typedef struct exam* pos;
typedef struct exam {
    char exam_id[MAX];
    char name[MAX];
    pos next;
} Exam;

int readStudents(char*, position);
position createStudentNode(char*, char*, char*, char*);
int insertInStudentList(position, position);
int printStudents(position);
int deleteStudents(position);

int readExams(char*, pos);
pos createExamNode(char*, char*);
int insertInExamList(pos, pos);
int printExams(pos);
int deleteExams(pos);

int findStudents(char*, position);

int main() {
    Student headS = {
        .first_name = {0},
        .last_name = {0},
        .exam_id = {0},
        .student_id = {0},
        .next = NULL
    };

    Exam headE = {
        .exam_id = {0},
        .name = {0},
        .next = NULL
    };

    readStudents("students.txt", &headS);
    printStudents(&headS);

    readExams("exams.txt", &headE);
    printExams(&headE);

    char subject[MAX] = { 0 };
    int count = 0;

    printf("Select the subject for which you want to read students who passed\n(enter the subject code)\n");
    scanf("%s", subject);

    count = findStudents(subject, &headS);
    printf("Number of students who passed this subject: %d\n", count);

    deleteStudents(&headS);
    deleteExams(&headE);

    return 0;
}

int findStudents(char* subject_code, position head) {
    int counter = 0;

    while (head->next != NULL) {
        if (strcmp(head->next->exam_id, subject_code) == 0) {
            counter++;
            printf("%s\t%s\t%s\n", head->next->student_id, head->next->first_name, head->next->last_name);
        }
        head = head->next;
    }

    return counter;
}

int readExams(char* filename, pos head) {
    char code[MAX] = { 0 }, name[MAX] = { 0 };
    pos newExamNode = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return ERROR;
    }

    while (!feof(fp)) {
        fscanf(fp, "%s %s", code, name);
        newExamNode = createExamNode(code, name);
        insertInExamList(head, newExamNode);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

pos createExamNode(char* code, char* name) {
    pos newExamNode = (pos)malloc(sizeof(Exam));

    if (newExamNode == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    strcpy(newExamNode->exam_id, code);
    strcpy(newExamNode->name, name);
    newExamNode->next = NULL;

    return newExamNode;
}

int insertInExamList(pos head, pos newExamNode) {
    newExamNode->next = head->next;
    head->next = newExamNode;

    return EXIT_SUCCESS;
}

int printExams(pos head) {
    while (head->next != NULL) {
        printf("%s\t%s\n", head->next->name, head->next->exam_id);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int deleteExams(pos head) {
    pos temp = NULL;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}

int readStudents(char* filename, position head) {
    char student_id[MAX] = { 0 }, exam_id[MAX] = { 0 }, first_name[MAX] = { 0 }, last_name[MAX] = { 0 };
    position newStudentNode = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return ERROR;
    }

    while (!feof(fp)) {
        fscanf(fp, "%s %s %s %s", student_id, first_name, last_name, exam_id);
        newStudentNode = createStudentNode(student_id, first_name, last_name, exam_id);
        insertInStudentList(head, newStudentNode);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

position createStudentNode(char* student_id, char* first_name, char* last_name, char* exam_id) {
    position newStudentNode = (position)malloc(sizeof(Student));

    if (newStudentNode == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    strcpy(newStudentNode->student_id, student_id);
    strcpy(newStudentNode->exam_id, exam_id);
    strcpy(newStudentNode->first_name, first_name);
    strcpy(newStudentNode->last_name, last_name);
    newStudentNode->next = NULL;

    return newStudentNode;
}

int insertInStudentList(position head, position newStudentNode) {
    newStudentNode->next = head->next;
    head->next = newStudentNode;

    return EXIT_SUCCESS;
}

int printStudents(position head) {
    while (head->next != NULL) {
        printf("%s\t%s\t%s\t%s\n", head->next->first_name, head->next->last_name,
            head->next->student_id, head->next->exam_id);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int deleteStudents(position head) {
    position temp = NULL;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}