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

namespace gfxe {

    enum RenderGroup
    {
        RenderGroup_Solid,
        RenderGroup_Alpha,
        RenderGroup_End
    };

    class GFXRenderer
    {
    public:
        typedef ITargetFunction<void> render_target_func_t;

    private:
        std::mutex m_mutex;
        std::vector< render_target_func_t* > _targetFuncList;

    public:
        virtual ~GFXRenderer();

        void addTargetFunc( render_target_func_t* targetFunc )
        {
            _targetFuncList.push_back( targetFunc );
        }

        template <class T>
        void removeTarget( T* pTarget ) {
            for( auto it = _targetFuncList.begin(); it != _targetFuncList.end(); ++it ) {
                auto tgt = dynamic_cast<TargetFunction<T, void>*>(*it);
                if( tgt->getTarget() == pTarget ) {
                    delete tgt;
                    _targetFuncList.erase( it );
                    break;
                }
            }
        }
        void render();
    };

    class GFXRenderManager : public Singleton<GFXRenderManager>
    {
    private:
        GFXRenderer _renderers[ RenderGroup_End ];

    public:
        void addTargetFunc( GFXRenderer::render_target_func_t* targetFunc, int renderGroup ) {
            _renderers[ renderGroup ].addTargetFunc( targetFunc );
        }

        template <class T>
        void removeTarget( T* pTarget )
        {
            for( GFXRenderer& renderer : _renderers ) {
                renderer.removeTarget( pTarget );
            }
        }
        
        void render();

    };


}

#endif /* defined(__gfxe_test__GFXRenderManager__) */
