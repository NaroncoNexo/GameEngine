//
//  Material.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 21.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "Material.h"

const std::map<int, std::string> g_materialTextureIdentifiers =
{
    { eMATERIALTEXTURE_DIFFUSE, "u_DiffuseTexture" },
    { eMATERIALTEXTURE_SKYBOX, "u_SkyboxTexture" }
};

UnknownUniformLookUp_t g_sharedUniformLookUp =
{
    { "u_WorldMatrix", { eUNIFORMDATATYPE_MAT4, nullptr } },
    { "u_WorldViewProjectionMatrix", { eUNIFORMDATATYPE_MAT4, nullptr } },
    { "u_TextureMatrix", { eUNIFORMDATATYPE_MAT4, nullptr } },
    { "u_RotationMatrix", { eUNIFORMDATATYPE_MAT4, nullptr } },
    { "u_CameraPosition", { eUNIFORMDATATYPE_VEC3, nullptr } },
    { "u_PlanetRadius", { eUNIFORMDATATYPE_FLOAT, nullptr } },
    { "u_PlanetCenter", { eUNIFORMDATATYPE_VEC3, nullptr } },
};

const std::map<int, UniformShaderBindFunc_t> g_uniformDataTypeBindingFunctions =
{
    { eUNIFORMDATATYPE_INT,   [] (const IShaderProgram *s, const std::string &n, const void *data) { s->SetUniformDataInt(n, data);     } },
    { eUNIFORMDATATYPE_FLOAT, [] (const IShaderProgram *s, const std::string &n, const void *data) { s->SetUniformDataFloat(n, data);   } },
    { eUNIFORMDATATYPE_VEC3,  [] (const IShaderProgram *s, const std::string &n, const void *data) { s->SetUniformDataVector3(n, data); } },
    { eUNIFORMDATATYPE_COLOR, [] (const IShaderProgram *s, const std::string &n, const void *data) { s->SetUniformDataColor(n, data);   } },
    { eUNIFORMDATATYPE_MAT4,  [] (const IShaderProgram *s, const std::string &n, const void *data) { s->SetUniformDataMatrix4(n, data); } },
};

void CMaterial::RenderShaderPasses(const UnknownUniformLookUp_t &uniformLookUp, const std::function<void (const IShaderProgram *shaderProgram)> &renderCallback) const
{
    for (const auto &shaderProgram : m_shaderPasses)
    {
        shaderProgram->Use();
        shaderProgram->SetProperties();
        
        BindMaterialUniforms(shaderProgram);
        
        renderCallback(shaderProgram);
    }
}

void CMaterial::BindMaterialUniforms(const IShaderProgram *shader) const
{
    for (const auto &color : m_colors)
    {
        shader->SetUniformColor(color.first, color.second);
    }
    
    for (const auto &materialTexture : m_textures)
    {
        shader->BindTexture(materialTexture.first, materialTexture.second.texture, materialTexture.second.textureSlot);
    }
}

void CMaterial::BindUnknownUniforms(const IShaderProgram *shader, const UnknownUniformLookUp_t &uniformLookUp) const
{
    for (auto uniform : shader->GetUniforms())
    {
        auto uniformDataIter = uniformLookUp.find(uniform);
        if (uniformDataIter != uniformLookUp.end() && uniformDataIter->second.data)
        {
            g_uniformDataTypeBindingFunctions.at(uniformDataIter->second.type)(shader, uniform, uniformDataIter->second.data);
        }
    }
}