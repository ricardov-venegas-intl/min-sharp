// min-sharp-runtime.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "test.h"



int main()
{
	system_services_tests();
	system_list_tests();
	managed_memory_services_tests();
	runtime_services_tests();
	runtime_number_tests();
}
