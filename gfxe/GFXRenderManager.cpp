//
//  GFXRenderManager.cpp
//  gfxe-test
//
//  Created by YOSHIDA MASAHIRO on 13/04/09.
//  Copyright (c) 2013年 ROm. All rights reserved.
//

#include "GFXRenderManager.h"
#include "gfxe.h"
#include "GFXCamera.h"
#include <algorithm>

using namespace std;
using namespace gfxe;

//void GFXRenderer::AddRenderable( IRenderable* pRenderable )
//{
//    lock_guard< std::mutex > lock( m_mutex );
//
//    if( std::find( m_vecRenderable.begin(), m_vecRenderable.end(), pRenderable ) == m_vecRenderable.end() ) {
//        m_vecRenderable.push_back( pRenderable );
//    }
//}

GFXRenderer::~GFXRenderer()
{
    for( auto it = m_vecRenderFunc.begin(); it != m_vecRenderFunc.end(); ++it ) {
        delete *it;
    }
}

void GFXRenderer::RemoveRenderFunc( void* pTarget )
{
    for( auto it = m_vecRenderFunc.begin(); it != m_vecRenderFunc.end(); ++it ) {
        if( (*it)->GetTarget() == pTarget ) {
            delete *it;
            m_vecRenderFunc.erase( it );
            break;
        }
    }
}

void GFXRenderer::Render()
{
    for( auto it = m_vecRenderFunc.begin(); it != m_vecRenderFunc.end(); ++it ) {
        (*it)->CallFunc();
    }
//    for_each( m_vecRenderFunc.begin(), m_vecRenderFunc.end(), []( std::unique_ptr<GFXRenderer::RenderFuncBase> p ) { p->CallFunc(); } );
}

void GFXRenderManager::RemoveRenderFunc( void* pTarget )
{
    for( GFXRenderer& renderer : m_arrRenderer ) {
        renderer.RemoveRenderFunc( pTarget );
    }
}

void GFXRenderManager::Render()
{
    m_arrRenderer[ RenderGroup_Solid ].Render();

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_arrRenderer[ RenderGroup_Alpha ].Render();

}
