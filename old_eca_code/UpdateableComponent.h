#ifndef SWITCH__UPDATEABLECOMPONENT__H_
#define SWITCH__UPDATEABLECOMPONENT__H_

#include "Component.h"

namespace puni
{
	class UpdateableComponent :
		public Component
	{
	public:
		UpdateableComponent();
		~UpdateableComponent();

		bool enabled;

		virtual void update();
		bool isActive() override;
	};
}
#endif