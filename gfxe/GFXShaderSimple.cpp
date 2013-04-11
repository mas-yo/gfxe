//
//  GFXShaderSimple.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXShaderSimple.h"

using namespace gfxe;

GFXShaderSimple::GFXShaderSimple()
{
//    s_pThis = this;
}

void GFXShaderSimple::s_DrawCallBack( void *ptr )
{
    PROGRAM *curr_program = (PROGRAM*)ptr;

	unsigned int i = 0;

	while( i != curr_program->uniform_count ) {

		if( !strcmp( curr_program->uniform_array[ i ].name, "MODELVIEWPROJECTIONMATRIX" ) ) {

			glUniformMatrix4fv( curr_program->uniform_array[ i ].location,
                               1,
                               GL_FALSE,
                               ( float * )GFX_get_modelview_projection_matrix() );
		}
        
        
		++i;
	}

}

void GFXShaderSimple::Create()
{
    GFXShaderProgram::Create("default", "vertex.glsl", "fragment.glsl", GFXShaderSimple::s_DrawCallBack );
}
