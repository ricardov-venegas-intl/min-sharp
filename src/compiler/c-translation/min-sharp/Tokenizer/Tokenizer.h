#pragma once
#include "../Runtime/Runtime.h"

typedef struct { 
	IObject __base;
	IString *Type;
	IString* Value;
} MinSharp_Compiler_Tokenizer_Token;


typedef struct 
{
	callSuccess (*Parse) (IException** __exception, IEnumerable** __result, IString *source);
} MinSharp_Compiler_Tokenizer_ITokenizer;