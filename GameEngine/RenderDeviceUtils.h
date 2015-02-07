//
//  RenderDeviceUtils.h
//  3DGameEngine
//
//  Created by Johannes Roth on 04.02.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__RenderDeviceUtils__
#define __GameEngine__RenderDeviceUtils__

#include "Environment.h"

extern ITexture *LoadTexture2D(const std::string &name);
extern ITexture *LoadTextureCubeMap(const std::string &name);
extern IShaderProgram *CreateShaderProgram(IShader *vertexShader, IShader *fragmentShader);
extern IShaderProgram *CreateShaderProgram(const std::string &vertexShaderSourceCode, const std::string &fragmentShaderSourceCode);

#endif
