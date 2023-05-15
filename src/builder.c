/* This file it's responsible for building the entire project */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

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
		fatal("Shell session not found");
	
	// Build command
	(void)memset(command, 0, sizeof(command));
	(void)sprintf(command, "git init ./%s/", PROJECT_NAME);

	// Run gitinit and check return value
	(void)fprintf(stdout, "%scforge:%s Initializing git project at ./%s/\n", INIT_GREEN, END_COLOR, PROJECT_NAME);
	command_status = system(command);	
	if (command_status == -1 || command_status == 127){
		fatal("Some error occurred during the shell execution");
	}
}

void project_build()
{
	char current_path[BUFFER];
	char proj_name[BUFFER];
	size_t str_len = sizeof(current_path);
	size_t dir_parsing_flag = 0;

	(void)memset(current_path, 0, sizeof(current_path));

	// Parse current folder name
	if (getcwd(current_path, sizeof(current_path)) == NULL) // Get current folder path
		(void)fprintf(stdout, "%scforge:%s wasn't possible to get current folder path\n", INIT_GREEN, END_COLOR);
	for (int i = 0; i < str_len; i++)
		if (current_path[i] == '/' || current_path[i] == '\\')
			dir_parsing_flag = i;

	// Build project name
	char *parsing_ptr = &current_path[++dir_parsing_flag];
	(void)strcpy(proj_name, parsing_ptr);
	(void)fprintf(stdout, "%scforge:%s building %s\n", INIT_GREEN, END_COLOR, proj_name);

	// Search main.c file
	

	// Build main.c file
	
	
	// Or build whatever has in it in case main.c insn't there
}

void file_make(FileType file_type, const char *PROJECT_NAME)
{
	// Files path buffer
	FILE *source_file = NULL;
	FILE *destination_file = NULL;
	char source_file_path[BUFFER] = {0};
	char destination_file_path[BUFFER] = {0};
	char file_text_buffer[BUFFER] = {0};
	size_t read_size = 0;
	
	// Builds the path to the source and destination files
	switch(file_type){
		case FILE_CMAKE:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_CMAKE_NAME);
			(void)sprintf(destination_file_path, "./%s/%s", PROJECT_NAME, FILE_CMAKE_NAME);
			break;
		case FILE_README:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_README_NAME);
			(void)sprintf(destination_file_path, "./%s/%s", PROJECT_NAME, FILE_README_NAME);
			break;
		case FILE_MAIN:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_MAIN_NAME);
			(void)sprintf(destination_file_path, "./%s/%s/%s", PROJECT_NAME, SRC_PATH, FILE_MAIN_NAME);
			break;
		case FILE_TESTS:
			(void)sprintf(source_file_path, "%s/%s", STATIC_PATH, FILE_TESTS_NAME);
			(void)sprintf(destination_file_path, "./%s/%s/%s", PROJECT_NAME, SRC_PATH, FILE_TESTS_NAME);
			break;
		default:
		    fatal("Failed to build project file");
			break;
	}

	// Open source file for reading
	(void)fprintf(stdout, "%scforge:%s reading template file at %s\n", INIT_GREEN, END_COLOR, destination_file_path);

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

	(void)fprintf(stdout, "%scforge:%s %s file created successfully\n", INIT_GREEN, END_COLOR, destination_file_path);

	// Close source and destination files
	(void)fclose(source_file);
	(void)fclose(destination_file);
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

int proj_init(char *proj_name)
{
	char path_src[BUFFER];
	char path_build[BUFFER];

	// Clean memory and populate it
	(void)sprintf(path_src, "%s/src", proj_name);
	(void)sprintf(path_build, "%s/build", proj_name);

	// Create default folders
	folder_make(proj_name);
	folder_make(path_src);
	folder_make(path_build);

	// Create default files
	file_make(FILE_README, proj_name);
	file_make(FILE_MAIN, proj_name);
	if (config.make_test_file)
		file_make(FILE_TESTS, proj_name);
	if (config.make_cmake_file)
		file_make(FILE_CMAKE, proj_name);

	// Initialize git project
	if (config.initialize_git)
		git_initialize(proj_name);

	exit(EXIT_SUCCESS);
}
