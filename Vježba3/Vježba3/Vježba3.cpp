#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _person* position;
typedef struct _person {
	char name[30];
	char sname[30];
	int date;
	position next;
} Per;

int insertAfter(position P, position newP) {
	newP->next = P->next;
	P->next = newP;
	return 0;
}

position createPerson(char* Name, char* Sname, int Date) {
	position newPerson = (position)malloc(sizeof(Per));
	if (newPerson == NULL) {
		return NULL;
	}
	newPerson->date = Date;
	strcpy(newPerson->name, Name);
	strcpy(newPerson->sname, Sname);
	newPerson->next = NULL;
	return newPerson;
}

int insertBegin(char* Name, char* Sname, int Date, position P) {
	position newPerson = createPerson(Name, Sname, Date);
	if (newPerson == NULL) {
		return -1;
	}
	insertAfter(P, newPerson);
	return 0;
}

int insertEnd(char* Name, char* Sname, int Date, position P) {
	position newPerson = createPerson(Name, Sname, Date);
	if (newPerson == NULL) {
		return -1;
	}
	while (P->next != NULL) {
		P = P->next;
	}
	insertAfter(P, newPerson);
	return 0;
}

position findLastN(char* LastN, position P) {
	position q = NULL;
	for (q = P->next; q != NULL; q = q->next) {
		if (strcmp(q->sname, LastN) == 0) {
			return q;
		}
	}
	return NULL;
}

int deletePerson(char* LastN, position P) {
	position prev = P;
	position curr = prev->next;

	while (curr != NULL && strcmp(curr->sname, LastN) != 0) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		return -1;
	}

	prev->next = curr->next;
	free(curr);
	return 0;
}

int addAfter(char* Name, char* Sname,int Date, position P,char *Lname) {
	position oldper = findLastN(Lname,P);
	

	if (oldper == NULL) {

		return -1;
	}
	position newPer = createPerson(Name, Sname, Date);
	if (newPer == NULL) {

		return -1;
	}

	insertAfter(P,newPer);


	return 0;
}

int  addBefore(char* Name, char* Sname, int Date, position P, char* Lname) {
	position prev = P;
	position curr = P->next;
	position oldP = findLastN(Lname, P);
	if (oldP == NULL) {
		return -1;

	}

	position NP = createPerson(Name, Sname, Date);
	if (NP == NULL) {
		return -1;
	}

	while (curr != NULL && strcmp(curr->sname, Lname) != 0) {

		prev = curr;
		curr = curr->next;

	}

	NP->next = curr;
	prev->next = NP;

	return 0;

}

int writeList(position P) {

	position q;
	FILE* dat = fopen("lista.txt", "w");

	if (!dat) {
		return -1;
}
	for (q = P->next; q != NULL; q = q->next) {

		fprintf(dat,"%s %s %d\n", q->name, q->sname, q->date);
	}
	fclose(dat);
	return 0;
}

int sortList(position P) {
	int n = 0, i;
	position prev, a, b, q;

	for (q = P->next; q != NULL; q = q->next) {
		n++;
	}
	if (n < 2) {
		return 0;

	}

	for (i = 0; i < n - 1; i++) {
		prev = P;
		while (prev->next != NULL && prev->next->next != NULL) {

			a = prev->next;
			b = a->next;
			if (strcmp(a->sname, b->sname) > 0) {
				a->next = b->next;
				b->next = a;
				prev->next = b;
				prev = b;
			}
			else {
				prev = a;
			}
		}
	}

	return 0;
		

}

int readList(position P) {
	int date;
	char name[30], sname[30];
	FILE* dat = fopen("lista.txt", "r");
	if (!dat) {
		return -1;
	}

	while (fscanf(dat, "%s %s %d", name, sname, &date) == 3) {
		insertEnd(name, sname, date,P);
	}
	
	fclose(dat);
	return 0;
}

int main() {
	Per Head = { "", "", 0, NULL };
	position p = &Head;

	for (position q = p->next; q != NULL; q = q->next) {
		printf("%s %s %d\n", q->name, q->sname, q->date);
	}

	return 0;
}