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

typedef OBJ         GFX3DModelInfo;
typedef OBJMESH     GFX3DMeshInfo;
typedef PROGRAM     GFXShaderProgramInfo;
typedef SHADER      GFXShaderInfo;


#endif
