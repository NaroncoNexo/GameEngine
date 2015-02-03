//
//  Camera.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 06.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "Camera.h"
#include "Environment.h"

CCamera::CCamera()
{
    m_transform = new CTransform;
}

CCamera::~CCamera()
{
    if (m_viewport != nullptr && m_releaseViewport)
    {
        g_subSystem->GetRenderDevice()->ReleaseViewport(m_viewport);
    }
    
    delete m_transform;
}

void CCamera::UpdateMatrices()
{
	m_translationMatrix = SMatrix4::CreateTranslation(-m_transform->GetTranslation());
	m_rotationMatrix = m_transform->GetRotation().GetMatrix4();
	m_scaleMatrix = SMatrix4::CreateScale(m_transform->GetScale());

	m_viewMatrix = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void CCamera::SetViewport(int x, int y, int width, int height)
{
    if (m_viewport != nullptr && m_releaseViewport)
    {
        g_subSystem->GetRenderDevice()->ReleaseViewport(m_viewport);
    }
    
    m_viewport = g_subSystem->GetRenderDevice()->CreateViewport(x, y, width, height);
    m_releaseViewport = true;
}

void CCamera::SetViewport(IViewport *viewport)
{
    if (m_viewport != nullptr && m_releaseViewport)
    {
        g_subSystem->GetRenderDevice()->ReleaseViewport(m_viewport);
    }
    
    m_viewport = viewport;
    m_releaseViewport = false;
}

void CCamera::SetPerspectiveProjection(f32 fov, f32 aspectRatio, f32 zNear, f32 zFar)
{
    m_projectionMatrix = SMatrix4::CreatePerspective(fov, aspectRatio, zNear, zFar);
}
