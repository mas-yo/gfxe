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
#include "GFXRenderManager.h"
#include "GFXCamera.h"
#include "GFXResourceManager.h"
#include "GFXPhysicWorld.h"
#include <iostream>

#define VERTEX_SHADER (char*)"vertex.glsl"
#define FRAGMENT_SHADER (char*)"fragment.glsl"
#define DEBUG_SHADERS 1

using namespace std;
using namespace gfxe;

GFX3DModel* pModel;
GFX3DModel* pModel2;

GFXAPP gfxApp = {
    gfxAppInit,
    gfxAppDraw,
    gfxAppToucheBegan,
    gfxAppToucheMoved
};



void gfxAppInit( int width, int height )
{
	atexit( gfxAppExit );

	GFX_start();

	glViewport( 0.0f, 0.0f, width, height );

	GFX_set_matrix_mode( PROJECTION_MATRIX );
	GFX_load_identity();
	
	GFX_set_perspective( 45.0f,
						 ( float )width / ( float )height,
						 0.1f,
						 100.0f,
						 -90.0f );

    GFXRenderManager::CreateInstance();
    GFXCamera::CreateInstance();
    GFXResourceManager<GFX3DModelInfo>::CreateInstance();
    GFXPhysicWorld::CreateInstance();
    GFXPhysicWorld::Instance()->Initialize();
    

    pModel = new GFX3DModel();
    pModel->Create( "scene.obj" );
    pModel2 = new GFX3DModel();
    pModel2->Create( "ram.obj" );
    
    GFXCamera::Instance()->SetPosition( vec3( {0,-6,1.35} ) );
    GFXCamera::Instance()->SetRotation( vec3({0,0,0}) );
    GFXCamera::Instance()->MoveRotation( 90, 0, 0);
//    GFXCamera::Instance()->SetTarget( vec3({0,-5,1.35}) );
//    GFXCamera::Instance()->SetTarget( vec3({0,0,0}) );
//    GFXCamera::Instance()->SetUp( vec3({0,0,1}) );
    
}


void gfxAppDraw( void )
{
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    GFXRenderManager::Instance()->Render();
    
    GFXPhysicWorld::Instance()->Update();
}

void gfxAppToucheBegan( float x, float y, unsigned int tap_count )
{
	/* Insert code to execute when a new touche is detected on screen. */
	
	float mx = 0;
	float my = 0;
	if( x < 300 ) mx = -10; else mx = 10;
	if( y < 300 ) my = -0.2f; else my = 0.2f;
	
	GFXCamera::Instance()->MoveRotation( mx, 0, 0 );
	
	const vec3& pos = GFXCamera::Instance()->GetPosition();
	const vec3& tgt = GFXCamera::Instance()->GetTarget();
	const vec3& rot = GFXCamera::Instance()->GetRotation();
	
	console_print("pos:%f %f %f", pos.x, pos.y, pos.z );
//	console_print("tgt:%f %f %f", tgt.x, tgt.y, tgt.z );
	console_print("rot:%f %f %f", rot.x, rot.y, rot.z );
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
    delete pModel2;
}
