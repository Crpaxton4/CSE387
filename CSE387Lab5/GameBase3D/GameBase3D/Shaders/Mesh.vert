// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

// Uniforms for world transform and view-proj
uniform mat4 uWorldTransform;
uniform mat4 uViewTransform;
uniform mat4 uProjTransform;

// Attribute 0 is position
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 worldCoord;
out vec3 fragNormal;
out vec2 fragtexCoord;

void main()
{
	// Convert position to homogeneous coordinates
	vec4 pos = vec4(inPosition, 1.0);
	vec4 norm = vec4(inNormal, 1.0);

	// transform position wo world coordinates
	vec4 worldCoordv4 = uWorldTransformation * pos;

	// Transform position to clip space
	gl_Position = uProjTransform * uViewTransform * worldCoordv4;

	worldCoord = vec3(worldCoordv4);
	fragNormal = vec3(uWorldTransform * norm);
	fragTextCoord = inTexCoord;

}
