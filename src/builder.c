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

void create_folder(const char *path_folder){
	int dir_status;

	printf("%scforge:%s creating %s folder\n", INIT_GREEN, END_COLOR, path_folder);
	if ((dir_status = mkdir(path_folder, 0777)) == -1){
		fprintf(stderr, "%sERROR:%s was not possible to create %s directory\n", INIT_RED, END_COLOR, path_folder);
		exit(EXIT_FAILURE);
	};
	printf("%scforge:%s %s folder created with success!\n", INIT_GREEN, END_COLOR, path_folder);
}

int proj_init(char *path_main[]){
	char *path_src = malloc(sizeof(path_src) * 1024);
	char *path_build = malloc(sizeof(path_build) * 1024);
	sprintf(path_src, "%s/src", *path_main);
	sprintf(path_build, "%s/build", *path_main);

	create_folder(*path_main);
	create_folder(path_src);
	create_folder(path_build);
	
	free(path_src);
	free(path_build);

	exit(EXIT_SUCCESS);
}
