#include "PlaneMesh.h"

PlaneMesh::PlaneMesh(float width, float height) 
	: halfWidth(width / 2.0f),halfHeight(height / 2.0f) {

}

bool PlaneMesh::Load(const std::string &fileName, Material material) {
	std::vector<pntVertexData> vData;
	std::vector<unsigned int> indices;

	vec3 v1(-halfWidth, -halfHeight, 0.0f); //-x, -y
	vec3 v2(halfWidth, -halfHeight, 0.0f);  //+x, -y
	vec3 v3(halfWidth, halfHeight, 0.0f);	//+x, +y
	vec3 v4(-halfWidth, halfHeight, 0.0f);	//-x, +y

	vec3 n1(0, 0, 1); //face positive z direction

	vec2 t1(0, 6);
	vec2 t2(8, 6);
	vec2 t3(8, 0);
	vec2 t4(0, 0);

	// front face
	vData.push_back(pntVertexData(v1, n1, t4));
	vData.push_back(pntVertexData(v2, n1, t3));
	vData.push_back(pntVertexData(v3, n1, t2));
	vData.push_back(pntVertexData(v4, n1, t1));

	// index the vertecies
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	VertexArray * va = new VertexArray(vData, indices);

	mVertexArrays.push_back(va);

	va->vaoMaterial = material;

	return true;
}