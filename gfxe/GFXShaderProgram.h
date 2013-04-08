//
//  GFXShaderProgram.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFXShaderProgram__
#define __gfxe_GFXShaderProgram__

#include "gfx.h"

#define SHADER_DEBUG 1

namespace gfxe {

    class GFXShaderProgram
    {
    protected:
        PROGRAM* m_pProgram;

    public:
        GFXShaderProgram();
        virtual ~GFXShaderProgram();

        virtual void Create( const char* shaderName, const char* vertexShaderFileName, const char* fragmentShaderFileName, PROGRAMDRAWCALLBACK *drawCallBack );

        PROGRAM* GetProgram() { return m_pProgram; }
    };

}
#endif /* defined(__gfxe_test__GFXShaderProgram__) */
