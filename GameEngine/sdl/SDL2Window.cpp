//
//  SDL2Window.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 16.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "SDL2Window.h"

CSDL2Window::CSDL2Window(const std::string &title, int width, int height)
{
	m_SDLWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (m_SDLWindow == nullptr)
	{
		std::cerr << "Failed to create SDL window\nError message: " << SDL_GetError() << std::endl;
	}
}

CSDL2Window::~CSDL2Window()
{
	SDL_DestroyWindow(m_SDLWindow);
}

void CSDL2Window::SetTitle(const std::string &title)
{
	SDL_SetWindowTitle(m_SDLWindow, title.c_str());
}

void CSDL2Window::SetWidth(int width)
{
	SDL_SetWindowSize(m_SDLWindow, width, GetHeight());
}

void CSDL2Window::SetHeight(int height)
{
	SDL_SetWindowSize(m_SDLWindow, GetWidth(), height);
}

void CSDL2Window::SetSize(int width, int height)
{
	SDL_SetWindowSize(m_SDLWindow, width, height);
}

std::string CSDL2Window::GetTitle() const
{
	return std::string(SDL_GetWindowTitle(m_SDLWindow));
}

int CSDL2Window::GetWidth() const
{
	int w;
	SDL_GetWindowSize(m_SDLWindow, &w, nullptr);
	return w;
}

int CSDL2Window::GetHeight() const
{
	int h;
	SDL_GetWindowSize(m_SDLWindow, nullptr, &h);
	return h;
}

bool CSDL2Window::HasFocus() const
{
	return m_hasFocus;
}
