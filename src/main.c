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

	if ((fstream = fopen("../static/HELP.txt", "re")) == NULL){
		(void)fprintf(stderr, "%sERROR:%s Failed to open HELP file", INIT_RED, END_COLOR);
		exit(EXIT_FAILURE);
	}

	while ((read_c = fgetc(fstream)) != EOF){
		printf("%c", read_c);
	}

	(void)fclose(fstream);

	exit(EXIT_SUCCESS);
}

void check_arguments(char **arguments, size_t arg_counter){
	// This function should search for special arguments
	for (int i = 1; i < arg_counter; ++i){
		if ((strcmp(arguments[i], "--no-cmake") == 0))
			config.make_cmake_file = FALSE;
		if ((strcmp(arguments[i], "--no-test") == 0))
			config.make_test_file = FALSE;
		if ((strcmp(arguments[i], "--no-git-init") == 0))
			config.initialize_git= FALSE;
	}
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
		if ((strcmp(first_arg, "--help") == 0) ||
		    (strcmp(first_arg, "-h") == 0) ||
		    (strcmp(first_arg, "help") == 0)){
			print_help();
			exit(EXIT_SUCCESS);
		}
	}
	if (argc >= 3){
		char *first_arg = &argv[1][0];
		char *proj_name = &argv[2][0];
		if ((strcmp(first_arg, "--new") == 0) ||
		    (strcmp(first_arg, "-n") == 0)    ||
		    (strcmp(first_arg, "new") == 0)){
			proj_config_create();
			check_arguments(&argv[0], argc);
			proj_init(&proj_name);
			exit(EXIT_SUCCESS);
		}
	}
	// Prints usage message in any of these cases
	else print_usage(&argv[0]);

	exit(EXIT_SUCCESS);
}
