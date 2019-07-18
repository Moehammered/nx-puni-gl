#ifndef COMPONENT__H_
#define COMPONENT__H_

namespace puni
{
	class Object;
	class GameObject; //resolves cyclical dependency (forward decleration)
}

#include "GameObject.h"

namespace puni
{
	class Component : public Object
	{
	public:
		friend class GameObject;
		friend class Object;
		GameObject* owner;

		virtual void initialise();

		bool isAttached();
		virtual bool isActive();

	private:
		static unsigned long ID_COUNTER;

	protected:
		Component();
		virtual ~Component();

	};
}

#endif