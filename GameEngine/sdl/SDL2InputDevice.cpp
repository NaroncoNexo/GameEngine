//
//  SDL2InputDevice.cpp
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "SDL2InputDevice.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <Environment.h>
#include "SDL2Window.h"

CSDL2InputDevice::CSDL2InputDevice()
{
	memset(m_mouseButtons, 0, sizeof(m_mouseButtons));
	memset(m_keys, 0, sizeof(m_keys));
}

CSDL2InputDevice::~CSDL2InputDevice()
{
}

void CSDL2InputDevice::Update()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_mousePosition = { mouseX, mouseY };

	if (m_mouseLocked)
	{
		SVector2_i32 screenCenter = SVector2_i32(g_subSystem->GetDisplay()->GetWidth() >> 1, g_subSystem->GetDisplay()->GetHeight() >> 1);
		
		if (m_firstFrameLockedCursor)
		{
			m_mouseMotion = { 0, 0 };
			SDL_WarpMouseInWindow(((CSDL2Window *)g_subSystem->GetDisplay())->GetSDLWindow(), screenCenter.x, screenCenter.y);
			m_firstFrameLockedCursor = false;
		}
		else
		{
			m_mouseMotion = m_mousePosition - screenCenter;
			SDL_WarpMouseInWindow(((CSDL2Window *)g_subSystem->GetDisplay())->GetSDLWindow(), screenCenter.x, screenCenter.y);
		}
	}
	else
	{
		static SVector2_i32 lastMousePosition = m_mousePosition;
		m_mouseMotion = m_mousePosition - lastMousePosition;
		lastMousePosition = m_mousePosition;
	}
}

void CSDL2InputDevice::SetMouseCurserLocked(bool locked)
{
	m_mouseLocked = locked;
	SDL_ShowCursor(!locked);

	if (m_mouseLocked)
		m_firstFrameLockedCursor = true;
}

bool CSDL2InputDevice::IsKeyDown(int key) const
{
	return m_keys[key];
}

bool CSDL2InputDevice::IsMouseButtonDown(int mouseButton) const
{
	assert((mouseButton >= 0) && (mouseButton < 3));
	return m_mouseButtons[mouseButton];
}

const SVector2_i32 &CSDL2InputDevice::GetMousePosition() const
{
	return m_mousePosition;
}

const SVector2_i32 &CSDL2InputDevice::GetMouseMotion() const
{
	return m_mouseMotion;
}
