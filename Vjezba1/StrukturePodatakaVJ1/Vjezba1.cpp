#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


typedef struct student {
	char name[30];
	char surname[30];
	int points;

}Stud;

int main() {


	FILE *dat = fopen("popis.txt", "r");
	char buffer[50] = { 0 };
	int count = 0;
	Stud* studenti = NULL;
	if (!dat) {
		perror("fopen");
		return -1;
	}

	if (!dat) {
		printf("Greska");
		return -1;
	}

	while (!feof(dat)) {
		fgets(buffer, 50, dat);
		count++;

	}
	studenti = (Stud*)malloc(count * sizeof(Stud));
	if (!dat) {
		printf("Greska");
		return -1;
	}
	int M;
	printf("Unesi maksimalan broj bodova:  ");
	scanf("%d", &M);
	printf("\n");

	
	int num = 0;
	while (!feof(dat)) {
		fscanf(dat,"%s %s %d", studenti[num].name, studenti[num].surname, &studenti[num].points);
		num++;
	}
	rewind(dat);
	int numb = 0;
	for (int i = 0; i <= count; i++) {
		float rbb = ((float)studenti[i].points / M) * 100;
		printf("%s %s %d %.3f\n", studenti[i].name, studenti[i].surname, studenti[i].points, rbb);

	}

	

	fclose(dat);

	free(studenti);
	return 0;
}