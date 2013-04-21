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
#include "GFXResourceManager.h"
#include "stlutil.h"

using namespace gfxe;

GFX3DModel::GFX3DModel()
{
    
}

GFX3DModel::~GFX3DModel()
{
}

void GFX3DModel::Create( const char *fileName )
{
    bool result = GFXResourceManager<GFX3DModelInfo>::Instance()->Load( fileName, m_shrModelInfo );
    if( !result ) return;

    for( int i = 0; i < m_shrModelInfo->n_objmesh; ++i ) {

        GFX3DMesh* pMesh = new GFX3DMesh( &m_shrModelInfo->objmesh[i] );
        pMesh->Create();

        m_vecMesh.resize( m_vecMesh.size() + 1 );
        m_vecMesh[ m_vecMesh.size() - 1 ].reset( pMesh );
    }

}
