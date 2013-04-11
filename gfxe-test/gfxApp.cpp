/*

Book:      	Game and Graphics Programming for iOS and Android with OpenGL(R) ES 2.0
Author:    	Romain Marucchi-Foino
ISBN-10: 	1119975913
ISBN-13: 	978-1119975915
Publisher: 	John Wiley & Sons	

Copyright (C) 2011 Romain Marucchi-Foino

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of
this software. Permission is granted to anyone who either own or purchase a copy of
the book specified above, to use this software for any purpose, including commercial
applications subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that
you wrote the original software. If you use this software in a product, an acknowledgment
in the product would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented
as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/

#include "gfxApp.h"

#include "GFX3DModel.h"
#include "GFXShaderManager.h"
#include "GFXRenderManager.h"
#include "Owner.h"
#include <iostream>

#define OBJ_FILE (char*)"PC_00.obj"
#define VERTEX_SHADER (char*)"vertex.glsl"
#define FRAGMENT_SHADER (char*)"fragment.glsl"
#define DEBUG_SHADERS 1

//OBJ* obj = NULL;
//OBJMESH* objmesh = NULL;
//PROGRAM* program = NULL;
using namespace std;
using namespace gfxe;
using namespace ragtime;

GFX3DModel* pModel;

GFXAPP gfxApp = {
    gfxAppInit,
    gfxAppDraw,
    gfxAppToucheBegan,
    gfxAppToucheMoved
};


void program_draw_callback( void *ptr )
{
    PROGRAM* curr_program = (PROGRAM*)ptr;
    unsigned int i = 0;
    while( i != curr_program->uniform_count )
    {
        if( ! strcmp( curr_program->uniform_array[i].name, "MODELVIEWPROJECTIONMATRIX" ) ) {
            glUniformMatrix4fv(curr_program->uniform_array[i].location, 1, GL_FALSE, (float*)GFX_get_modelview_projection_matrix() );

        }
        ++i;
    }
};



void gfxAppInit( int width, int height )
{
    // Setup the exit callback function.
	atexit( gfxAppExit );

	// Initialize GLES.
	GFX_start();

	// Setup a GLES viewport using the current width and height of the screen.
	glViewport( 0, 0, width, height );

    GFX_set_matrix_mode( PROJECTION_MATRIX );
    GFX_load_identity();
    GFX_set_perspective(45, (float)width/(float)height, 0.1f, 100.0f, 0.0f);

    GFXShaderManager::Create();

    GFXRenderManager::CreateInstance();

    pModel = new GFX3DModel();
    pModel->Create( OBJ_FILE );

}


void gfxAppDraw( void )
{
    glClearColor( 0.5, 0.5, 0.5, 1.0);
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	/* Insert your drawing code here */
    GFX_set_matrix_mode( MODELVIEW_MATRIX );
    GFX_load_identity();
    vec3 e = {0, -20, 10 };
    vec3 c = {0, 0, 0 };
    vec3 u = {0, 0, 1 };
    GFX_look_at(&e, &c, &u);

    GFXRenderManager::Instance()->Render();
}

void gfxAppToucheBegan( float x, float y, unsigned int tap_count )
{
	/* Insert code to execute when a new touche is detected on screen. */
}


void gfxAppToucheMoved( float x, float y, unsigned int tap_count )
{
	/* Insert code to execute when a touche move on screen. */
}


void gfxAppToucheEnded( float x, float y, unsigned int tap_count )
{
	/* Insert code to execute when a touche is removed from the screen. */
}


void gfxAppAccelerometer( float x, float y, float z )
{
	/* Insert code to execute with the accelerometer values ( when available on the system ). */
}


void gfxAppExit( void )
{
	/* Code to run when the application exit, perfect location to free everything. */
    delete pModel;
    GFXShaderManager::Clean();
}
