//
//  SDL2GL3RenderContext.h
//  3DGameEngine
//
//  Created by Johannes Roth on 16.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__SDL2GL3RenderContext__
#define __3DGameEngine__SDL2GL3RenderContext__

#include <SDL2/SDL.h>
#include "IRenderContext.h"

class CSDL2GL3RenderContext : public IRenderContext
{
public:
	CSDL2GL3RenderContext(SDL_Window *);
	~CSDL2GL3RenderContext();

	virtual int CreateContext(int colorBits, int depthBits, int stencilBits, int samples, int width, int height);
	virtual void Release();

	virtual void SwapBuffers();

private:
	SDL_Window *m_SDLWindow { nullptr };
	SDL_GLContext m_GLContext { nullptr };
};

#endif