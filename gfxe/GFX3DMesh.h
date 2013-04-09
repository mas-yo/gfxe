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
#include "IRenderable.h"
#include "GFXShaderProgram.h"

namespace gfxe {

    class GFX3DMesh : public IRenderable
    {
    private:
        GFX3DMeshInfo* m_pMeshInfo; //reference only
        GFXShaderProgram* m_pShader;

    public:
        GFX3DMesh( GFX3DMeshInfo* pMeshInfo, GFXShaderProgram* pShader );
        virtual ~GFX3DMesh();

        void Create();
        virtual void Render() override;

        GFXShaderProgram* GetShaderProgram() { return m_pShader; }

    };
}


#endif /* defined(__gfxe_test__GFX3DMesh__) */
