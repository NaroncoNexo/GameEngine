//
//  Material.h
//  3DGameEngine
//
//  Created by Johannes Roth on 21.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__Material__
#define __3DGameEngine__Material__

#include <string>
#include <map>
#include <functional>
#include <assert.h>

#include "Math3D.h"
#include "ITexture.h"
#include "IShaderProgram.h"

struct SMaterialTexture
{
	const ITexture *texture;
	int textureSlot;
};

enum
{
	eMATERIALTEXTURE_DIFFUSE,
	eMATERIALTEXTURE_SKYBOX,
	eMATERIALTEXTURE_COUNT
};

extern const std::map<int, std::string> g_materialTextureIdentifiers;

enum
{
    eUNIFORMDATATYPE_INT,
    eUNIFORMDATATYPE_FLOAT,
    eUNIFORMDATATYPE_VEC3,
    eUNIFORMDATATYPE_COLOR,
    eUNIFORMDATATYPE_MAT4
};

typedef std::function<void (const IShaderProgram *, const std::string &, const void *)> UniformShaderBindFunc_t;
extern const std::map<int, UniformShaderBindFunc_t> g_uniformDataTypeBindingFunctions;

struct SUniformData
{
    int type;
    const void *data;
};

typedef std::map<std::string, SUniformData> UnknownUniformLookUp_t;

extern UnknownUniformLookUp_t g_sharedUniformLookUp;

class CMaterial
{
public:
    void RenderShaderPasses(const UnknownUniformLookUp_t &uniformLookUp, const std::function<void (const IShaderProgram *shaderProgram)> &renderCallback) const;
    
    void BindMaterialUniforms(const IShaderProgram *shaderProgram) const;
    void BindUnknownUniforms(const IShaderProgram *shaderProgram, const UnknownUniformLookUp_t &uniformLookUp) const;
    
    inline void AddShaderPass(IShaderProgram *shaderProgram) { m_shaderPasses.push_back(shaderProgram); }
    
    inline void SetShader(IShaderProgram *shaderProgram)
    {
        if (m_shaderPasses.size() == 0)
            m_shaderPasses.push_back(shaderProgram);
        else
            m_shaderPasses[0] = shaderProgram;
    }
    
    inline void SetTexture(int textureType, const ITexture *texture)
    {
        assert(textureType >= 0 && textureType < eMATERIALTEXTURE_COUNT);
        SMaterialTexture tex = { texture, textureType /* Texture type is used to specify the texture slot in OpenGL */ };
        m_textures[g_materialTextureIdentifiers.at(textureType)] = tex;
    }
    
    inline void SetTextureOffset(const SVector2 &textureOffset) { m_textureOffset = textureOffset; }
    inline void SetTextureScale(const SVector2 &textureScale) { m_textureScale = textureScale; }
    
    inline const std::vector<IShaderProgram *> &GetShaderPasses() const { return m_shaderPasses; }
    inline SVector2 GetTextureOffset() const { return m_textureOffset; }
    inline SVector2 GetTextureScale() const { return m_textureScale; }
    
	inline SMatrix4 GetTextureMatrix() const { return { m_textureScale.x, 0, 0, m_textureOffset.x, 0, m_textureScale.y, 0, m_textureOffset.y, 0, 0, 1, 0, 0, 0, 0, 1 }; }
    
private:
    std::vector<IShaderProgram *> m_shaderPasses;
    std::map<std::string, SColor> m_colors;
    std::map<std::string, SMaterialTexture> m_textures;
	SVector2 m_textureOffset{ 0, 0 }, m_textureScale{ 1, 1 };
};

#endif
