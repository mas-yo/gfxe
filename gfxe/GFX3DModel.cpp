//
//  GFX3DModel.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFX3DModel.h"
#include "gfxe.h"
#include "glutil.h"
#include "GFXShaderSimple.h"
#include "GFXResourceManager.h"
#include "stlutil.h"

using namespace gfxe;

void program_bind_attrib_location( void *ptr ) {

    PROGRAM *program = ( PROGRAM * )ptr;

    glBindAttribLocation( program->pid, 0, "POSITION"  );
    glBindAttribLocation( program->pid, 1, "NORMAL"    );
    glBindAttribLocation( program->pid, 2, "TEXCOORD0" );
}


void material_draw_callback( void *ptr ) {

    OBJMATERIAL *objmaterial = ( OBJMATERIAL * )ptr;

    PROGRAM *program = objmaterial->program;

    unsigned int i = 0;

    while( i != program->uniform_count ) {

        if( !strcmp( program->uniform_array[ i ].name, "DIFFUSE" ) ) {

            glUniform1i( program->uniform_array[ i ].location, 1 );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "MODELVIEWPROJECTIONMATRIX" ) ) {

            glUniformMatrix4fv( program->uniform_array[ i ].location,
                                1,
                                GL_FALSE,
                                ( float * )GFX_get_modelview_projection_matrix() );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "DISSOLVE" ) ) {

            glUniform1f( program->uniform_array[ i ].location, objmaterial->dissolve );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "AMBIENT_COLOR" ) ) {

            glUniform3fv( program->uniform_array[ i ].location,
                          1,
                          ( float * )&objmaterial->ambient );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "DIFFUSE_COLOR" ) ) {

            glUniform3fv( program->uniform_array[ i ].location,
                          1,
                          ( float * )&objmaterial->diffuse );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "SPECULAR_COLOR" ) ) {

            glUniform3fv( program->uniform_array[ i ].location,
                          1,
                          ( float * )&objmaterial->specular );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "SHININESS" ) ) {

            glUniform1f( program->uniform_array[ i ].location,
                         objmaterial->specular_exponent * 0.128f );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "MODELVIEWMATRIX" ) ) {

            glUniformMatrix4fv( program->uniform_array[ i ].location,
                                1,
                                GL_FALSE,
                                ( float * )GFX_get_modelview_matrix() );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "PROJECTIONMATRIX" ) ) {

            glUniformMatrix4fv( program->uniform_array[ i ].location,
                                1,
                                GL_FALSE,
                                ( float * )GFX_get_projection_matrix() );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "NORMALMATRIX" ) ) {

            glUniformMatrix3fv( program->uniform_array[ i ].location,
                                1,
                                GL_FALSE,
                                ( float * )GFX_get_normal_matrix() );
        }

        else if( !strcmp( program->uniform_array[ i ].name, "LIGHTPOSITION" ) ) {

            vec3 position    = { 0.0f, -3.0f, 10.0f };
            vec3 eyeposition = { 0.0f,  0.0f,  0.0f };

            vec3_multiply_mat4( &eyeposition,
                                &position,
                                &gfx.modelview_matrix[ gfx.modelview_matrix_index - 1 ] );

            glUniform3fv( program->uniform_array[ i ].location,
                          1,
                          ( float * )&eyeposition );
        }

        ++i;
    }
}


GFX3DModel::GFX3DModel()
{
    
}

GFX3DModel::~GFX3DModel()
{
}

void GFX3DModel::Create( const char *fileName )
{
    bool result = GFXResourceManager<GFX3DModelInfo>::Instance()->Load( fileName, m_shrModelInfo );
    if( !result ) return;

    for( int i = 0; i < m_shrModelInfo->n_objmesh; ++i ) {

        OBJ_optimize_mesh( m_shrModelInfo.get(), i, 128 );

        OBJ_build_mesh( m_shrModelInfo.get(), i );
        OBJ_free_mesh_vertex_data( m_shrModelInfo.get(), i );


        GFX3DMesh* pMesh = new GFX3DMesh( m_shrModelInfo.get(), &m_shrModelInfo->objmesh[i], i );

        m_vecMesh.resize( m_vecMesh.size() + 1 );
        m_vecMesh[ m_vecMesh.size() - 1 ].reset( pMesh );
    }

    for( int i = 0;i < m_shrModelInfo->n_texture; ++i ) {

        OBJ_build_texture( m_shrModelInfo.get(),
                           i,
                           m_shrModelInfo->texture_path,
                           TEXTURE_MIPMAP,
                           TEXTURE_FILTER_2X,
                           0.0f );
    }


    for( int i = 0; i < m_shrModelInfo->n_objmaterial; ++i ) {

        MEMORY *fragment_shader = mopen( ( char * )"fragment.glsl", 1 );

        MEMORY *vertex_shader = mopen( ( char * )"vertex.glsl", 1 );

        OBJMATERIAL *objmaterial = &m_shrModelInfo->objmaterial[ i ];

        OBJ_build_material( m_shrModelInfo.get(), i, NULL );

        if( objmaterial->dissolve == 1.0f )
            minsert( fragment_shader, ( char * )"#define SOLID_OBJECT\n", 0 );

        else if( !objmaterial->dissolve )
            minsert( fragment_shader, ( char * )"#define ALPHA_TESTED_OBJECT\n", 0 );

        else
            minsert( fragment_shader, ( char * )"#define TRANSPARENT_OBJECT\n", 0 );

        if( objmaterial->illumination_model ) {

            minsert( vertex_shader, ( char * )"#define LIGHTING_SHADER\n", 0 );
            minsert( fragment_shader, ( char * )"#define LIGHTING_SHADER\n", 0 );
        }

        objmaterial->program = PROGRAM_init( objmaterial->name );

        objmaterial->program->vertex_shader = SHADER_init( ( char * )"vertex", GL_VERTEX_SHADER );

        objmaterial->program->fragment_shader = SHADER_init( ( char * )"fragment", GL_FRAGMENT_SHADER );

        SHADER_compile( objmaterial->program->vertex_shader,
                        ( char * )vertex_shader->buffer,
                        1 );

        SHADER_compile( objmaterial->program->fragment_shader,
                        ( char * )fragment_shader->buffer,
                        1 );

        PROGRAM_set_bind_attrib_location_callback( objmaterial->program,
                                                   program_bind_attrib_location );

        PROGRAM_link( objmaterial->program, 1 );

        OBJ_set_draw_callback_material( m_shrModelInfo.get(), i, material_draw_callback );

        mclose( fragment_shader );

        mclose( vertex_shader );

    }


}
