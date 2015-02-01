//
//  CCMSkybox.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__CCMSkybox__
#define __GameEngine__CCMSkybox__

#include "Camera.h"
#include "Skybox.h"

class CSkyboxClearMethod : public IClearMethod
{
public:
    CSkyboxClearMethod(CSkybox *skybox);
    ~CSkyboxClearMethod();
    
    virtual void Clear(CCamera *camera, IRenderDevice *renderDevice);
    
    inline void SetSkybox(CSkybox *skybox) { m_skybox = skybox; }
    inline CSkybox *GetSkybox() const { return m_skybox; }
    
private:
    CSkybox *m_skybox { nullptr };
};

#endif /* defined(__GameEngine__CCMSkybox__) */
