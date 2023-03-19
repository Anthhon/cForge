/* This main file has the unique intention to deal with user input */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builder.c"

/* TODO: header file not working
 * #define "console_colors.h" */
#define INIT_RED "\033[0;31m"
#define INIT_GREEN "\033[0;32m"
#define END_COLOR "\033[0m"

void print_usage(char *argv[]){
	(void)fprintf(stderr, "%sUSAGE:%s %s <new> <proj-name>\n", INIT_RED, END_COLOR, argv[0]);
	exit(EXIT_FAILURE);
}

void print_help(void){
	/* The help message itself isn't contained here
	 * you can find it in the HELP.txt file in the main folder */
	FILE *finfo = NULL;
	int read_c = 0;

	if ((finfo = fopen("../static/HELP.txt", "re")) == NULL){
		(void)fprintf(stderr, "%sERROR:%s Failed to open HELP file", INIT_RED, END_COLOR);
		exit(EXIT_FAILURE);
	}

	while ((read_c = fgetc(finfo)) != EOF){
		printf("%c", read_c);
	}

	(void)fclose(finfo);

	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	if (argc <= 1){
		print_usage(&argv[0]);
		exit(EXIT_SUCCESS);
	}

	/* Parse arguments */
	if (argc == 2){
		char *first_arg = &argv[1][0];
		if ((strcmp(first_arg, "--help") == 0) ||
		    (strcmp(first_arg, "-h") == 0) ||
		    (strcmp(first_arg, "help") == 0)){
			print_help();
			exit(EXIT_SUCCESS);
		}
		/* Prints usage message in any of these cases */
		else{ print_usage(&argv[0]); }
	}

	if (argc == 3){
		char *first_arg = &argv[1][0];
		char *proj_name = &argv[2][0];
		if ((strcmp(first_arg, "--new") == 0) ||
		    (strcmp(first_arg, "-n") == 0) ||
		    (strcmp(first_arg, "new") == 0)){
			proj_init(&proj_name);
			exit(EXIT_SUCCESS);
		}
	}

	exit(EXIT_SUCCESS);
}
