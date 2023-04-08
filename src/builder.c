/* This file it's responsible for building the entire project */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "common.c"

void git_initialize(const char *PROJECT_NAME)
{
	char *command = malloc(sizeof(*command) * BUFFER);
	int command_status = 0;

	// Check if shell console is available	
	(void)fprintf(stdout, "%scforge:%s checking if shell session is available\n", INIT_GREEN, END_COLOR);
	if (system(NULL))
		(void)fprintf(stdout, "%scforge:%s shell session found\n", INIT_GREEN, END_COLOR);
	else
		(void)fprintf(stdout, "%scforge:%s shell session not found\n", INIT_RED, END_COLOR);
	
	// Build command
	(void)memset(command, 0, sizeof(command));
	(void)sprintf(command, "git init ./%s/", PROJECT_NAME);

	// Run gitinit
	(void)fprintf(stdout, "%scforge:%s Initializing git project at ./%s/\n", INIT_GREEN, END_COLOR, PROJECT_NAME);
	command_status = system(command);	
	if (command_status == -1 || command_status == 127){
		(void)fprintf(stdout, "%scforge:%s Some error occurred during the shell execution\n", INIT_RED, END_COLOR);
		(void)fprintf(stdout, "%scforge:%s This is the error status %i\n", INIT_RED, END_COLOR, command_status);
	}
}

void file_make(FileType file_type, const char *DESTINATION_PATH)
{
	// Files path buffer
	FILE *source_file = NULL;
	FILE *destination_file = NULL;
	char *source_file_path = malloc(sizeof(*source_file_path) * BUFFER);
	char *destination_file_path = malloc(sizeof(*destination_file_path) * BUFFER);
	char file_text_buffer[BUFFER];
	size_t read_size = 0;
	
	(void)memset(source_file_path, 0, sizeof(source_file_path));
	(void)memset(destination_file_path, 0, sizeof(destination_file_path));
	(void)memset(file_text_buffer, 0, sizeof(file_text_buffer));

	// Builds the path to the source and destination files
	switch(file_type){
		case FILE_CMAKE:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_CMAKE_NAME);
			(void)sprintf(destination_file_path, "./%s/%s", DESTINATION_PATH, FILE_CMAKE_NAME);
			break;
		case FILE_README:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_README_NAME);
			(void)sprintf(destination_file_path, "./%s/%s", DESTINATION_PATH, FILE_README_NAME);
			break;
		case FILE_MAIN:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_MAIN_NAME);
			(void)sprintf(destination_file_path, "./%s/%s/%s", DESTINATION_PATH, SRC_PATH, FILE_MAIN_NAME);
			break;
		case FILE_TESTS:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_TESTS_NAME);
			(void)sprintf(destination_file_path, "./%s/%s/%s", DESTINATION_PATH, SRC_PATH, FILE_TESTS_NAME);
			break;
		default:
			(void)fprintf(stderr, "%sERROR:%s Failed to build path to pointed file\n", INIT_RED, END_COLOR);
			exit(EXIT_FAILURE);
			break;
	}

	// Open file for reading
	(void)fprintf(stderr, "%scforge:%s reading template %s file\n", INIT_GREEN, END_COLOR, destination_file_path);
	if ((source_file = fopen(source_file_path, "rbe")) == NULL){
		(void)fprintf(stderr, "%sERROR:%s Failed to read %s file\n", INIT_RED, END_COLOR, source_file_path);
		exit(EXIT_FAILURE);
	}

	// Open destination file for writing
	if ((destination_file = fopen(destination_file_path, "wbe")) == NULL){
		(void)fprintf(stderr, "%sERROR:%s Failed to create %s file\n", INIT_RED, END_COLOR, destination_file_path); 
		exit(EXIT_FAILURE);
	}

	// Copy the content of the source file to the destination file
	while ((read_size = fread(file_text_buffer, 1, sizeof(file_text_buffer), source_file)) > 0){
		(void)fwrite(file_text_buffer, 1, read_size, destination_file);
	}

	(void)fprintf(stderr, "%scforge:%s %s file created succesffully\n", INIT_GREEN, END_COLOR, destination_file_path);

	// Close source and destination files
	(void)fclose(source_file);
	(void)fclose(destination_file);

	// Free memory used in file paths
	if (source_file_path != NULL){
		(void)free(source_file_path);
		source_file_path = NULL;
	}

	if (destination_file_path != NULL){
		(void)free(destination_file_path);
		destination_file_path = NULL;
	}
}

void folder_make(const char *folder_path)
{
	int dir_status = 0;

	printf("%scforge:%s creating %s folder\n", INIT_GREEN, END_COLOR, folder_path);
	if ((dir_status = mkdir(folder_path, PERMISSION_TO_MODIFY)) == -1){
		(void)fprintf(stderr, "%sERROR:%s was not possible to create %s directory\n", INIT_RED, END_COLOR, folder_path);
		exit(EXIT_FAILURE);
	};
	printf("%scforge:%s %s folder created with success!\n", INIT_GREEN, END_COLOR, folder_path);
}

int proj_init(char *path_main[])
{
	char *path_src = malloc(sizeof(*path_src) * BUFFER);
	char *path_build = malloc(sizeof(*path_build) * BUFFER);

	// Clean memory and populate it
	(void)memset(path_src, 0, sizeof(path_src)); 
	(void)memset(path_build, 0, sizeof(path_build)); 
	(void)sprintf(path_src, "%s/src", *path_main);
	(void)sprintf(path_build, "%s/build", *path_main);

	// Create default folders
	folder_make(*path_main);
	folder_make(path_src);
	folder_make(path_build);

	// Create default files
	file_make(FILE_README, *path_main);
	file_make(FILE_MAIN, *path_main);
	if (config.make_test_file)
		file_make(FILE_TESTS, *path_main);
	if (config.make_cmake_file)
		file_make(FILE_CMAKE, *path_main);

	// Initialize git project
	if (config.initialize_git)
		git_initialize(*path_main);

	if (path_src != NULL){
		(void)free(path_src);
		path_src = NULL;
	}
	if (path_build != NULL){
		(void)free(path_build);
		path_build = NULL;
	}
	exit(EXIT_SUCCESS);
}
