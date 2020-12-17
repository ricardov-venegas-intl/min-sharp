#pragma once

__declspec(noreturn) extern void abort_with_message(char* message);

#define CRITICAL_ASSERT(condition) { if ((int)(condition) == 0) { abort_with_message("CRITICAL_ASSERT FAILED"); } }

#define VALIDATE_ARGUMENT(condition, argument_name) { \
	if (((int)(condition)) == 0)\
	{\
		fcr = runtime->system_argument_exception(runtime, returned_exception, argument_name);\
		if (function_call_result_success != fcr) { abort_with_message("runtime->system_argument_exception FAILED");  }\
		goto fail;\
	}\
}

#define VALIDATE_ARGUMENT_NOTNULL(runtime, argument_object, argument_name) { \
	if (min_sharp_null == argument_object) \
	{\
		function_call_result fcr; \
		fcr = runtime->system_argument_null_exception(runtime, returned_exception, argument_name);\
		if (function_call_result_success != fcr) \
		{ \
			abort_with_message("runtime->system_argument_null_exception FAILED");\
		};\
		goto fail;\
	}\
}

#define VALIDATE_ARGUMENT_TYPE(runtime, argument_object, argument_type, argument_name) { \
	min_sharp_object_type argument_object_type; \
	function_call_result fcr;\
	fcr = argument_object->object_intrinsicts->get_object_type(argument_object, &argument_object_type);\
	if (function_call_result_fail == fcr)\
	{\
		fcr = runtime->system_argument_exception(runtime, returned_exception, argument_name);\
		if (function_call_result_success != fcr) { abort_with_message("runtime->system_argument_exception FAILED"); }\
		goto fail;\
	}\
	if (argument_type == argument_object_type)\
	{\
		fcr = runtime->system_argument_exception(runtime, returned_exception, argument_name);\
		if (function_call_result_success != fcr) { abort_with_message("runtime->system_argument_exception FAILED"); }\
		goto fail;\
	}\
}

#define VALIDATE_RETURNED_EXCEPTION() \
{ \
  if ((min_sharp_null == returned_exception) \
	  || (min_sharp_null == *returned_exception)) \
  { \
	  abort_with_message("VALIDATE_RETURNED_EXCEPTION FAILED"); \
  } \
}