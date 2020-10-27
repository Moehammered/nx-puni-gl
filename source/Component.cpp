#include "Component.h"

#include <limits>

unsigned long puni::Component::ID_COUNTER = ULONG_MAX;

puni::Component::Component()
{
	id = --ID_COUNTER;
	owner = nullptr;
}

puni::Component::~Component()
{
	printf("Base component destructor called\n");
}

void puni::Component::initialise()
{
}

bool puni::Component::isAttached()
{
	return owner != nullptr;
}

bool puni::Component::isActive()
{
	return owner->IsActive();
}
