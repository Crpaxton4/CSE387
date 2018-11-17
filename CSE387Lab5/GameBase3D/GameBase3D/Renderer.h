// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include "MathLibsConstsFuncs.h"


class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize( int screenWidth, int screenHeight );
	void Shutdown();
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	class Texture* GetTexture(const std::string& fileName);
	class Mesh* GetMesh(const std::string& fileName);

	void SetViewMatrix(const mat4& view) { mViewMat = view; }

	int GetScreenWidth() const { return mScreenWidth; }
	int GetScreenHeight() const { return mScreenHeight; }

	void Resize( );

private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms();

	// Map of textures loaded
	std::unordered_map<std::string, class Texture*> mTextures;

	// Map of meshes loaded
	std::unordered_map<std::string, class Mesh*> mMeshes;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	// All mesh components drawn
	std::vector<class MeshComponent*> mMeshComps;

	// Game
	class Game* mGame;

	// Sprite shader
	class Shader* mSpriteShader;
	// Sprite vertex array
	class VertexArray* mSpriteVerts;

	// Mesh shader
	class Shader* mMeshShader;

	// View/projection for 3D shaders
	mat4 mViewMat;
	mat4 mProjectionMat;

	// Current window width and height
	int mScreenWidth = 1024;
	int mScreenHeight = 768;

	// Window
	SDL_Window* mWindow;
	// OpenGL context
	SDL_GLContext mContext;

	// Current window clear color
	vec4 mClearColor = vec4(0.75f, 0.75f, 0.75f, 1.0f);
};