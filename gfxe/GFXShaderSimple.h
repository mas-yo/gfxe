//
//  GFXShaderSimple.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/05.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFXShaderSimple__
#define __gfxe_GFXShaderSimple__

#include "GFXShaderProgram.h"

namespace gfxe {

    class GFXShaderSimple : public GFXShaderProgram
    {
    private:
        virtual void SetUniformVariable() override;

    public:
        GFXShaderSimple();
        void Create();
        
    };


}


#endif /* defined(__gfxe_test__GFXShaderSimple__) */
