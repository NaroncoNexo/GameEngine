//
//  IInputDevice.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__IInputDevice__
#define __GameEngine__IInputDevice__

#include "Math3D.h"

class IInputDevice
{
public:
    IInputDevice() {  }
    virtual ~IInputDevice() {  }
    
    virtual void Update() = 0;
    
    virtual const SVector2_i32 &GetMousePosition() const = 0;
};

#endif
