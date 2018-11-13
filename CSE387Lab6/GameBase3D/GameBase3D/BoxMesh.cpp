#include "BoxMesh.h"
#include "Renderer.h"

vec2 getBoxTextCoords(vec3 vertex, float halfHeight)
{
	float s = (vertex.z + halfHeight) / 2*halfHeight;

	float t = (vertex.y + halfHeight) / 2 * halfHeight;

	return vec2(s, t);
}


BoxMesh::BoxMesh(float width, float height, float depth)
	: halfWidth(width / 2), halfHeight(height / 2), halfDepth(depth / 2)
{
}


bool BoxMesh::Load(const std::string & fileName, Material material)
{
	std::vector<pntVertexData> vData;
	std::vector<unsigned int> indices;

	vec3 v1(-halfWidth, -halfHeight, halfDepth);
	vec3 v2(halfWidth, -halfHeight, halfDepth);
	vec3 v3(halfWidth, halfHeight, halfDepth);
	vec3 v4(-halfWidth, halfHeight, halfDepth);
	vec3 v5(-halfWidth, -halfHeight, -halfDepth);
	vec3 v6(halfWidth, -halfHeight, -halfDepth);
	vec3 v7(halfWidth, halfHeight, -halfDepth);
	vec3 v8(-halfWidth, halfHeight, -halfDepth);

	vec3 n1(0, 0, 1);
	vec3 n2(0, 0, -1);
	vec3 n3(1, 0, 0);
	vec3 n4(-1, 0, 0);
	vec3 n5(0, -1, 0);
	vec3 n6(0, 1, 0);

	// front face
	vData.push_back(pntVertexData(v1, n1, getBoxTextCoords(v1, halfHeight)));
	vData.push_back(pntVertexData(v2, n1, getBoxTextCoords(v2, halfHeight)));
	vData.push_back(pntVertexData(v3, n1, getBoxTextCoords(v3, halfHeight)));
	vData.push_back(pntVertexData(v4, n1, getBoxTextCoords(v4, halfHeight)));

	// right face
	vData.push_back(pntVertexData(v2, n3, getBoxTextCoords(v2, halfHeight)));
	vData.push_back(pntVertexData(v6, n3, getBoxTextCoords(v6, halfHeight)));
	vData.push_back(pntVertexData(v7, n3, getBoxTextCoords(v7, halfHeight)));
	vData.push_back(pntVertexData(v3, n3, getBoxTextCoords(v3, halfHeight)));

	// left face
	vData.push_back(pntVertexData(v5, n4, getBoxTextCoords(v5, halfHeight)));
	vData.push_back(pntVertexData(v1, n4, getBoxTextCoords(v1, halfHeight)));
	vData.push_back(pntVertexData(v4, n4, getBoxTextCoords(v4, halfHeight)));
	vData.push_back(pntVertexData(v8, n4, getBoxTextCoords(v8, halfHeight)));

	// back face
	vData.push_back(pntVertexData(v5, n2, getBoxTextCoords(v5, halfHeight)));
	vData.push_back(pntVertexData(v6, n2, getBoxTextCoords(v6, halfHeight)));
	vData.push_back(pntVertexData(v7, n2, getBoxTextCoords(v7, halfHeight)));
	vData.push_back(pntVertexData(v8, n2, getBoxTextCoords(v8, halfHeight)));

	// top
	vData.push_back(pntVertexData(v4, n6, getBoxTextCoords(v4, halfHeight)));
	vData.push_back(pntVertexData(v3, n6, getBoxTextCoords(v3, halfHeight)));
	vData.push_back(pntVertexData(v7, n6, getBoxTextCoords(v7, halfHeight)));
	vData.push_back(pntVertexData(v8, n6, getBoxTextCoords(v8, halfHeight)));

	// bot
	vData.push_back(pntVertexData(v6, n5, getBoxTextCoords(v6, halfHeight)));
	vData.push_back(pntVertexData(v2, n5, getBoxTextCoords(v2, halfHeight)));
	vData.push_back(pntVertexData(v1, n5, getBoxTextCoords(v1, halfHeight)));
	vData.push_back(pntVertexData(v5, n5, getBoxTextCoords(v5, halfHeight)));

	// Push back the indices for each face
	for (int i = 0; i < 6; i++) {
		indices.push_back(0 + 4 * i);
		indices.push_back(1 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(2 + 4 * i);
		indices.push_back(3 + 4 * i);
		indices.push_back(0 + 4 * i);
	}

	VertexArray * va = new VertexArray(vData, indices);

	mVertexArrays.push_back(va);

	va->vaoMaterial = material;

	return true;

}
