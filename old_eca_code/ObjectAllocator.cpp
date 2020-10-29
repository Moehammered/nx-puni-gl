#include "ObjectAllocator.h"

puni::ObjectAllocator* puni::ObjectAllocator::_instance = nullptr;

puni::ObjectAllocator * const puni::ObjectAllocator::Instance()
{
	if (_instance)
		return _instance;

	_instance = new ObjectAllocator();
	return _instance;
}

void puni::ObjectAllocator::addToDestroyQueue(Object * obj)
{
	destroyQueue.push_back(obj);
}

void puni::ObjectAllocator::processDestroyQueue()
{
	for (unsigned long i = 0; i < destroyQueue.size(); ++i)
	{
		if (destroyQueue[i] != nullptr)
		{
			for (unsigned long k = 0; k < instanceList.size(); ++k)
			{
				if (instanceList[k]->id == destroyQueue[i]->id)
				{
					instanceList.erase(instanceList.begin() + k);
					delete destroyQueue[i];
					destroyQueue[i] = nullptr;
					break;
				}
			}
		}
	}

	destroyQueue.clear();
}

puni::ObjectAllocator::ObjectAllocator()
{
	ID_COUNTER = 0;
	instanceList.reserve(30);
}

puni::ObjectAllocator::~ObjectAllocator()
{
	for (unsigned long i = 0; i < instanceList.size(); ++i)
	{
		delete instanceList[i];
	}

	instanceList.clear();
}

unsigned long puni::ObjectAllocator::GetID()
{
	return ID_COUNTER++;
}

void puni::ObjectAllocator::storeInstance(Object * inst)
{
	instanceList.push_back(inst);
}
