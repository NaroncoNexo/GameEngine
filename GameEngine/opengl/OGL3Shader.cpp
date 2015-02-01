//
//  OGL3Shader.cpp
//  GameEngine
//
//  Created by Johannes Roth on 25.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3Shader.h"
#include <map>
#include <iostream>

const std::map<int, GLenum> GLShaderTypes =
{
    { eSHADERTYPE_VERTEX, GL_VERTEX_SHADER },
    { eSHADERTYPE_FRAGMENT, GL_FRAGMENT_SHADER }
};

GLuint LoadShader(GLenum shaderType, const std::string &sourceCode);

COGL3Shader::COGL3Shader(int shaderType, const std::string &sourceCode)
{
    m_GLShader = glCreateShader(GLShaderTypes.at(shaderType));
    
    auto sourceString = sourceCode.c_str();
    auto sourceLength = (int)sourceCode.length();
    
    glShaderSource(m_GLShader, 1, &sourceString, &sourceLength);
    glCompileShader(m_GLShader);
    
    int compiled = 0;
    glGetShaderiv(m_GLShader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        int maxLength = 0;
        glGetShaderiv(m_GLShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        char errorLog[maxLength];
        glGetShaderInfoLog(m_GLShader, maxLength, &maxLength, errorLog);
        
        glDeleteShader(m_GLShader);
        
        std::cerr << "SHADER: Error compiling shader" << std::endl;
        std::cerr << errorLog << std::endl;
    }
}

COGL3Shader::~COGL3Shader()
{
    glDeleteShader(m_GLShader);
}