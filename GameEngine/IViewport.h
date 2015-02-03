//
//  IViewport.h
//  GameEngine
//
//  Created by Johannes Roth on 02.02.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__IViewport__
#define __GameEngine__IViewport__

class IViewport
{
public:
    IViewport() {  }
    virtual ~IViewport() {  }
    
    virtual void Set() = 0;
    
    inline int GetX() const { return m_x; }
    inline int GetY() const { return m_y; }
    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }
    
    inline float GetAspectRatio() const { return ((float)m_width / (float)m_height); }
    
protected:
    int m_x { 0 }, m_y { 0 }, m_width { 0 }, m_height { 0 };
};

#endif
