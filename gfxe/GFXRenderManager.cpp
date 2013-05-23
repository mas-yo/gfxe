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
    for( auto it = _targetFuncList.begin(); it != _targetFuncList.end(); ++it ) {
        delete *it;
    }
}

void GFXRenderer::render()
{
    for( auto it = _targetFuncList.begin(); it != _targetFuncList.end(); ++it ) {
        (*it)->call();
    }
//    for_each( m_vecRenderFunc.begin(), m_vecRenderFunc.end(), []( std::unique_ptr<GFXRenderer::RenderFuncBase> p ) { p->CallFunc(); } );
}

void GFXRenderManager::render()
{
    _renderers[ RenderGroup_Solid ].render();

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    _renderers[ RenderGroup_Alpha ].render();

}
