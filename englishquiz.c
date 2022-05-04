#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define idsize 10
#define passwordsize 20
#define namesize 12
#define Engsize 12
#define Korsize 6

bool logincheck = 0;
int opt = 0;
int wordsize;
int sizecnt = 0;

typedef struct membersManager {
	struct membersManager* next;
	char id[idsize];
	char password[passwordsize];
	char name[namesize];
}membersManager;

membersManager* First = NULL;
membersManager* Next() {
	membersManager* tmp = (membersManager*)malloc(sizeof(membersManager));
	tmp->next = NULL;
	return tmp;
}

typedef struct wordsManager {
	struct wordsManager* next_W;
	char Eng[Engsize];
	char Kor[Korsize];
}wordsManager;

wordsManager* First_W = NULL;
wordsManager* Next_W() {
	wordsManager* tmp = (wordsManager*)malloc(sizeof(wordsManager));
	tmp->next_W = NULL;
	return tmp;
}

void addMember(membersManager** head, char id[], char password[], char name[]);
void swapdata(wordsManager* set1, wordsManager* set2);
void sortWords(int size);
void wordsCall(void);
void memberCall(void);
void memberSave(void);
void PrintMenu(char ID[]);
void SignUp();
void LogIn(char ID[]);
void LogOut(char ID[]);
void ChooseOne(void);
void Test(void);
void Delete(char ID[]);
void Exit(void);

int main(void) {

	char ID[idsize];
	
	memberCall();
	wordsCall();
	wordsize = sizecnt;
	
	while (opt != 4) {
		system("clear");
		switch (opt) {

		case 0:
			PrintMenu(ID);
			break;
		case 1:
			SignUp();
			break;
		case 2:
			LogIn(ID);
			break;
		case 3:
			LogOut(ID);
			break;
		case 5:
			Delete(ID);
			break;
		case 6:
			Exit();
			break;
		}
	}
	ChooseOne();
	return 0;
}

void addMember(membersManager** head, char id[], char password[], char name[]) {

	if (!*head) {
		*head = Next();
		strcpy((*head)->id, id);
		strcpy((*head)->password, password);
		strcpy((*head)->name, name);
		return;
	}
	addMember(&(*head)->next, id, password, name);
}

void swapdata(wordsManager* set1, wordsManager* set2) {

	char tempEng[Engsize], tempKor[Korsize];
	strncpy(tempEng ,set1->Eng,Engsize);
	strncpy(tempKor, set1->Kor,Korsize);
	strncpy(set1->Eng, set2->Eng,Engsize);
	strncpy(set1->Kor, set2->Kor,Korsize);
	strncpy(set2->Eng, tempEng,Engsize);
	strncpy(set2->Kor, tempKor,Korsize);

}

void sortWords(int size) {

	wordsManager* tmp;
	tmp = First_W;
	
	for (int i = 0;i < size-1;i++) {
		if (tmp->next_W == NULL)
			break;
		for (int j = 0;j < size - i -1;j++) {
			if (strcmp(tmp->Eng, tmp->next_W->Eng) > 0)
				swapdata(tmp, tmp->next_W);
			tmp = tmp->next_W;
		}
		tmp = First_W->next_W;
	}
	
}

void wordsCall(void) {

	FILE* wordin;
	wordin = fopen("dic.txt", "r");
	wordsManager* info = NULL;
	while (feof(wordin) == 0) {
		info = (wordsManager*)malloc(sizeof(wordsManager));
		info->next_W = NULL;
		fscanf(wordin, "%s %s\n", info->Eng, info->Kor);
		sizecnt++;

		if (First_W == NULL) {
			First_W = info;
		}
		else {
			wordsManager* temp = First_W;
			while (temp->next_W != NULL)
				temp = temp->next_W;
			temp->next_W = info;
		}
	}
	fclose(wordin);

	sortWords(sizecnt);
}

void memberCall(void) {

	FILE* in;
	in = fopen("members.txt", "r");
	if (in != NULL) {
		membersManager* infor = NULL;
		while (feof(in) == 0) {
			infor = (membersManager*)malloc(sizeof(membersManager));
			infor->next = NULL;
			fscanf(in, "%s %s %s\n", infor->id, infor->password, infor->name);

			if (First == NULL) {
				First = infor;
			}
			else {
				membersManager* temp = First;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = infor;
			}
		}
	}
	fclose(in);
}

void memberSave(void) {

	FILE* out;
	out = fopen("members.txt", "w");
	if (First != NULL) {
		while (First->next != NULL) {
			membersManager* info = First;
			fprintf(out, "%s %s %s\n", info->id, info->password, info->name);
			First = First->next;
		}
		fprintf(out, "%s %s %s", First->id, First->password, First->name);
		free(First);
	}
	fclose(out);
}

void PrintMenu(char ID[]) {
	for (int i = 0;i < 30;i++)
		printf("=");
	printf("\n");
	for (int i = 0;i < 10;i++)
		printf("=");
	printf("2021 SPLUG");
	for (int i = 0;i < 10;i++)
		printf("=");
	printf("\n");
	if (logincheck) {
		for (int i = 0;i < 30 - strlen(ID);i++)
			printf("=");
		printf("%s", ID);
	}
	else {
		for (int i = 0;i < 30;i++)
			printf("=");
	}
	printf("\n");
	for (int i = 0;i < 30;i++)
		printf("=");
	printf("\n=");
	for (int i = 0;i < 12;i++)
		printf(" ");
	printf("MENU");
	for (int i = 0; i < 12;i++)
		printf(" ");
	printf("=\n");
	for (int i = 0;i < 30;i++)
		printf("=");
	printf("\n");
	printf("       1. Sign up\n");
	printf("       2. Log in\n");
	printf("       3. Log out\n");
	printf("       4. English words test\n");
	printf("       5. Delete account\n");
	printf("       6. Exit\n");
	for (int i = 0;i < 30;i++)
		printf("=");
	printf("\n");
	scanf("%d", &opt);

}

void SignUp() {
	
	char tempID[idsize], tempPW[passwordsize], tempNAME[namesize];
	printf("Sign up page");
	bool IDoverlap;
	
	do {
		tempID[0] = '\0';
		printf("\nID : ");
		scanf("%s", tempID);

		IDoverlap = 0;
		membersManager* tmp;
		tmp = First;

		while (1) {
			tmp = tmp->next;
			if (tmp == NULL)
				break;
			if (tmp->id == tempID) {
				IDoverlap = 1;
				break;
			}
		}
	} while (IDoverlap && printf("ID already exists."));
	printf("ID is available.");
	printf("\nPassword : ");
	scanf("%s", tempPW);
	printf("Name : ");
	scanf("%s", tempNAME);

	addMember(&First, tempID, tempPW, tempNAME);
	

	opt = 0;
}

void LogIn(char ID[]) {

	char tempID[idsize] = {};
	char tempPW[passwordsize] = {};
	bool login;
	
	do {
		tempID[0] = '\0';
		tempPW[0] = '\0';
		login = 0;

		printf("Login");
		printf("\nID : ");
		scanf("%s", tempID);
		printf("\nPassword : ");
		scanf("%s", tempPW);

		membersManager* tmp;
		tmp = First;

		while (1) {
			if (tmp == NULL) {
				break;
			}
			if (strcmp(tmp->id,tempID)==0 && strcmp(tmp->password , tempPW)==0) {
				login = 1;
				break;
			}
			tmp = tmp->next;
		}

	} while ((login==0) && printf("Login Failed\n"));

	strcpy(ID, tempID);
	logincheck = 1;
	opt = 0;
}

void LogOut(char ID[]) {
	char choice;
	printf("Do you want to log out? [y/n] : ");
	scanf(" %c", &choice);
	if (choice == 'y' || choice == 'Y') {
		logincheck = 0;
		ID[0] = '\0';
	}
	opt = 0;
}

void ChooseOne(void) {
	system("clear");
	printf(">> English words test <<");
	printf("\n1. Test 2. Exit\n");
	printf("Choose one: ");
	scanf("%d", &opt);
	if (opt == 1)
		Test();
	else
		Exit();
}

void Test(void) {

	wordsManager* test;
	test = First_W;
	int score=0;
	char* quit = ".quit";

	do {
		char answer[Engsize];
		test = test->next_W;
		printf("%s -> ", test->Kor);
		scanf("%s", answer);
		if (strcmp(answer, quit) == 0)
			break;
		else if (strcmp(test->Eng, answer)==0) {
			printf("correct!\n");
			score++;
		}
		else
			printf("incorrect!\n");
		
	} while (1);

	printf("Your score is %.2f.\n", score / (double)wordsize * 100);
	Exit();
}

void Delete(char ID[]) {

	int i;
	membersManager* temp;
	membersManager* prev;
	temp = First;
	if (strcmp(temp->id, ID) == 0) {
		First = temp->next;
		free(temp);
	}
	else {
		for (i = 0;strcmp(temp->id, ID) != 0;++i) {
			temp = temp->next;
			if (i != 0)
				prev = prev->next;
			if (i == 1)
				prev = First;
		}
		prev->next = temp->next;
		free(temp);

	}
	logincheck = 0;
	ID[0] = '\0';
	opt = 0;
}

void Exit(void) {
	printf("See you later~\n");
	memberSave();
	exit(0);
}

