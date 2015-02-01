//
//  IRenderContext.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IRenderContext__
#define __3DGameEngine__IRenderContext__

/*SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);*/

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