//
//  SDL2Timer.cpp
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "SDL2Timer.h"
#include <SDL2/SDL.h>

CSDL2Timer::CSDL2Timer()
{
    m_time = SDL_GetTicks();
    m_deltaTime = 0.0f;
}

CSDL2Timer::~CSDL2Timer()
{
}

void CSDL2Timer::Update()
{
    TimeValue_t currentTime = SDL_GetTicks();
    m_deltaTime = (currentTime - m_time) * 0.001f;
    m_time = currentTime;
}

TimeValue_t CSDL2Timer::GetTime() const
{
    return m_time;
}

float CSDL2Timer::GetDeltaTime() const
{
    return m_deltaTime;
}
