#include "UpdateableComponent.h"

#include "ComponentUpdateQueue.h"
#include "Input.h"
#include <switch.h>

puni::UpdateableComponent::UpdateableComponent()
{
	//add itself to the update queue
	enabled = true;
	ComponentUpdateQueue::Instance()->AddToQueue(this);
}


puni::UpdateableComponent::~UpdateableComponent()
{
	printf("Removing from queue....\n");
	ComponentUpdateQueue::Instance()->removeFromQueue(this);
}

void puni::UpdateableComponent::update()
{
	if(Input::IsKeyPressed(KEY_MINUS))
		printf("Updateable component input found!\n\n");
}

bool puni::UpdateableComponent::isActive()
{
	return enabled & owner->IsActive();
}
