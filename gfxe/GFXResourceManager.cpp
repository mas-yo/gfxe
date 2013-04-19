//
//  ResourceManager.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/19.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXResourceManager.h"

using namespace std;
using namespace gfxe;

//bool GFXResourceManager::Load( const char* fileName, std::shared_ptr<GFXTexture>& object )
//{
//    struct GFXTextureDeleter {
//        void operator()( GFXTexture* obj ) { TEXTURE_free(obj); }
//    };
//
//    GFXTexture* pTexture = TEXTURE_create( (char*)fileName, (char*)fileName, 1, TEXTURE_MIPMAP, TEXTURE_FILTER_2X, 0.0f );
//
//    m_vecEntry.resize( m_vecEntry.size() + 1 );
//    Entry& entry = m_vecEntry[ m_vecEntry.size() - 1 ];
//    entry.fileName = fileName;
//    entry.shrObject.reset( pTexture );
//
//    return true;
//}
