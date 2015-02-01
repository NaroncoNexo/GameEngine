//
//  EE_Skybox.h
//  3DGameEngine
//
//  Created by Johannes Roth on 06.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "EE_Skybox.h"
#include "EE_Mesh.h"
#include "IShaderProgram.h"

extern const EntityConfigurator_t g_SkyboxConfigurator = [] (CEntity *entity, int argc, va_list args)
{
    assert(argc == 2);

    CMeshRendererExtension *meshRenderer = entity->AddExtension<CMeshRendererExtension>(2, va_arg(args, IVertexArray *), va_arg(args, CMaterial *));
};