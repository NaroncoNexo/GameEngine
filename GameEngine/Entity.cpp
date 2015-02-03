//
//  Entity.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 05.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "Entity.h"
#include "Camera.h"
#include "EE_Mesh.h"

CEntity::CEntity()
{
	m_transform = new CTransform;
}

CEntity::CEntity(ISubSystem *subSystem)
{
	m_subSystem = subSystem;
	m_transform = new CTransform;
}

CEntity::~CEntity()
{
	for (auto extension : m_extensions)
	{
		extension->OnRemove();
		extension->Release();
		delete extension;
	}
	
	for (auto child : m_children)
	{
		if (child->IsAutoreleasing())
		{
			delete child;
		}
	}
	
	delete m_transform;
}

void CEntity::AddChild(CEntity *child)
{
	if (child->m_parent != nullptr)
	{
		child->RemoveFromParent();
	}

	child->m_subSystem = m_subSystem;
	
	m_children.push_back(child);
	child->m_parent = this;
}

CEntity *CEntity::AddChild(EntityConfigurator_t Configurator, int argc, ...)
{
	CEntity *child = new CEntity(m_subSystem);
	
	m_children.push_back(child);
	child->m_parent = this;
	child->m_autoreleasing = true;

	va_list args;
	va_start(args, argc);

	Configurator(child, argc, args);

	va_end(args);

	return child;
}

void CEntity::RemoveAllChildren()
{
	for (auto child : m_children)
	{
		child->m_parent = nullptr;
	}
	
	m_children.clear();
}

void CEntity::RemoveFromParent()
{
	if (m_parent == nullptr)
	{
		return;
	}
	
	m_parent->m_children.erase(std::find(m_children.begin(), m_children.end(), this));
	m_parent = nullptr;
}

void CEntity::Update()
{
	m_transform->UpdateMatrices();

	UpdateExtensions();
	
	for (auto child : m_children)
	{
		child->Update();
	}
}

void CEntity::Render(const SEntityExtensionRenderParams &params)
{
	RenderExtensions(params);
	
	for (auto child : m_children)
	{
		child->Render(params);
	}
}

void CEntity::UpdateExtensions()
{
	for (auto extension : m_extensions)
	{
		extension->Update();
	}
}

void CEntity::RenderExtensions(const SEntityExtensionRenderParams &params)
{
	for (auto extension : m_extensions)
	{
		extension->Render(params);
	}
}

SMatrix4 CEntity::GetTransformationMatrix() const
{
	return m_parent != nullptr ? m_parent->GetTransformationMatrix() * m_transform->GetTransformationMatrix() : m_transform->GetTransformationMatrix();
}

CEntityRoot::CEntityRoot() : CEntity()
{
}

CEntityRoot::CEntityRoot(ISubSystem *subSystem) : CEntity(subSystem)
{
}

CEntityRoot::~CEntityRoot()
{
}

void CEntityRoot::Update()
{
    for (auto &camera : m_cameras)
    {
        camera->UpdateMatrices();
    }
}

void CEntityRoot::Render()
{
    SEntityExtensionRenderParams params;
    
    for (auto &camera : m_cameras)
    {
        camera->GetViewport()->Set();
        camera->GetClearMethod()->Clear(camera, m_subSystem->GetRenderDevice());
        
        params.camera = camera;
        
        CShaderSortedMeshRenderer::GetInstance()->Render(camera);
        
        for (auto &child : m_children)
        {
            child->Render(params);
        }
    }
}