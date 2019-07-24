#include "Mesh.h"

#include <glad\glad.h>
#include <stdio.h>

puni::Mesh::Mesh()
{
	triangleCount = 0;
	meshType = GL_TRIANGLES;
	BufferProperty bf[] = {
			{
				GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vertex) * VertexCount()), Vertices(), GL_STATIC_DRAW
			},
			{
				GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(GLuint) * IndexCount()), Indices(), GL_STATIC_DRAW
			}
	};
	buffers.insert(buffers.begin(), bf, bf + 2);
}

puni::Mesh::Mesh(const Mesh & mesh)
{
	this->buffers = mesh.buffers;
	this->meshType = mesh.meshType;
	this->triangleCount = mesh.triangleCount;
	setVertices(mesh.vertices.data(), mesh.vertices.size());
	setIndices(mesh.indices.data(), mesh.indices.size());
	printf("Mesh copy constructor called.\n\n");
}

void puni::Mesh::operator=(const Mesh& mesh)
{
	this->buffers = mesh.buffers;
	this->meshType = mesh.meshType;
	this->triangleCount = mesh.triangleCount;
	setVertices(mesh.vertices.data(), mesh.vertices.size());
	setIndices(mesh.indices.data(), mesh.indices.size());
	printf("Mesh assignment operator called.\n\n");
}

puni::Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
}

void puni::Mesh::setVertices(const Vertex * vertices, unsigned int vertexCount)
{
	updateFlag = updateFlag | VERT_BUFFER_DATA_BIT;
	if (vertexCount > this->vertices.size())
		updateFlag = updateFlag | VERT_BUFFER_SIZE_BIT;
	this->vertices.clear();
	this->vertices.reserve(vertexCount);
	this->vertices.insert(this->vertices.begin(), vertices, vertices + vertexCount);

	updateBufferProperties();
}

void puni::Mesh::setIndices(const int * indices, unsigned int indexCount)
{
	updateFlag = updateFlag | ELEM_BUFFER_DATA_BIT;
	if (indexCount > this->indices.size())
		updateFlag = updateFlag | ELEM_BUFFER_SIZE_BIT;
	this->indices.clear();
	this->indices.reserve(indexCount);
	this->indices.insert(this->indices.begin(), indices, indices + indexCount);

	triangleCount = meshType == GL_TRIANGLES ? indexCount / 3 : indexCount - 2;

	updateBufferProperties();
}

void puni::Mesh::useTriangleList()
{
	meshType = GL_TRIANGLES;
	triangleCount = indices.size() / 3;
}

void puni::Mesh::useTriangleStrip()
{
	meshType = GL_TRIANGLE_STRIP;
	triangleCount = indices.size() - 2;
}

void puni::Mesh::forceBufferPropertyUpdate()
{
	updateFlag = updateFlag | VERT_ELEM_DATA_BITS;
	updateFlag = updateFlag | VERT_ELEM_SIZE_BITS;
	updateBufferProperties();
}

unsigned int puni::Mesh::IndexCount()
{
	return indices.size();
}

unsigned int puni::Mesh::VertexCount()
{
	return vertices.size();
}

unsigned int puni::Mesh::TriangleCount()
{
	return triangleCount;
}

unsigned int puni::Mesh::MeshType()
{
	return meshType;
}

const std::vector<puni::BufferProperty> puni::Mesh::VertexBufferProperty() const
{
	return buffers;
}

const puni::Vertex * const puni::Mesh::Vertices()
{
	return vertices.data();
}

const int * const puni::Mesh::Indices()
{
	return indices.data();
}

void puni::Mesh::updateBufferProperties()
{
	///flags seem unnecessary????
		///maybe move them into VAO instead as it can actually
		///perform changes to state that are costly
	if (updateFlag & 0x0)
		return; //nothing to update(no flag set)

	//if the size of the buffers needs updating (glBufferData)
	if (updateFlag & VERT_ELEM_SIZE_BITS)
	{
		if (updateFlag & VERT_BUFFER_SIZE_BIT)
		{
			//update vertexbuffer size
			buffers[0].bufferSize = VertexCount() * sizeof(Vertex);
		}
		if (updateFlag & ELEM_BUFFER_SIZE_BIT)
		{
			//update element buffer size
			buffers[1].bufferSize = IndexCount() * sizeof(unsigned int);
		}
	}

	if (updateFlag & VERT_BUFFER_DATA_BIT)
	{
		//update vert data
		buffers[0].data = Vertices();
	}
	if (updateFlag & ELEM_BUFFER_DATA_BIT)
	{
		//update elem data
		buffers[1].data = Indices();
	}

	//clear the flags
	updateFlag = 0x0;
}
