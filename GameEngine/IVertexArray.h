//
//  IVertexArray.h
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IVertexArray__
#define __3DGameEngine__IVertexArray__

enum
{
	eBUFFERTYPE_VERTEXBUFFER,
	eBUFFERTYPE_INDEXBUFFER
};

class IVertexArray
{
public:
	IVertexArray() {  }
	virtual ~IVertexArray() {  }

	virtual void Render() const = 0;

	virtual void *MapBuffer(int bufferType) = 0;
	virtual void UnmapBuffer(int bufferType) = 0;
};

#endif