//
//  SDL2InputDevice.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__SDL2InputDevice__
#define __GameEngine__SDL2InputDevice__

#include "IInputDevice.h"
#include <assert.h>

class CSDL2InputDevice : public IInputDevice
{
public:
	CSDL2InputDevice();
	~CSDL2InputDevice();

	virtual void Update();

	virtual void SetMouseCurserLocked(bool locked);

	virtual bool IsKeyDown(int key) const;

	virtual bool IsMouseButtonDown(int mouseButton) const;
	virtual const SVector2_i32 &GetMousePosition() const;
	virtual const SVector2_i32 &GetMouseMotion() const;

	inline void SetKey(int key, bool pressed) { m_keys[key] = pressed; }
	inline void SetMouseButton(int mouseButton, bool pressed) { assert((mouseButton >= 0) && (mouseButton < 3)); m_mouseButtons[mouseButton] = pressed; }
	
private:
	SVector2_i32 m_mousePosition{ 0, 0 };
	SVector2_i32 m_mouseMotion{ 0, 0 };
	bool m_mouseButtons[3];
	bool m_mouseLocked{ false };
	bool m_keys[512];
	bool m_firstFrameLockedCursor{ true };
};

#endif /* defined(__GameEngine__SDL2InputDevice__) */
