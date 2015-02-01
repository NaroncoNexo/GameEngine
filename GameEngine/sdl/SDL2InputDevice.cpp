//
//  SDL2InputDevice.cpp
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "SDL2InputDevice.h"
#include <SDL2/SDL.h>

CSDL2InputDevice::CSDL2InputDevice()
{
}

CSDL2InputDevice::~CSDL2InputDevice()
{
}

void CSDL2InputDevice::Update()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    m_mousePosition = { mouseX, mouseY };
}

const SVector2_i32 &CSDL2InputDevice::GetMousePosition() const
{
    return m_mousePosition;
}
