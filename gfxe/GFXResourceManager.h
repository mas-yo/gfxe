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
            std::string _fileName;
            std::shared_ptr<T> _object;
        };

        std::vector< Entry > _entryList;

        const Entry* findEntry( const char* fileName )
        {
            for( Entry& e : _entryList ) {
                if( e._fileName == fileName ) {
                    return &e;
                }
            }
            return NULL;
        }

    public:
        bool load( const char* fileName, T* object );
        bool load( const char* fileName, std::shared_ptr<GFXTexture>& shrObj )
        {
            struct GFXTextureDeleter {
                void operator()( GFXTexture* obj ) { TEXTURE_free(obj); }
            };

            Entry* find = findEntry( fileName );
            if( find ) {
                shrObj = find->shrObject;
                return true;
            }

            GFXTexture* pTexture = TEXTURE_create( (char*)fileName, (char*)fileName, 1, TEXTURE_MIPMAP, TEXTURE_FILTER_2X, 0.0f );
            if( !pTexture ) return false;

            _entryList.resize( _entryList.size() + 1 );
            Entry& entry = _entryList[ _entryList.size() - 1 ];
            entry._fileName = fileName;
            entry._object.reset( pTexture, GFXTextureDeleter() );

            shrObj = entry._object;

            return true;
        }

        bool load( const char* fileName, std::shared_ptr<GFX3DModelInfo>& shrObj )
        {
            struct GFX3DModelInfoDeleter {
                void operator()( GFX3DModelInfo* obj ) { OBJ_free( obj ); }
            };

            const Entry* find = findEntry( fileName );
            if( find ) {
                shrObj = find->_object;
                return true;
            }

            GFX3DModelInfo* pInfo = OBJ_load( (char*)fileName, 1 );
            if( !pInfo ) return false;

            _entryList.resize( _entryList.size() + 1 );
            Entry& entry = _entryList[ _entryList.size() - 1 ];
            entry._fileName = fileName;
            entry._object.reset( pInfo, GFX3DModelInfoDeleter() );
            
            shrObj = entry._object;

            return true;
        }
    };

}
#endif /* defined(__gfxe_test__ResourceManager__) */
