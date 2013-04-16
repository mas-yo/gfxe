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

    // meshごとにshaderのインスタンスを持ち、shaderに対して見るべき変数の
    // アドレスを渡しておく
    class GFX3DMesh : public IRenderable
    {
    private:
        GFX3DMeshInfo* m_pMeshInfo; //reference only
        std::unique_ptr<GFXShaderProgram> m_unqShader;

    public:
        GFX3DMesh( GFX3DMeshInfo* pMeshInfo );
        virtual ~GFX3DMesh();

        void Create();
        virtual void Render() override;

        GFXShaderProgram* GetShaderProgram() { return m_unqShader.get(); }

    };
}


#endif /* defined(__gfxe_test__GFX3DMesh__) */
