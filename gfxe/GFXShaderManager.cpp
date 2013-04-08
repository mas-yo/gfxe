//
//  GFXShaderManager.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXShaderManager.h"

using namespace gfxe;

GFXShaderSimple* GFXShaderManager::s_shaderSimple;

void GFXShaderManager::Create()
{
    s_shaderSimple = new GFXShaderSimple();
    s_shaderSimple->Create();
}

void GFXShaderManager::Clean()
{
    delete s_shaderSimple;
}