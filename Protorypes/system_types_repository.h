#pragma once
#include "min-sharp-runtime.h"
#include "system_services.h"
#include "system_unmanaged_data_manager.h"

static const internal_string object_type_name = "Object";
static const internal_string string_type_name = "String";
static const internal_string number_type_name = "Number";
static const internal_string boolean_type_name = "Boolean";
static const internal_string function_type_name = "Function";
static const internal_string exception_type_name = "Exception";
static const internal_string runtime_exception_type_name = "RuntimeException";
static const internal_string null_reference_exception_type_name = "NullReferenceException";


typedef struct system_types_repository_struct system_types_repository;
typedef struct system_repository_data_struct system_repository_data;

// member info
typedef struct
{
	min_sharp_memberid member_id;
	internal_string member_name;
	internal_string member_type;
} min_sharp_member_info;

// type info
typedef struct
{
	internal_string interface_name;
	internal_string parent_interface_name;
	unsigned_int_16 number_of_members;
	min_sharp_member_info members[1];
} min_sharp_type_info;

typedef struct system_types_repository_struct
{
	function_call_result(*register_type_info)(system_types_repository* this_instance, min_sharp_type_info* type_info, internal_string type_name);
	function_call_result(*get_type_info)(system_types_repository* this_instance, min_sharp_type_info** type_info, internal_string type_name);
	function_call_result (*release)(system_types_repository *this_instance);
	system_repository_data *data;
} system_types_repository;


extern function_call_result system_repository_factory(system_types_repository** repository, system_services* system_services_instance, system_unmanaged_data_manager * unmanaged_data_manager);