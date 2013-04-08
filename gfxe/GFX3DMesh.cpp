//
//  GFX3DMesh.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFX3DMesh.h"
#include "gfx.h"
#include "glutil.h"

using namespace gfxe;

GFX3DMesh::GFX3DMesh( OBJMESH* pObjMesh, GFXShaderProgram* pShader ) : m_prObjMesh( pObjMesh ), m_prShader( pShader )
{

}

GFX3DMesh::~GFX3DMesh()
{
    
}

void GFX3DMesh::Create()
{
    create_vao(m_prObjMesh, m_prShader->GetProgram() );
}