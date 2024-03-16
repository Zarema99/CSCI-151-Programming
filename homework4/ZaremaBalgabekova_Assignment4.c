#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	char strData[50];
	struct _Node *next;
} Node;

void writeFile2(char fileName[], char ssData[], Node **oLinkedList) {

	FILE*outfile;
	//using "w" to clean the file before appending data to the file
	outfile = fopen(fileName, "w");
	fclose(outfile);
	outfile = fopen(fileName, "a");

	//checking the validity
	if (outfile == NULL) {
		printf("CANNOT open %s\n", fileName);
		return;
	}

	fputs(ssData, outfile);
	fprintf(outfile, "\n");

	//pointer which is used as an iterator
	Node*p = (Node*) malloc(sizeof(Node));

	for (p = *oLinkedList; p != NULL; p = p->next) {
		fputs(p->strData, outfile);
	}
	fprintf(outfile, "\n");
}

int isPalindrome(char str[]) {

	int left = 0, right = strlen(str) - 1, x;

	while (left < right) {
		//using post-increment and post-decrement
		if (str[left++] == str[right--]) {
			x = 1;   //means TRUE

		} else {
			x = 0;   //means FALSE
		}
	}
	return x;
}

char *getPalindrome(char str[]) {

	int i = isPalindrome(str);
	if (i == 1) {
		return "Is_Palindrome";

	} else {
		return "Not_Palindrome";
	}
}

int howManySubstrings(char subStr[], char str[]) {

	//this function considers only 3-letter substrings
	int i = 0, count = 0;
	while (str[i] != '\0') {
		char ch = subStr[0];
		if (str[i] != ch) {
			i++;
		} else {
			ch = subStr[1];
			i++;
			if (str[i] == ch) {
				ch = subStr[2];
				i++;
				if (str[i] == ch) {
					count++;
					i++;
				}
			}
		}
	}
	return count;
}

//this code is similar to the code from Lesson 26
void freeLinkedlist(Node *head) {

	if (head != NULL) {
		freeLinkedlist(head->next);
		free(head);
	}
}

//this code is also similar to the code from Lesson 26
void printLinkedlist(Node *head) {

	if (head != NULL) {
		printf("%s", head->strData);
		printLinkedlist(head->next);
	}
}

void appendNode(Node **oLinkedList, char outputLine[]) {

	Node*prev = NULL;
	if (*oLinkedList == NULL) {   //only the first time
		prev = (Node*) malloc(sizeof(Node));
		strcpy(prev->strData, outputLine);
		prev->next = NULL;
		*oLinkedList = prev;

	} else {
		prev = *oLinkedList;
		//prev is used as an iterator
		while (prev->next != NULL) {
			prev = prev->next;
		}
		Node*new = (Node*) malloc(sizeof(Node));
		strcpy(new->strData, outputLine);
		new->next = NULL;
		prev->next = new;
	}
}

void checkSubstringPalindrome2(char ssData[], char *iStringData[],
		Node **oLinkedList, int nrIOfileLines) {

	int i;
	char buf[5];   //array for itoa
	char string[50];   //an additional string (array of characters)

	for (i = 0; i < nrIOfileLines; i++) {
		int x = howManySubstrings(ssData, iStringData[i]);
		char*arr = getPalindrome(iStringData[i]);
		strcpy(string, iStringData[i]);
		strcat(string, "\t");
		strcat(string, itoa(x, buf, 10));
		strcat(string, "\t");
		strcat(string, arr);
		strcat(string, "\n");
		appendNode(oLinkedList, string);
	}
}

void readFile2(char filename[], char *ArrayPtr[]) {

	FILE*infile;
	infile = fopen(filename, "r");

	//checking the validity
	if (infile == NULL) {
		printf("CANNOT open %s\n", filename);
		return;
	}

	char buf[50];   //array for fgets
	int i = 0;
	while (fgets(buf, 50, infile) != NULL) {
		//'\0' instead of '\n'
		buf[strlen(buf) - 1] = '\0';
		strcpy(ArrayPtr[i], buf);
		i++;
	}
	fclose(infile);
}

int countFileLines(char filename[]) {

	FILE*infile;
	infile = fopen(filename, "r");

	//checking the validity
	if (infile == NULL) {
		printf("CANNOT open %s\n", filename);
		return 1;
	}

	int count = 0;
	char ch;
	while (!feof(infile)) {
		ch = getc(infile);
		if (ch == '\n') {
			count++;
		}
	}
	fclose(infile);
	return count;
}

int main(void) {
	int num_lines1 = countFileLines("iStrings.txt");
	int num_lines2 = countFileLines("subStrings.txt");

	//declaring arrays of pointers and a linked list
	char*iStr_arr[num_lines1];
	char*subStr_arr[num_lines2];
	Node*head = NULL;

	//allocating memory
	int i;
	for (i = 0; i < num_lines1; i++) {
		iStr_arr[i] = (char*) malloc(50 * sizeof(char));
	}

	for (i = 0; i < num_lines2; i++) {
		subStr_arr[i] = (char*) malloc(50 * sizeof(char));
	}

	readFile2("iStrings.txt", iStr_arr);

	readFile2("subStrings.txt", subStr_arr);

	for (i = 0; i < num_lines2; i++) {

		checkSubstringPalindrome2(subStr_arr[i], iStr_arr, &head, num_lines1);

		writeFile2("oStrings.txt", subStr_arr[i], &head);

		//calling printLinkedlist just for debugging
		printLinkedlist(head);

		freeLinkedlist(head);

		//initializing head again before creating a new linked list
		head = NULL;
	}

	return 0;
}