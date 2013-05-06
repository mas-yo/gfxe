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
#include "glutil.h"
#include <vector>
#include <memory>
#include <string>

namespace gfxe
{
    
    template <class T>
    class GFXResourceManager : public Singleton< GFXResourceManager<T> >
    {
    private:
        struct Entry
        {
            std::string fileName;
            std::shared_ptr<T> shrObject;
        };

        std::vector< Entry > m_vecEntry;

        const Entry* FindEntry( const char* fileName )
        {
            for( Entry& e : m_vecEntry ) {
                if( e.fileName == fileName ) {
                    return &e;
                }
            }
            return NULL;
        }

    public:
        bool Load( const char* fileName, T* object );
        bool Load( const char* fileName, std::shared_ptr<GFXTexture>& shrObj )
        {
            struct GFXTextureDeleter {
                void operator()( GFXTexture* obj ) { TEXTURE_free(obj); }
            };

            Entry* find = FindEntry( fileName );
            if( find ) {
                shrObj = find->shrObject;
                return true;
            }

            GFXTexture* pTexture = TEXTURE_create( (char*)fileName, (char*)fileName, 1, TEXTURE_MIPMAP, TEXTURE_FILTER_2X, 0.0f );
            if( !pTexture ) return false;

            m_vecEntry.resize( m_vecEntry.size() + 1 );
            Entry& entry = m_vecEntry[ m_vecEntry.size() - 1 ];
            entry.fileName = fileName;
            entry.shrObject.reset( pTexture, GFXTextureDeleter() );

            shrObj = entry.shrObject;

            return true;
        }

        bool Load( const char* fileName, std::shared_ptr<GFX3DModelInfo>& shrObj )
        {
            struct GFX3DModelInfoDeleter {
                void operator()( GFX3DModelInfo* obj ) { OBJ_free( obj ); }
            };

            const Entry* find = FindEntry( fileName );
            if( find ) {
                shrObj = find->shrObject;
                return true;
            }

            GFX3DModelInfo* pInfo = OBJ_load( (char*)fileName, 1 );
            if( !pInfo ) return false;

            m_vecEntry.resize( m_vecEntry.size() + 1 );
            Entry& entry = m_vecEntry[ m_vecEntry.size() - 1 ];
            entry.fileName = fileName;
            entry.shrObject.reset( pInfo, GFX3DModelInfoDeleter() );
            
            shrObj = entry.shrObject;

            return true;
        }
    };

}
#endif /* defined(__gfxe_test__ResourceManager__) */
