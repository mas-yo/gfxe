//
//  GFXShaderProgram.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFXShaderProgram__
#define __gfxe_GFXShaderProgram__

#include "gfxe.h"
#include "Owner.h"

#define SHADER_DEBUG 1

namespace gfxe {

    class GFXShaderProgram
    {
    protected:
        ragtime::own<GFXShaderProgramInfo> m_ownShaderProgramInfo;

    public:
        GFXShaderProgram();
        virtual ~GFXShaderProgram();

        virtual void Create( const char* shaderName, const char* vertexShaderFileName, const char* fragmentShaderFileName, PROGRAMDRAWCALLBACK *drawCallBack );

        GFXShaderProgramInfo* GetProgram() { return static_cast<GFXShaderProgramInfo*>( m_ownShaderProgramInfo ); }
    };

}
#endif /* defined(__gfxe_test__GFXShaderProgram__) */
