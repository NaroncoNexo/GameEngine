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

class CSDL2InputDevice : public IInputDevice
{
public:
    CSDL2InputDevice();
    ~CSDL2InputDevice();
    
    virtual void Update();
    
    virtual const SVector2_i32 &GetMousePosition() const;
    
private:
    SVector2_i32 m_mousePosition { 0, 0 };
};

#endif /* defined(__GameEngine__SDL2InputDevice__) */
