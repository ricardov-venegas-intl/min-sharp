#include "min-sharp-runtime.h"
#include "services/runtime_services.h"
#include "services/internal/system_services.h"
#include "services/internal/managed_memory_services.h"
#include "min_sharp-runtime-support.h"
#include "Types/runtime_number.h"
#include "Types/runtime_function.h"

void initialize_runtime(runtime_services** runtime_services_instance)
{
	system_services* system_services_instance;
	managed_memory_services* managed_memory_services_instance;
	runtime_services* new_runtime_services_instance;
	function_call_result fcr;

	// validate input
	if (min_sharp_null == runtime_services_instance)
	{
		goto fail;
	}

	// Create require services
	fcr = system_services_factory(&system_services_instance);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	fcr = managed_memory_services_factory(system_services_instance, 
		&managed_memory_services_instance);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Create runtime services instance
	fcr= runtime_services_factory(system_services_instance,
			managed_memory_services_instance,
			&new_runtime_services_instance);
	if (function_call_result_fail == fcr)
	{
		goto fail;
	}

	// Types self registration
	register_number_type(system_services_instance, new_runtime_services_instance);


	register_function_type(system_services_instance, new_runtime_services_instance);

	*runtime_services_instance = new_runtime_services_instance;
	return;

fail:
	abort_with_message("CRITICAl ERROR: initialize_runtime Failed");
}