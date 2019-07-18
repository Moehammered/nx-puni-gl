#include "PrimitiveShapes.h"

namespace PrimitiveShapes
{
	void CreateCube(puni::Mesh & mesh)
	{
		mesh.useTriangleList();
		puni::Vertex vertices[16];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0.5f);	//FTL
		vertices[0].col = glm::vec3(1.0f);
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0.5f);//FBL
		vertices[1].col = glm::vec3(1.0f);
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0.5f, 0.5f);	//FTR
		vertices[2].col = glm::vec3(1.0f);
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, -0.5f, 0.5f);	//FBR
		vertices[3].col = glm::vec3(1.0f);
		vertices[3].uv = glm::vec2(1, 0);

		vertices[4].pos = glm::vec3(0.5f, 0.5f, -0.5f);	//BTR
		vertices[4].col = glm::vec3(1.0f);
		vertices[4].uv = glm::vec2(0, 1);
		vertices[5].pos = glm::vec3(0.5f, -0.5f, -0.5f);//BBR
		vertices[5].col = glm::vec3(1.0f);
		vertices[5].uv = glm::vec2(0, 0);
		vertices[6].pos = glm::vec3(-0.5f, 0.5f, -0.5f);//BTL
		vertices[6].col = glm::vec3(1.0f);
		vertices[6].uv = glm::vec2(1, 1);
		vertices[7].pos = glm::vec3(-0.5f, -0.5f, -0.5f);//BBL
		vertices[7].col = glm::vec3(1.0f);
		vertices[7].uv = glm::vec2(1, 0);

		//make the top face unique to correct the UVs
		vertices[8].pos = vertices[6].pos;				//BTL
		vertices[8].col = glm::vec3(1.0f);
		vertices[8].uv = glm::vec2(0, 1);
		vertices[9].pos = vertices[0].pos;				//FTL
		vertices[9].col = glm::vec3(1.0f);
		vertices[9].uv = glm::vec2(0, 0);
		vertices[10].pos = vertices[2].pos;				//FTR
		vertices[10].col = glm::vec3(1.0f);
		vertices[10].uv = glm::vec2(1, 0);
		vertices[11].pos = vertices[4].pos;				//BTR
		vertices[11].col = glm::vec3(1.0f);
		vertices[11].uv = glm::vec2(1, 1);

		//make the bottom face unique to correct the UVs
		vertices[12].pos = vertices[3].pos;				//FBR
		vertices[12].col = glm::vec3(1.0f);
		vertices[12].uv = glm::vec2(1, 0);
		vertices[13].pos = vertices[1].pos;				//FBL
		vertices[13].col = glm::vec3(1.0f);
		vertices[13].uv = glm::vec2(0, 0);
		vertices[14].pos = vertices[7].pos;				//BBL
		vertices[14].col = glm::vec3(1.0f);
		vertices[14].uv = glm::vec2(0, 1);
		vertices[15].pos = vertices[5].pos;				//BBR
		vertices[15].col = glm::vec3(1.0f);
		vertices[15].uv = glm::vec2(1, 1);


		//setup the indices
		int indices[36]{
			0, 1, 2,	//1st tri //front face
			2, 1, 3,	//2nd tri

			4, 2, 3,	//1st tri //right face
			4, 3, 5,	//2nd tri

			4, 5, 6,	//1st tri //back face
			5, 7, 6,	//2nd tri

			0, 6, 7,	//1st tri //left face
			0, 7, 1,	//2nd tri

			//6, 0, 2,	//1st tri //top face - warped uvs
			//6, 2, 4,	//2nd tri
			8, 9, 10,	//1st tri //top face
			8, 10, 11,	//2nd tri


			//3, 1, 7,	//1st tri //bottom face - warped uvs
			//3, 7, 5	//2nd tri
			12, 13, 14,	//1st tri //bottom face
			12, 14, 15	//2nd tri
		};

		mesh.setVertices(vertices, 16);
		mesh.setIndices(indices, 36);
	}

	void CreateXYPlane(puni::Mesh & mesh)
	{
		mesh.useTriangleList();
		puni::Vertex vertices[4];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0); //TL
		//vertices[0].col = col::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0.5f, 0); //TR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, -0.5f, 0); //BR
		vertices[3].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[6]{
			0, 1, 2,	//1st tri
			2, 1, 3		//2nd tri
		};

		mesh.setVertices(vertices, 4);
		mesh.setIndices(indices, 6);
		//mesh.updateMesh();
	}

	void CreateXZPlane(puni::Mesh & mesh)
	{
		mesh.useTriangleList();
		puni::Vertex vertices[4];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0, -0.5f); //TL
		//vertices[0].col = col::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, 0, 0.5f); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0, -0.5f); //TR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, 0, 0.5f); //BR
		vertices[3].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[6]{
			0, 1, 2,	//1st tri
			2, 1, 3		//2nd tri
		};

		mesh.setVertices(vertices, 4);
		mesh.setIndices(indices, 6);
		//mesh.updateMesh();
	}

	void CreateTriangle(puni::Mesh & mesh)
	{
		mesh.useTriangleList();
		puni::Vertex vertices[3];
		//setup the positions
		vertices[0].pos = glm::vec3(0, 0.5f, 0); //TM
		//vertices[0].col = col::Blue();
		vertices[0].uv = glm::vec2(0.5f, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, -0.5f, 0); //BR
		vertices[2].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[3]{
			0, 1, 2	//1st tri
		};

		mesh.setVertices(vertices, 3);
		mesh.setIndices(indices, 3);
		//mesh.updateMesh();
	}

	void CreateSphere(puni::Mesh & mesh)
	{
		//not yet implemented
	}

	void CreatePyramid(puni::Mesh & mesh)
	{
		//not yet implemented
	}

	puni::Mesh CreateCube()
	{
		puni::Mesh mesh;
		mesh.useTriangleList();
		puni::Vertex vertices[16];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0.5f);	//FTL
		vertices[0].col = glm::vec3(1.0f);
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0.5f);//FBL
		vertices[1].col = glm::vec3(1.0f);
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0.5f, 0.5f);	//FTR
		vertices[2].col = glm::vec3(1.0f);
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, -0.5f, 0.5f);	//FBR
		vertices[3].col = glm::vec3(1.0f);
		vertices[3].uv = glm::vec2(1, 0);

		vertices[4].pos = glm::vec3(0.5f, 0.5f, -0.5f);	//BTR
		vertices[4].col = glm::vec3(1.0f);
		vertices[4].uv = glm::vec2(0, 1);
		vertices[5].pos = glm::vec3(0.5f, -0.5f, -0.5f);//BBR
		vertices[5].col = glm::vec3(1.0f);
		vertices[5].uv = glm::vec2(0, 0);
		vertices[6].pos = glm::vec3(-0.5f, 0.5f, -0.5f);//BTL
		vertices[6].col = glm::vec3(1.0f);
		vertices[6].uv = glm::vec2(1, 1);
		vertices[7].pos = glm::vec3(-0.5f, -0.5f, -0.5f);//BBL
		vertices[7].col = glm::vec3(1.0f);
		vertices[7].uv = glm::vec2(1, 0);

		//make the top face unique to correct the UVs
		vertices[8].pos = vertices[6].pos;				//BTL
		vertices[8].col = glm::vec3(1.0f);
		vertices[8].uv = glm::vec2(0, 1);
		vertices[9].pos = vertices[0].pos;				//FTL
		vertices[9].col = glm::vec3(1.0f);
		vertices[9].uv = glm::vec2(0, 0);
		vertices[10].pos = vertices[2].pos;				//FTR
		vertices[10].col = glm::vec3(1.0f);
		vertices[10].uv = glm::vec2(1, 0);
		vertices[11].pos = vertices[4].pos;				//BTR
		vertices[11].col = glm::vec3(1.0f);
		vertices[11].uv = glm::vec2(1, 1);

		//make the bottom face unique to correct the UVs
		vertices[12].pos = vertices[3].pos;				//FBR
		vertices[12].col = glm::vec3(1.0f);
		vertices[12].uv = glm::vec2(1, 0);
		vertices[13].pos = vertices[1].pos;				//FBL
		vertices[13].col = glm::vec3(1.0f);
		vertices[13].uv = glm::vec2(0, 0);
		vertices[14].pos = vertices[7].pos;				//BBL
		vertices[14].col = glm::vec3(1.0f);
		vertices[14].uv = glm::vec2(0, 1);
		vertices[15].pos = vertices[5].pos;				//BBR
		vertices[15].col = glm::vec3(1.0f);
		vertices[15].uv = glm::vec2(1, 1);


		//setup the indices
		int indices[36]{
			0, 1, 2,	//1st tri //front face
			2, 1, 3,	//2nd tri

			4, 2, 3,	//1st tri //right face
			4, 3, 5,	//2nd tri

			4, 5, 6,	//1st tri //back face
			5, 7, 6,	//2nd tri

			0, 6, 7,	//1st tri //left face
			0, 7, 1,	//2nd tri

			//6, 0, 2,	//1st tri //top face - warped uvs
			//6, 2, 4,	//2nd tri
			8, 9, 10,	//1st tri //top face
			8, 10, 11,	//2nd tri


			//3, 1, 7,	//1st tri //bottom face - warped uvs
			//3, 7, 5	//2nd tri
			12, 13, 14,	//1st tri //bottom face
			12, 14, 15	//2nd tri
		};

		mesh.setVertices(vertices, 16);
		mesh.setIndices(indices, 36);

		return mesh;
	}

	puni::Mesh CreateXYPlane()
	{
		puni::Mesh mesh;
		mesh.useTriangleList();
		puni::Vertex vertices[4];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0.5f, 0); //TL
		//vertices[0].col = col::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0.5f, 0); //TR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, -0.5f, 0); //BR
		vertices[3].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[6]{
			0, 1, 2,	//1st tri
			2, 1, 3		//2nd tri
		};

		mesh.setVertices(vertices, 4);
		mesh.setIndices(indices, 6);
		//mesh.updateMesh();

		return mesh;
	}

	puni::Mesh CreateXZPlane()
	{
		puni::Mesh mesh;
		mesh.useTriangleList();
		puni::Vertex vertices[4];
		//setup the positions
		vertices[0].pos = glm::vec3(-0.5f, 0, -0.5f); //TL
		//vertices[0].col = col::Blue();
		vertices[0].uv = glm::vec2(0, 1);
		vertices[1].pos = glm::vec3(-0.5f, 0, 0.5f); //BL
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, 0, -0.5f); //TR
		vertices[2].uv = glm::vec2(1, 1);
		vertices[3].pos = glm::vec3(0.5f, 0, 0.5f); //BR
		vertices[3].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[6]{
			0, 1, 2,	//1st tri
			2, 1, 3		//2nd tri
		};

		mesh.setVertices(vertices, 4);
		mesh.setIndices(indices, 6);
		//mesh.updateMesh();

		return mesh;
	}

	puni::Mesh CreateTriangle()
	{
		puni::Mesh mesh;
		mesh.useTriangleList();
		puni::Vertex vertices[3];
		//setup the positions
		vertices[0].pos = glm::vec3(0, 0.5f, 0); //TM
		vertices[0].col = glm::vec3(1);
		vertices[0].uv = glm::vec2(0.5f, 1);
		vertices[1].pos = glm::vec3(-0.5f, -0.5f, 0); //BL
		vertices[1].col = glm::vec3(1);
		vertices[1].uv = glm::vec2(0, 0);
		vertices[2].pos = glm::vec3(0.5f, -0.5f, 0); //BR
		vertices[2].col = glm::vec3(1);
		vertices[2].uv = glm::vec2(1, 0);

		//setup the indices
		int indices[3]{
			0, 1, 2	//1st tri
		};

		mesh.setVertices(vertices, 3);
		mesh.setIndices(indices, 3);
		//mesh.updateMesh();

		return mesh;
	}

	//not yet implemented
	puni::Mesh CreateSphere()
	{
		return puni::Mesh();
	}

	//not yet implemented
	puni::Mesh CreatePyramid()
	{
		return puni::Mesh();
	}
}