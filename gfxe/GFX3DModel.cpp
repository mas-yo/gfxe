//
//  GFX3DModel.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFX3DModel.h"
#include "gfxe.h"
#include "glutil.h"
#include "GFXShaderSimple.h"
#include "stlutil.h"

using namespace gfxe;

GFX3DModel::GFX3DModel() : m_unqModelInfo()
{
    
}

GFX3DModel::~GFX3DModel()
{
}

void GFX3DModel::Create( const char *fileName )
{
    GFX3DModelInfo* pObj = OBJ_load((char*)fileName, 1);

    create_vbo( pObj );

    for( int i = 0; i < pObj->n_objmesh; ++i ) {

        GFX3DMesh* pMesh = new GFX3DMesh( &pObj->objmesh[i] );
        pMesh->Create();

        m_vecMesh.resize( m_vecMesh.size() + 1 );
        m_vecMesh[ m_vecMesh.size() - 1 ].reset( pMesh );
    }

    m_unqModelInfo.reset( pObj );
}