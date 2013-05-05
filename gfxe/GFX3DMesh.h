//
//  GFX3DMesh.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFX3DMesh__
#define __gfxe_GFX3DMesh__

#include "gfxe.h"
#include "GFXShaderProgram.h"

namespace gfxe {

    class GFX3DMesh
    {
    private:
        int m_nMeshIndex;
        GFX3DModelInfo* m_pModelInfo;
        GFX3DMeshInfo* m_pMeshInfo; //reference only
//        std::unique_ptr<GFXShaderProgram> m_unqShader;

    public:
        GFX3DMesh( GFX3DModelInfo* pModelInfo, GFX3DMeshInfo* pMeshInfo, int meshIdx );
        virtual ~GFX3DMesh();

        void RenderSolid();
        void RenderAlpha();

//        GFXShaderProgram* GetShaderProgram() { return m_unqShader.get(); }

    };
}


#endif /* defined(__gfxe_test__GFX3DMesh__) */
