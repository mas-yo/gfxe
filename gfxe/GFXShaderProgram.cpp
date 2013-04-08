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

GFXShaderProgram::GFXShaderProgram() : m_pProgram(NULL)
{

}

GFXShaderProgram::~GFXShaderProgram()
{
    if( m_pProgram ) {
        m_pProgram->vertex_shader = SHADER_free( m_pProgram->vertex_shader );
        m_pProgram->fragment_shader = SHADER_free( m_pProgram->fragment_shader );
        m_pProgram = PROGRAM_free( m_pProgram );
    }
}

void GFXShaderProgram::Create( const char* shaderName, const char* vertexShaderFileName, const char* fragmentShaderFileName, PROGRAMDRAWCALLBACK *drawCallBack )
{
    m_pProgram = PROGRAM_create( (char*)shaderName,
                             (char*)vertexShaderFileName,
                             (char*)fragmentShaderFileName,
                             1,
                                SHADER_DEBUG,
                             NULL,
                                drawCallBack );

}

