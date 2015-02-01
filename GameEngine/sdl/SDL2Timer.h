//
//  SDL2Timer.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__SDL2Timer__
#define __GameEngine__SDL2Timer__

#include "ITimer.h"

class CSDL2Timer : public ITimer
{
public:
    CSDL2Timer();
    ~CSDL2Timer();
    
    virtual void Update();
    
    virtual TimeValue_t GetTime() const;
    virtual float GetDeltaTime() const;
    
private:
    TimeValue_t m_time { 0 };
    float m_deltaTime { 0 };
};

#endif /* defined(__GameEngine__SDL2Timer__) */
