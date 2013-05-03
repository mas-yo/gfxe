//
//  gfxe.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_gfxe_h__
#define __gfxe_gfxe_h__

#ifdef __IPHONE_4_0
	#include "gfx.h"
#else
	#include "../../../gfx/gfx.h"
#endif

typedef OBJ             GFX3DModelInfo;
typedef OBJMESH         GFX3DMeshInfo;
typedef OBJTRIANGLELIST GFX3DTriangleListInfo;
typedef PROGRAM         GFXShaderProgramInfo;
typedef SHADER          GFXShaderInfo;
typedef TEXTURE         GFXTexture;

#ifdef __IPHONE_4_0

inline void printlog( const char* format, ... )
{
	va_list args;
	va_start( args, format );
	printf( format, args );
	va_end( args );
}

#else

inline void printlog(const char *format, ...)
{
	va_list args;
	va_start( args, format );
    __android_log_print( ANDROID_LOG_INFO, "", format, args );
	va_end( args );
}

#endif

#endif
