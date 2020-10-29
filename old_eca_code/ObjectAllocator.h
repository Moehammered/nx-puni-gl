#ifndef SWITCH__OBJECTALLOCATOR__H_
#define SWITCH__OBJECTALLOCATOR__H_

namespace puni
{
	class Object;
}
#include <vector>

namespace puni
{
	class ObjectAllocator
	{
	public:
		friend class Object;
		static ObjectAllocator* const Instance();

		void addToDestroyQueue(Object* obj);
		void processDestroyQueue();

	private:
		ObjectAllocator();
		~ObjectAllocator();

		unsigned long ID_COUNTER;
		unsigned long GetID();
		void storeInstance(Object* inst);
		std::vector<Object*> instanceList;
		std::vector<Object*> destroyQueue;
		static ObjectAllocator* _instance;
	};
}

//literally moving this to the bottom fixed the damn cyclical dependency.... fucks sake xD
#include "Object.h" 

#endif