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
        int _meshIndex;
        GFX3DModelInfo* _modelInfo = nullptr;
        GFX3DMeshInfo* _meshInfo = nullptr;
//        std::unique_ptr<GFXShaderProgram> m_unqShader;

    public:
        GFX3DMesh( GFX3DModelInfo* modelInfo, GFX3DMeshInfo* meshInfo, int meshIdx );
        virtual ~GFX3DMesh();

        void renderSolid();
        void renderAlpha();

//        GFXShaderProgram* GetShaderProgram() { return m_unqShader.get(); }

    };
}


#endif /* defined(__gfxe_test__GFX3DMesh__) */
