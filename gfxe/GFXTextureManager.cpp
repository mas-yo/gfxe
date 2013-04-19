//
//  GFXTextureManager.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/17.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXTextureManager.h"

using namespace std;
using namespace gfxe;

shared_ptr<GFXTexture> GFXTextureManager::LoadTexture( const char* fileName )
{
    GFXTexture* pTexture = TEXTURE_create( (char*)fileName, (char*)fileName, 1, TEXTURE_MIPMAP, TEXTURE_FILTER_2X, 0.0f );

    m_vecTexture.resize( m_vecTexture.size() + 1 );
    auto tex = m_vecTexture[ m_vecTexture.size() - 1 ];
    tex.reset( pTexture, GFXTextureDeleter() );

    return tex;
}

const std::shared_ptr<GFXTexture>& GFXTextureManager::FindTexture( const char* fileName )
{
    for( shared_ptr<GFXTexture>& tex : m_vecTexture ) {
        if( !strcmp( tex->name, fileName ) ) return tex;
    }
    return nullptr;
}
