#include "MeshRendererComponent.h"
#include "PrimitiveShapes.h"
#include "Camera.h"

puni::MeshRendererComponent::MeshRendererComponent()
{
}


puni::MeshRendererComponent::~MeshRendererComponent()
{
}

const puni::Mesh & puni::MeshRendererComponent::getMesh()
{
	// TODO: insert return statement here
	return mesh;
}

void puni::MeshRendererComponent::updateMaterialAttributes(const VertexAttributes * attribs, unsigned int count)
{
	if (material)
	{
		material->setAttributes(attribs, count);
		updateVAO();
	}
}

void puni::MeshRendererComponent::setMesh(const Mesh & newMesh)
{
	this->mesh = newMesh;
	//this->mesh.forceBufferPropertyUpdate();
	updateVAO();
}

void puni::MeshRendererComponent::setVertexData(const Vertex * newVerts, const GLuint vertCount)
{
	this->mesh.setVertices(newVerts, vertCount);
}

void puni::MeshRendererComponent::setIndexData(const int * newIndices, const GLuint indCount)
{
	this->mesh.setIndices(newIndices, indCount);
}

void puni::MeshRendererComponent::initialise()
{
	RenderComponent::initialise();
	PrimitiveShapes::CreateCube(mesh);
	updateVAO();
}

void puni::MeshRendererComponent::draw()
{
	if (material)
	{
		if (Camera::MainCamera)
		{
			/*printf("RenderComponent rendering[id:%i]\n", id);
			printf("RenderComponent owner[%s]\n", owner->toString().c_str());*/
			material->use();
			material->setTransformProperty("transform",
				Camera::MainCamera->ProjView() * owner->transform.TransformMat4());
			vao.bindVAO();
			glDrawElements(mesh.MeshType(), mesh.IndexCount(), GL_UNSIGNED_INT, 0);
			vao.unbind();
		}
	}
}

void puni::MeshRendererComponent::updateVAO()
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
	vao.setupAttributes(material->MaterialAttributes().data(), material->MaterialAttributes().size());
}
