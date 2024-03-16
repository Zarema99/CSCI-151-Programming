#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	setvbuf (stdout, NULL, _IONBF, 0);

	char command;
	float average;
	int user_number, secret_number, trials, maximum, number_of_games, total_trials;
	int seed=time(NULL);
	srand(seed);
	maximum=9999;
	number_of_games=0;
	total_trials=0;
	average=0.0;

	printf ("WELCOME to our game!\n");
	do {
		if (command!='\n')
			printf ("MENU: (s) to start a guessing game, (n) to choose a new range, (q) to exit\n");
		scanf ("%c", &command);

		if (command=='s') {
			printf ("The range is BETWEEN 0 AND %i. Guess:\n", maximum);
			secret_number=rand()%maximum;
			trials=0;

			do {
				scanf ("%i", &user_number);
				if (secret_number>user_number){
				   printf ("Too LOW! Guess:\n");
				   trials++;
				   total_trials++;
				}else if (secret_number <user_number){
				   printf ("Too HIGH! Guess:\n");
				   trials++;
				   total_trials++;
				}

			}while (secret_number!=user_number);
		    	trials++;
		    	total_trials++;
			printf ("Correct: You TOOK %i trials\n", trials);
			number_of_games++;

		}else if (command=='n') {
			printf ("Please enter a new MAXIMUM:\n");
			scanf ("%i", &maximum);

		}else if (command=='q') {
			if (total_trials==0 && number_of_games==0){
				printf ("Thank you for playing! Your guess count AVERAGE %.1f\n", average);
			}else {
				average=(float)total_trials/number_of_games;
				printf ("Thank you for playing! Your guess count AVERAGE %.1f\n", average);
			}

		}else if (command!='\n') {
			printf ("UNRECOGNIZED action!\n");
		}

	} while (command!='q');

	return 0;
}
