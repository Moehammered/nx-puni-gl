#pragma once
#include "VertexArrayObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

namespace puni
{
	class MeshRenderer
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		const Mesh& getMesh();
		void updateMaterialAttributes(const VertexAttributes* attribs, unsigned int count);
		void setMesh(const Mesh& newMesh);
        void setMaterial(const Material& newMaterial);
		void setVertexData(const Vertex* newVerts, const GLuint vertCount);
		void setIndexData(const int * newIndices, const GLuint indCount);
		void initialise();
		void draw(const Transform& transform);

	private:
		Mesh mesh;
		VertexArrayObject vao;
        Material material;

		void updateVAO();
	};
}
