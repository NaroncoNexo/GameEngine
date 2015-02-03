//
//  CCMSkybox.cpp
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "CCMSkybox.h"
#include "Environment.h"

CSkyboxClearMethod::CSkyboxClearMethod(CSkybox *skybox)
{
    m_skybox = skybox;
}

CSkyboxClearMethod::~CSkyboxClearMethod()
{
}

void CSkyboxClearMethod::Clear(CCamera *camera, IRenderDevice *renderDevice)
{
    g_subSystem->GetRenderDevice()->Clear(eCLEAR_DEPTH);
    m_skybox->Render(camera);
}