/* This test section makes use of CUnit lib
 * use this command to install it on linux system
 * sudo apt install libcunit1-dev */
#include <CUnit/CUnit.h>
#include "main.c"

void test_operation_sum(void){
	/* Write your tests here */
	CU_ASSERT_EQUAL(operation_sum(10, 20), 30);
/*	~~~~~~~~~~~~~~^ 	    ^          ~^
 *	CUnit test func		    |           |
 *		     Function to test		|
 *				   Expected value
 */
}

int main(void) {
    CU_pSuite mytestsuite = NULL;

    /* Initialize CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add test suite to registry */
    mytestsuite = CU_add_suite("operation_sum_suite", NULL, NULL);
    if (mytestsuite == NULL) {
        (void)CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add test cases to suite */
    if (CU_add_test(mytestsuite, "test_operation_sum", test_operation_sum) == NULL) {
        (void)CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run tests */
    (void)CU_basic_set_mode(CU_BRM_VERBOSE);
    (void)CU_basic_run_tests();

    /* Cleanup */
    (void)CU_cleanup_registry();
    return CU_get_error();
}
