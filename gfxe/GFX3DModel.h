//
//  GFX3DModel.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFX3DModel__
#define __gfxe_GFX3DModel__

#include "RTObject.h"
#include "gfx.h"
#include "GFXShaderProgram.h"
#include "GFX3DMesh.h"
#include <vector>

namespace gfxe
{
    class GFX3DModel : public ragtime::RTObject
    {
    private:
        OBJ* m_pObj;
        std::vector<GFX3DMesh*> m_vecMesh;

    public:
        GFX3DModel();
        virtual ~GFX3DModel();
        
        void Create( const char* fileName );
        OBJ* GetOBJ() { return m_pObj; }
        GFX3DMesh* GetMesh( int idx ) { return m_vecMesh.at(idx); }
    };
}

#endif /* defined(__gfxe_GFX3DModel__) */
