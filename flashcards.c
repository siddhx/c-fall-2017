if (condition1)
{
	// code;
}

else if (condition2)
{
	// code;
}

else 
{
	// code;
}

switch (OPERAND)
{

	case CONSTANT1:
	
		// code;
		break;

	case CONSTANT2:

		// code;
		break;

	default: 

		//code;
}

while (TEST) 
{
	// code;
}

while (TEST)
{

	if(CONDITION)
	{

		continue;
	}

	// code;
}

while (TEST) 
{

	if (CONDITION) 
	{

		break;
	}

	// code;
}

do 
{

	// code;
} 

while(TEST);

for (INIT; TEST, POST) 
{
	// CODE;
}

for (int i = 0; i < count; ++i)
{
	/* code */
}

enum { CONST1, CONST2, CONST3} NAME;

if (ERROR_TEST) 
{
	goto fail;
}

fail:
	// CODE;

// FUNCTION
TYPE NAME (ARG1, ARG2, ...) 
{
	
	// CODE;

	return VALUE;

}

int name(arg1, arg2 )
{
	CODE;

	return 0;
}

typedef DEFINITION IDENTIFIER;

typedef unsigned char byte;

struct NAME
{
	ELEMENTS;
} [VARIABLE_NAME];

struct $
{
	
};

typedef struct [STRUCT_NAME]
{
	ELEMENTS

} IDENTIFIER;



union NAME
{
	ELEMENTS;

} [VARIABLE_NAME];