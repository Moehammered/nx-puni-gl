#ifndef SWITCH__COMPONENTUPDATEQUEUE__H_
#define SWITCH__COMPONENTUPDATEQUEUE__H_

#include <vector>
#include "UpdateableComponent.h"

namespace puni
{
	class ComponentUpdateQueue
	{
	public:
		friend class UpdateableComponent;
		friend class FPSMovementComponent;
		static ComponentUpdateQueue* const Instance();

		void updateComponents();

	private:
		ComponentUpdateQueue();
		~ComponentUpdateQueue();

		void AddToQueue(UpdateableComponent* comp);
		void removeFromQueue(UpdateableComponent* comp);
		void removeFromQueue(unsigned int id);
		std::vector<UpdateableComponent*> components;

		static ComponentUpdateQueue* _instance;
	};
}
#endif