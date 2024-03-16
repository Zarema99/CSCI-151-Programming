#include <stdio.h>
#include <stdlib.h>
#include <string.h> //to use strlen function

void encrypt(FILE*fin, FILE*fout, char subarr[], char pass[]) {
	char ch_fin, ch_pass;
	int x = 0;
	while (!feof(fin)) {
		ch_fin = getc(fin);
		//using % to repeat password as many as needed
		ch_pass = pass[x % strlen(pass)];
		//condition to avoid '\0'
		if (ch_fin >= 0) {
			char index = (ch_fin + ch_pass) % 254;
			putc(subarr[(unsigned char) index], fout);
			x++;
		}
	}
}

void decrypt(FILE*fin, FILE*fout, char subarr[], char pass[]) {
	char ch_fin, ch_pass;
	int x = 0;
	while (!feof(fin)) {
		ch_fin = getc(fin);
		//to repeat password
		ch_pass = pass[x % strlen(pass)];
		//condition to avoid '\0'
		if ((unsigned char) ch_fin < 255) {
			char text_char = (subarr[(unsigned char) ch_fin] - ch_pass) % 254;
			putc(text_char, fout);
			x++;
		}
	}
}

void read_keyfile(char subarr1[], char subarr2[]) {
	FILE*key_file;
	key_file = fopen("key.254", "r");
	//checking key_file
	if (key_file == NULL) {
		printf("CANNOT open key.254\n");
		exit(0);
	} else {
		int i = 0;
		do {
			char ch = getc(key_file);
			subarr1[(unsigned char) i] = ch;
			subarr2[(unsigned char) ch] = i;
			i++;
		} while (!feof(key_file));
	}
	fclose(key_file);
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	char password[256], buf[256], command, filename[256];

	printf("WELCOME to the encryption service!\n");
	printf("ENTER your password, please:\n");
	scanf("%s", password);
	//reading a new line
	getchar();

	//creating 2 arrays and passing them to read_keyfile function
	char subarr1[254], subarr2[254];
	read_keyfile(subarr1, subarr2);

	printf("MENU: <e> to encode, <d> to decode, <q> to quit\n");

	while (fgets(buf, 256, stdin) != NULL) {
		command = buf[0];
		if (command == 'e') {
			printf("ENTER a file to encrypt:\n");
			scanf("%s", filename);
			//reading a new line
			getchar();
			FILE*infile;
			infile = fopen(filename, "r");
			if (infile == NULL) {
				printf("CANNOT open %s\n", filename);
			} else {
				printf("ENTER a filename for the encrypted file:\n");
				scanf("%s", filename);
				//reading a new line
				getchar();
				FILE*outfile;
				outfile = fopen(filename, "w");
				if (outfile == NULL) {
					printf("CANNOT open %s\n", filename);
				} else {
					encrypt(infile, outfile, subarr1, password);
				}
				fclose(outfile);
			}
			fclose(infile);

		} else if (command == 'd') {
			printf("ENTER a file to decrypt:\n");
			scanf("%s", filename);
			//reading a new line
			getchar();
			FILE*infile;
			infile = fopen(filename, "r");
			if (infile == NULL) {
				printf("CANNOT open %s\n", filename);
			} else {
				printf("ENTER a filename for the decrypted file:\n");
				scanf("%s", filename);
				//reading a new line
				getchar();
				FILE*outfile;
				outfile = fopen(filename, "w");
				if (outfile == NULL) {
					printf("CANNOT open %s\n", filename);
				} else {
					decrypt(infile, outfile, subarr2, password);
				}
				fclose(outfile);
			}
			fclose(infile);

		} else if (command == 'q') {
			printf("BYE!\n");
			exit(0);

		} else {
			printf("UNRECOGNIZED %c\n", command);
		}
		printf("MENU: <e> to encode, <d> to decode, <q> to quit\n");
	}
	return 0;
}
