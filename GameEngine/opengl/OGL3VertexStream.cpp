//
//  OGL3VertexStream.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3VertexStream.h"
#include "OGL3.h"
#include <stdio.h>

COGL3VertexStream::COGL3VertexStream(int streamNumber, int componentCount, int stride, int offset)
{
    m_streamNumber = streamNumber;
    m_componentCount = componentCount;
    m_stride = stride;
    m_offset = offset;
}

void COGL3VertexStream::Enable() const
{
    glEnableVertexAttribArray(m_streamNumber);
}

void COGL3VertexStream::SetPointer() const
{
    glVertexAttribPointer(m_streamNumber, m_componentCount, GL_FLOAT, GL_FALSE, m_stride, (unsigned char *)nullptr + m_offset);
}

void COGL3VertexStream::Disable() const
{
    glDisableVertexAttribArray(m_streamNumber);
}