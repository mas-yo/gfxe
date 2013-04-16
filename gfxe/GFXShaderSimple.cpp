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
}

void GFXShaderSimple::SetUniformVariable()
{
	PROGRAM *curr_program = m_unqShaderProgramInfo.get();
	glUseProgram( curr_program->pid );

	unsigned int i = 0;

	while( i != curr_program->uniform_count ) {

		if( !strcmp( curr_program->uniform_array[ i ].name, "MODELVIEWMATRIX" ) ) {

			glUniformMatrix4fv( curr_program->uniform_array[ i ].location,
                               1,
                               GL_FALSE,
                               ( float * )GFX_get_modelview_matrix() ); }

		else if( !strcmp( curr_program->uniform_array[ i ].name, "PROJECTIONMATRIX" ) ) {

			glUniformMatrix4fv( curr_program->uniform_array[ i ].location,
                               1,
                               GL_FALSE,
                               ( float * )GFX_get_projection_matrix() ); }

		else if( !strcmp( curr_program->uniform_array[ i ].name, "NORMALMATRIX" ) ) {

			glUniformMatrix3fv( curr_program->uniform_array[ i ].location,
                               1,
                               GL_FALSE,
                               ( float * )GFX_get_normal_matrix() ); }

		else if( !strcmp( curr_program->uniform_array[ i ].name, "LIGHTPOSITION" ) ) {

			// In eye space, far is Z
			vec3 l = { 0.0f, 0.0f, 0.0f };

			glUniform3fv( curr_program->uniform_array[ i ].location,
                         1,
                         ( float * )&l ); }
        
		++i;
	}
}

void GFXShaderSimple::Create()
{
    GFXShaderProgram::Create("default", "vertex.glsl", "fragment.glsl" );
}
