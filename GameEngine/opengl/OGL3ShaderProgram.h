//
//  OGL3ShaderProgram.h
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__OGL3ShaderProgram__
#define __3DGameEngine__OGL3ShaderProgram__

#include <IShaderProgram.h>
#include <OpenGL/gl3.h>
#include "OGL3Shader.h"

struct SOGL3Uniform
{
	GLenum GLType;
	GLuint GLLocation;
};

class COGL3ShaderProgram : public IShaderProgram
{
public:
    COGL3ShaderProgram();
    COGL3ShaderProgram(const std::string &vertexShaderSourceCode, const std::string &fragmentShaderSourceCode);
    ~COGL3ShaderProgram();
    
    virtual void AddShader(IShader *shader);
    virtual void Build();

    virtual void SetProperties() const;
    virtual void Use() const;
    
    virtual void SetUniformInt(const std::string &uniformName, int value) const;
    virtual void SetUniformFloat(const std::string &uniformName, float value) const;
    virtual void SetUniformVector3(const std::string &uniformName, const SVector3 &vector) const;
    virtual void SetUniformColor(const std::string &uniformName, const SColor &color) const;
    virtual void SetUniformMatrix4(const std::string &uniformName, const SMatrix4 &matrix) const;
    
    virtual void SetUniformDataInt(const std::string &uniformName, const void *value) const;
    virtual void SetUniformDataFloat(const std::string &uniformName, const void *value) const;
    virtual void SetUniformDataVector3(const std::string &uniformName, const void *vector) const;
    virtual void SetUniformDataColor(const std::string &uniformName, const void *color) const;
    virtual void SetUniformDataMatrix4(const std::string &uniformName, const void *matrix) const;
    
    virtual void BindTexture(const std::string &textureName, const ITexture *texture, int textureSlot) const;

    inline GLuint GetProgram() const { return m_program; }
    virtual const std::vector<std::string> &GetUniforms() const { return m_uniformNames; }

private:
    GLuint m_program { 0 };
    std::map<std::string, SOGL3Uniform> m_uniforms;
    std::vector<std::string> m_uniformNames;
};

#endif