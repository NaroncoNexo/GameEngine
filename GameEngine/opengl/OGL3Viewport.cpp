//
//  OGL3Viewport.cpp
//  GameEngine
//
//  Created by Johannes Roth on 02.02.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3Viewport.h"
#include "OGL3.h"
#include <stdio.h>

COGL3Viewport::COGL3Viewport(int x, int y, int width, int height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

COGL3Viewport::~COGL3Viewport()
{
}

void COGL3Viewport::Set()
{
    glViewport(m_x, m_y, m_width, m_height);
}
