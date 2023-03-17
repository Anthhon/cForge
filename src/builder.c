/* This file it's responsible for building the entire project */

#include <stdio.h>
#include <stdio.h>
#include <sys/stat.h>

/* These values should be used to make the
 * console messages more fancy and easier to read */
#define INIT_RED "\033[0;31m"
#define INIT_GREEN "\033[0;32m"
#define END_COLOR "\033[0m"

#define BUFFER 1024 
#define TERMINATOR 1

/* TODO: Create a struct to contain all the projects definition 
 * typedef struct ProjDefinitions{
 * 	int make_readme = TRUE;
 * 	int make_git = TRUE;
 * }*/

typedef enum {
	FILE_CMAKE,
	FILE_README,
	FILE_MAIN,
	FILE_TESTS
} File;

void file_make(File file_type){
	static const char *STATICS_PATH = "../statics/";
	static const char *TESTS_PATH = "./tests/";
	static const char *SRC_PATH = "../src/";
	const char *FILE_CMAKE_NAME = "CMakeLists.txt";
	const char *FILE_README_NAME = "README";
	const char *FILE_MAIN_NAME = "main.c";
	const char *FILE_TESTS_NAME = "tests.c";

	FILE *source_file, *destination_file;
	char *source_file_path = malloc(sizeof(*source_file_path) * BUFFER);
	char *destination_file_path = malloc(sizeof(*destination_file_path) * BUFFER);
	char text_buffer[BUFFER];
	size_t read_size;

	/* Builds the path to the source and destination files */
	switch(file_type){
		case FILE_CMAKE:
			sprintf(source_file_path, "%s%s", STATICS_PATH, FILE_CMAKE_NAME);
			break;
		case FILE_README:
			sprintf(source_file_path, "%s%s", STATICS_PATH, FILE_README_NAME);
			break;
		case FILE_MAIN:
			sprintf(source_file_path, "%s%s", STATICS_PATH, FILE_MAIN_NAME);
			break;
		case FILE_TESTS:
			sprintf(source_file_path, "%s%s", STATICS_PATH, FILE_TESTS_NAME);
			break;
		default:
			fprintf(stderr, "%sERROR:%s Failed to build path to pointed file\n", INIT_RED, END_COLOR);
			exit(EXIT_FAILURE);
			break;
	}

	/* Open source file for reading */
	if ((source_file = fopen(source_file_path, "rb")) == NULL){
		fprintf(stderr, "%sERROR:%s Failed to read %s file\n", INIT_RED, END_COLOR, source_file_path);
		exit(EXIT_FAILURE);
	}

	/* Open destination file for writing */
	if ((destination_file = fopen(destination_file_path, "wb")) == NULL){
		fprintf(stderr, "%sERROR:%s Failed to create %s file\n", INIT_RED, END_COLOR, destination_file_path); 
		exit(EXIT_FAILURE);
	}

	/* Copy the content of the source file to the destination file */
	while ((read_size = fread(text_buffer, 1, sizeof(text_buffer), source_file)) > 0){
		fwrite(text_buffer, 1, read_size, destination_file);
	}

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

	return;
}

void folder_make(const char *folder_path){
	int dir_status;
	printf("%scforge:%s creating %s folder\n", INIT_GREEN, END_COLOR, folder_path);
	if ((dir_status = mkdir(folder_path, 0777)) == -1){
		fprintf(stderr, "%sERROR:%s was not possible to create %s directory\n", INIT_RED, END_COLOR, folder_path);
		exit(EXIT_FAILURE);
	};
	printf("%scforge:%s %s folder created with success!\n", INIT_GREEN, END_COLOR, folder_path);

	return;
}

int proj_init(char *path_main[]){
	char *path_src = malloc(sizeof(*path_src) * BUFFER);
	char *path_build = malloc(sizeof(*path_build) * BUFFER);
	char *path_CMakeLists = "CMakeLists.txt";
	sprintf(path_src, "%s/src", *path_main);
	sprintf(path_build, "%s/build", *path_main);

	/* Create default folders and files */
	folder_make(*path_main);
	folder_make(path_src);
	folder_make(path_build);

	file_make(FILE_CMAKE);
	
	free(path_src);
	path_src = NULL;
	free(path_build);
	path_build = NULL;
	exit(EXIT_SUCCESS);
}
