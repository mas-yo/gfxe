//
//  GFXRenderManager.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXRenderManager.h"
#include <algorithm>

using namespace std;
using namespace gfxe;

void GFXRenderManager::AddRenderable( IRenderable* pRenderable )
{
//    lock_guard< std::mutex > lock( m_mutex );

    if( std::find( m_vecRenderable.begin(), m_vecRenderable.end(), pRenderable ) == m_vecRenderable.end() ) {
        m_vecRenderable.push_back( pRenderable );
    }
}

void GFXRenderManager::RemoveRenderable( IRenderable* pRenderable )
{
//    lock_guard< std::mutex > lock( m_mutex );

    auto it = std::find( m_vecRenderable.begin(), m_vecRenderable.end(), pRenderable );
    if( it != m_vecRenderable.end() ) {
        (*it) = nullptr;
    }
}

void GFXRenderManager::Render()
{
    for_each( m_vecRenderable.begin(), m_vecRenderable.end(), []( IRenderable* p ) { p->Render(); } );
}
