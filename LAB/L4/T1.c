
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Employeee {
	char id[20];
	char name[50];
	char gender[2];
	char position[50];
	int experience;
	float salary;
};
struct Employeee emp;

long int size = sizeof(emp);

FILE* fp;

void addRecord()
{
	system("cls");
	fseek(fp, 0, SEEK_END);
	char another = 'y';

	while (another == 'y') {
		printf("\nEnter Employee ID : ");
		scanf("%s", &emp.id);

		printf("\nEnter Employee Name : ");
		scanf("%s", &emp.name);

		printf("\nEnter Employee Gender : ");
		scanf("%s", &emp.gender);

		printf("\nEnter Employee Position : ");
		scanf("%s", &emp.position);

		printf("\nEnter Employeee Experience : ");
		scanf("%d", &emp.experience);

		printf("\nEnter Employee Salary : ");
		scanf("%f", &emp.salary);

		fwrite(&emp, size, 1, fp);

		printf("\nWant to add another record (y/n) : ");
		fflush(stdin);

		scanf("%c", &another);
	}
}


void showByID(char* id)
{
	system("cls");
	rewind(fp);

	printf("\nEMP ID\t\tNAME\t\tGENDER\t\tPOSITION\t\tEXPERIENCE\t\tSALARY", emp.id, emp.name, emp.gender, emp.position, emp.experience, emp.salary);
	while (fread(&emp, size, 1, fp) == 1) {
		if (strcmp(emp.id, id) == 0)
			printf("\n%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t\t%.2f\t", emp.id, emp.name, emp.gender, emp.position, emp.experience, emp.salary);
	}

	fclose(fp);
	system("pause");
}


void displayrecord()
{
	system("cls");
	rewind(fp);

	printf("\nEMP ID\t\tNAME\t\tGENDER\t\tPOSITION\t\tEXPERIENCE\t\tSALARY\t", emp.id, emp.name, emp.gender, emp.position, emp.experience, emp.salary);

	while (fread(&emp, size, 1, fp) == 1)
		printf("\n%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t\t%.2f\t", emp.id, emp.name, emp.gender, emp.position, emp.experience, emp.salary);

	printf("\n\n\n\t");
	system("pause");
}

void conditionaldisplayrecord()
{
	system("cls");
	rewind(fp);

	printf("\nEMP ID\t\tNAME\t\tGENDER\t\tPOSITION\t\tEXPERIENCE\t\tSALARY\t", emp.id, emp.name, emp.gender, emp.position, emp.experience, emp.salary);

	while (fread(&emp, size, 1, fp) == 1) {
		if (emp.salary < 20000) {
			printf("\n%s\t\t%s\t\t%s\t\t%s\t\t%d\t\t\t%.2f\t", emp.id, emp.name, emp.gender, emp.position, emp.experience, emp.salary);
		}
	}

	printf("\n\n\n\t");
	system("pause");
}

// Driver code
int main()
{
	int choice;
	char* temp_id[50];
	fp = fopen("data.txt", "rb+");

	if (fp == NULL) {
		fp = fopen("data.txt", "wb+");
		if (fp == NULL) {
			printf("\nCannot open file...");
			exit(1);
		}
	}

	while (1) {
		system("cls");
		printf("\n1. Add a record\n");
		printf("\n2. Search a record be ID\n");
		printf("\n3. Show all records\n");
		printf("\n4. Show employess having pay less than basic pay (20000)\n");
		printf("\n5. Save and exit\n");
		printf("\nENTER YOUR CHOICE...\n");
		fflush(stdin);
		scanf("%d", &choice);

		// Switch Case
		switch (choice) {
		case 1:
			addRecord();
			break;

		case 2:
			printf("Enter the ID: ");
			scanf("%s", &*temp_id);
			showByID(*temp_id);
			break;

		case 3:
			displayrecord();
			break;

		case 4:
			conditionaldisplayrecord();
			break;

		case 5:
			fclose(fp);
			exit(0);
			break;

		default:
			printf("\nINVALID CHOICE...\n");
		}
	}

	return 0;
}
