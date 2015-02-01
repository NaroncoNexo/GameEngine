//
//  OGL3VertexArray.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3VertexArray.h"
#include <map>

const std::map<int, GLenum> g_drawModeToGLDrawMode =
{
    { eDRAWMODE_POINTS, GL_POINTS },
    { eDRAWMODE_LINESTRIP, GL_LINE_STRIP },
    { eDRAWMODE_LINELOOP, GL_LINE_LOOP },
    { eDRAWMODE_LINES, GL_LINES },
    { eDRAWMODE_TRIANGLESTRIP, GL_TRIANGLE_STRIP },
    { eDRAWMODE_TRIANGLEFAN, GL_TRIANGLE_FAN },
    { eDRAWMODE_TRIANGLES, GL_TRIANGLES },
};

COGL3VertexArray::COGL3VertexArray(int drawMode, const void *vertexData, int vertexCount, const void *indexData, int indexCount, int stride, const std::vector<COGL3VertexStream> &streams)
{
    m_drawMode = g_drawModeToGLDrawMode.at(drawMode);
    m_streams = streams;
    
	int size = vertexCount * stride;

	glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);
    
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertexData, GL_STATIC_DRAW);

	for (const auto &stream : m_streams)
	{
		stream.Enable();
		stream.SetPointer();
	}

	if (indexData)
	{
		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index_t) * indexCount, indexData, GL_STATIC_DRAW);

		m_drawCount = indexCount;
		m_drawFunc = [this] ()
		{
			glDrawElements(m_drawMode, m_drawCount, GL_UNSIGNED_INT, 0);
		};
	}
	else
	{
        m_drawCount = vertexCount;
		m_drawFunc = [this] ()
		{
			glDrawArrays(m_drawMode, 0, m_drawCount);
		};
	}

    glBindVertexArray(0);
}

COGL3VertexArray::~COGL3VertexArray()
{
 	glDeleteBuffers(1, &m_vertexBuffer);
	if (m_indexBuffer != 0)
	{
		glDeleteBuffers(1, &m_indexBuffer);
	}

    glDeleteVertexArrays(1, &m_vertexArray);
}

void COGL3VertexArray::Render() const
{
	glBindVertexArray(m_vertexArray);
	m_drawFunc();
}

void *COGL3VertexArray::MapBuffer(int bufferType)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	return glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
}

void COGL3VertexArray::UnmapBuffer(int bufferType)
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}