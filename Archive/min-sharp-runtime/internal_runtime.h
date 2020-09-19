#pragma once
#include "type_internals.h"

//Globals
extern min_sharp_type_info* object_type_info;
extern min_sharp_type_info* string_type_info;
extern min_sharp_type_info* number_type_info;
extern min_sharp_type_info* boolean_type_info;
extern min_sharp_type_info* function_type_info;
extern min_sharp_type_info* exception_type_info;
extern min_sharp_type_info* runtime_exception_type_info;
extern min_sharp_type_info* null_reference_exception_type_info;


extern void minsharp_init_runtime();
// internal not callable outside
extern min_sharp_memberid calculate_member_id(internal_string member_name);
extern min_sharp_object* internal_allocate_object(min_sharp_type_info typeinfo, int extra_data);
extern min_sharp_string* internal_build_string_constant(internal_string value);
extern function_call_result minsharp_runtime_exception(min_sharp_exception** new_exception, internal_string exception_type_name, internal_string exception_message);
extern function_call_result minsharp_null_reference_exception(min_sharp_exception** new_exception, internal_string exception_message);

extern function_call_result min_sharp_internal_object_builder_factory(min_sharp_object** exception, min_sharp_internal_object_builder** internal_object_builder);
