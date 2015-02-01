//
//  OGL3Shader.h
//  GameEngine
//
//  Created by Johannes Roth on 25.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__OGL3Shader__
#define __GameEngine__OGL3Shader__

#include <IShader.h>
#include <OpenGL/gl3.h>
#include <string>

class COGL3Shader : public IShader
{
public:
    COGL3Shader(int shaderType, const std::string &sourceCode);
    ~COGL3Shader();
    
    inline GLuint GetGLShader() const { return m_GLShader; }
    
private:
    GLuint m_GLShader { 0 };
};

#endif /* defined(__GameEngine__OGL3Shader__) */
