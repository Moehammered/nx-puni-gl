#ifndef SWITCH__MATERIAL__H_
#define SWITCH__MATERIAL__H_

#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include <glm\glm.hpp>
#include <string>
#include <vector>

namespace puni
{
	class Material
	{
	public:
		Material();
		Material(std::string vertexShaderPath, std::string fragmentShaderPath);
		Material(Shader* const preMadeShader);
		~Material();

		unsigned int shaderID();
		void loadShader(std::string vertP, std::string fragP);
		void setAttributes(const VertexAttributes* attribs, unsigned int attribCount);
		void setShader(Shader* const sh);
		void setTexture(Texture* const tx);
		void setIntProperty(std::string prop, int val);
		void setTransformProperty(std::string prop, glm::mat4 transform);
		void use();

		const std::vector<VertexAttributes> MaterialAttributes() const;

	private:
		Texture* texture;
		Shader* shader;
		std::vector<VertexAttributes> attributes;

		void createDefaultAttributes();
	};
}
#endif