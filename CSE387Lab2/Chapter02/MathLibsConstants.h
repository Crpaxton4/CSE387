// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <memory.h>
#include <limits>

// Forward declaration to speed compilation
#include "glm/fwd.hpp"

// In a source file using GLM types
#include "glm/glm.hpp"

// Stable glm extensions
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using glm::mat4;

const float PI = glm::pi<float>( );

const float Infinity = std::numeric_limits<float>::infinity( );
const float NegInfinity = -std::numeric_limits<float>::infinity( );

namespace v2
{
	const vec2 ZERO( 0.0f, 0.0f );
	const vec2 UNIT_X( 1.0f, 0.0f );
	const vec2 UNIT_Y( 0.0f, 1.0f );
	const vec2 NEG_UNIT_X( -1.0f, 0.0f );
	const vec2 NEG_UNIT_Y( 0.0f, -1.0f );
}

namespace v3
{

	const vec3 Zero(0.0f, 0.0f, 0.f);
	const vec3 UnitX(1.0f, 0.0f, 0.0f);
	const vec3 UnitY(0.0f, 1.0f, 0.0f);
	const vec3 UnitZ(0.0f, 0.0f, 1.0f);
	const vec3 NegUnitX(-1.0f, 0.0f, 0.0f);
	const vec3 NegUnitY(0.0f, -1.0f, 0.0f);
	const vec3 NegUnitZ(0.0f, 0.0f, -1.0f);
	const vec3 Infinity(Infinity, Infinity, Infinity);
	const vec3 NegInfinity(NegInfinity, NegInfinity, NegInfinity);
}

namespace Color3
{
	static const vec3 Black(0.0f, 0.0f, 0.0f);
	static const vec3 White(1.0f, 1.0f, 1.0f);
	static const vec3 Red(1.0f, 0.0f, 0.0f);
	static const vec3 Green(0.0f, 1.0f, 0.0f);
	static const vec3 Blue(0.0f, 0.0f, 1.0f);
	static const vec3 Yellow(1.0f, 1.0f, 0.0f);
	static const vec3 LightYellow(1.0f, 1.0f, 0.88f);
	static const vec3 LightBlue(0.68f, 0.85f, 0.9f);
	static const vec3 LightPink(1.0f, 0.71f, 0.76f);
	static const vec3 LightGreen(0.56f, 0.93f, 0.56f);
}
