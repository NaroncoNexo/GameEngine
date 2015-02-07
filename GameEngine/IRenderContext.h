//
//  IRenderContext.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IRenderContext__
#define __3DGameEngine__IRenderContext__

class IRenderContext
{
public:
	IRenderContext() {  }
	virtual ~IRenderContext() {  }

	virtual int CreateContext(int colorBits, int depthBits, int stencilBits, int samples, int width, int height) = 0;
	virtual void Release() = 0;

	virtual void SwapBuffers() = 0;
};

#endif