//
//  OGL3Viewport.h
//  GameEngine
//
//  Created by Johannes Roth on 02.02.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__OGL3Viewport__
#define __GameEngine__OGL3Viewport__

#include "IViewport.h"

class COGL3Viewport : public IViewport
{
public:
    COGL3Viewport(int x, int y, int width, int height);
    ~COGL3Viewport();
    
    virtual void Set();
};

#endif /* defined(__GameEngine__OGL3Viewport__) */
