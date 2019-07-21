#ifndef SWITCH__RENDERCOMPONENT__H_
#define SWITCH__RENDERCOMPONENT__H_

#include "Component.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

namespace puni
{
	class RenderComponent :
		public Component
	{
	public:
		RenderComponent();
		~RenderComponent();

		bool enabled;
		
		Material* material;

		void initialise() override;
		bool isActive() override;
		virtual void draw() = 0;
	};
}
#endif