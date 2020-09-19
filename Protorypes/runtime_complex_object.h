#pragma once

#include "../min-sharp-runtime.h"





// Object member
typedef struct
{
	min_sharp_memberid member_id;
	min_sharp_object* value;
} min_sharp_object_member;

typedef struct min_sharp_interface_struct {
	min_sharp_type_info* type_info;
	unsigned_int_16 number_of_members;
} min_sharp_interface;

typedef struct min_sharp_object_header_struct {
	unsigned_int_16 number_of_interfaces;
} min_sharp_object_header;