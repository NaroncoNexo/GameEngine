//
//  Skybox.cpp
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "Skybox.h"
#include "Camera.h"
#include "IndexedModel.h"

int CSkybox::s_referenceCounter = 0;
IVertexArray *CSkybox::s_mesh = nullptr;
IShaderProgram *CSkybox::s_shader = nullptr;

CSkybox::CSkybox(IRenderDevice *renderDevice, ITexture *cubeMapTexture)
{
    m_renderDevice = renderDevice;
    m_cubeMapTexture = cubeMapTexture;
    
    if (s_referenceCounter++ == 0)
    {
        CIndexedModel model(eDRAWMODE_TRIANGLESTRIP);
        
        SVector3 vertices[] =
        {
            {  1, -1,  1 },
            { -1, -1,  1 },
            {  1,  1,  1 },
            { -1,  1,  1 },
            {  1, -1, -1 },
            { -1, -1, -1 },
            {  1,  1, -1 },
            { -1,  1, -1 },
        };
        
        Index_t indices[] =
        {
            0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
        };
        
        model.SetVertexData((const float *)vertices, 8, eVERTEXDESC_POSITION);
        model.SetIndexData(indices, 14);
        
        s_mesh = m_renderDevice->CreateVertexArray(&model);
        
        std::string vertexShaderSourceCode = "#version 330\nlayout(location = 0) in vec4 a_Position;out vec3 v_Position;uniform mat4 u_RotationMatrix;void main() { v_Position = a_Position.xyz; gl_Position = u_RotationMatrix * a_Position; }";
        std::string fragmentShaderSourceCode = "#version 330\nin vec3 v_Position;out vec4 v_FragColor;uniform samplerCube u_SkyboxTexture;void main() { vec3 textureDirection = normalize(v_Position); v_FragColor = texture(u_SkyboxTexture, textureDirection); }";
        
        s_shader = m_renderDevice->CreateShaderProgram(vertexShaderSourceCode, fragmentShaderSourceCode);
    }
}

CSkybox::~CSkybox()
{
    if (--s_referenceCounter == 0)
    {
        m_renderDevice->ReleaseShaderProgram(s_shader);
        m_renderDevice->ReleaseVertexArray(s_mesh);
    }
}

void CSkybox::Render(CCamera *camera)
{
    s_shader->Use();
    s_shader->SetProperties();
    
    s_shader->SetUniformMatrix4("u_RotationMatrix", camera->GetProjectionMatrix() * camera->GetRotationMatrix());
    s_shader->BindTexture("u_SkyboxTexture", m_cubeMapTexture);
    
    s_mesh->Render();
}