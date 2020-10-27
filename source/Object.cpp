#include "Object.h"
#include <stdio.h>

void puni::Object::initialise()
{
	printf("\nI'm initialising myself\n");
}

void puni::Object::cleanup()
{
	printf("\nI'm cleaning myself up!\n");
}

puni::Object::Object()
{
	id = 0;
}

puni::Object::~Object()
{
	cleanup();
}
