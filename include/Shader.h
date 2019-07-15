#ifndef SWITCH__SHADER__H_
#define SWITCH__SHADER__H_

#include <string>

namespace puni
{
	class Shader
	{
		public:
			Shader();
			//Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
			~Shader();

			unsigned int ID();
			void use();
			void compile(std::string vertexShaderPath, std::string fragmentShaderPath);
			void setBool(std::string paramName, bool value);
			void setFloat(std::string paramName, float value);
			void setInt(std::string paramName, int value);
			/*template <class ParamType>
			void setParameter(const std::string paramName, ParamType value);*/

		private:
			unsigned int shaderID;

			void clearShaderProgram();
	};
}

#endif
