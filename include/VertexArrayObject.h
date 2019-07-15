#ifndef SWITCH__VAO__H_
#define SWITCH__VAO__H_

#include <glad\glad.h>
#include <vector>

namespace puni
{
	struct VertexAttributes
	{
		//where in the attribute is it located? (location=? from shader)
		GLuint		position;
		//amount of components in the attribute (x,y,z) = 3. (u,v) = 2, etc
		GLint		componentCount;
		//what data type is it?
		GLenum		type;
		//is the data already within normalised values?
		GLboolean	normalised;
		//how far till the next attribute from this vertex to the next vertex data
		GLsizei		stride;
		//location within a single vertex
		const GLvoid *	componentOffset;
	};

	struct BufferProperty
	{
		GLenum		bufferTarget;
		GLsizeiptr	bufferSize;
		const GLvoid *	data;
		GLenum		usage;
	};

	class VertexArrayObject
	{
		public:
			VertexArrayObject();
			~VertexArrayObject();

			void setupBuffers(const BufferProperty * const properties, GLuint propertyCount);
			void setupAttributes(const VertexAttributes * const attributes, GLuint attribCount);
			void enableAttribute(GLuint attribNumber);
			void disableAttribute(GLuint attribNumber);
			void resizeBuffer(GLenum target, GLsizeiptr newSize);
			void copyDataToBuffer(GLenum target, const GLvoid * data, GLsizeiptr dataSize);
			void bindVAO();
			void bindVBO();
			void bindEBO();
			void unbind();

			const std::vector<BufferProperty>& Properties();
			const std::vector<VertexAttributes>& Attributes();
		private:
			GLuint vao, vbo, ebo;
			unsigned int VBO_INDEX, EBO_INDEX; //this needs to be removed somehow... :/
			std::vector<BufferProperty> properties;
			std::vector<VertexAttributes> attributes;
			void initialise();
			void printBufferProperty(const BufferProperty& prop);
			void printVertexAttribute(VertexAttributes& attr);
	};

}
#endif