//
//  GFXShaderManager.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_test__GFXShaderManager__
#define __gfxe_test__GFXShaderManager__

#include "GFXShaderSimple.h"

namespace gfxe {

    class GFXShaderManager
    {
    public:
        static GFXShaderSimple* s_shaderSimple;

        static void Create();
        static void Clean();
    };
}

#endif /* defined(__gfxe_test__GFXShaderManager__) */
