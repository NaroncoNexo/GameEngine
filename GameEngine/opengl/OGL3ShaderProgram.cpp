//
//  OGL3ShaderProgram.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 17.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3ShaderProgram.h"
#include <iostream>

GLuint LoadShader(GLenum shaderType, const std::string &sourceCode);

COGL3ShaderProgram::COGL3ShaderProgram()
{
    m_program = glCreateProgram();
}

COGL3ShaderProgram::COGL3ShaderProgram(const std::string &vertexShaderSourceCode, const std::string &fragmentShaderSourceCode)
{
    m_program = glCreateProgram();
    
    COGL3Shader *vertexShader = new COGL3Shader(eSHADERTYPE_VERTEX, vertexShaderSourceCode);
    COGL3Shader *fragmentShader = new COGL3Shader(eSHADERTYPE_FRAGMENT, fragmentShaderSourceCode);
    
    AddShader(vertexShader);
    AddShader(fragmentShader);
    
    Build();
    
    delete vertexShader;
    delete fragmentShader;
}

COGL3ShaderProgram::~COGL3ShaderProgram()
{
    glDeleteProgram(m_program);
}

void COGL3ShaderProgram::AddShader(IShader *shader)
{
    m_attachedShaders.push_back(shader);
}

void COGL3ShaderProgram::Build()
{
    for (const auto &shader : m_attachedShaders)
    {
        glAttachShader(m_program, ((COGL3Shader *)shader)->GetGLShader());
    }
    
    glBindFragDataLocation(m_program, 0, "v_FragColor");
    
    glLinkProgram(m_program);
    glValidateProgram(m_program);
    
    int numActiveUniforms = -1;
    glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
    
    for (int i = 0; i < numActiveUniforms; ++i)
    {
        int name_len = -1, num = -1;
        GLenum type = GL_ZERO;
        char name[128];
        glGetActiveUniform(m_program, GLuint(i), sizeof(name)-1, &name_len, &num, &type, name);
        name[name_len] = 0;
        GLuint location = glGetUniformLocation(m_program, name);
        
        SOGL3Uniform uniform = { type, location };
        m_uniforms[std::string(name)] = uniform;
        m_uniformNames.push_back(std::string(name));
    }
    
    SetBool(eSHADERPROPERTY_DEPTHTESTENABLED, true);
    SetInt(eSHADERPROPERTY_DEPTHTESTCOMPAREFUNC, eCOMPAREFUNC_LOWEREQUAL);
    SetBool(eSHADERPROPERTY_DEPTHMASKENABLED, true);
    SetBool(eSHADERPROPERTY_BLENDENABLED, false);
    SetInt(eSHADERPROPERTY_BLENDEQUATION, eBLENDEQUATION_ADD);
    SetInt(eSHADERPROPERTY_BLENDSOURCEFUNC, eBLENDFUNC_ZERO);
    SetInt(eSHADERPROPERTY_BLENDDESTFUNC, eBLENDFUNC_ZERO);
    SetInt(eSHADERPROPERTY_RENDERMODE, eRENDERMODE_SOLID);
    SetBool(eSHADERPROPERTY_CULLFACEENABLED, true);
    SetInt(eSHADERPROPERTY_CULLFACE, eCULLFACE_BACK);
    SetInt(eSHADERPROPERTY_FRONTFACE, eFRONTFACE_CLOCKWISE);
}

void COGL3ShaderProgram::SetProperties() const
{
    if (m_boolValues[eSHADERPROPERTY_DEPTHTESTENABLED])
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_NEVER+m_intValues[eSHADERPROPERTY_DEPTHTESTCOMPAREFUNC]);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    glDepthMask(m_boolValues[eSHADERPROPERTY_DEPTHMASKENABLED]);

    if (m_boolValues[eSHADERPROPERTY_BLENDENABLED])
    {
    	glEnable(GL_BLEND);
    	glBlendEquation(GL_FUNC_ADD+m_intValues[eSHADERPROPERTY_BLENDEQUATION]);
    	glBlendFunc(GL_ZERO+m_intValues[eSHADERPROPERTY_BLENDSOURCEFUNC], GL_ZERO+m_intValues[eSHADERPROPERTY_BLENDDESTFUNC]);
    }
    else
    {
    	glDisable(GL_BLEND);
    }

    glPolygonMode(GL_FRONT_AND_BACK, m_intValues[eSHADERPROPERTY_RENDERMODE]==eRENDERMODE_SOLID?GL_FILL:GL_LINE);
    
    if (m_boolValues[eSHADERPROPERTY_CULLFACEENABLED])
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT+m_intValues[eSHADERPROPERTY_CULLFACE]);
        glFrontFace(GL_CW+m_intValues[eSHADERPROPERTY_FRONTFACE]);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
}

void COGL3ShaderProgram::Use() const
{
    glUseProgram(m_program);
}

//#define TEMP_CHECKCONTAINS(s){if(m_uniforms.find(s)==m_uniforms.end())printf("FAILED TO FIND %s\n", s);}
#define TEMP_CHECKCONTAINS(s) ((void)0);

void COGL3ShaderProgram::SetUniformInt(const std::string &uniformName, int value) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform1i(m_uniforms.at(uniformName).GLLocation, value);
}

void COGL3ShaderProgram::SetUniformFloat(const std::string &uniformName, float value) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform1f(m_uniforms.at(uniformName).GLLocation, value);
}

void COGL3ShaderProgram::SetUniformVector3(const std::string &uniformName, const SVector3 &vector) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform3f(m_uniforms.at(uniformName).GLLocation, vector.x, vector.y, vector.z);
}

void COGL3ShaderProgram::SetUniformColor(const std::string &uniformName, const SColor &color) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform4f(m_uniforms.at(uniformName).GLLocation, color.r, color.g, color.b, color.a);
}

void COGL3ShaderProgram::SetUniformMatrix4(const std::string &uniformName, const SMatrix4 &matrix) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniformMatrix4fv(m_uniforms.at(uniformName).GLLocation, 1, GL_TRUE, (const float *)matrix.m);
}

void COGL3ShaderProgram::SetUniformDataInt(const std::string &uniformName, const void *value) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform1iv(m_uniforms.at(uniformName).GLLocation, 1, (const GLint *)value);
}

void COGL3ShaderProgram::SetUniformDataFloat(const std::string &uniformName, const void *value) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform1fv(m_uniforms.at(uniformName).GLLocation, 1, (const GLfloat *)value);
}

void COGL3ShaderProgram::SetUniformDataVector3(const std::string &uniformName, const void *vector) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform3fv(m_uniforms.at(uniformName).GLLocation, 1, (const GLfloat *)vector);
}

void COGL3ShaderProgram::SetUniformDataColor(const std::string &uniformName, const void *color) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniform4fv(m_uniforms.at(uniformName).GLLocation, 1, (const GLfloat *)color);
}

void COGL3ShaderProgram::SetUniformDataMatrix4(const std::string &uniformName, const void *matrix) const
{
    TEMP_CHECKCONTAINS(uniformName.c_str());
    glUniformMatrix4fv(m_uniforms.at(uniformName).GLLocation, 1, GL_TRUE, (const float *)matrix);
}

void COGL3ShaderProgram::BindTexture(const std::string &textureName, const ITexture *texture, int textureSlot) const
{
    texture->Bind(textureSlot);
    SetUniformInt(textureName, textureSlot);
}