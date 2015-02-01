//
//  OGL3VertexStream.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3VertexStream.h"
#include <OpenGL/gl3.h>
#include <stdio.h>

COGL3VertexStream::COGL3VertexStream(int streamNumber, int componentCount, int stride, int offset)
{
    m_streamNumber = streamNumber;
    m_componentCount = componentCount;
    m_stride = stride;
    m_offset = offset;
}

#define GLERR2(f){int err=glGetError();if(err!=0){printf("%i: %i\n",f,err);}}

void COGL3VertexStream::Enable() const
{
    glEnableVertexAttribArray(m_streamNumber);
    GLERR2(m_streamNumber*2+0);
}

void COGL3VertexStream::SetPointer() const
{
    glVertexAttribPointer(m_streamNumber, m_componentCount, GL_FLOAT, GL_FALSE, m_stride, (unsigned char *)nullptr + m_offset);
    GLERR2(m_streamNumber*2+1);
}

void COGL3VertexStream::Disable() const
{
    glDisableVertexAttribArray(m_streamNumber);
}