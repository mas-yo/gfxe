//
//  glutil.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "glutil.h"
#include "gfx.h"

using namespace gfxe;

void gfxe::create_vbo( OBJ* obj )
{
    OBJMESH* objmesh = obj->objmesh;

    for( int meshIdx = 0; meshIdx < obj->n_objmesh; ++meshIdx, ++objmesh ) {

        unsigned char *vertex_array = NULL;
        unsigned char *vertex_start = NULL;

        unsigned int index  = 0;
        //    unsigned int stride = 0;
        unsigned int size   = 0;

        size = objmesh->n_objvertexdata * sizeof( vec3 ) * sizeof( vec3 );
        vertex_array = ( unsigned char * ) malloc( size );
        vertex_start = vertex_array;

        OBJVERTEXDATA* vertexData = objmesh->objvertexdata;
        for( int i = 0; i < objmesh->n_objvertexdata; ++i, ++vertexData ) {

            index = vertexData->vertex_index;
            memcpy( vertex_array, &obj->indexed_vertex[ index ], sizeof( vec3 ) );
            vertex_array += sizeof( vec3 );

            memcpy( vertex_array, &obj->indexed_normal[ index ], sizeof( vec3 ) );
            vertex_array += sizeof( vec3 );

        }

        glGenBuffers( 1, &objmesh->vbo );
        glBindBuffer( GL_ARRAY_BUFFER, objmesh->vbo );

        glBufferData( GL_ARRAY_BUFFER,
                     size,
                     vertex_start,
                     GL_STATIC_DRAW );

        free( vertex_start );

        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        OBJTRIANGLELIST* triangle = objmesh->objtrianglelist;
        for( int i = 0; i < objmesh->n_objtrianglelist; ++i, ++triangle ) {

            glGenBuffers( 1, &triangle->vbo );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, triangle->vbo );

            glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                         triangle->n_indice_array *
                         sizeof( unsigned short ),
                         triangle->indice_array,
                         GL_STATIC_DRAW );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

        }


    }

}

void gfxe::create_vao( OBJMESH* objmesh, PROGRAM* program)
{

    unsigned int stride = 0;

	unsigned char attribute;
    stride = sizeof( vec3 ) + sizeof( vec3 );

	glGenVertexArraysOES( 1, &objmesh->vao );

	glBindVertexArrayOES( objmesh->vao );


	glBindBuffer( GL_ARRAY_BUFFER, objmesh->vbo );

	attribute = PROGRAM_get_vertex_attrib_location( program, ( char * )"POSITION" );

	glEnableVertexAttribArray( attribute );

	glVertexAttribPointer( attribute,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          ( void * )NULL );

	attribute = PROGRAM_get_vertex_attrib_location( program, ( char * )"NORMAL" );

	glEnableVertexAttribArray( attribute );

	glVertexAttribPointer( attribute,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          BUFFER_OFFSET( sizeof( vec3 ) ) );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER,
                 objmesh->objtrianglelist[ 0 ].vbo );
    //TODO これだけで良い？

	glBindVertexArrayOES( 0 );

}