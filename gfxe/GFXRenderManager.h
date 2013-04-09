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
#include "IRenderable.h"
#include <vector>
#include <mutex>

namespace gfxe {

    class GFXRenderManager : public ragtime::Singleton<GFXRenderManager>
    {
    private:
        std::mutex m_mutex;
        std::vector< gfxe::IRenderable* > m_vecRenderable;

    public:
        void AddRenderable( gfxe::IRenderable* pRenderable );
        void RemoveRenderable( gfxe::IRenderable* pRenderable );
        void Render();

    };


}

#endif /* defined(__gfxe_test__GFXRenderManager__) */
