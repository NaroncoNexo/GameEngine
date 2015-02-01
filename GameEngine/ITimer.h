//
//  ITimer.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__ITimer__
#define __GameEngine__ITimer__

typedef unsigned int TimeValue_t;

class ITimer
{
public:
    ITimer() {  }
    virtual ~ITimer() {  }
    
    virtual void Update() = 0;
    
    virtual TimeValue_t GetTime() const = 0;
    virtual float GetDeltaTime() const = 0;
};

#endif
