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
#include <memory>

#define SHADER_DEBUG 1

namespace gfxe {

    class GFXShaderProgram
    {
    protected:
        struct GFXShaderProgramDeleter
        {
            void operator()( GFXShaderProgramInfo* info ) { PROGRAM_free( info ); }
        };

//        ragtime::own<GFXShaderProgramInfo> m_ownShaderProgramInfo;
        std::unique_ptr<GFXShaderProgramInfo, GFXShaderProgramDeleter> m_unqShaderProgramInfo;

    public:
        GFXShaderProgram();
        virtual ~GFXShaderProgram();

        virtual void Create( const char* shaderName, const char* vertexShaderFileName, const char* fragmentShaderFileName );
        virtual void SetUniformVariable() = 0;

        GFXShaderProgramInfo* GetProgram() { return m_unqShaderProgramInfo.get(); }
    };

}
#endif /* defined(__gfxe_test__GFXShaderProgram__) */
