// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <memory.h>
//#include <limits>

// Forward declaration to speed compilation
#include "glm/fwd.hpp"

// Basic GLM functionality
#include "glm/glm.hpp"

// Stable glm extensions
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL

// For scale, rotate, and translate
#include <glm/gtx/transform.hpp>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using glm::mat4;

const float PI = glm::pi<float>( );
const float TWO_PI = PI * 2.0f;
const float PI_OVER_2 = PI / 2.0f;

//const float INFINITY = std::numeric_limits<float>::infinity( );
const float NEG_INFINITY = -INFINITY;

const vec2 ZERO_V2( 0.0f, 0.0f );
const vec2 UNIT_X_V2( 1.0f, 0.0f );
const vec2 UNIT_Y_V2( 0.0f, 1.0f );
const vec2 NEG_UNIT_X_V2( -1.0f, 0.0f );
const vec2 NEG_UNIT_Y_V2( 0.0f, -1.0f );

const vec3 ZERO_V3(0.0f, 0.0f, 0.f);
const vec3 UNIT_X_V3(1.0f, 0.0f, 0.0f);
const vec3 UNIT_Y_V3(0.0f, 1.0f, 0.0f);
const vec3 UNIT_Z_V3(0.0f, 0.0f, 1.0f);
const vec3 NEG_UNIT_X_V3(-1.0f, 0.0f, 0.0f);
const vec3 NEG_UNIT_Y_V3(0.0f, -1.0f, 0.0f);
const vec3 NEG_UNIT_Z_V3(0.0f, 0.0f, -1.0f);
const vec3 INFINITY_V3(INFINITY, INFINITY, INFINITY);
const vec3 NEG_INFINITY_V3( NEG_INFINITY, NEG_INFINITY, NEG_INFINITY);

const vec3 BLACK_RGB(0.0f, 0.0f, 0.0f);
const vec3 WHITE_RGB(1.0f, 1.0f, 1.0f);
const vec3 RED_RGB(1.0f, 0.0f, 0.0f);
const vec3 GREEN_RGB(0.0f, 1.0f, 0.0f);
const vec3 BLUE_RGB(0.0f, 0.0f, 1.0f);
const vec3 YELLOW_RGB(1.0f, 1.0f, 0.0f);
const vec3 LIGHT_YELLOW_RGB(1.0f, 1.0f, 0.88f);
const vec3 LIGHT_BLUE_RGB(0.68f, 0.85f, 0.9f);
const vec3 LIGHT_PINK_RGB(1.0f, 0.71f, 0.76f);
const vec3 LIGHT_GREEN_RGB(0.56f, 0.93f, 0.56f);

inline bool NearZero( float val, float epsilon = 0.001f )
{
	if( fabs( val ) <= epsilon ) {
		return true;
	}
	else {
		return false;
	}
}