#include "RenderComponent.h"

#include "RenderQueue.h"

void puni::RenderComponent::initialise()
{
	//add reference to the renderqueue for this component
	enabled = true;
	RenderQueue::Instance()->AddToQueue(this);
	material = new Material();
}

bool puni::RenderComponent::isActive()
{
	return enabled & owner->IsActive();
}

puni::RenderComponent::RenderComponent()
{
}

puni::RenderComponent::~RenderComponent()
{
	delete material;
	material = nullptr;
	printf("RenderComponent destructor called\n");
	RenderQueue::Instance()->removeFromQueue(id);
}
