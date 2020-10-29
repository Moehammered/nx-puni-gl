#include "ComponentUpdateQueue.h"

puni::ComponentUpdateQueue* puni::ComponentUpdateQueue::_instance = nullptr;

puni::ComponentUpdateQueue * const puni::ComponentUpdateQueue::Instance()
{
	if (_instance)
		return _instance;

	_instance = new ComponentUpdateQueue();
	return _instance;
}

void puni::ComponentUpdateQueue::updateComponents()
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i])
		{
			if (components[i] != nullptr & components[i]->isActive())
				components[i]->update();
		}
	}
}

puni::ComponentUpdateQueue::ComponentUpdateQueue()
{
	components.reserve(20);
}


puni::ComponentUpdateQueue::~ComponentUpdateQueue()
{
	delete _instance;
	_instance = nullptr;
}

void puni::ComponentUpdateQueue::AddToQueue(UpdateableComponent * comp)
{
	components.push_back(comp);
}

void puni::ComponentUpdateQueue::removeFromQueue(UpdateableComponent * comp)
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i]->id == comp->id)
		{
			components.erase(components.begin() + i);
			break;
		}
	}
}

void puni::ComponentUpdateQueue::removeFromQueue(unsigned int id)
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i]->id == id)
		{
			components.erase(components.begin() + i);
			break;
		}
	}
}
