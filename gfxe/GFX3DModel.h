//
//  GFX3DModel.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFX3DModel__
#define __gfxe_GFX3DModel__

#include "gfxe.h"
#include "GFXShaderProgram.h"
#include "GFX3DMesh.h"
#include <vector>

namespace gfxe
{
    class GFX3DModel
    {
    private:
        std::shared_ptr<GFX3DModelInfo> _modelInfo;
        std::vector< std::unique_ptr<GFX3DMesh> > _meshList;

    public:
        GFX3DModel();
        virtual ~GFX3DModel();
        
        void initialize( const char* fileName );
//        GFX3DModelInfo* GetModelInfo() { return (GFX3DModelInfo*)m_ownModelInfo; }
//        GFX3DMesh* GetMesh( int idx ) { return m_vecMesh.at(idx); }
    };
}

#endif /* defined(__gfxe_GFX3DModel__) */
