#version 430 core

#pragma optimize(off)
#pragma debug(on)

const int MaxLights = 8;

// Structure for holding general light properties
struct GeneralLight {
  
	vec4 ambientColor;		// ambient color of the light
	vec4 diffuseColor;		// diffuse color of the light
	vec4 specularColor;		// specular color of the light

	// Either the position or direction
	// if w = 0 then the light is directional and direction specified 
	// is the negative of the direction the light is shinning
	// if w = 1 then the light is positional
	vec4 positionOrDirection;    
					  
	// Spotlight attributes
	vec3 spotDirection;		// the direction the cone of light is shinning    
	bool isSpot;				// 1 if the light is a spotlight  
	float spotCutoffCos;	// Cosine of the spot cutoff angle
	float spotExponent;		// For gradual falloff near cone edge

	// Attenuation coefficients
	float constant; 
	float linear;
	float quadratic;

	bool enabled;			// true if light is "on"

};

layout (shared) uniform LightBlock
{
 GeneralLight lights[MaxLights];
};


struct Material
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
	int textureMode;
	bool diffuseTextureEnabled;
	bool specularTextureEnabled;
	bool normalMapEnabled;
};

layout (shared) uniform MaterialBlock
{
	Material object;
};

layout (shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

layout (location = 100) uniform sampler2D diffuseSampler;
layout (location = 101) uniform sampler2D specularSampler;
layout (location = 102) uniform sampler2D normalMapSampler;

in vec3 vertexWorldPosition;
in vec3 vertexWorldNormal;
in vec2 TexCoord;

out vec4 fragmentColor;

vec3 shadingCaculation(GeneralLight light, Material object );

void main()
{
	// Make copy of material properties that can be written to
	Material material = object;

	// Substitute diffuse texture for ambient and diffuse material properties
	if (material.diffuseTextureEnabled == true && material.textureMode != 0) {

			material.diffuseMat = texture(diffuseSampler, TexCoord.st);
			material.ambientMat = material.diffuseMat;
	}

	// Substitute specular texture for specular material properties
	if (material.specularTextureEnabled == true && material.textureMode != 0) {

			material.specularMat = texture(specularSampler, TexCoord.st);
	}

	// Should shading calculations be performed
	if(material.textureMode == 2 || material.textureMode == 0) {

		fragmentColor = material.emmissiveMat;

		for (int i = 0; i < MaxLights; i++)  {

			fragmentColor = material.diffuseMat; //+= vec4( shadingCaculation( lights[i], material ), 1.0);
		}	

	} else if(material.textureMode == 1){ // No shading calculations
		
		fragmentColor = texture(diffuseSampler, TexCoord.st);
	} 

} // main

vec3 shadingCaculation(GeneralLight light, Material object )
{
	vec3 totalFromThisLight = vec3(0.0, 0.0, 0.0);

	if (light.enabled == true) {

		// TODO
		// Implement shading calculations  

	}

	return totalFromThisLight;

} // end shadingCaculation
