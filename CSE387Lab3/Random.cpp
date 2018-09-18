// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Random.h"

void Random::Init()
{
	std::random_device rd;
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed)
{
	sGenerator.seed(seed);
}

float Random::GetFloat()
{
	return GetFloatRange(0.0f, 1.0f);
}

float Random::GetFloatRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(sGenerator);
}

int Random::GetIntRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(sGenerator);
}

vec2 Random::GetVector(const vec2& min, const vec2& max)
{
	vec2 r = vec2(GetFloat(), GetFloat());
	return min + (max - min) * r;
}

vec3 Random::GetVector(const vec3& min, const vec3& max)
{
	vec3 r = vec3(GetFloat(), GetFloat(), GetFloat());
	return min + (max - min) * r;
}

std::mt19937 Random::sGenerator;
