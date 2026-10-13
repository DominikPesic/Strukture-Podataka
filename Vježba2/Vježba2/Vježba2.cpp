#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct _person* position;
typedef struct _person {
	char name[30];
	char sname[30];
	int date;
	position next;

}Per;


int insertBegin(char *Name, char *Sname, int Date,position P) {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Per));
	newPerson->date = Date;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->next = NULL;

	insertAfter(P, newPerson);

}

int insertAfter(position P,position newP) {
	newP->next = P->next;
	P->next = newP;


}

int insertEnd(char* Name, char* Sname, int Date, position P) {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Per));
	newPerson->date = Date;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->next = NULL;

	insertAfter(P, newPerson);


	while (p->next != NULL) {
		p = p->next;
		insertAfter(p, newPerson);
	}


}

int findLastN(char* LastN, position P) {
	position q = NULL;
	for (q = p->next; q != NULL; q = q->next) {
		if (strcmp(q->LastN, LastN) == 0) {

			return 1;
		}
	}
	
}

int deletePerson(char* LastN, position P) {

	position curr=NULL;
	position prev=P;
	curr = prev->next;

	if (strcmp(curr->LastN,LastN) == 0) {
		prev->next = curr->next;
		free(curr);
	}
	else {
		prev = prev->next;
		curr = prev->next;
	}


}
int main() {
	Per Head = { Per.name = {0}, Per.sname = {0},Per.date = 0, Per.next = NULL };

	position p = &Head;

	for (position q = p; q->next != NULL; q = q->next) {

		printf("%c", q->name);
		printf("%c", q->sname);
		printf("%d", q->date);
		printf("\n");
		
	}

	return 0;
}