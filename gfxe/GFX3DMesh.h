//
//  GFX3DMesh.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFX3DMesh__
#define __gfxe_GFX3DMesh__

#include "RTObject.h"
#include "gfx.h"
#include "GFXShaderProgram.h"

namespace gfxe {

    class GFX3DMesh : public ragtime::RTObject
    {
    private:
        OBJMESH* m_pObjMesh; //reference only
        GFXShaderProgram* m_pShader;

    public:
        GFX3DMesh( OBJMESH* pObjMesh, GFXShaderProgram* pShader );
        virtual ~GFX3DMesh();

        void Create();
        GFXShaderProgram* GetShaderProgram() { return m_pShader; }

    };
}


#endif /* defined(__gfxe_test__GFX3DMesh__) */
