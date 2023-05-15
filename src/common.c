#define PERMISSION_TO_MODIFY 0777
#define TERMINATOR 1
#define BUFFER 1024
#define FALSE 0
#define TRUE 1

#define INIT_GREEN "\e[0;32m"
#define INIT_RED "\e[0;31m"
#define END_COLOR "\e[0m"

#define FILE_CMAKE_NAME "CMakeLists.txt"
#define FILE_README_NAME "README.md"
#define FILE_TESTS_NAME "tests.c"
#define FILE_MAIN_NAME "main.c"

#define STATIC_PATH "../static"
#define TESTS_PATH "tests"
#define SRC_PATH "src"

// Project definitions
typedef struct {
	int initialize_git;
	int make_test_file;
	int make_cmake_file;
} ProjConfig;
ProjConfig config;

typedef enum {
	GIT,
	TEST_FILE,
	CMAKE,
} ProjDefinition;

typedef enum {
	FILE_CMAKE,
	FILE_README,
	FILE_MAIN,
	FILE_TESTS
} FileType;

void fatal(char *message){
		(void)fprintf(stderr, "%sERROR:%s %s\n", INIT_RED, END_COLOR, message);
		exit(EXIT_FAILURE);
}

void pmess(char *message){
		(void)fprintf(stdout, "%scforge:%s %s\n", INIT_GREEN, END_COLOR, message);
}

void proj_config_initialize(void){
	// Declare and define configuration properties
	config.initialize_git = TRUE;
	config.make_test_file = TRUE;
	config.make_cmake_file = TRUE;

	// Print project definition
	(void)fprintf(stdout, "%scforge:%s initialize git is %s\n", INIT_GREEN, END_COLOR,
			      (config.initialize_git) ? "enabled" : "disabled");
	(void)fprintf(stdout, "%scforge:%s create test file is %s\n", INIT_GREEN, END_COLOR,
			      (config.make_test_file) ? "enabled" : "disabled");
	(void)fprintf(stdout, "%scforge:%s create cmake file is %s\n", INIT_GREEN, END_COLOR,
			      (config.make_test_file) ? "enabled" : "disabled");
}

void proj_config_disable(ProjDefinition proj_definition){
	// TODO: Implement this function
	switch(proj_definition)
	{
	case GIT:
		config.initialize_git = FALSE;
	case TEST_FILE:
		config.make_test_file = FALSE;
	case CMAKE:
		config.make_cmake_file= FALSE;
	default:
		fatal("Somehow you passed an impossible parameter");
	}
}
