#include "main.h"
#include "test.h"
#include <stdio.h>

char* current_test_case_name;
int current_test_case_result;

void start_test(char* test_case_name)
{
	if (NULL != test_case_name)
	{
		current_test_case_name = test_case_name;
	}
	else
	{
		current_test_case_name = "<NO NAME>";
	}
	current_test_case_result = -1;
	printf("%s", current_test_case_name);
}
void end_test()
{
	char* test_result = "<No Result>";
	if (current_test_case_result == 0)
	{
		test_result = "FAIL";
	}
	else if (current_test_case_result == 1)
	{
		test_result = "SUCCEED";
	}

	printf(" -> %s \n", test_result);
}


void test_assertion(int assertion_result, char* assertion_description)
{
	if (0 == assertion_result)
	{
		current_test_case_result = 0;
		if (NULL != assertion_description)
		{
			printf("\n ASSERTION FAILED while testing :%s", assertion_description);
		}
		else
		{
			printf("\n ASSERTION FAILED");
		}
	}
	else if (current_test_case_result != 0)
	{
		current_test_case_result = 1;
		printf(".");
	}
}