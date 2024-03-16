#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void writeFile(char fileName[], char ssData[], char oStringData[][50],
		int nrIOfileLines) {

	FILE*outfile;
	//using "w" to clean file before "a"
	outfile = fopen(fileName, "w");
	outfile = fopen(fileName, "a");
	//checking the validity
	if (outfile == NULL) {
		printf("CANNOT open %s\n", fileName);
		return;
	}
	fputs(ssData, outfile);
	fprintf(outfile, "\n");
	int i;
	for (i = 0; i < nrIOfileLines; i++) {
		fputs(oStringData[i], outfile);
	}
	fprintf(outfile, "\n");
}

int isPalindrome(char str[]) {

	int left = 0, right = strlen(str) - 1, x;
	while (left < right) {
		//using post-increment and post-decrement
		if (str[left++] == str[right--]) {
			x = 1;

		} else {
			x = 0;
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

void checkSubstringPalindrome(char subStr[], char iStringData[][50],
		char oStringData[][50], int nrIOfileLines) {

	int i;
	// array for itoa
	char buf[5];
	//calling functions for each string
	for (i = 0; i < nrIOfileLines; i++) {
		int x = howManySubstrings(subStr, iStringData[i]);
		char*arr = getPalindrome(iStringData[i]);
		strcpy(oStringData[i], iStringData[i]);
		strcat(oStringData[i], "\t");
		strcat(oStringData[i], itoa(x, buf, 10));
		strcat(oStringData[i], "\t");
		strcat(oStringData[i], arr);
		strcat(oStringData[i], "\n");
	}
}

void readFile(char filename[], char twoDimArr[][50]) {

	FILE*infile;
	infile = fopen(filename, "r");
	//checking the validity
	if (infile == NULL) {
		printf("CANNOT open %s\n", filename);
		return;
	}
	//array for fgets
	char buf[50];
	int i = 0, j;
	while (fgets(buf, 50, infile) != NULL) {
		j = -1;
		//putting '\0' instead of '\n'
		buf[strlen(buf) - 1] = '\0';
		do {
			j++;
			twoDimArr[i][j] = buf[j];
		} while (buf[j] != '\0');
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

//function to remove leading and trailing white spaces
void remove_whitespace(char string[]) {

	int index = 0, index2 = 0;
	while (isspace(string[index]) != 0) {
		index++;
	}
	while (string[index + index2] != '\0') {
		string[index2] = string[index + index2];
		index2++;
	}
	string[index2] = '\0';

	index2 = 0;
	while (string[index2] != '\0') {
		if (isspace(string[index2]) == 0) {
			index = index2;
		}
		index2++;
	}
	string[index + 1] = '\0';
}

int main(void) {

	int num_lines1 = countFileLines("iStrings.txt");
	int num_lines2 = countFileLines("subStrings.txt");

	//declaring 2D arrays
	char iStr_arr[num_lines1][50], subStr_arr[num_lines2][50],
			oStr_arr[num_lines1][50];

	readFile("iStrings.txt", iStr_arr);
	readFile("subStrings.txt", subStr_arr);

	// calling function to remove leading and trailing white spaces
	int x;
	for (x = 0; x < num_lines1; x++) {
		remove_whitespace(iStr_arr[x]);
	}

	//calling functions for each subString
	int i;
	for (i = 0; i < num_lines2; i++) {
		checkSubstringPalindrome(subStr_arr[i], iStr_arr, oStr_arr, num_lines1);
		writeFile("oStrings.txt", subStr_arr[i], oStr_arr, num_lines1);
	}

	return 0;
}