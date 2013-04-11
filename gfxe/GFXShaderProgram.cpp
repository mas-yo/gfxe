//
//  GFXShaderProgram.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXShaderProgram.h"

using namespace gfxe;


//GFXShaderProgram::s_DrawCallBack( void *ptr )
//{
//    GFXShaderProgram::s_pThis->DrawCallBack();
//}

GFXShaderProgram::GFXShaderProgram() : m_unqShaderProgramInfo()
{

}

GFXShaderProgram::~GFXShaderProgram()
{
}

void GFXShaderProgram::Create( const char* shaderName, const char* vertexShaderFileName, const char* fragmentShaderFileName, PROGRAMDRAWCALLBACK *drawCallBack )
{
    GFXShaderProgramInfo* pInfo = PROGRAM_create( (char*)shaderName,
                             (char*)vertexShaderFileName,
                             (char*)fragmentShaderFileName,
                             1,
                                SHADER_DEBUG,
                             NULL,
                                drawCallBack );

    m_unqShaderProgramInfo.reset( pInfo );
//    , []( GFXShaderProgramInfo* obj ) {
//        obj->vertex_shader = SHADER_free( obj->vertex_shader );
//        obj->fragment_shader = SHADER_free( obj->fragment_shader );
//        obj = PROGRAM_free( obj );
//    } );

}

