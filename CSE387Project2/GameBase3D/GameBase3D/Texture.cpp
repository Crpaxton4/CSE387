// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Texture.h"
//#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include "FreeImage.h"

Texture::Texture()
:mTextureID(0)
,mWidth(0)
,mHeight(0)
{
	
}

Texture::~Texture()
{
	
}

#include <iostream>
bool Texture::Load(const std::string& fileName)
{
	// Analyze the bitmap signature to determine the file type
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType( fileName.c_str( ), 0 );

	// Read the bitmap from the file
	FIBITMAP* image = FreeImage_Load( format, fileName.c_str( ) );

	// Convert the bitmap to 32 bits
	FIBITMAP* temp = image;
	image = FreeImage_ConvertTo32Bits( image );
	FreeImage_Unload( temp );

	// Get the dimensions of the bitmap
	int width = FreeImage_GetWidth( image );
	int height = FreeImage_GetHeight( image );

	// Check bitmap parameters to determine is a valid image was loaded
	if( image == nullptr || width == 0 || height == 0 ) {
		std::cerr << "ERROR: Unable to load " << fileName << "!" << std::endl;
		return false;
	}

	// Create a pointer to the bitmap data with the proper type
	GLubyte* texture = new GLubyte[4 * width*height];
	char* texels = (char*)FreeImage_GetBits( image );

	//FreeImage loads in BGR format, so you need to swap some bytes.
	for( int j = 0; j < width*height; j++ ) {
		texture[j * 4 + 0] = texels[j * 4 + 2];
		texture[j * 4 + 1] = texels[j * 4 + 1];
		texture[j * 4 + 2] = texels[j * 4 + 0];
		texture[j * 4 + 3] = texels[j * 4 + 3];
	}

	glGenTextures( 1, &mTextureID );

	// Assign texture to ID
	glBindTexture( GL_TEXTURE_2D, mTextureID );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture );

	std::cout << "Loaded: " << fileName.c_str( ) << " texture. width " << width << " height " << height << std::endl;

	glGenerateMipmap( GL_TEXTURE_2D );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glBindTexture( GL_TEXTURE_2D, 0 );

	FreeImage_Unload( image );
	
	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
