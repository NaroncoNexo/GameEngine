//
//  OGL3Texture.h
//  3DGameEngine
//
//  Created by Johannes Roth on 19.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__OGL3Texture__
#define __3DGameEngine__OGL3Texture__

#include <ITexture.h>
#include <OpenGL/gl3.h>

//int width, int height, const Pixel_t *data, int filter, int wrap
class COGL3Texture : public ITexture
{
public:
	COGL3Texture(const STextureData2D *data, int filter, int wrap); // Texture2D
	COGL3Texture(const STextureDataCubeMap *data, int filter); // TextureCubeMap
	~COGL3Texture();

	virtual void Bind(int textureSlot) const;

	inline GLuint GetID() const { return m_ID; }

private:
	GLenum m_type { 0 };
	GLuint m_ID { 0 };
};

#endif