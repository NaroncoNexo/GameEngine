//
//  SDL2GL3RenderContext.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 16.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "SDL2GL3RenderContext.h"

CSDL2GL3RenderContext::CSDL2GL3RenderContext(SDL_Window *SDLWindow)
{
	m_SDLWindow = SDLWindow;
}

CSDL2GL3RenderContext::~CSDL2GL3RenderContext()
{
}

int CSDL2GL3RenderContext::CreateContext(int colorBits, int depthBits, int stencilBits, int samples, int width, int height)
{
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,           colorBits);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,            depthBits);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,          stencilBits);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    samples);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,          1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);

    m_GLContext = SDL_GL_CreateContext(m_SDLWindow);
    if (!m_GLContext)
    {
    	return 1;
    }

    return 0;
}

void CSDL2GL3RenderContext::Release()
{
	if (m_GLContext)
	{
		SDL_GL_DeleteContext(m_GLContext);
		m_GLContext = nullptr;
	}
}

void CSDL2GL3RenderContext::SwapBuffers()
{
	SDL_GL_SwapWindow(m_SDLWindow);
}