//
//  OGL3Texture.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 19.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3Texture.h"
#include <map>

const std::map<int, GLenum> GLFilterLookup =
{
	{ eTEXTUREFILTER_NEAREST, GL_NEAREST },
	{ eTEXTUREFILTER_LINEAR,  GL_LINEAR }
};

const std::map<int, GLenum> GLWrapLookup =
{
	{ eTEXTUREWRAP_REPEAT,        GL_REPEAT },
	{ eTEXTUREWRAP_CLAMP,         GL_CLAMP_TO_BORDER },
	{ eTEXTUREWRAP_CLAMPTOEDGE,   GL_CLAMP_TO_EDGE },
	{ eTEXTUREWRAP_CLAMPTOBORDER, GL_CLAMP_TO_BORDER }
};

COGL3Texture::COGL3Texture(const STextureData2D *data, int filter, int wrap)
{
	m_type = GL_TEXTURE_2D;

    glGenTextures(1, &m_ID);
    
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLFilterLookup.at(filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLFilterLookup.at(filter));
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLWrapLookup.at(wrap));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLWrapLookup.at(wrap));
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data->pixels[0]);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

COGL3Texture::COGL3Texture(const STextureDataCubeMap *data, int filter)
{
	m_type = GL_TEXTURE_CUBE_MAP;

	glGenTextures(1, &m_ID);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GLFilterLookup.at(filter));
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GLFilterLookup.at(filter));
    
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    for (int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data->pixels[i][0]);
	}
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

COGL3Texture::~COGL3Texture()
{
	glDeleteTextures(1, &m_ID);
}

void COGL3Texture::Bind(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(m_type, m_ID);
}