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

#ifndef GFXAPP_H
#define GFXAPP_H

#ifdef __IPHONE_4_0

	#include "gfx.h"
#else

	#include "../../../gfx/gfx.h"
#endif



typedef struct
{
void ( *Init			)( int width, int height );
void ( *Draw			)( void );
void ( *ToucheBegan	    )( float x, float y, unsigned int tap_count );
void ( *ToucheMoved	    )( float x, float y, unsigned int tap_count );
void ( *ToucheEnded	    )( float x, float y, unsigned int tap_count );
void ( *Accelerometer   )( float x, float y, float z );

} GFXAPP;

extern GFXAPP gfxApp;

void gfxAppInit( int width, int height );

void gfxAppDraw( void );

void gfxAppToucheBegan( float x, float y, unsigned int tap_count );

void gfxAppToucheMoved( float x, float y, unsigned int tap_count );

void gfxAppToucheEnded( float x, float y, unsigned int tap_count );

void gfxAppToucheCancelled( float x, float y, unsigned int tap_count );

void gfxAppAccelerometer( float x, float y, float z );

void gfxAppExit( void );

	#ifndef __IPHONE_4_0

		extern "C"
		{
			JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_Init( JNIEnv *env, jobject obj, jint width, jint height, jstring apkFilePath );

			JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_Draw( JNIEnv *env, jobject obj );

			JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_ToucheBegan( JNIEnv *env, jobject obj, jfloat x, jfloat y, jint tap_count );

			JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_ToucheMoved( JNIEnv *env, jobject obj, jfloat x, jfloat y, jint tap_count );

			JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_ToucheEnded( JNIEnv *env, jobject obj, jfloat x, jfloat y, jint tap_count );

			JNIEXPORT void JNICALL Java_com_android_gfxApp_gfxApp_Accelerometer( JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z );
		};

		JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_Init( JNIEnv *env, jobject obj, jint width, jint height, jstring apkFilePath )
		{
			setenv( "FILESYSTEM", env->GetStringUTFChars( apkFilePath, NULL ), 1 );

			if( gfxApp.Init ) gfxApp.Init( width, height );
		}

		JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_Draw( JNIEnv *env, jobject obj )
		{ if( gfxApp.Draw ) gfxApp.Draw(); }

		JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_ToucheBegan( JNIEnv *env, jobject obj, jfloat x, jfloat y, jint tap_count )
		{ if( gfxApp.ToucheBegan ) gfxApp.ToucheBegan( x, y, tap_count ); }

		JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_ToucheMoved( JNIEnv *env, jobject obj, jfloat x, jfloat y, jint tap_count )
		{ if( gfxApp.ToucheMoved ) gfxApp.ToucheMoved( x, y, tap_count ); }

		JNIEXPORT void JNICALL Java_com_android_gfxApp_GL2View_ToucheEnded( JNIEnv *env, jobject obj, jfloat x, jfloat y, jint tap_count )
		{ if( gfxApp.ToucheEnded ) gfxApp.ToucheEnded( x, y, tap_count ); }

		JNIEXPORT void JNICALL Java_com_android_gfxApp_gfxApp_Accelerometer( JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z )
		{ if( gfxApp.Accelerometer ) gfxApp.Accelerometer( x, y, z ); }

	#endif

#endif
