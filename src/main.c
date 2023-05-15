/* This main file has the unique intention to deal with user input */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builder.c"

/* TODO: header file not working
 * #define "console_colors.h" */
#define INIT_RED "\e[0;31m"
#define INIT_GREEN "\e[0;32m"
#define END_COLOR "\e[0m"

void print_usage(char *argv[])
{
	(void)fprintf(stderr, "%sUSAGE:%s %s <new> <proj-name>\n", INIT_RED, END_COLOR, argv[0]);
	exit(EXIT_FAILURE);
}

void print_help(void)
{
	FILE *fstream = NULL;
	int read_c = 0;

	if ((fstream = fopen("../static/HELP.txt", "re")) == NULL)
			fatal("Failed to open HELP file");

	while ((read_c = fgetc(fstream)) != EOF){
		printf("%c", read_c);
	}

	(void)fclose(fstream);

	exit(EXIT_SUCCESS);
}

void flags_check(char **arguments, size_t arg_counter){
	for (int i = 1; i < arg_counter; ++i){
		if ((strcmp(arguments[i], "--no-cmake") == 0))
			config.make_cmake_file = FALSE;
		if ((strcmp(arguments[i], "--no-test") == 0))
			config.make_test_file = FALSE;
		if ((strcmp(arguments[i], "--no-git-init") == 0))
			config.initialize_git= FALSE;
	}
}

// This should abstract the arguments checking like:
// substr -> "help"
// d_dash -> "--help"
// s_dash -> "-h"
int argument_check(char *argument, char *substr){
		char double_dash[BUFFER];
		char single_dash[BUFFER];
		char single_letter[BUFFER];

		sprintf(double_dash, "--%s", substr);
		sprintf(single_dash, "-%c", substr[0]);
		sprintf(single_letter, "%c", substr[0]);

		if ((strcmp(argument, substr) == 0)      ||
		    (strcmp(argument, double_dash) == 0) ||
		    (strcmp(argument, single_dash) == 0) ||
		    (strcmp(argument, single_letter) == 0)){
				return 1; // Substring found
		}
		return 0; // Substring not found
}

int main(int argc, char *argv[])
{
	char *first_arg = &argv[1][0];
	char *proj_name = &argv[2][0];

	if (argc <= 1){
		print_usage(&argv[0]);
		exit(EXIT_SUCCESS);
	}
	if (argc == 2){
		char *first_arg = &argv[1][0];
		if (argument_check(first_arg, "help")){
			print_help();
			exit(EXIT_SUCCESS);
		}
		//if (argument_check(first_arg, "build")){
		//	project_build();	
		//	flags_check(&argv[0], argc);
		//	exit(EXIT_SUCCESS);
		//}
	}
	if (argc >= 3){
		char *first_arg = &argv[1][0];
		char *proj_name = &argv[2][0];
		if (argument_check(first_arg, "new")){
			proj_config_initialize();
			flags_check(&argv[0], argc);
			proj_init(proj_name);
			exit(EXIT_SUCCESS);
		}
	}
	// Prints usage message in any of these cases
	else print_usage(&argv[0]);

	exit(EXIT_SUCCESS);
}
