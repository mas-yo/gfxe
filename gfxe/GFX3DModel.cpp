//
//  GFX3DModel.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFX3DModel.h"
#include "gfx.h"
#include "glutil.h"
#include "GFXShaderSimple.h"
#include "stlutil.h"
#include "GFXShaderManager.h"

using namespace gfxe;

GFX3DModel::GFX3DModel()
{
    
}

GFX3DModel::~GFX3DModel()
{
    if( m_pObj ) {
        delete_all( m_vecMesh );
        m_pObj = OBJ_free( m_pObj );
    }
}

void GFX3DModel::Create( const char *fileName )
{
    m_pObj = OBJ_load((char*)fileName, 1);

    create_vbo( m_pObj, 0 );

    for( int i = 0; i < m_pObj->n_objmesh; ++i ) {

        GFX3DMesh* pMesh = new GFX3DMesh( &m_pObj->objmesh[i], GFXShaderManager::s_shaderSimple );
        pMesh->Create();
        
        m_vecMesh.push_back( pMesh );
    }
}