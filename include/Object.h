#ifndef SWITCH__OBJECT__H_
#define SWITCH__OBJECT__H_

namespace puni
{
	class ObjectAllocator;
}
// class GameObject;
// class RenderQueue;
// class ComponentUpdateQueue;

#include "ObjectAllocator.h"
#include <assert.h>
#include <type_traits>

namespace puni
{
	class Object
	{
	public:
		friend class ObjectAllocator;
		// friend class RenderQueue;
		// friend class ComponentUpdateQueue;
		virtual void initialise();
		virtual void cleanup();

		template <class O>
		static O & Instantiate();

	protected:
		unsigned long id;
		Object();
		virtual ~Object();
	};

	template<class O>
	inline O & Object::Instantiate()
	{
		assert((std::is_base_of<Object, O>::value));
		O* obj = new O();
		Object* casted = (Object*)obj;
		casted->id = ObjectAllocator::Instance()->GetID();
		obj->initialise();
		ObjectAllocator::Instance()->storeInstance(casted);

		return *obj;
	}

}

#endif