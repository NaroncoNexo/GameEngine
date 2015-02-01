//
//  ISubSystem.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__ISubSystem__
#define __3DGameEngine__ISubSystem__

#include "IRenderContext.h"
#include "IRenderDevice.h"
#include "IDisplay.h"
#include "IInputDevice.h"
#include "ITimer.h"
#include <string>
#include <vector>

#define CHECKERROR(code) ((code)!=0)

class ISubSystem
{
public:
	ISubSystem() {  }
	virtual ~ISubSystem() {  }

	virtual IDisplay *CreateDisplay(int width, int height, const std::string &title) = 0;
	virtual void Release() = 0;

	virtual bool Update() = 0;

    virtual ITimer *GetTimer() const = 0;
    virtual IInputDevice *GetInputDevice() const = 0;
	virtual IRenderContext *GetRenderContext() const = 0;
	virtual IRenderDevice *GetRenderDevice() const = 0;
};

#endif