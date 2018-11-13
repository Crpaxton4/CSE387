#version 430 core

#pragma optimize(off)
#pragma debug(on)

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat4 normalModelMatrix;
	mat4 viewingMatrix;
	mat4 projectionMatrix;
};


out vec3 vertexWorldPosition;
out vec3 vertexWorldNormal;
out vec2 TexCoord;

layout (location = 0) in vec3 vertexPosition; 
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;

void main()
{
	vec4 vPos = vec4(vertexPosition, 1.0f);

    // Calculate the position in clip coordinates
    gl_Position = projectionMatrix * viewingMatrix * modelMatrix * vPos;

	vertexWorldPosition = vec3(modelMatrix * vPos);

	vertexWorldNormal = mat3(normalModelMatrix) * vertexNormal;

	TexCoord = vertexTexCoord; 

} // end main

