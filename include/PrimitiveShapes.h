#ifndef SWITCH__PRIMITIVESHAPES__H_
#define SWITCH__PRIMITIVESHAPES__H_

#include "Mesh.h"

namespace PrimitiveShapes
{
	void CreateCube(puni::Mesh& mesh);
	void CreateXYPlane(puni::Mesh & mesh);
	void CreateXZPlane(puni::Mesh & mesh);
	void CreateTriangle(puni::Mesh & mesh);
	void CreateSphere(puni::Mesh & mesh);
	void CreatePyramid(puni::Mesh & mesh);

	puni::Mesh CreateCube();
	puni::Mesh CreateXYPlane();
	puni::Mesh CreateXZPlane();
	puni::Mesh CreateTriangle();
	puni::Mesh CreateSphere();
	puni::Mesh CreatePyramid();
}
#endif