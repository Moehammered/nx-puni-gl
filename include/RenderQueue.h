#ifndef SWITCH__RENDERQUEUE__H_
#define SWITCH__RENDERQUEUE__H_

#include <vector>
#include "RenderComponent.h"
// #include "UIRenderComponent.h"

namespace puni
{
	class RenderQueue
	{
	public:
		friend class RenderComponent;
		// friend class UIRenderComponent;
		static RenderQueue* const Instance();

		void processRenderQueue();
		void processUIRenderQueue();

	private:
		RenderQueue();
		~RenderQueue();

		void AddToQueue(RenderComponent* rendComp);
		// void AddToQueue(UIRenderComponent* rendComp);
		void removeFromQueue(RenderComponent* rendComp);
		void removeFromQueue(unsigned int id);
		// void removeFromQueue(UIRenderComponent* rendComp);
		std::vector<RenderComponent*> renderers;
		// std::vector<UIRenderComponent*> uiRenderers;

		static RenderQueue* _instance;
	};
}
#endif