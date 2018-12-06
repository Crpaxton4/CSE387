// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "Game.h"
#include <GL/glew.h>

#include "SharedGeneralLighting.h"
#include "SharedMaterialProperties.h"
#include "SharedProjectionAndViewing.h"


Renderer::Renderer(Game* game)
	:mGame(game)
	,mSpriteShader(nullptr)
	,mMeshShader(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 4.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(	mGame->GetWindowTitle().c_str(), 
								100, 100, 
								mScreenWidth, mScreenHeight, 
								SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create an OpenGL context
	mContext = SDL_GL_CreateContext(mWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// On some platforms, GLEW will emit a benign error code,
	// so clear it
	glGetError();

	// Make sure we can create/compile shaders
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	// Initialize light uniforms
	Renderer::SetUniforms();

	// Create quad for drawing sprites
	CreateSpriteVerts();

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set the clear color
	glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);

	return true;
}

void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;

	mMeshShader->Unload();
	delete mMeshShader;

	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	// Destroy textures
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// Destroy meshes
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::Draw()
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw mesh components

	// Set the mesh shader active
	mMeshShader->SetActive();

	// THERE NEEDS TO BE A FOR LOOP AROUND THIS SO THAT ALL CAMERAS ARE RENDERED

	// Update view-projection and viewing matrices
	activeCamera->setViewingTransformation( );
	
	for (auto mc : mMeshComps)
	{
		mc->Draw(mMeshShader);
	}

	// END FOR LOOP

	// Draw all sprite components
	// Disable depth testing
	glDisable(GL_DEPTH_TEST);

	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// Set shader/vao as active
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	mSpriteShader->SetMatrixUniform( "uViewProj", mSpriteProjectionMat );

	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// Swap the buffers
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	mMeshComps.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Renderer::GetMesh( const std::string & fileName )
{
	Mesh* m = nullptr;
	auto iter = mMeshes.find( fileName );
	if( iter != mMeshes.end( ) ) {
		m = iter->second;
	}
	//else {
	//	m = new Mesh( );
	//	if( m->Load( this, fileName ) ) {
	//		mMeshes.emplace( fileName, m );
	//	}
	//	else {
	//		delete m;
	//		m = nullptr;
	//	}
	//}
	return m;
}

bool Renderer::LoadShaders()
{
	// Create sprite shader
	mSpriteShader = new Shader();

	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	// Create basic mesh shader
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/vertexShader.vs.glsl", "Shaders/fragmentShader.fs.glsl"))
	{
		return false;
	}

	Resize( );

	return true;
}

void Renderer::CreateSpriteVerts()
{
	std::vector<pntVertexData> vertexData;
	std::vector<unsigned int> indices;

	vec3 v0( -0.5f, 0.5f, 0.0f );
	vec3 v1( 0.5f, 0.5f, 0.0f );
	vec3 v2( 0.5f, -0.5f, 0.0f);
	vec3 v3( -0.5f, -0.5f, 0.0f);

	vec3 norm( 0.0f, 0.0f, 1.0f );

	vec2 t0( 0.0f, 0.0f );
	vec2 t1( 1.0f, 0.0f );
	vec2 t2( 1.0f, 1.0f );
	vec2 t3( 0.0f, 1.0f );

	vertexData.push_back( pntVertexData( v0, norm, t0 ) );
	vertexData.push_back( pntVertexData( v1, norm, t1 ) );
	vertexData.push_back( pntVertexData( v2, norm, t2 ) );
	vertexData.push_back( pntVertexData( v3, norm, t3 ) );

	indices.push_back( 0 );
	indices.push_back( 1 );
	indices.push_back( 2 );
	indices.push_back( 2 );
	indices.push_back( 3 );
	indices.push_back( 0 );

	mSpriteVerts = new VertexArray(vertexData, indices);
}

void Renderer::SetUniforms()
{
	// Set up a buffer for the projectionViewBlock and worldEyeBlock in the 
	// shader program
	SharedProjectionAndViewing::setUniformBlockForShader(mMeshShader->mShaderProgram);
	SharedMaterialProperties::setUniformBlockForShader(mMeshShader->mShaderProgram);
	SharedGeneralLighting::setUniformBlockForShader(mMeshShader->mShaderProgram);
}

void Renderer::Resize( )
{
	// Get the current width and height of the rendering window
	SDL_GetWindowSize( mWindow, &mScreenWidth, &mScreenHeight );

	// Set the viewport to match the window size
	glViewport( 0, 0, mScreenWidth, mScreenHeight );

	// Set the active shader
	mSpriteShader->SetActive( );

	//	Create the sprite projection matrix
	mSpriteProjectionMat = glm::ortho( -mScreenWidth / 2.0f, mScreenWidth / 2.0f, -mScreenHeight / 2.0f, mScreenHeight / 2.0f, 0.0f, 2.0f );
	mSpriteShader->SetMatrixUniform( "uViewProj", mSpriteProjectionMat );

}
