//
//  CCMSkybox.cpp
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "CCMSkybox.h"

CSkyboxClearMethod::CSkyboxClearMethod(CSkybox *skybox)
{
    m_skybox = skybox;
}

CSkyboxClearMethod::~CSkyboxClearMethod()
{
}

void CSkyboxClearMethod::Clear(CCamera *camera, IRenderDevice *renderDevice)
{
    m_skybox->Render(camera);
}