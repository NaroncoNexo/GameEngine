//
//  OGL3VertexStream.h
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__COGL3VertexStream__
#define __3DGameEngine__COGL3VertexStream__

class COGL3VertexStream
{
public:
    COGL3VertexStream(int streamNumber, int componentCount, int stride, int offset);
    
    void Enable() const;
    void SetPointer() const;
    void Disable() const;
    
private:
    int m_streamNumber { 0 };
    int m_componentCount { 0 };
    int m_stride { 0 };
    int m_offset { 0 };
};

#endif