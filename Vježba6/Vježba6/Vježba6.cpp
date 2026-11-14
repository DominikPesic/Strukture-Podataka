#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct Artikli {
	int kolicina;
	double cijena;
	char imeArtikla[50];
	struct Artikli* next;

}Artikli;

typedef struct Racuni {
	char datum[11];
	Artikli* prvi;
	struct Racuni* next;
}Racuni;


int sortiranUnos(Racuni** glava, Racuni* novi) {
	if (!novi) {
		return -1;
	}
	if (*glava == NULL || strcmp(novi->datum, (*glava)->datum) < 0) {
		novi->next = *glava;
		*glava = novi;
		return 0;
	}


	Racuni* trenutni = *glava;
	while (trenutni->next != NULL && strcmp(trenutni->next->datum, novi->datum) < 0 ) {
		trenutni = trenutni->next;
		}
	novi->next = trenutni->next;
	trenutni->next = novi;
	return 0;
}


Racuni* racun(char* ndat) {
	FILE* fp = fopen(ndat, "r");
	if (!fp) {
		return NULL;
	}

	Racuni* novi = (Racuni*)malloc(sizeof(Racuni));
	if (!novi) {
		fclose(fp);
		return NULL;
	}

	novi->next = NULL;
	novi->prvi = NULL;
	fscanf(fp, "%10s", novi->datum);

	char redak[200];
	fgets(redak, sizeof(redak), fp);

	while (fgets(redak, sizeof(redak), fp)) {
		Artikli* novia = (Artikli*)malloc(sizeof(Artikli));
		if (!novia) {
			
			break;
		}if (sscanf(redak, "%49[^,], %d, %lf", novia->imeArtikla, &novia->kolicina, &novia->cijena)==3) {
			novia->next = novi->prvi;
			novi->prvi = novia;
		}
		else {
			free(novia);
		}
	}
	

	fclose(fp);
	return novi;
}

int prviracun(const char* datname,Racuni** glava) {
	FILE* dat = fopen(datname, "r");
	char drugiracuni[100];
	if (!dat) {
		return -1;
	}
	
	while (fgets(drugiracuni, sizeof(drugiracuni), dat) ){

		drugiracuni[strcspn(drugiracuni, "\n")]='\0';
		Racuni* novi = racun(drugiracuni);
		if (novi) {
			sortiranUnos(glava,novi);
		}
	}
	
	fclose(dat);
	return 0;
}

int main() {
	Racuni* glava = NULL;
	prviracun("racuni.txt", &glava);

	Racuni* t = glava;

	while (t) {
		printf("%s\n", t->datum);
		Artikli* a = t->prvi;
		while (a) {
			printf("Ime artikl: %s\nKolicina: %d\nCijena: %.3f \n", a->imeArtikla, a->kolicina, a->cijena);
			a = a->next;
		}
		t = t->next;
	}
	return 0;
}