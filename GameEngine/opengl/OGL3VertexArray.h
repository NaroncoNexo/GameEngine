//
//  OGL3VertexArray.h
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__OGL3VertexArray__
#define __3DGameEngine__OGL3VertexArray__

#include "OGL3VertexStream.h"
#include <IVertexArray.h>
#include <IndexedModel.h>
#include <functional>
#include <vector>

typedef unsigned int GLuint, GLenum;

class COGL3VertexArray : public IVertexArray
{
public:
	COGL3VertexArray(int drawMode, const void *vertexData, int vertexCount, const void *indexData, int indexCount, int stride, const std::vector<COGL3VertexStream> &streams);
	~COGL3VertexArray();

	virtual void Render() const;

	virtual void *MapBuffer(int bufferType);
	virtual void UnmapBuffer(int bufferType);

private:
    GLenum m_drawMode { 0 };
	std::vector<COGL3VertexStream> m_streams;
	std::function<void (void)> m_drawFunc;
	GLuint m_vertexArray { 0 };
	GLuint m_vertexBuffer { 0 }, m_indexBuffer { 0 };
	int m_drawCount { 0 };
};

#endif