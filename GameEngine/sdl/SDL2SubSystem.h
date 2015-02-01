//
//  SDL2SubSystem.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__SDL2SubSystem__
#define __3DGameEngine__SDL2SubSystem__

#include <SDL2/SDL.h>
#include <ISubSystem.h>
#include <opengl/OGL3RenderDevice.h>
#include "SDL2Window.h"
#include "SDL2Timer.h"
#include "SDL2InputDevice.h"
#include "SDL2GL3RenderContext.h"

class CSDL2SubSystem : public ISubSystem
{
public:
	CSDL2SubSystem();
	~CSDL2SubSystem();

	virtual IDisplay *CreateDisplay(int width, int height, const std::string &title);
	virtual void Release();

	virtual bool Update();

    virtual ITimer *GetTimer() const;
    virtual IInputDevice *GetInputDevice() const;
	virtual IRenderContext *GetRenderContext() const;
	virtual IRenderDevice *GetRenderDevice() const;

private:
	CSDL2Window *m_window { nullptr };
    CSDL2Timer *m_timer { nullptr };
    CSDL2InputDevice *m_inputDevice { nullptr };
	CSDL2GL3RenderContext *m_renderContext { nullptr };
	COGL3RenderDevice *m_renderDevice { nullptr };
};

#endif