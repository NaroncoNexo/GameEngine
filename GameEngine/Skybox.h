//
//  Skybox.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__Skybox__
#define __GameEngine__Skybox__

#include "IRenderDevice.h"

class CCamera;

class CSkybox
{
public:
    CSkybox(IRenderDevice *renderDevice, ITexture *cubeMapTexture);
    ~CSkybox();
    
    void Render(CCamera *camera);
    
private:
    IRenderDevice *m_renderDevice { nullptr };
    ITexture *m_cubeMapTexture { nullptr };
    
    static int s_referenceCounter;
    static IVertexArray *s_mesh;
    static IShaderProgram *s_shader;
};

#endif /* defined(__GameEngine__Skybox__) */
