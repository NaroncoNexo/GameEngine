//
//  EE_Mesh.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 05.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "EE_Mesh.h"
#include "Camera.h"

void CShaderSortedMeshRenderer::Render(CCamera *camera)
{
    SVector3 cameraPosition = camera->GetTransform()->GetTranslation();
    SMatrix4 rotationMatrix = camera->GetProjectionMatrix() * camera->GetRotationMatrix();
    
    g_sharedUniformLookUp.at("u_RotationMatrix").data = &rotationMatrix;
    g_sharedUniformLookUp.at("u_CameraPosition").data = &cameraPosition;
    
    for (const auto &materialGroup : m_meshRendererExtensions)
    {
        const CMaterial *material = materialGroup.first;
        const std::vector<const CMeshRendererExtension *> &meshRendererExtensions = materialGroup.second;
        
        if (material == nullptr)
        {
            continue;
        }
        
        SMatrix4 textureMatrix = material->GetTextureMatrix();
        
        g_sharedUniformLookUp.at("u_TextureMatrix").data = &textureMatrix;
        
        material->RenderShaderPasses(g_sharedUniformLookUp, [this, material, meshRendererExtensions, camera] (const IShaderProgram *shaderProgram)
        {
            for (const auto &meshRendererExtension : meshRendererExtensions)
            {
                SMatrix4 worldMatrix = meshRendererExtension->GetEntity()->GetTransformationMatrix();
                SMatrix4 worldViewProjectionMatrix = camera->GetViewProjectionMatrix() * worldMatrix;
                
                g_sharedUniformLookUp.at("u_WorldMatrix").data = &worldMatrix;
                g_sharedUniformLookUp.at("u_WorldViewProjectionMatrix").data = &worldViewProjectionMatrix;
                
                material->BindUnknownUniforms(shaderProgram, g_sharedUniformLookUp);
                
                meshRendererExtension->GetModel()->Render();
            }
        });
    }
    
    g_sharedUniformLookUp.at("u_WorldMatrix").data = nullptr;
    g_sharedUniformLookUp.at("u_WorldViewProjectionMatrix").data = nullptr;
    g_sharedUniformLookUp.at("u_TextureMatrix").data = nullptr;
    g_sharedUniformLookUp.at("u_RotationMatrix").data = nullptr;
    g_sharedUniformLookUp.at("u_CameraPosition").data = nullptr;
}

void CShaderSortedMeshRenderer::AddMeshRendererExtension(CMeshRendererExtension *meshRendererExtension)
{
    auto materialIterator = m_meshRendererExtensions.find(meshRendererExtension->GetMaterial());
    
    if (materialIterator != m_meshRendererExtensions.end())
        materialIterator->second.push_back(meshRendererExtension);
    else
        m_meshRendererExtensions[meshRendererExtension->GetMaterial()] = { meshRendererExtension };
}

void CShaderSortedMeshRenderer::RemoveMeshRendererExtension(CMeshRendererExtension *meshRendererExtension)
{
    auto iter = m_meshRendererExtensions.find(meshRendererExtension->GetMaterial());
    
    iter->second.erase(std::find(iter->second.begin(), iter->second.end(), meshRendererExtension));
    if (iter->second.size() == 0)
    {
        m_meshRendererExtensions.erase(iter);
    }
}

void CShaderSortedMeshRenderer::SwitchMeshRendererExtensionMaterial(CMeshRendererExtension *meshRendererExtension, const CMaterial *oldMaterial)
{
    std::vector<const CMeshRendererExtension *> meshRendererExtensionList = m_meshRendererExtensions[oldMaterial];
    
    meshRendererExtensionList.erase(std::find(meshRendererExtensionList.begin(), meshRendererExtensionList.end(), meshRendererExtension));
    if (meshRendererExtensionList.size() == 0)
    {
        m_meshRendererExtensions.erase(m_meshRendererExtensions.find(oldMaterial));
    }
    
    auto iter = m_meshRendererExtensions.find(meshRendererExtension->GetMaterial());
    if (iter != m_meshRendererExtensions.end())
        iter->second.push_back(meshRendererExtension);
    else
        m_meshRendererExtensions[meshRendererExtension->GetMaterial()] = { meshRendererExtension };
}

void CMeshRendererExtension::Create(int argc, va_list args)
{
}

void CMeshRendererExtension::Release()
{
}

void CMeshRendererExtension::OnAdd()
{
    CShaderSortedMeshRenderer::GetInstance()->AddMeshRendererExtension(this);
}

void CMeshRendererExtension::OnRemove()
{
    CShaderSortedMeshRenderer::GetInstance()->RemoveMeshRendererExtension(this);
}

void CMeshRendererExtension::Update()
{
}

void CMeshRendererExtension::Render(const SEntityExtensionRenderParams &params)
{
}

void CMeshRendererExtension::SetModel(const IVertexArray *model)
{
    m_model = model;
}

void CMeshRendererExtension::SetMaterial(const CMaterial *material)
{
    CShaderSortedMeshRenderer::GetInstance()->RemoveMeshRendererExtension(this);
    m_material = material;
    CShaderSortedMeshRenderer::GetInstance()->AddMeshRendererExtension(this);
}
