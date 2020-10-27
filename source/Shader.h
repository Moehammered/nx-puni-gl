#ifndef SWITCH__SHADER__H_
#define SWITCH__SHADER__H_

#include <string>
#include <unordered_map>

namespace puni
{
	struct MAT_HASH
	{
		template<class A, class B>
		std::size_t operator () (const std::pair<A,B> &p) const{
			auto h1 = std::hash<A>{}(p.first);
			auto h2 = std::hash<B>{}(p.second);

			return h1 ^ h2;
		}
	};

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

			static void CleanUpShaderCache();
		private:
			unsigned int shaderID;

			static std::unordered_map<std::string, int> SHADER_CACHE;
			static std::unordered_map<int64_t, int> MATERIAL_CACHE;
	};
}

#endif
