//
//  ResourceManager.h
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/19.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#ifndef __gfxe_GFXResourceManager__
#define __gfxe_GFXResourceManager__

#include "Singleton.h"
#include "gfxe.h"
#include <vector>
#include <memory>
#include <string>

namespace gfxe
{
    
    template <class T>
    class GFXResourceManager : public ragtime::Singleton< GFXResourceManager<T> >
    {
    private:
        struct Entry
        {
            std::string fileName;
            std::shared_ptr<T> shrObject;
        };

        std::vector< Entry > m_vecEntry;

        const std::shared_ptr<T>& FindResource( const char* fileName );

    public:
        bool Load( const char* fileName, T* object );
        bool Load( const char* fileName, std::shared_ptr<GFXTexture>& object )
        {
            struct GFXTextureDeleter {
                void operator()( GFXTexture* obj ) { TEXTURE_free(obj); }
            };

            GFXTexture* pTexture = TEXTURE_create( (char*)fileName, (char*)fileName, 1, TEXTURE_MIPMAP, TEXTURE_FILTER_2X, 0.0f );
            if( !pTexture ) return false;

            m_vecEntry.resize( m_vecEntry.size() + 1 );
            Entry& entry = m_vecEntry[ m_vecEntry.size() - 1 ];
            entry.fileName = fileName;
            entry.shrObject.reset( pTexture );
            
            return true;
        }
    };

}
#endif /* defined(__gfxe_test__ResourceManager__) */
