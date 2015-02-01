//
//  SDL2SubSystem.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "SDL2SubSystem.h"

CSDL2SubSystem::CSDL2SubSystem()
{
}

CSDL2SubSystem::~CSDL2SubSystem()
{
}

IDisplay *CSDL2SubSystem::CreateDisplay(int width, int height, const std::string &title)
{
	SDL_Init(SDL_INIT_VIDEO);
    
    m_timer = new CSDL2Timer;
    
    m_inputDevice = new CSDL2InputDevice;

	m_window = new CSDL2Window(title, width, height);

	m_renderContext = new CSDL2GL3RenderContext(m_window->GetSDLWindow());

	int error = m_renderContext->CreateContext(24, 16, 0, 0, width, height);
	if (CHECKERROR(error))
	{
		return nullptr;
	}

	m_renderDevice = new COGL3RenderDevice;
    m_renderDevice->Create();

	return m_window;
}

void CSDL2SubSystem::Release()
{
	if (m_renderDevice)
	{
        m_renderDevice->Release();
		delete m_renderDevice;
		m_renderDevice = nullptr;
	}

	if (m_renderContext)
	{
		m_renderContext->Release();
		delete m_renderContext;
		m_renderContext = nullptr;
	}

	if (m_window)
	{
		delete m_window;
		m_window = nullptr;
	}
    
    if (m_inputDevice)
    {
        delete m_inputDevice;
        m_inputDevice = nullptr;
    }
    
    if (m_timer)
    {
        delete m_timer;
        m_timer = nullptr;
    }

	SDL_Quit();
}

bool CSDL2SubSystem::Update()
{
    m_timer->Update();
    m_inputDevice->Update();
    
	static SDL_Event event;
	while (SDL_PollEvent(&event))
	{
        switch (event.type)
        {
            case SDL_QUIT:
                return false;
        }
	}
	
	return true;
}

ITimer *CSDL2SubSystem::GetTimer() const
{
    return m_timer;
}

IInputDevice *CSDL2SubSystem::GetInputDevice() const
{
    return m_inputDevice;
}

IRenderContext *CSDL2SubSystem::GetRenderContext() const
{
    return m_renderContext;
}

IRenderDevice *CSDL2SubSystem::GetRenderDevice() const
{
    return m_renderDevice;
}
