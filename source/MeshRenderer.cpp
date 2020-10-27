#include "MeshRenderer.h"
#include "PrimitiveShapes.h"
#include "Camera.h"

puni::MeshRenderer::MeshRenderer()
{
}


puni::MeshRenderer::~MeshRenderer()
{
	//printf("Destroying MeshRenderer.\n\n");
}

const puni::Mesh & puni::MeshRenderer::getMesh()
{
	// TODO: insert return statement here
	return mesh;
}

void puni::MeshRenderer::updateMaterialAttributes(const VertexAttributes * attribs, unsigned int count)
{
	if (count)
	{
		material.setAttributes(attribs, count);
		vao.setupAttributes(material.MaterialAttributes().data(), material.MaterialAttributes().size());
	}
}

void puni::MeshRenderer::setMesh(const Mesh & newMesh)
{
	this->mesh = newMesh;
	vao.setupBuffers(mesh.VertexBufferProperty().data(), mesh.VertexBufferProperty().size());
}

void puni::MeshRenderer::setMaterial(const Material & newMaterial)
{
	this->material = newMaterial;
	vao.setupAttributes(material.MaterialAttributes().data(), material.MaterialAttributes().size());
}

void puni::MeshRenderer::setVertexData(const Vertex * newVerts, const GLuint vertCount)
{
	this->mesh.setVertices(newVerts, vertCount);
	vao.setupBuffers(mesh.VertexBufferProperty().data(), mesh.VertexBufferProperty().size());
}

void puni::MeshRenderer::setIndexData(const int * newIndices, const GLuint indCount)
{
	this->mesh.setIndices(newIndices, indCount);
	vao.setupBuffers(mesh.VertexBufferProperty().data(), mesh.VertexBufferProperty().size());
}

void puni::MeshRenderer::initialise()
{
	PrimitiveShapes::CreateCube(mesh);
	updateVAO();
}

void puni::MeshRenderer::draw(const Transform& transform)
{
	if (Camera::MainCamera)
	{
		/*printf("RenderComponent rendering[id:%i]\n", id);
		printf("RenderComponent owner[%s]\n", owner->toString().c_str());*/
		material.use();
		material.setTransformProperty("transform",
			Camera::MainCamera->ProjView() * transform.TransformMat4());
		vao.bindVAO();
		glDrawElements(mesh.MeshType(), mesh.IndexCount(), GL_UNSIGNED_INT, 0);
		vao.unbind();
	}
}

void puni::MeshRenderer::updateVAO()
{
	/*BufferProperty buffers[] = {
			{
				GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.VertexCount(), mesh.Vertices(), GL_STATIC_DRAW
			},
			{
				GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.IndexCount(), mesh.Indices(), GL_STATIC_DRAW
			}
	};
	VertexAttributes attributes[] = {
		{
			0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::pos))
		},
		{
			1, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::colour))
		}
	};*/
	vao.setupBuffers(mesh.VertexBufferProperty().data(), mesh.VertexBufferProperty().size());
	vao.setupAttributes(material.MaterialAttributes().data(), material.MaterialAttributes().size());
}
