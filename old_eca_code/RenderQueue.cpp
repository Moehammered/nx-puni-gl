#include "RenderQueue.h"

puni::RenderQueue* puni::RenderQueue::_instance = nullptr;

puni::RenderQueue * const puni::RenderQueue::Instance()
{
	if (_instance)
		return _instance;
	
	_instance = new RenderQueue();

	return _instance;
}

void puni::RenderQueue::processRenderQueue()
{
	for (unsigned long i = 0; i < renderers.size(); ++i)
	{
		if (renderers[i]->isActive())
			renderers[i]->draw();
	}
}

// void puni::RenderQueue::processUIRenderQueue()
// {
// 	for (int i = 0; i < uiRenderers.size(); ++i)
// 	{
// 		if (uiRenderers[i]->isActive())
// 			uiRenderers[i]->draw();
// 	}
// }

puni::RenderQueue::RenderQueue()
{
	renderers.reserve(10);
}


puni::RenderQueue::~RenderQueue()
{
	delete _instance;
	_instance = nullptr;
}

void puni::RenderQueue::AddToQueue(RenderComponent * rendComp)
{
	renderers.push_back(rendComp);
}

// void puni::RenderQueue::AddToQueue(UIRenderComponent * rendComp)
// {
// 	uiRenderers.push_back(rendComp);
// }

void puni::RenderQueue::removeFromQueue(RenderComponent * rendComp)
{
	for (unsigned long i = 0; i < renderers.size(); ++i)
	{
		if (renderers[i]->id == rendComp->id)
		{
			renderers.erase(renderers.begin() + i);
			break;
		}
	}
}

void puni::RenderQueue::removeFromQueue(unsigned int id)
{
	for (unsigned long i = 0; i < renderers.size(); ++i)
	{
		if (renderers[i]->id == id)
		{
			renderers.erase(renderers.begin() + i);
			break;
		}
	}
}

// void puni::RenderQueue::removeFromQueue(UIRenderComponent * rendComp)
// {
// 	for (int i = 0; i < uiRenderers.size(); ++i)
// 	{
// 		if (uiRenderers[i]->id == rendComp->id)
// 		{
// 			uiRenderers.erase(uiRenderers.begin() + i);
// 			break;
// 		}
// 	}
// }
