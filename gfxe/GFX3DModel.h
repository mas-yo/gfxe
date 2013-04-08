//
//  GFX3DModel.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFX3DModel__
#define __gfxe_GFX3DModel__

#include "gfx.h"
#include "GFXShaderProgram.h"
#include "GFX3DMesh.h"
#include "RTOwn.h"
#include <vector>

namespace gfxe
{
    class PredObjFree
    {
    public:
        void operator()(OBJ* obj) { OBJ_free( obj ); }
    };    

    class GFX3DModel
    {
    private:
        ragtime::own<OBJ> m_ownObj;
        std::vector< ragtime::own<GFX3DMesh> > m_vecMesh;

    public:
        GFX3DModel();
        virtual ~GFX3DModel();
        
        void Create( const char* fileName );
        OBJ* GetOBJ() { return (OBJ*)m_ownObj; }
        GFX3DMesh* GetMesh( int idx ) { return m_vecMesh.at(idx); }
    };
}

#endif /* defined(__gfxe_GFX3DModel__) */
