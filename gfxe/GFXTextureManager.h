//
//  GFXTextureManager.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/17.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_test__GFXTextureManager__
#define __gfxe_test__GFXTextureManager__

#include "gfxe.h"
#include "Singleton.h"
#include <vector>
#include <memory>
#include <utility>

namespace gfxe {

    class GFXTextureManager : public ragtime::Singleton<GFXTextureManager>
    {
        struct GFXTextureDeleter {
            void operator()( GFXTexture* obj ) { TEXTURE_free(obj); }
        };
        std::vector< std::shared_ptr<GFXTexture> > m_vecTexture;

        const std::shared_ptr<GFXTexture>& FindTexture( const char* fileName );

    public:
        std::shared_ptr<GFXTexture> LoadTexture( const char* fileName );
    };

}

#endif /* defined(__gfxe_test__GFXTextureManager__) */
