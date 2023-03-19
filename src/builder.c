/* This file it's responsible for building the entire project */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER 1024 
#define TERMINATOR 1
#define PERMISSION_TO_MODIFY 0777
#define TRUE 1
#define FALSE 0

/* TODO: header file not working
 * #define "console_colors.h" */
#define INIT_RED "\033[0;31m"
#define INIT_GREEN "\033[0;32m"
#define END_COLOR "\033[0m"

typedef enum FileType {
	FILE_CMAKE,
	FILE_README,
	FILE_MAIN,
	FILE_TESTS
} File;

void file_make(File file_type, const char *DESTINATION_PATH){
	static const char *STATICS_PATH = "../static";
	static const char *TESTS_PATH = "tests";
	static const char *SRC_PATH = "src";
	const char *FILE_CMAKE_NAME = "CMakeLists.txt";
	const char *FILE_README_NAME = "README.md";
	const char *FILE_MAIN_NAME = "main.c";
	const char *FILE_TESTS_NAME = "tests.c";

	FILE *source_file = NULL;
	FILE *destination_file = NULL;
	char *source_file_path = malloc(sizeof(*source_file_path) * BUFFER);
	char *destination_file_path = malloc(sizeof(*destination_file_path) * BUFFER);
	char text_buffer[BUFFER];
	size_t read_size = 0;

	/* Builds the path to the source and destination files */
	switch(file_type){
		case FILE_CMAKE:
			(void)sprintf(source_file_path, "%s/%s", STATICS_PATH, FILE_CMAKE_NAME);
			(void)sprintf(destination_file_path, "./%s/%s", DESTINATION_PATH, FILE_CMAKE_NAME);
			break;
		case FILE_README:
			(void)sprintf(source_file_path, "%s/%s", STATICS_PATH, FILE_README_NAME);
			(void)sprintf(destination_file_path, "./%s/%s", DESTINATION_PATH, FILE_README_NAME);
			break;
		case FILE_MAIN:
			(void)sprintf(source_file_path, "%s/%s", STATICS_PATH, FILE_MAIN_NAME);
			(void)sprintf(destination_file_path, "./%s/%s/%s", DESTINATION_PATH, SRC_PATH, FILE_MAIN_NAME);
			break;
		case FILE_TESTS:
			(void)sprintf(source_file_path, "%s/%s", STATICS_PATH, FILE_TESTS_NAME);
			(void)sprintf(destination_file_path, "./%s/%s/%s", DESTINATION_PATH, SRC_PATH, FILE_TESTS_NAME);
			break;
		default:
			(void)fprintf(stderr, "%sERROR:%s Failed to build path to pointed file\n", INIT_RED, END_COLOR);
			exit(EXIT_FAILURE);
			break;
	}

	/* Open source file for reading */
	(void)fprintf(stderr, "%scforge:%s building %s file\n", INIT_GREEN, END_COLOR, destination_file_path);
	if ((source_file = fopen(source_file_path, "rbe")) == NULL){
		(void)fprintf(stderr, "%sERROR:%s Failed to read %s file\n", INIT_RED, END_COLOR, source_file_path);
		exit(EXIT_FAILURE);
	}

	/* Open destination file for writing */
	if ((destination_file = fopen(destination_file_path, "wbe")) == NULL){
		(void)fprintf(stderr, "%sERROR:%s Failed to create %s file\n", INIT_RED, END_COLOR, destination_file_path); 
		exit(EXIT_FAILURE);
	}

	/* Copy the content of the source file to the destination file */
	while ((read_size = fread(text_buffer, 1, sizeof(text_buffer), source_file)) > 0){
		(void)fwrite(text_buffer, 1, read_size, destination_file);
	}

	/* Just a success message */
	(void)fprintf(stderr, "%scforge:%s %s file created succesffully\n", INIT_GREEN, END_COLOR, destination_file_path);

	/* Close source and destination files */
	fclose(source_file);
	fclose(destination_file);

	/* Free memory used in file paths */
	if (source_file_path != NULL){
		free(source_file_path);
		source_file_path = NULL;
	}

	if (destination_file_path != NULL){
		free(destination_file_path);
		destination_file_path = NULL;
	}
}

void folder_make(const char *folder_path){
	int dir_status = 0;
	printf("%scforge:%s creating %s folder\n", INIT_GREEN, END_COLOR, folder_path);
	if ((dir_status = mkdir(folder_path, PERMISSION_TO_MODIFY)) == -1){
		(void)fprintf(stderr, "%sERROR:%s was not possible to create %s directory\n", INIT_RED, END_COLOR, folder_path);
		exit(EXIT_FAILURE);
	};
	printf("%scforge:%s %s folder created with success!\n", INIT_GREEN, END_COLOR, folder_path);
}

int proj_init(char *path_main[]){
	char *path_src = malloc(sizeof(*path_src) * BUFFER);
	char *path_build = malloc(sizeof(*path_build) * BUFFER);
	char *path_CMakeLists = "CMakeLists.txt";
	(void)sprintf(path_src, "%s/src", *path_main);
	(void)sprintf(path_build, "%s/build", *path_main);

	/* Create default folders and files */
	folder_make(*path_main);
	folder_make(path_src);
	folder_make(path_build);

	file_make(FILE_CMAKE, *path_main);
	file_make(FILE_README, *path_main);
	file_make(FILE_MAIN, *path_main);
	file_make(FILE_TESTS, *path_main);
	
	free(path_src);
	path_src = NULL;
	free(path_build);
	path_build = NULL;
	exit(EXIT_SUCCESS);
}
