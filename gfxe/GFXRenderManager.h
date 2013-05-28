//
//  GFXRenderManager.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFXRenderManager__
#define __gfxe_GFXRenderManager__

#include "Singleton.h"
#include "TargetFunction.h"
#include <vector>
#include <mutex>
#include <memory>
#include <functional>
#include <tuple>

namespace gfxe {

    enum RenderGroup
    {
        RenderGroup_Solid,
        RenderGroup_Alpha,
        RenderGroup_End
    };

    class GFXRenderer
    {
    private:
        struct ObjFunc {
            void* _obj;
            std::function<void()> _func;
        };

    private:
        std::vector< ObjFunc > _functions;


    public:
        virtual ~GFXRenderer();

        void addFunc( void* obj, std::function<void()> func );
        void removeFunc( void* obj );
        void render();
    };

    class GFXRenderManager : public Singleton<GFXRenderManager>
    {
    private:
        GFXRenderer _renderers[ RenderGroup_End ];

    public:
        void addFunc( void* obj, std::function<void()> func, int renderGroup );
        void removeFunc( void* );
        void render();

    };


}

#endif /* defined(__gfxe_test__GFXRenderManager__) */
