//
//  Camera.h
//  3DGameEngine
//
//  Created by Johannes Roth on 06.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__Camera__
#define __3DGameEngine__Camera__

#include "Math3D.h"
#include "Transform.h"
#include "IRenderDevice.h"

class CCamera;

class IClearMethod
{
public:
    IClearMethod() {  }
    virtual ~IClearMethod() {  }
    
    virtual void Clear(CCamera *camera, IRenderDevice *renderDevice) = 0;
};

class CCamera
{
public:
    CCamera();
    ~CCamera();
    
	void UpdateMatrices();
    
    void SetViewport(int x, int y, int width, int height);
    void SetViewport(IViewport *viewport);
    void SetPerspectiveProjection(f32 fov, f32 aspectRatio, f32 zNear, f32 zFar);
    
    inline void SetClearMethod(IClearMethod *clearMethod) { m_clearMethod = clearMethod; }
    
    inline CTransform *GetTransform() const { return m_transform; }
    inline IViewport *GetViewport() const { return m_viewport; }
    inline IClearMethod *GetClearMethod() const { return m_clearMethod; }
    
	inline const SMatrix4 &GetViewMatrix() const { return m_viewMatrix; }
	inline const SMatrix4 &GetProjectionMatrix() const { return m_projectionMatrix; }
	inline const SMatrix4 &GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }

	inline const SMatrix4 &GetTranslationMatrix() const { return m_translationMatrix; }
	inline const SMatrix4 &GetRotationMatrix() const { return m_rotationMatrix; }
    inline const SMatrix4 &GetScaleMatrix() const { return m_scaleMatrix; }
    
private:
    CTransform *m_transform { nullptr };
    IViewport *m_viewport { nullptr };
    IClearMethod *m_clearMethod { nullptr };
	SMatrix4 m_viewMatrix, m_projectionMatrix, m_viewProjectionMatrix;
	SMatrix4 m_translationMatrix, m_rotationMatrix, m_scaleMatrix;
    bool m_releaseViewport { false };
};

#endif